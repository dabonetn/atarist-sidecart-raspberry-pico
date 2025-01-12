# Changelog

## BETA 0.0.16 (2024-04-04) - GEMDRIVE Hard Disk Emulator
### Changes
- **Issue 89**: Introduced a new parameters page featuring pagination.
- Revamped the start and configuration menu screen for the Emulate Floppy feature.
- Adjusted the download process from the floppy database to now redirect users to the Emulate Floppy menu.
- RP2040 Overclock and power management enhancements to avoid bus synchronizations glitches. 

### New Features
- **Issue 18**: Launched the GEMDRIVE hard disk emulation mode. For setup instructions, please [consult the user guide](https://docs.sidecartridge.com/sidecartridge-multidevice/userguide/#hard-disk-emulation) and refer to the detailed blog post [here](https://sidecartridge.com/blog/2024/01/26/hard-disk-emulation-sidecart/).
- **Issue 38**: Added the ability to configure Floppy emulation mode directly from the Configurator menu.
- **Issue 97**: Introduced an option to enable or disable the boot sector during startup in floppy emulation mode.
- **Issue 100**: Implemented a new **Dark mode** option for the Configurator for enhanced user experience.
- **Issue 98**: Added compatibility for using GEMDRIVE hard disk emulation mode alongside other hard disk drivers.

### Fixes
- **Issue 101**: Toggle function for displaying file count on the microSD card in Configurator mode.

## BETA 0.0.15 (2024-02-16)- Network stability release
### Changed
- **Issue #85**: Change FLOPPY_DB_URL and ROMS_YAML_URL to sidecartridge.com.

### New Features
- **Issue #79**: Add a configurable timeout when downloading ROMs or Floppy images.
- **Issue #80**: Add a configurable polling parameter for network status detection.
- **Issue #81**: Add a per-country configuration of the Wifi.
- **Issue #87**: Open the floppy database repository to all users.
- **Issue #90**: Enhance Wi-Fi Configuration Menu with Comprehensive Network Information.

## BETA 0.0.14 (2023-12-19)- Mega STE support and floppy stability release
### Fixes
- **Issue #71**: New reload floppy image after reset now keeps opened descriptors.
- **Issue #72**: Enhanced Reliability of Floppy Image Read/Write Routines.

### Changed
- **Issue #73**: Domain Change from sidecart.xyz to sidecartridge.com enhancement.

### New Features
- **Issue #69**: Support for MegaSTE 16Mhz and Cache enhancement.
- **Issue #70**: Toggle Hooked XBIOS Calls in Floppy Emulation Mode enhancement.
- **Issue #74**: Display context information from remote ROM and floppy catalogs enhancement.
- **Issue #75**: New crackers crews collections uploded.

## BETA 0.0.13 (2023-11-30)- Bugs and stabilization release
### Fixes
- **Issue #23**: The number of elements in the lists  now can be up to 32KBytes.
- **Issue #61**: Added delays and extra checks when changing functions after reset/reboot.
- **Issue #62**: Memory handling of the TOS process improved. Enhanced memory management.
- **Issue #66**: Documentation of the Atari ST floppy database updated to fix a placeholder field not documented.

### Changed
Overal stability of the system improved, also key handling and memory management.

### New Features
- **Issue #45**: Start in 'Rescue mode', booting a selected ROM image file after power on/reset.
- **Issue #60**: Configure the password for the WiFi in a configuration file of the SD card.

## BETA 0.0.12 (2023-11-13)- Feature aditions release
### Fixes
- **Issue #46**: Change the keyboard GEMDOS calls to BIOS calls bug enhancement to avoid buffering issues.
- **Issue #55**: Bus error on boot of SIDECART.TOS application in low memory computers fixed in all computers and TOS versions.

### Changed
- **Issue #57**: Faster text display. Listings now display faster.

### New Features
- **Issue #10**: Real Time Clock support using the RP2040 RTC and NTP.
- **Issue #56**: Dallas 1216 RTC support and emulation.
- **Issue #48**: Create an Empty Floppy Disk in Read/Write Floppy Emulation mode.
- **Issue #49**: Support for .MSA floppy images. Now the Floppy Emulator supports .ST and .MSA floppy images.  
- **Issue #58**: Implement BETA Releases Before FINAL Release Launch. 

## 0.0.11 (2023-10-26)- Feature aditions release, Update mandatory
### Fixes
- **Issue #42**: Floppy Emulator now supports read/write operations on odd memory addresses.
- **Issue #41**: Compatibility with Atari ST computers lacking a physical floppy drive.
- **Issue #28**: Improved Configurator's Wi-Fi reconnection mechanism.

### Changed
- **Issue #43**: Enhanced clarity in description texts.
- **Issue #31**: Transitioned from asynchronous to synchronous commands for increased reliability and performance.

### New Features
- **Issue #44**: Updated Wi-Fi menu requires user to disconnect from the current network before joining a new one.
- **Issue #40**: New microSD card status indicator, complementing the existing network status bar.
- **Issue #39**: Boot into 'SIDECART.TOS' post-reset for direct access to the Configurator.
- **Issue #36**: Display of the WiFi module's MAC address.
- **Issue #16**: Signal new firmware versions with a blinking exclamation mark.
- **Issue #12**: Access to a cloud-hosted, continuously updated database of Atari ST floppy images. The database is growing; please report any discrepancies.

## 0.0.10 (2023-10-13) - Feature aditions release, Update recommended
### Fixes
No fixes in this release

### Changed
- Atari ST firmware app now reports the meaning of the flashing LED.
- Atari ST firmware app now allows to toggle the Delay/Ripper mode from the menu.

### Feature aditions
- issue #7: Floppy drive emulation of .ST files now supports Read and Write in a PREVIEW mode to get feedback from the community. I have found some glitches and sometimes it fails. Please report any issues you find. Please note that this feature can make you loss the content of your content. Use it at your own risk.
- issue #25: New SAFE_CONFIG_REBOOT parameter. If true, pressing the SELECT button will not cause an immediate reboot. Instead, the RP2040 will change the board's status for the subsequent Atari ST power cycle, ensuring a smooth transition without disrupting ongoing processes. If false, the RP2040 will reboot immediately, as it did before.


## 0.0.9 (2023-09-29) - Bug fix release, Update recommended
### Fixes
- issue #9: Delete key now deletes in open fields.
- issue #8: Configuration mode now always looks for Wifi networks.

### Changed
- Atari ST firmware app now resets the computer when leaving the application.
- Atari ST firmware app now also uses shortcut keys for the menu, not only numerical.
- Release two versions of the firmware app, one with debug traces and other without.

### Feature aditions
- issue #6: 'Ultimate-Ripper' behaviour implement. New DELAY_ROM_EMULATION flag.
- issue #7: Read-only floppy drive emulation of .ST files is now supported as a PREVIEW feature to get feedback from the community. I have found some glitches and sometimes it fails. Please report any issues you find.

## 0.0.8 (2023-09-15) - Feature release
- First version
