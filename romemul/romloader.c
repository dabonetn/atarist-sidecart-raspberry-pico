/**
 * File: romloader.c
 * Author: Diego Parrilla Santamaría
 * Date: August 2023
 * Copyright: 2023 - GOODDATA LABS SL
 * Description: Load ROM files from SD card
 */

#include "include/romloader.h"

// Synchronous command variables
static uint16_t *payloadPtr = NULL;
static uint32_t random_token;

// Microsd variables
bool microsd_initialized = false;
bool microsd_mounted = false;
bool microsd_status = false;

// Filtered files list variables
int filtered_num_local_files = 0;
char **filtered_local_list = NULL;

// ROMs in sd card variables
static int list_roms = false;
static int rom_file_selected = -1;

// Floppy images in sd card variables
static bool list_floppies = false;
static int floppy_file_selected = -1;
static bool floppy_read_write = true;

// Query floppy database variables
static bool query_floppy_db = false;
static char query_floppy_letter = 'a';
static FloppyImageInfo *floppy_images_files = NULL;
static int filtered_num_floppy_images_files = 0;
static int floppy_image_selected = -1;
static int floppy_image_selected_status = 0;

// Network variables
static RomInfo *network_files;
static int filtered_num_network_files = 0;

WifiNetworkAuthInfo *wifi_auth = NULL; // IF NULL, do not connect to any network
static bool persist_config = false;
static bool reset_default = false;
static bool scan_network = false;
static bool disconnect_network = false;
static bool get_json_file = false;

// ROMs in network variables
static int rom_network_selected = -1;

#include "ff.h"

void get_card_info(FATFS *fs_ptr, uint32_t *totalSize_MB, uint32_t *freeSpace_MB)
{
    DWORD fre_clust;

    // Set initial values to zero as a precaution
    *totalSize_MB = 0;
    *freeSpace_MB = 0;

    // Get volume information and free clusters of drive
    if (f_getfree("", &fre_clust, &fs_ptr) != FR_OK)
    {
        return; // Error handling: Set values to zero if getfree fails
    }

    // Calculate total sectors in the SD card
    uint64_t total_sectors = (fs_ptr->n_fatent - 2) * fs_ptr->csize;

    // Convert total sectors to bytes and then to megabytes
    *totalSize_MB = (total_sectors * 512) / 1048576;

    // Convert free clusters to sectors and then to bytes
    uint64_t free_space_bytes = (uint64_t)fre_clust * fs_ptr->csize * 512;

    // Convert bytes to megabytes
    *freeSpace_MB = free_space_bytes / 1048576;
}

static uint32_t calculate_folder_count(const char *path)
{
    FRESULT res;
    DIR dir;
    FILINFO fno;
    uint32_t totalSize = 0;
    char newPath[256]; // Buffer to hold sub-directory paths

    res = f_opendir(&dir, path); // Open the directory
    if (res != FR_OK)
    {
        return 0; // Error, return 0
    }

    while (1)
    {
        res = f_readdir(&dir, &fno); // Read a directory item
        if (res != FR_OK || fno.fname[0] == 0)
        {
            break; // Error or end of dir, exit
        }

        if (fno.fattrib & AM_DIR)
        { // It's a directory
            sprintf(newPath, "%s/%s", path, fno.fname);
            totalSize += calculate_folder_count(newPath); // Recursive call
        }
        else
        { // It's a file
            totalSize += 1;
        }
    }

    f_closedir(&dir);
    return totalSize;
}

/**
 * @brief Checks if a directory exists in the filesystem.
 *
 * This function uses the FatFS library's f_stat() method to determine if
 * a specified directory exists on the filesystem. It returns 1 if the directory
 * exists and 0 otherwise.
 *
 * @param dir A pointer to a string containing the path of the directory to check.
 * @return int Returns 1 if the directory exists, 0 otherwise.
 */
static int directory_exists(const char *dir)
{
    FILINFO fno;
    FRESULT res = f_stat(dir, &fno);

    // Check if the result is OK and if the attribute indicates it's a directory
    if (res == FR_OK && (fno.fattrib & AM_DIR))
    {
        return 1; // Directory exists
    }

    return 0; // Directory does not exist
}

static void get_sdcard_data(FATFS *fs, SdCardData *sd_data)
{

    sd_data->status = microsd_mounted ? SD_CARD_MOUNTED : SD_CARD_NOT_MOUNTED; // SD card status
    strncpy(sd_data->floppies_folder, find_entry("FLOPPIES_FOLDER")->value, MAX_FOLDER_LENGTH - 1);
    sd_data->floppies_folder[MAX_FOLDER_LENGTH - 1] = '\0'; // Ensure null termination

    strncpy(sd_data->roms_folder, find_entry("ROMS_FOLDER")->value, MAX_FOLDER_LENGTH - 1);
    sd_data->roms_folder[MAX_FOLDER_LENGTH - 1] = '\0'; // Ensure null termination

    // strncpy(sd_data->harddisks_folder, find_entry("HARDDISKS_FOLDER")->value, MAX_FOLDER_LENGTH - 1);
    // sd_data->harddisks_folder[MAX_FOLDER_LENGTH - 1] = '\0'; // Ensure null termination

    if (microsd_mounted)
    {
        sd_data->floppies_folder_status = directory_exists(sd_data->floppies_folder) ? FLOPPIES_FOLDER_OK : FLOPPIES_FOLDER_NOTFOUND;
        sd_data->roms_folder_status = directory_exists(sd_data->roms_folder) ? ROMS_FOLDER_OK : ROMS_FOLDER_NOTFOUND;
        // sd_data->harddisks_folder_status = directory_exists(sd_data->harddisks_folder) ? HARDDISKS_FOLDER_OK : HARDDISKS_FOLDER_NOTFOUND;

        uint32_t total, freeSpace;
        get_card_info(fs, &total, &freeSpace);

        sd_data->sd_size = total;
        sd_data->sd_free_space = freeSpace;

        sd_data->roms_folder_count = calculate_folder_count(sd_data->roms_folder);
        sd_data->floppies_folder_count = calculate_folder_count(sd_data->floppies_folder);
        // sd_data->harddisks_folder_count = calculate_folder_count(sd_data->harddisks_folder);
    }
    else
    {
        sd_data->floppies_folder_status = FLOPPIES_FOLDER_NOTFOUND;
        sd_data->roms_folder_status = ROMS_FOLDER_NOTFOUND;
        // sd_data->harddisks_folder_status = HARDDISKS_FOLDER_NOTFOUND;
        sd_data->sd_size = 0;
        sd_data->sd_free_space = 0;
        sd_data->roms_folder_count = 0;
        sd_data->floppies_folder_count = 0;
        // sd_data->harddisks_folder_count = 0;
    }
    DPRINTF("SD card status: %d\n", sd_data->status);
    DPRINTF("SD card size: %d MB\n", sd_data->sd_size);
    DPRINTF("SD card free space: %d MB\n", sd_data->sd_free_space);
    DPRINTF("Floppies folder: %s\n", sd_data->floppies_folder);
    DPRINTF("Floppies folder status: %d\n", sd_data->floppies_folder_status);
    DPRINTF("Floppies folder size: %d\n", sd_data->floppies_folder_count);
    DPRINTF("ROMs folder: %s\n", sd_data->roms_folder);
    DPRINTF("ROMs folder status: %d\n", sd_data->roms_folder_status);
    DPRINTF("ROMs folder size: %d\n", sd_data->roms_folder_count);
    // DPRINTF("Hard disks folder: %s\n", sd_data->harddisks_folder);
    // DPRINTF("Hard disks folder status: %d\n", sd_data->harddisks_folder_status);
    // DPRINTF("Hard disks folder size: %d MB\n", sd_data->harddisks_folder_count/ (1024 * 1024));
}

/**
 * @brief Copies a file within the same folder to a new file with a specified name.
 *
 * This function reads a specified file from a specified folder, and creates a new file
 * with a specified name in the same folder, copying the contents of the original file
 * to the new file. If a file with the specified new name already exists, the behavior
 * depends on the value of the overwrite_flag argument: if true, the existing file is
 * overwritten; if false, the function returns an error code and the operation is canceled.
 *
 * @param folder The path of the folder containing the source file, as a null-terminated string.
 * @param src_filename The name of the source file, as a null-terminated string.
 * @param dest_filename The name for the new file, as a null-terminated string.
 * @param overwrite_flag A flag indicating whether to overwrite the destination file
 *        if it already exists: true to overwrite, false to cancel the operation.
 *
 * @return A result code of type FRESULT, indicating the result of the operation:
 *         - FR_OK on success.
 *         - FR_FILE_EXISTS if the destination file exists and overwrite_flag is false.
 *         - Other FatFS error codes for other error conditions.
 *
 * @note This function uses the FatFS library to perform file operations, and is designed
 *       to work in environments where FatFS is available. It requires the ff.h header file.
 *
 * Usage:
 * @code
 * FRESULT result = copy_file("/folder", "source.txt", "destination.txt", true);  // Overwrite if destination.txt exists
 * @endcode
 */
static FRESULT copy_file(const char *folder, const char *src_filename, const char *dest_filename, bool overwrite_flag)
{
    FRESULT fr;   // FatFS function common result code
    FIL src_file; // File objects
    FIL dest_file;
    UINT br, bw;       // File read/write count
    BYTE buffer[4096]; // File copy buffer

    char src_path[256];
    char dest_path[256];

    // Create full paths for source and destination files
    sprintf(src_path, "%s/%s", folder, src_filename);
    sprintf(dest_path, "%s/%s", folder, dest_filename);

    DPRINTF("Copying file '%s' to '%s'. Overwrite? %s\n", src_path, dest_path, overwrite_flag ? "YES" : "NO");

    // Check if the destination file already exists
    FILINFO fno;
    fr = f_stat(dest_path, &fno);
    if (fr == FR_OK && !overwrite_flag)
    {
        DPRINTF("Destination file exists and overwrite_flag is false, canceling operation\n");
        return FR_FILE_EXISTS; // Destination file exists and overwrite_flag is false, cancel the operation
    }

    // Open the source file
    fr = f_open(&src_file, src_path, FA_READ);
    if (fr != FR_OK)
    {
        DPRINTF("f_open error: %s (%d)\n", FRESULT_str(fr), fr);
        return fr;
    }

    // Create and open the destination file
    fr = f_open(&dest_file, dest_path, FA_CREATE_ALWAYS | FA_WRITE);
    if (fr != FR_OK)
    {
        DPRINTF("f_open error: %s (%d)\n", FRESULT_str(fr), fr);
        f_close(&src_file); // Close the source file if it was opened successfully
        return fr;
    }

    // Copy the file
    do
    {
        fr = f_read(&src_file, buffer, sizeof buffer, &br); // Read a chunk of source file
        if (fr != FR_OK)
            break;                                 // Break on error
        fr = f_write(&dest_file, buffer, br, &bw); // Write it to the destination file
    } while (fr == FR_OK && br == sizeof buffer);

    // Close files
    f_close(&src_file);
    f_close(&dest_file);

    DPRINTF("File copied\n");
    return fr; // Return the result
}

static void release_memory_files(char **files, int num_files)
{
    for (int i = 0; i < num_files; i++)
    {
        free(files[i]); // Free each string
    }
    free(files); // Free the list itself
}

static char **show_dir_files(const char *dir, int *num_files)
{
    char cwdbuf[FF_LFN_BUF] = {0};
    FRESULT fr;
    char const *p_dir;
    char **filenames = NULL;
    *num_files = 0; // Initialize the count of files to 0

    if (dir[0])
    {
        p_dir = dir;
    }
    else
    {
        fr = f_getcwd(cwdbuf, sizeof cwdbuf);
        if (FR_OK != fr)
        {
            DPRINTF("f_getcwd error: %s (%d)\n", FRESULT_str(fr), fr);
            return NULL;
        }
        p_dir = cwdbuf;
    }

    DIR dj;
    FILINFO fno;
    memset(&dj, 0, sizeof dj);
    memset(&fno, 0, sizeof fno);

    fr = f_findfirst(&dj, &fno, p_dir, "*");
    if (FR_OK != fr)
    {
        DPRINTF("f_findfirst error: %s (%d)\n", FRESULT_str(fr), fr);
        return NULL;
    }

    while (fr == FR_OK && fno.fname[0] && fno.fname[0])
    {
        // Allocate space for a new pointer in the filenames array
        filenames = realloc(filenames, sizeof(char *) * (*num_files + 1));
        if (!filenames)
        {
            DPRINTF("Memory allocation failed\n");
            return NULL;
        }
        filenames[*num_files] = strdup(fno.fname); // Store the filename
        (*num_files)++;

        fr = f_findnext(&dj, &fno); // Search for next item
    }

    f_closedir(&dj);

    return filenames;
}

static int load(char *path, char *filename, uint32_t rom_load_offset)
{
    FIL fsrc;                                           /* File objects */
    BYTE buffer[CONFIGURATOR_SHARED_MEMORY_SIZE_BYTES]; /* File copy buffer */
    FRESULT fr;                                         /* FatFs function common result code */
    unsigned int br = 0;                                /* File read/write count */
    unsigned int size = 0;                              // File size
    uint32_t dest_address = rom_load_offset;            // Initialize pointer to the ROM address

    char fullpath[512]; // Assuming 512 bytes as the max path+filename length. Adjust if necessary.
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, filename);

    DPRINTF("Loading file '%s'  ", fullpath);

    /* Open source file on the drive 0 */
    fr = f_open(&fsrc, fullpath, FA_READ);
    if (fr)
        return (int)fr;

    // Get file size
    size = f_size(&fsrc);
    DPRINTF("File size: %i bytes\n", size);

    // If the size of the image is not 65536 or 131072 bytes, check if the file
    // is 4 bytes larger and the first 4 bytes are 0x0000. If so, skip them
    if ((size == ROM_SIZE_BYTES + 4) || (size == ROM_SIZE_BYTES * 2 + 4))
    {
        // Read the first 4 bytes
        fr = f_read(&fsrc, buffer, 4, &br);
        if (fr)
        {
            f_close(&fsrc);
            return (int)fr; // Check for error in reading
        }

        // Check if the first 4 bytes are 0x0000
        if (buffer[0] == 0x00 && buffer[1] == 0x00 && buffer[2] == 0x00 && buffer[3] == 0x00)
        {
            DPRINTF("Skipping first 4 bytes. Looks like a STEEM cartridge image.\n");
        }
        else
        {
            // Rollback the file pointer to the previous 4 bytes read
            f_lseek(&fsrc, -4);
        }
    }
    /* Copy source to destination */
    size = 0;
    for (;;)
    {
        fr = f_read(&fsrc, buffer, sizeof buffer, &br); /* Read a chunk of data from the source file */
        if (fr)
        {
            f_close(&fsrc);
            return (int)fr; // Check for error in reading
        }
        if (br == 0)
            break; // EOF

        // Transform buffer's words from little endian to big endian inline
        for (int i = 0; i < br; i += 2)
        {
            uint16_t value = *(uint16_t *)(buffer + i);
            value = (value << 8) | (value >> 8);
            *(uint16_t *)(buffer + i) = value;
        }

        // Transfer buffer to FLASH
        // WARNING! TRANSFER THE INFORMATION IN THE BUFFER AS LITTLE ENDIAN!!!!
        uint32_t ints = save_and_disable_interrupts();
        flash_range_program(dest_address, buffer, br);
        restore_interrupts(ints);

        dest_address += br; // Increment the pointer to the ROM address
        size += br;

        DPRINTF(".");
    }

    // Close open file
    f_close(&fsrc);

    DPRINTF(" %i bytes loaded\n", size);
    DPRINTF("File loaded at offset 0x%x\n", rom_load_offset);
    DPRINTF("Dest ROM address end is 0x%x\n", dest_address - 1);
    return (int)fr;
}

static char **filter(char **file_list, int file_count, int *num_files)
{
    int validCount = 0;

    // Count valid filenames
    for (int i = 0; i < file_count; i++)
    {
        if (file_list[i][0] != '.')
        {
            validCount++;
        }
    }

    // Allocate memory for the new array
    char **filtered_list = (char **)malloc(validCount * sizeof(char *));
    if (filtered_list == NULL)
    {
        perror("Failed to allocate memory");
        exit(1);
    }

    int index = 0;
    for (int i = 0; i < file_count; i++)
    {
        if (file_list[i][0] != '.')
        {
            filtered_list[index++] = strdup(file_list[i]);
            if (filtered_list[index - 1] == NULL)
            {
                perror("Failed to duplicate string");
                exit(1);
            }
        }
    }
    *num_files = validCount;
    return filtered_list;
}

// Comparison function for qsort.
static int compare_strings(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

static int get_number_within_range(int num_files)
{
    char input[3];
    int number;

    while (1)
    {
        // Prompt the user
        DPRINTF("Enter the ROM to load (1 to %d): ", num_files);

        // Get the input as a string (this is to handle empty input)
        if (fgets(input, sizeof(input), stdin) == NULL || strlen(input) <= 1)
        {
            // If input is empty or just a newline character, return
            return -1; // Use -1 or another value to indicate that no valid number was received
        }

        // Convert the string input to an integer
        if (sscanf(input, "%d", &number) == 1)
        {
            if (number >= 1 && number <= num_files)
            {
                // If the number is within the desired range, return the number
                return number;
            }
        }

        // If out of range or not a valid number, print an error message
        DPRINTF("Invalid input! Please enter a number between 1 and %d.\n", num_files);
    }
}

static void store_file_list(char **file_list, int num_files, uint8_t *memory_location)
{
    uint8_t *dest_ptr = memory_location;

    int total_size = 0;
    // Iterate through each file in the file_list
    for (int i = 0; i < num_files; i++)
    {
        if ((total_size + strlen(file_list[i]) + 5) > CONFIGURATOR_SHARED_MEMORY_SIZE_BYTES)
        {
            DPRINTF("ERROR: Not enough memory to store the file list.\n");
            break;
        }
        char *current_file = file_list[i];
        total_size += strlen(current_file) + 1; // +1 for null terminator

        // Copy each character of the current file name into the memory location
        while (*current_file)
        {
            *dest_ptr++ = *current_file++;
        }

        // Place a zero after each file name
        *dest_ptr++ = 0x00;
    }

    // Ensure even address for the following data
    if ((uintptr_t)dest_ptr & 1)
    {
        *dest_ptr++ = 0x00;
    }
    // Add an additional 0x00 byte to mark the end of the list
    *dest_ptr++ = 0x00;
    *dest_ptr++ = 0x00;
    *dest_ptr++ = 0xFF;
    *dest_ptr++ = 0xFF;

    // Transform buffer's words from little endian to big endian inline
    uint16_t *dest_ptr_word = (uint16_t *)memory_location;
    for (int i = 0; i < total_size / 2; i++)
    {
        uint16_t value = *(uint16_t *)(dest_ptr_word);
        *(uint16_t *)(dest_ptr_word)++ = (value << 8) | (value >> 8);
    }
}

static void __not_in_flash_func(handle_protocol_command)(const TransmissionProtocol *protocol)
{
    ConfigEntry *entry = NULL;
    uint16_t value_payload = 0;
    uint8_t *memory_area = (uint8_t *)(ROM3_START_ADDRESS - CONFIGURATOR_SHARED_MEMORY_SIZE_BYTES);
    // Handle the protocol
    switch (protocol->command_id)
    {
    case DOWNLOAD_ROM:
        // Download the ROM index passed as argument in the payload
        DPRINTF("Command DOWNLOAD_ROM (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        value_payload = protocol->payload[4] | (protocol->payload[5] << 8);
        DPRINTF("Value: %d\n", value_payload);
        rom_network_selected = value_payload;
        break;
    case LOAD_ROM:
        // Load ROM passed as argument in the payload
        DPRINTF("Command LOAD_ROM (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        value_payload = protocol->payload[4] | (protocol->payload[5] << 8);
        DPRINTF("Value: %d\n", value_payload);
        if (microsd_mounted)
        {
            rom_file_selected = value_payload;
        }
        else
        {
            DPRINTF("SD card not mounted. Cannot load ROM.\n");
            null_words((uint16_t *)memory_area, CONFIGURATOR_SHARED_MEMORY_SIZE_BYTES / 2);
        }
        break;
    case LIST_ROMS:
        // Get the list of roms in the SD card
        DPRINTF("Command LIST_ROMS (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        if (!microsd_mounted)
        {
            DPRINTF("SD card not mounted. Cannot list ROMs.\n");
            null_words((uint16_t *)memory_area, CONFIGURATOR_SHARED_MEMORY_SIZE_BYTES / 2);
        }
        else
        {
            list_roms = true; // now the active loop should stop and list the ROMs
        }
        break;
    case GET_CONFIG:
        // Get the list of parameters in the device
        DPRINTF("Command GET_CONFIG (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        memcpy(memory_area + RANDOM_SEED_SIZE, &configData, sizeof(configData));

        // Swap the keys and values section bytes in the words
        // The endians conversions should be done always in the rp2040 side to relief
        // the ST side from this task
        uint16_t *dest_ptr = (uint16_t *)(memory_area + sizeof(__uint32_t) + RANDOM_SEED_SIZE); // Bypass magic number and random size
        for (int i = 0; i < configData.count; i++)
        {
            swap_data(dest_ptr);
            dest_ptr += sizeof(ConfigEntry) / 2;
        }
        *((volatile uint32_t *)(memory_area)) = random_token;
        break;
    case PUT_CONFIG_STRING:
        // Put a configuration string parameter in the device
        DPRINTF("Command PUT_CONFIG_STRING (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        entry = malloc(sizeof(ConfigEntry));
        memcpy(entry, protocol->payload + RANDOM_SEED_SIZE, sizeof(ConfigEntry));
        swap_data((__uint16_t *)entry);
        DPRINTF("Key:%s - Value: %s\n", entry->key, entry->value);
        put_string(entry->key, entry->value);
        *((volatile uint32_t *)(memory_area)) = random_token;
        break;
    case PUT_CONFIG_INTEGER:
        // Put a configuration integer parameter in the device
        DPRINTF("Command PUT_CONFIG_INTEGER (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        entry = malloc(sizeof(ConfigEntry));
        memcpy(entry, protocol->payload + RANDOM_SEED_SIZE, sizeof(ConfigEntry));
        swap_data((__uint16_t *)entry);
        DPRINTF("Key:%s - Value: %s\n", entry->key, entry->value);
        put_integer(entry->key, atoi(entry->value));
        *((volatile uint32_t *)(memory_area)) = random_token;
        break;
    case PUT_CONFIG_BOOL:
        // Put a configuration boolean parameter in the device
        DPRINTF("Command PUT_CONFIG_BOOL (6) received: %d\n", protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        entry = malloc(sizeof(ConfigEntry));
        memcpy(entry, protocol->payload + RANDOM_SEED_SIZE, sizeof(ConfigEntry));
        swap_data((__uint16_t *)entry);
        DPRINTF("Key:%s - Value: %s\n", entry->key, entry->value);
        put_bool(entry->key, (strcmp(entry->value, "true") == 0) ? true : false);
        *((volatile uint32_t *)(memory_area)) = random_token;
        break;
    case SAVE_CONFIG:
        // Save the current configuration in the FLASH of the device
        DPRINTF("Command SAVE_CONFIG (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        persist_config = true; // now the active loop should stop and save the config
        break;
    case RESET_DEVICE:
        // Reset the device
        DPRINTF("Command RESET_DEVICE (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        reset_default = true; // now the active loop should stop and reset the config
        break;
    case LAUNCH_SCAN_NETWORKS:
        // Scan the networks and return the results
        DPRINTF("Command LAUNCH_SCAN_NETWORKS (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        scan_network = true; // now the active loop should stop and scan the networks
        *((volatile uint32_t *)(memory_area)) = random_token;
        break;
    case GET_SCANNED_NETWORKS:
        // Get the results of the scanned networks
        DPRINTF("Command GET_SCANNED_NETWORKS (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        memcpy(memory_area + RANDOM_SEED_SIZE, &wifiScanData, sizeof(wifiScanData));
        network_swap_data((__uint16_t *)(memory_area + RANDOM_SEED_SIZE), wifiScanData.count);
        *((volatile uint32_t *)(memory_area)) = random_token;
        break;
    case CONNECT_NETWORK:
        // Put a configuration string parameter in the device
        DPRINTF("Command CONNECT_NETWORK (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        wifi_auth = malloc(sizeof(WifiNetworkAuthInfo));
        memcpy(wifi_auth, protocol->payload, sizeof(WifiNetworkAuthInfo));
        network_swap_auth_data((__uint16_t *)wifi_auth);
        DPRINTF("SSID:%s - Pass: %s - Auth: %d\n", wifi_auth->ssid, wifi_auth->password, wifi_auth->auth_mode);
        break;
    case GET_IP_DATA:
        // Get IPv4 and IPv6 and SSID info
        DPRINTF("Command GET_IP_DATA (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        ConnectionData *connection_data = malloc(sizeof(ConnectionData));
        get_connection_data(connection_data);
        memcpy(memory_area + RANDOM_SEED_SIZE, connection_data, sizeof(ConnectionData));
        network_swap_connection_data((__uint16_t *)(memory_area + RANDOM_SEED_SIZE));
        free(connection_data);
        *((volatile uint32_t *)(memory_area)) = random_token;
        break;
    case DISCONNECT_NETWORK:
        // Disconnect from the network
        DPRINTF("Command DISCONNECT_NETWORK (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        disconnect_network = true; // now in the active loop should stop and disconnect from the network
        break;
    case GET_ROMS_JSON_FILE:
        // Download the JSON file of the ROMs from the URL
        DPRINTF("Command GET_ROMS_JSON_FILE (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        get_json_file = true; // now in the active loop should stop and download the JSON file
        break;
    case LOAD_FLOPPY_RO:
        // Load the floppy image in ro mode passed as argument in the payload
        DPRINTF("Command LOAD_FLOPPY_RO (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        value_payload = protocol->payload[4] | (protocol->payload[5] << 8);
        DPRINTF("Value: %d\n", value_payload);
        if (microsd_mounted)
        {
            floppy_file_selected = value_payload;
            floppy_read_write = false;
        }
        else
        {
            DPRINTF("SD card not mounted. Cannot load ROM.\n");
            null_words((uint16_t *)memory_area, CONFIGURATOR_SHARED_MEMORY_SIZE_BYTES / 2);
        }
        break;
    case LOAD_FLOPPY_RW:
        // Load the floppy image in rw mode passed as argument in the payload
        DPRINTF("Command LOAD_FLOPPY_RW (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        value_payload = protocol->payload[4] | (protocol->payload[5] << 8);
        DPRINTF("Value: %d\n", value_payload);
        if (microsd_mounted)
        {
            floppy_file_selected = value_payload;
            floppy_read_write = true;
        }
        else
        {
            DPRINTF("SD card not mounted. Cannot load ROM.\n");
            null_words((uint16_t *)memory_area, CONFIGURATOR_SHARED_MEMORY_SIZE_BYTES / 2);
        }
        break;
    case LIST_FLOPPIES:
        // Get the list of floppy images in the SD card
        DPRINTF("Command LIST_FLOPPIES (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        if (!microsd_mounted)
        {
            DPRINTF("SD card not mounted. Cannot list Floppies.\n");
            null_words((uint16_t *)memory_area, CONFIGURATOR_SHARED_MEMORY_SIZE_BYTES / 2);
        }
        else
        {
            list_floppies = true; // now the active loop should stop and list the floppy images
        }
        break;
    case QUERY_FLOPPY_DB:
        // Get the list of floppy images for a given letter from the Atari ST Databse
        DPRINTF("Command QUERY_FLOPPY_DB (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        payloadPtr = (uint16_t *)protocol->payload + 2;
        query_floppy_letter = (char)(*(payloadPtr)&0xFF);

        // Convert to lowercase if it's an uppercase letter
        if (query_floppy_letter >= 'A' && query_floppy_letter <= 'Z')
        {
            query_floppy_letter += 'a' - 'A';
        }

        DPRINTF("Random token: %x\n", random_token);
        DPRINTF("Letter: %c\n", query_floppy_letter);
        query_floppy_db = true;
        break;
    case DOWNLOAD_FLOPPY:
        // Download the floppy image passed as argument in the payload
        DPRINTF("Command DOWNLOAD_FLOPPY (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        value_payload = protocol->payload[4] | (protocol->payload[5] << 8);
        DPRINTF("Value: %d\n", value_payload);
        floppy_image_selected_status = 0; // Reset the status
        if (microsd_mounted)
        {
            floppy_image_selected = value_payload;
        }
        else
        {
            DPRINTF("SD card not mounted. Cannot save the image to download.\n");
            null_words((uint16_t *)memory_area, CONFIGURATOR_SHARED_MEMORY_SIZE_BYTES / 2);
            floppy_image_selected_status = 1; // Error: SD card not mounted
            floppy_image_selected = 0;
        }
        break;
    case GET_SD_DATA:
        // Get the SD card data
        DPRINTF("Command GET_SD_DATA (%i) received: %d\n", protocol->command_id, protocol->payload_size);
        random_token = ((*((uint32_t *)protocol->payload) & 0xFFFF0000) >> 16) | ((*((uint32_t *)protocol->payload) & 0x0000FFFF) << 16);
        microsd_status = true;
        break;

    // ... handle other commands
    default:
        DPRINTF("Unknown command: %d\n", protocol->command_id);
    }
}

// Interrupt handler callback for DMA completion
void __not_in_flash_func(dma_irq_handler_lookup_callback)(void)
{
    // Clear the interrupt request for the channel
    dma_hw->ints1 = 1u << lookup_data_rom_dma_channel;

    // Read the address to process
    uint32_t addr = (uint32_t)dma_hw->ch[lookup_data_rom_dma_channel].al3_read_addr_trig;

    // Avoid priting anything inside an IRQ handled function
    // DPRINTF("DMA LOOKUP: $%x\n", addr);
    if (addr >= ROM3_START_ADDRESS)
    {
        parse_protocol((uint16_t)(addr & 0xFFFF), handle_protocol_command);
    }
}

int copy_firmware_to_RAM()
{
    // Need to initialize the ROM4 section with the firmware data
    extern uint16_t __rom_in_ram_start__;
    uint16_t *rom4_dest = &__rom_in_ram_start__;
    uint16_t *rom4_src = (uint16_t *)firmwareROM;
    for (int i = 0; i < firmwareROM_length; i++)
    {
        uint16_t value = *rom4_src++;
        *rom4_dest++ = value;
    }
    DPRINTF("Firmware copied to RAM.\n");
    return 0;
}

int delete_FLASH(void)
{
    // Erase the content before loading the new file. It seems that
    // overwriting it's not enough
    DPRINTF("Erasing FLASH...\n");
    flash_range_erase(FLASH_ROM_LOAD_OFFSET, (ROM_SIZE_BYTES * 2) - 1); // Two banks of 64K
    DPRINTF("FLASH erased.\n");
    return 0;
}

int init_firmware()
{

    FRESULT fr;
    FATFS fs;
    int num_files = 0;
    char **file_list = NULL;

    DPRINTF("\033[2J\033[H"); // Clear Screen
    DPRINTF("\n> ");
    printf("Initializing Configurator...\n"); // Always this print message to the console
    stdio_flush();

    // Initialize SD card
    microsd_initialized = sd_init_driver();
    if (!microsd_initialized)
    {
        DPRINTF("ERROR: Could not initialize SD card\r\n");
    }

    if (microsd_initialized)
    {
        // Mount drive
        fr = f_mount(&fs, "0:", 1);
        microsd_mounted = (fr == FR_OK);
        if (!microsd_mounted)
        {
            DPRINTF("ERROR: Could not mount filesystem (%d)\r\n", fr);
        }
    }

    // Copy the content of the file list to the end of the ROM4 memory minus 4Kbytes
    // Translated to pure ROM4 address of the ST: 0xFB0000 - 0x1000 = 0xFAF000
    // The firmware code should be able to read the list of files from 0xFAF000
    // To select the desired ROM from the list, the ST code should send the command
    // LOAD_ROM with the number of the ROM to load PLUS 1. For example, to load the
    // first ROM in the list, the ST code should send the command LOAD_ROM with the
    // value 1 (0 + 1) because the first ROM of the index  is 0.
    // x=PEEK(&HFBABCD) 'Magic header number of commands
    // x=PEEK(&HFB0001) 'Command LOAD_ROM
    // x=PEEK(&HFB0002) 'Size of the payload (always even numbers)
    // x=PEEK(&HFB0001) 'Payload (two bytes per word)

    uint8_t *memory_area = (uint8_t *)(ROM3_START_ADDRESS - CONFIGURATOR_SHARED_MEMORY_SIZE_BYTES);

    // Here comes the tricky part. We have to put in the higher section of the ROM4 memory the content
    // of the file list available in the SD card.
    // The structure is a list of chars separated with a 0x00 byte. The end of the list is marked with
    // two 0x00 bytes.

    u_int16_t wifi_scan_poll_counter = 0;
    u_int64_t wifi_scan_poll_counter_mcs = 0; // Force the first scan to be done in the loop

    ConfigEntry *default_config_entry = find_entry("WIFI_SCAN_SECONDS");
    if (default_config_entry != NULL)
    {
        wifi_scan_poll_counter = atoi(default_config_entry->value);
    }
    else
    {
        DPRINTF("WIFI_SCAN_SECONDS not found in the config file. Disabling polling.\n");
    }

    // Start the network.
    network_connect(false, NETWORK_CONNECTION_ASYNC);

    // The "C" character stands for "Configurator"
    blink_morse('C');

    u_int16_t network_poll_counter = 0;
    while ((rom_file_selected < 0) && (rom_network_selected < 0) && (floppy_file_selected < 0) && (floppy_image_selected < 0) && (reset_default == false))
    {
        tight_loop_contents();

#if PICO_CYW43_ARCH_POLL
        cyw43_arch_lwip_begin();
        network_poll();
        cyw43_arch_wait_for_work_until(make_timeout_time_ms(1000));
        cyw43_arch_lwip_end();
#elif PICO_CYW43_ARCH_THREADSAFE_BACKGROUND
        cyw43_arch_lwip_begin();
        cyw43_arch_wait_for_work_until(make_timeout_time_ms(10));
        cyw43_arch_lwip_end();
#else
        sleep_ms(1000);
#endif
        if ((time_us_64() - wifi_scan_poll_counter_mcs) > (wifi_scan_poll_counter * 1000000))
        {
            ConfigEntry *default_config_entry = find_entry("WIFI_SCAN_SECONDS");
            if (default_config_entry != NULL)
            {
                network_scan();
                wifi_scan_poll_counter = atoi(default_config_entry->value);
                wifi_scan_poll_counter_mcs = time_us_64();
            }
            else
            {
                DPRINTF("WIFI_SCAN_SECONDS not found in the config file. Disabling polling.\n");
            }
        }
        if (wifi_auth != NULL)
        {
            DPRINTF("Connecting to network...\n");
            put_string("WIFI_SSID", wifi_auth->ssid);
            put_string("WIFI_PASSWORD", wifi_auth->password);
            put_integer("WIFI_AUTH", wifi_auth->auth_mode);
            write_all_entries();

            network_connect(true, NETWORK_CONNECTION_ASYNC);
            free(wifi_auth);
            wifi_auth = NULL;
        }
        if (disconnect_network)
        {
            disconnect_network = false;
            // Force  network disconnection
            network_disconnect();
            // Need to deinit and init again the full network stack to be able to scan again
            cyw43_arch_deinit();
            cyw43_arch_init();
            network_init();

            network_scan();

            // Clean the credentials configuration
            put_string("WIFI_SSID", "");
            put_string("WIFI_PASSWORD", "");
            put_integer("WIFI_AUTH", 0);
            write_all_entries();
        }
        if (network_poll_counter == 0)
        {
            if (strlen(find_entry("WIFI_SSID")->value) > 0)
            {
                // Only display when changes status to avoid flooding the console
                ConnectionStatus previous_status = get_previous_connection_status();
                ConnectionStatus current_status = get_network_connection_status();
                if (current_status != previous_status)
                {
                    DPRINTF("Network status: %d\n", current_status);
                    DPRINTF("Network previous status: %d\n", previous_status);
                    ConnectionData *connection_data = malloc(sizeof(ConnectionData));
                    get_connection_data(connection_data);
<<<<<<< HEAD
                    DPRINTF("SSID: %s - Status: %d - IPv4: %s - IPv6: %s - GW:%s - Mask:%s\n", connection_data->ssid, connection_data->status, connection_data->ipv4_address, connection_data->ipv6_address, print_ipv4(get_gateway()), print_ipv4(get_netmask()));
                    free(connection_data);

                    // If there is a connection and an IP address, get the latest version from the github repository
                    if (current_status == CONNECTED_WIFI_IP)
                    {
                        // Print the latest release found in the github repository
                        DPRINTF("Latest version found: %s\n", get_latest_release());
=======
                    DPRINTF("SSID: %s - Status: %d - IPv4: %s - IPv6: %s - GW:%s - Mask:%s - MAC:%s\n",
                            connection_data->ssid,
                            connection_data->status,
                            connection_data->ipv4_address,
                            connection_data->ipv6_address,
                            print_ipv4(get_gateway()),
                            print_ipv4(get_netmask()),
                            print_mac(get_mac_address()));
                    free(connection_data);
                    if (current_status == BADAUTH_ERROR)
                    {
                        DPRINTF("Bad authentication. Should enter again the credentials...\n");
                        network_disconnect();

                        // Need to deinit and init again the full network stack to be able to scan again
                        cyw43_arch_deinit();
                        cyw43_arch_init();
                        network_init();

                        network_scan();

                        // Clean the credentials configuration
                        put_string("WIFI_SSID", "");
                        put_string("WIFI_PASSWORD", "");
                        put_integer("WIFI_AUTH", 0);
                        write_all_entries();

                        // Start the network.
                        network_connect(false, NETWORK_CONNECTION_ASYNC);
                    }
                    else if ((current_status >= TIMEOUT_ERROR) && (current_status <= INSUFFICIENT_RESOURCES_ERROR))
                    {
                        DPRINTF("Connection failed. Resetting network...\n");
                        network_disconnect();

                        // Need to deinit and init again the full network stack to be able to scan again
                        cyw43_arch_deinit();
                        cyw43_arch_init();
                        network_init();

                        network_scan();
                        // Start the network.
                        network_connect(true, NETWORK_CONNECTION_ASYNC);
>>>>>>> origin/main
                    }
                }
            }
        }

        if (persist_config)
        {
            persist_config = false;
            DPRINTF("Saving configuration to FLASH\n");
            write_all_entries();
            *((volatile uint32_t *)(memory_area)) = random_token;
        }

        if (microsd_status)
        {
            microsd_status = false;
            SdCardData *sd_data = malloc(sizeof(SdCardData));
            get_sdcard_data(&fs, sd_data);

            // Swap the bytes to motorola endian format
            sd_data->roms_folder_count = (sd_data->roms_folder_count >> 16) | (sd_data->roms_folder_count << 16);
            sd_data->floppies_folder_count = (sd_data->floppies_folder_count >> 16) | (sd_data->floppies_folder_count << 16);
            sd_data->harddisks_folder_count = (sd_data->harddisks_folder_count >> 16) | (sd_data->harddisks_folder_count << 16);
            sd_data->sd_free_space = (sd_data->sd_free_space >> 16) | (sd_data->sd_free_space << 16);
            sd_data->sd_size = (sd_data->sd_size >> 16) | (sd_data->sd_size << 16);
            memcpy(memory_area + RANDOM_SEED_SIZE, sd_data, sizeof(SdCardData));

            // More endian conversions
            uint16_t *dest_ptr_word = (uint16_t *)(memory_area + RANDOM_SEED_SIZE);
            for (int j = 0; j < (MAX_FOLDER_LENGTH * 3); j += 2)
            {
                uint16_t value = *(uint16_t *)(dest_ptr_word);
                *(uint16_t *)(dest_ptr_word)++ = (value << 8) | (value >> 8);
            }
            free(sd_data);
            *((volatile uint32_t *)(memory_area)) = random_token;
        }

        // Download the json file
        if (get_json_file)
        {
            get_json_file = false;

            // Clean memory space
            memset(memory_area + RANDOM_SEED_SIZE, 0, CONFIGURATOR_SHARED_MEMORY_SIZE_BYTES);

            // Get the URL from the configuration
            char *url = find_entry("ROMS_YAML_URL")->value;

            // The the JSON file info
            get_json_files(&network_files, &filtered_num_network_files, url);

            // Iterate over the RomInfo items and populate the names array
            char *dest_ptr = (char *)(memory_area + RANDOM_SEED_SIZE);
            for (int i = 0; i < filtered_num_network_files; i++)
            {
                // Copy the string from network_files[i].name to dest_ptr with strcpy
                // strcpy(dest_ptr, network_files[i].name + "(" + network_files[i].size_kb + " Kb)" + '\0');
                // dest_ptr += strlen(network_files[i].name) + 1;
                sprintf(dest_ptr, "%s\t(%d Kb)", network_files[i].name, network_files[i].size_kb);
                dest_ptr += strlen(dest_ptr) + 1;
            }
            // If dest_ptr is odd, add a 0x00 byte to align the next string
            if ((uintptr_t)dest_ptr & 1)
            {
                *dest_ptr++ = 0x00;
            } // Add an additional 0x00 word to mark the end of the list
            *dest_ptr++ = 0x00;
            *dest_ptr++ = 0x00;

            // Swap the words to motorola endian format: BIG ENDIAN
            network_swap_json_data((__uint16_t *)(memory_area + RANDOM_SEED_SIZE));

            *((volatile uint32_t *)(memory_area)) = random_token;
        }

        // List the ROM images in the SD card
        if (list_roms)
        {
            list_roms = false;
            // Show the root directory content (ls command)
            char *dir = find_entry("ROMS_FOLDER")->value;
            if (strlen(dir) == 0)
            {
                dir = "";
            }
            DPRINTF("ROM images folder: %s\n", dir);
            file_list = show_dir_files(dir, &num_files);

            // Remove hidden files from the list
            filtered_local_list = filter(file_list, num_files, &filtered_num_local_files);
            // Sort remaining valid filenames lexicographically
            qsort(filtered_local_list, filtered_num_local_files, sizeof(char *), compare_strings);
            // Store the list in the ROM memory space
            store_file_list(filtered_local_list, filtered_num_local_files, (memory_area + RANDOM_SEED_SIZE));

            *((volatile uint32_t *)(memory_area)) = random_token;
        }

        // List the floppy images in the SD card
        if (list_floppies)
        {
            list_floppies = false;
            // Show the root directory content (ls command)
            char *dir = find_entry("FLOPPIES_FOLDER")->value;
            if (strlen(dir) == 0)
            {
                dir = "";
            }
            DPRINTF("Floppy images folder: %s\n", dir);
            // Get the list of floppy image files in the directory
            file_list = show_dir_files(dir, &num_files);

            // Remove hidden files from the list
            filtered_local_list = filter(file_list, num_files, &filtered_num_local_files);
            // Sort remaining valid filenames lexicographically
            qsort(filtered_local_list, filtered_num_local_files, sizeof(char *), compare_strings);
            // Store the list in the ROM memory space
            store_file_list(filtered_local_list, filtered_num_local_files, (memory_area + RANDOM_SEED_SIZE));

            *((volatile uint32_t *)(memory_area)) = random_token;
        }

        // Query the Atari ST Database for the list of floppy images for a given letter
        if (query_floppy_db)
        {
            query_floppy_db = false;

            // Free dynamically allocated memory first
            if (floppy_images_files != NULL)
            {
                for (int i = 0; i < filtered_num_floppy_images_files; i++)
                {
                    free(floppy_images_files[i].name);
                    free(floppy_images_files[i].status);
                    free(floppy_images_files[i].description);
                    free(floppy_images_files[i].tags);
                    free(floppy_images_files[i].extra);
                    free(floppy_images_files[i].url);
                }

                free(floppy_images_files);
            }

            dma_channel_set_irq1_enabled(lookup_data_rom_dma_channel, false);

            // Clean memory space
            memset(memory_area, 0, CONFIGURATOR_SHARED_MEMORY_SIZE_BYTES);

            // Get the URL from the configuration
            char *base_url = find_entry("FLOPPY_DB_URL")->value;

            // Ensure that the buffer is large enough for the original URL, the `/db/`, the letter, `.csv`, and the null terminator.
            char url[256]; // Adjust the size as needed based on the maximum length of base_url.

            sprintf(url, "%s/db/%c.csv", base_url, query_floppy_letter);

            get_floppy_db_files(&floppy_images_files, &filtered_num_floppy_images_files, url);

            dma_channel_set_irq1_enabled(lookup_data_rom_dma_channel, true);

            // Demonstrate the results
            // for (int i = 0; i < filtered_num_floppy_images_files; i++)
            // {
            //     DPRINTF("Name: %s, Status: %s, Description: %s, Tags: %s, Extra: %s, URL: %s\n",
            //             floppy_images_files[i].name, floppy_images_files[i].status, floppy_images_files[i].description,
            //             floppy_images_files[i].tags, floppy_images_files[i].extra, floppy_images_files[i].url);
            // }

            // Iterate over the RomInfo items and populate the names array
            char *dest_ptr = (char *)(memory_area + 4); // Bypass random token
            for (int i = 0; i < filtered_num_floppy_images_files; i++)
            {
                // Copy the string from network_files[i].name to dest_ptr
                sprintf(dest_ptr, "%s", floppy_images_files[i].name);
                dest_ptr += strlen(dest_ptr) + 1;
            }
            // If dest_ptr is odd, add a 0x00 byte to align the next string
            if ((uintptr_t)dest_ptr & 1)
            {
                *dest_ptr++ = 0x00;
            } // Add an additional 0x00 word to mark the end of the list
            *dest_ptr++ = 0x00;
            *dest_ptr++ = 0x00;

            // Swap the words to motorola endian format: BIG ENDIAN
            network_swap_json_data((__uint16_t *)(memory_area + 4));

            DPRINTF("Random token: %x\n", random_token);

            *((volatile uint32_t *)(memory_area)) = random_token;
        }

        // Increase the counter and reset it if it reaches the limit
        network_poll_counter >= NETWORK_POLL_INTERVAL ? network_poll_counter = 0 : network_poll_counter++;

        // Store the seed of the random number generator in the ROM memory space
        *((volatile uint32_t *)(memory_area - RANDOM_SEED_SIZE)) = rand() % 0xFFFFFFFF;
    }

    if (rom_file_selected > 0)
    {
        DPRINTF("ROM file selected: %d\n", rom_file_selected);

        // Erase the content before loading the new file. It seems that
        // overwriting it's not enough
        uint32_t ints = save_and_disable_interrupts();
        flash_range_erase(FLASH_ROM_LOAD_OFFSET, ROM_SIZE_BYTES * 2); // Two banks of 64K
        restore_interrupts(ints);
        int res = load(find_entry("ROMS_FOLDER")->value, filtered_local_list[rom_file_selected - 1], FLASH_ROM_LOAD_OFFSET);

        if (res != FR_OK)
            DPRINTF("f_open error: %s (%d)\n", FRESULT_str(res), res);

        release_memory_files(file_list, num_files);
        release_memory_files(filtered_local_list, filtered_num_local_files);

        put_string("BOOT_FEATURE", "ROM_EMULATOR");
        write_all_entries();
        *((volatile uint32_t *)(memory_area)) = random_token;
    }

    if (rom_network_selected > 0)
    {
        DPRINTF("ROM network selected: %d\n", rom_network_selected);
        int res = download_rom(network_files[rom_network_selected - 1].url, FLASH_ROM_LOAD_OFFSET);

        // Free dynamically allocated memory
        for (int i = 0; i < filtered_num_network_files; i++)
        {
            freeRomItem(&network_files[i]);
        }
        free(network_files);

        put_string("BOOT_FEATURE", "ROM_EMULATOR");
        write_all_entries();

        *((volatile uint32_t *)(memory_area)) = random_token;
    }

    if (floppy_file_selected > 0)
    {
        DPRINTF("Floppy file selected: %d\n", floppy_file_selected);

        char *old_floppy = filtered_local_list[floppy_file_selected - 1];
        DPRINTF("Load file: %s\n", old_floppy);

        char *new_floppy = NULL;
        // Check if old_floppy ends with ".rw"
        bool use_existing_rw = (strlen(old_floppy) > 3 && strcmp(&old_floppy[strlen(old_floppy) - 3], ".rw") == 0);

        if (floppy_read_write && !use_existing_rw)
        {
            new_floppy = malloc(strlen(old_floppy) + strlen(".rw") + 1); // Allocate space for the old string, the new suffix, and the null terminator
            sprintf(new_floppy, "%s.rw", old_floppy);                    // Create the new string with the .rw suffix
            char *dir = find_entry("FLOPPIES_FOLDER")->value;
            dma_channel_set_irq1_enabled(lookup_data_rom_dma_channel, false);
            FRESULT result = copy_file(dir, old_floppy, new_floppy, false); // Do not overwrite if exists
            dma_channel_set_irq1_enabled(lookup_data_rom_dma_channel, true);
        }
        else
        {
            new_floppy = strdup(old_floppy);
        }
        DPRINTF("Floppy Read/Write: %s\n", floppy_read_write ? "true" : "false");

        put_string("FLOPPY_IMAGE_A", new_floppy);
        put_string("BOOT_FEATURE", "FLOPPY_EMULATOR");
        write_all_entries();

        release_memory_files(file_list, num_files);
        release_memory_files(filtered_local_list, filtered_num_local_files);

        free(new_floppy);
        fflush(stdout);

        // The "F" character stands for "Floppy"
        blink_morse('F');
        *((volatile uint32_t *)(memory_area)) = random_token;
    }

    if (floppy_image_selected > 0)
    {
        char *extract_filename(char *path)
        {
            char *last_slash = strrchr(path, '/'); // Find the last occurrence of '/'

            // If '/' was found, return the string after it
            if (last_slash && *(last_slash + 1))
            {
                return last_slash + 1;
            }
            return path; // Return the original path if '/' wasn't found
        }

        DPRINTF("Floppy image selected to download: %d\n", floppy_image_selected);
        FloppyImageInfo remote = floppy_images_files[floppy_image_selected - 1];
        char *remote_name = remote.name;
        char *remote_uri = remote.url;

        char full_url[512];
        // Get the URL from the configuration
        char *base_url = find_entry("FLOPPY_DB_URL")->value;

        char *dest_filename = extract_filename(remote.url);
        char *dir = find_entry("FLOPPIES_FOLDER")->value;

        if (strncmp(remote_uri, "http", 4) == 0)
        { // Check if remote_uri starts with "http"
            strcpy(full_url, remote_uri);
        }
        else
        {
            // Use sprintf to format and concatenate strings
            sprintf(full_url, "%s/%s", base_url, remote_uri);
        }

        DPRINTF("Full URL: %s\n", full_url);
        DPRINTF("Remote name: %s\n", remote_name);
        DPRINTF("Name in folder: %s\n", dest_filename);
        DPRINTF("Directory: %s\n", dir);

        if (directory_exists(dir))
        {
            // Directory exists
            DPRINTF("Directory exists: %s\n", dir);

            int err = download_floppy(&full_url[0], dir, dest_filename, true);

            if (err != 0)
            {
                floppy_image_selected = 0;
                floppy_image_selected_status = 3; // Error: Failed downloading file
                DPRINTF("Download floppy error: %d\n", err);
            }
            else
            {
                put_string("FLOPPY_IMAGE_A", dest_filename);
                put_string("BOOT_FEATURE", "FLOPPY_EMULATOR");
                write_all_entries();
                // The "F" character stands for "Floppy"
                blink_morse('F');
            }
        }
        else
        {
            floppy_image_selected_status = 2; // Error: Directory does not exist
            floppy_image_selected = 0;
            DPRINTF("Directory does not exist: %s\n", dir);
        }

        *((volatile uint16_t *)(memory_area + 4)) = floppy_image_selected_status;

        DPRINTF("Random token: %x\n", random_token);
        *((volatile uint32_t *)(memory_area)) = random_token;
    }
    if (reset_default)
    {
        DPRINTF("Resetting configuration to default and rebooting SidecarT.\n");
        reset_config_default();
        *((volatile uint32_t *)(memory_area)) = random_token;
    }
    // Release memory from the protocol
    terminate_protocol_parser();
}
