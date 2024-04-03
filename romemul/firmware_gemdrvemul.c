#include "include/firmware_gemdrvemul.h"

const uint16_t gemdrvemulROM[] = {
    0xABCD, 0xEF42, 0x0000, 0x0000, 0x08FA, 0x001E, 0x0000, 0x0000, 0x9C16, 0x5882, 0x0000, 0x0022, 0x454D, 0x554C, 0x0000, 0x7E3F,
    0x3F3C, 0x0025, 0x4E4E, 0x548F, 0x51CF, 0xFFF6, 0x4879, 0x000B, 0xFFFF, 0x4E4D, 0x588F, 0x0800, 0x0001, 0x6700, 0x0004, 0x4E75,
    0x4879, 0x00FA, 0x122E, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x4AB9, 0x00FB, 0x0018, 0x6704, 0x6100, 0x02A6, 0x4AB9, 0x00FB, 0x218C,
    0x6610, 0x4879, 0x00FA, 0x1292, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x600E, 0x4879, 0x00FA, 0x1271, 0x3F3C, 0x0009, 0x4E41, 0x5C8F,
    0x4879, 0x00FA, 0x137F, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x6100, 0x00F2, 0x6100, 0x0130, 0x4879, 0x00FA, 0x12B5, 0x3F3C, 0x0009,
    0x4E41, 0x5C8F, 0x6100, 0x01DE, 0x4A40, 0x6600, 0x00C0, 0x4879, 0x00FA, 0x137F, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x4879, 0x00FA,
    0x1336, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x6100, 0x03A6, 0x4879, 0x00FA, 0x137F, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x4879, 0x00FA,
    0x1322, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x1039, 0x00FB, 0x2187, 0x0280, 0x0000, 0x00FF, 0x3F00, 0x3F3C, 0x0002, 0x4E41, 0x588F,
    0x2F3C, 0x0002, 0x003A, 0x4E41, 0x588F, 0x2F3C, 0x0002, 0x005C, 0x4E41, 0x588F, 0x2F3C, 0x0002, 0x0020, 0x4E41, 0x588F, 0x2F3C,
    0x0002, 0x0020, 0x4E41, 0x588F, 0x2F3C, 0x0002, 0x0020, 0x4E41, 0x588F, 0x4879, 0x00FA, 0x137F, 0x3F3C, 0x0009, 0x4E41, 0x5C8F,
    0x6100, 0x033A, 0x4879, 0x00FA, 0x125F, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x6100, 0x034C, 0x4A40, 0x6600, 0x0012, 0x4879, 0x00FA,
    0x137F, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x4E75, 0x4879, 0x00FA, 0x1353, 0x3F3C, 0x0009, 0x4E41, 0x3F3C, 0x0007, 0x4E41, 0x508F,
    0x4E75, 0x3F3C, 0x0030, 0x4E41, 0x548F, 0xC0BC, 0x0000, 0xFFFF, 0x0C78, 0x00FC, 0x0004, 0x6608, 0x3239, 0x00FC, 0x0002, 0x6006,
    0x3239, 0x00E0, 0x0002, 0xC2BC, 0x0000, 0xFFFF, 0x4841, 0x8081, 0x263C, 0x0000, 0x0001, 0x2800, 0x7208, 0x303C, 0x0487, 0x6100,
    0x0E34, 0x4E75, 0x4879, 0x00FA, 0x124E, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x2039, 0x00FB, 0x217C, 0x4840, 0xC0BC, 0x0000, 0xFFFF,
    0x3200, 0xE049, 0x3400, 0xC47C, 0x00FF, 0xD27C, 0x0030, 0x3001, 0x0280, 0x0000, 0x00FF, 0x3F00, 0x3F3C, 0x0002, 0x4E41, 0x588F,
    0x2F3C, 0x0002, 0x002E, 0x4E41, 0x588F, 0x3002, 0x4840, 0xE188, 0x7201, 0x48E7, 0xFF00, 0x2C00, 0xE19E, 0x2606, 0x0801, 0x0000,
    0x6704, 0xE88B, 0x6002, 0xE19E, 0x0283, 0x0000, 0x000F, 0x0C83, 0x0000, 0x000A, 0x6D08, 0x0683, 0x0000, 0x0037, 0x6006, 0x0683,
    0x0000, 0x0030, 0x3F03, 0x3F3C, 0x0002, 0x4E41, 0x588F, 0x51C9, 0xFFCA, 0x4CDF, 0x00FF, 0x2F3C, 0x0002, 0x002E, 0x4E41, 0x588F,
    0x2F3C, 0x0002, 0x002E, 0x4E41, 0x588F, 0x2F3C, 0x0002, 0x002E, 0x4E41, 0x588F, 0x4879, 0x00FA, 0x137F, 0x3F3C, 0x0009, 0x4E41,
    0x5C8F, 0x4E75, 0x2E39, 0x00FB, 0x0008, 0x3F07, 0x7200, 0x303C, 0x0400, 0x6100, 0x0D60, 0x3E1F, 0x4A40, 0x665E, 0x4A79, 0x00FB,
    0x000C, 0x6704, 0x7000, 0x4E75, 0x3007, 0x0280, 0x0000, 0x00FF, 0x80FC, 0x000A, 0x0280, 0x00FF, 0x00FF, 0x0680, 0x0030, 0x0030,
    0x4840, 0x3F00, 0x4840, 0x3F00, 0x3F3C, 0x0002, 0x4E41, 0x588F, 0x3F3C, 0x0002, 0x4E41, 0x588F, 0x4879, 0x00FA, 0x137C, 0x3F3C,
    0x0009, 0x4E41, 0x5C8F, 0x3C3C, 0x0032, 0x3F3C, 0x0025, 0x4E4E, 0x548F, 0x51CE, 0xFFF6, 0x51CF, 0xFF92, 0x70FF, 0x4E75, 0x4AB9,
    0x00FB, 0x0010, 0x6712, 0x4879, 0x00FA, 0x1308, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x6000, 0x0108, 0x4879, 0x00FA, 0x12D1, 0x3F3C,
    0x0009, 0x4E41, 0x5C8F, 0x2E39, 0x00FB, 0x0008, 0x3007, 0x0280, 0x0000, 0x00FF, 0x80FC, 0x000A, 0x0280, 0x00FF, 0x00FF, 0x0680,
    0x0030, 0x0030, 0x4840, 0x3F00, 0x4840, 0x3F00, 0x3F3C, 0x0002, 0x4E41, 0x588F, 0x3F3C, 0x0002, 0x4E41, 0x588F, 0x4879, 0x00FA,
    0x137C, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x2F07, 0x3E3C, 0x0032, 0x3F3C, 0x0025, 0x4E4E, 0x548F, 0x51CF, 0xFFF6, 0x2E1F, 0x4AB9,
    0x00FB, 0x0014, 0x6608, 0x51CF, 0xFFA4, 0x6000, 0x00D4, 0x4879, 0x00FA, 0x137F, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x4879, 0x00FA,
    0x12EE, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x2E39, 0x00FB, 0x0008, 0x3007, 0x0280, 0x0000, 0x00FF, 0x80FC, 0x000A, 0x0280, 0x00FF,
    0x00FF, 0x0680, 0x0030, 0x0030, 0x4840, 0x3F00, 0x4840, 0x3F00, 0x3F3C, 0x0002, 0x4E41, 0x588F, 0x3F3C, 0x0002, 0x4E41, 0x588F,
    0x4879, 0x00FA, 0x137C, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x2F07, 0x3E3C, 0x0032, 0x3F3C, 0x0025, 0x4E4E, 0x548F, 0x51CF, 0xFFF6,
    0x2E1F, 0x4AB9, 0x00FB, 0x0010, 0x6606, 0x51CF, 0xFFA4, 0x6050, 0x4879, 0x00FA, 0x137F, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x4879,
    0x00FB, 0x0010, 0x3F3C, 0x0006, 0x3F3C, 0x0019, 0x4E4E, 0x508F, 0x7000, 0x3F3C, 0x0017, 0x4E4E, 0x548F, 0xD0BC, 0x3C00, 0x0000,
    0x2E00, 0x3F07, 0x3F3C, 0x002D, 0x4E41, 0x588F, 0x4847, 0x3F07, 0x3F3C, 0x002B, 0x4E41, 0x588F, 0x7000, 0x4E75, 0x7000, 0x4E75,
    0x4879, 0x00FA, 0x1384, 0x3F3C, 0x0009, 0x4E41, 0x5C8F, 0x70FF, 0x4E75, 0x303C, 0x0405, 0x7200, 0x6000, 0x0B7A, 0x3039, 0x00FB,
    0x218A, 0x7201, 0xE1A9, 0x2038, 0x04C2, 0xD081, 0x21C0, 0x04C2, 0x3F39, 0x00FB, 0x218A, 0x3F3C, 0x000E, 0x4E41, 0x588F, 0x4E75,
    0x2F3C, 0x00FA, 0x04DA, 0x3F3C, 0x0021, 0x3F3C, 0x0005, 0x4E4D, 0x508F, 0x2600, 0x283C, 0x00FA, 0x04D6, 0x7208, 0x303C, 0x0401,
    0x6100, 0x0B32, 0x4A40, 0x6602, 0x4E75, 0x70FF, 0x4E75, 0x5842, 0x5241, 0x5344, 0x4744, 0x0000, 0x0000, 0x0839, 0x0000, 0x00FB,
    0x0020, 0x6708, 0x2F39, 0x00FA, 0x04D6, 0x4E75, 0x0817, 0x0005, 0x6704, 0x204F, 0x6004, 0x4E68, 0x5D88, 0x4A79, 0x0000, 0x059E,
    0x6702, 0x5448, 0x48E7, 0x3F3E, 0x3628, 0x0006, 0xB67C, 0x0036, 0x6700, 0x00A8, 0xB67C, 0x0039, 0x6700, 0x00DC, 0xB67C, 0x003A,
    0x6700, 0x0136, 0xB67C, 0x003B, 0x6700, 0x0190, 0xB67C, 0x003C, 0x6700, 0x029A, 0xB67C, 0x0047, 0x6700, 0x01CC, 0xB67C, 0x003D,
    0x6700, 0x01F4, 0xB67C, 0x003E, 0x6700, 0x0250, 0xB67C, 0x0056, 0x6700, 0x0342, 0xB67C, 0x0057, 0x6700, 0x0458, 0xB67C, 0x003F,
    0x6700, 0x04EE, 0xB67C, 0x0040, 0x6700, 0x05A4, 0xB67C, 0x0043, 0x6700, 0x03D8, 0xB67C, 0x004E, 0x6700, 0x06AA, 0xB67C, 0x004F,
    0x6700, 0x073C, 0xB67C, 0x004B, 0x6700, 0x077E, 0xB67C, 0x0041, 0x6700, 0x02A0, 0xB67C, 0x0042, 0x6700, 0x037E, 0x4CDF, 0x7CFC,
    0x2F39, 0x00FA, 0x04D6, 0x4E75, 0x2628, 0x0008, 0x7204, 0x303C, 0x041A, 0x6100, 0x0A40, 0x6000, 0xFFE4, 0x3628, 0x0008, 0x5343,
    0xB679, 0x00FB, 0x218A, 0x6600, 0xFFD4, 0x2868, 0x000A, 0x7202, 0x303C, 0x0436, 0x6100, 0x0A1E, 0x2039, 0x00FB, 0x2140, 0x4A80,
    0x660E, 0x2A79, 0x00FB, 0x2144, 0x28DD, 0x28DD, 0x28DD, 0x28DD, 0x4CDF, 0x7CFC, 0x4E73, 0x2868, 0x0008, 0x0C2C, 0x003A, 0x0001,
    0x660E, 0x1014, 0xB039, 0x00FB, 0x2187, 0x6600, 0xFF90, 0x602A, 0x303C, 0x0403, 0x7200, 0x6100, 0x09DC, 0x3F3C, 0x0019, 0x4E41,
    0x548F, 0x2F00, 0x303C, 0x0405, 0x7200, 0x6100, 0x09C8, 0x201F, 0xB079, 0x00FB, 0x218A, 0x6600, 0xFF64, 0x303C, 0x0439, 0x720C,
    0x2C3C, 0x0000, 0x0100, 0x6100, 0x0ADA, 0x3039, 0x00FB, 0x20F8, 0x48C0, 0x4CDF, 0x7CFC, 0x4E73, 0x2868, 0x0008, 0x0C2C, 0x003A,
    0x0001, 0x660E, 0x1014, 0xB039, 0x00FB, 0x2187, 0x6600, 0xFF2E, 0x602A, 0x303C, 0x0403, 0x7200, 0x6100, 0x097A, 0x3F3C, 0x0019,
    0x4E41, 0x548F, 0x2F00, 0x303C, 0x0405, 0x7200, 0x6100, 0x0966, 0x201F, 0xB079, 0x00FB, 0x218A, 0x6600, 0xFF02, 0x303C, 0x043A,
    0x720C, 0x2C3C, 0x0000, 0x0100, 0x6100, 0x0A78, 0x3039, 0x00FB, 0x20FC, 0x48C0, 0x4CDF, 0x7CFC, 0x4E73, 0x2868, 0x0008, 0x303C,
    0x0403, 0x7200, 0x6100, 0x092E, 0x3F3C, 0x0019, 0x4E41, 0x548F, 0x2F00, 0x303C, 0x0405, 0x7200, 0x6100, 0x091A, 0x201F, 0xB079,
    0x00FB, 0x218A, 0x6600, 0xFEB6, 0x303C, 0x043B, 0x720C, 0x2C3C, 0x0000, 0x0100, 0x6100, 0x0A2C, 0x3039, 0x00FB, 0x00DC, 0x48C0,
    0x4CDF, 0x7CFC, 0x4E73, 0x2868, 0x0008, 0x3628, 0x000C, 0x5343, 0xB679, 0x00FB, 0x218A, 0x6600, 0xFE84, 0x303C, 0x0447, 0x720C,
    0x2C3C, 0x0000, 0x0100, 0x6100, 0x09FA, 0x303C, 0x0000, 0x48C0, 0x4CDF, 0x7CFC, 0x4E73, 0x2868, 0x0008, 0x3628, 0x000C, 0x0C2C,
    0x003A, 0x0001, 0x660E, 0x1014, 0xB039, 0x00FB, 0x2187, 0x6600, 0xFE4C, 0x602A, 0x303C, 0x0403, 0x7200, 0x6100, 0x0898, 0x3F3C,
    0x0019, 0x4E41, 0x548F, 0x2F00, 0x303C, 0x0405, 0x7200, 0x6100, 0x0884, 0x201F, 0xB079, 0x00FB, 0x218A, 0x6600, 0xFE20, 0x303C,
    0x043D, 0x720C, 0x2C3C, 0x0000, 0x0100, 0x6100, 0x0996, 0x2039, 0x00FB, 0x00E0, 0x4CDF, 0x7CFC, 0x4E73, 0x3628, 0x0008, 0xC6BC,
    0x0000, 0xFFFF, 0xC6BC, 0x0000, 0xFFFF, 0xB6B9, 0x00FB, 0x2180, 0x6D00, 0xFDEA, 0x7202, 0x303C, 0x043E, 0x6100, 0x0838, 0x3039,
    0x00FB, 0x20F4, 0x48C0, 0x4CDF, 0x7CFC, 0x4E73, 0x2868, 0x0008, 0x3628, 0x000C, 0x0C2C, 0x003A, 0x0001, 0x660E, 0x1014, 0xB039,
    0x00FB, 0x2187, 0x6600, 0xFDB6, 0x602A, 0x303C, 0x0403, 0x7200, 0x6100, 0x0802, 0x3F3C, 0x0019, 0x4E41, 0x548F, 0x2F00, 0x303C,
    0x0405, 0x7200, 0x6100, 0x07EE, 0x201F, 0xB079, 0x00FB, 0x218A, 0x6600, 0xFD8A, 0x303C, 0x043C, 0x720C, 0x2C3C, 0x0000, 0x0100,
    0x6100, 0x0900, 0x3039, 0x00FB, 0x2120, 0x48C0, 0x4CDF, 0x7CFC, 0x4E73, 0x2868, 0x0008, 0x0C2C, 0x003A, 0x0001, 0x660E, 0x1014,
    0xB039, 0x00FB, 0x2187, 0x6600, 0xFD54, 0x602A, 0x303C, 0x0403, 0x7200, 0x6100, 0x07A0, 0x3F3C, 0x0019, 0x4E41, 0x548F, 0x2F00,
    0x303C, 0x0405, 0x7200, 0x6100, 0x078C, 0x201F, 0xB079, 0x00FB, 0x218A, 0x6600, 0xFD28, 0x303C, 0x0441, 0x720C, 0x2C3C, 0x0000,
    0x0100, 0x6100, 0x089E, 0x3039, 0x00FB, 0x2124, 0x48C0, 0x4CDF, 0x7CFC, 0x4E73, 0x2A68, 0x000A, 0x2C68, 0x000E, 0x0C2C, 0x003A,
    0x0001, 0x660E, 0x1014, 0xB039, 0x00FB, 0x2187, 0x6600, 0xFCEE, 0x602A, 0x303C, 0x0403, 0x7200, 0x6100, 0x073A, 0x3F3C, 0x0019,
    0x4E41, 0x548F, 0x2F00, 0x303C, 0x0405, 0x7200, 0x6100, 0x0726, 0x201F, 0xB079, 0x00FB, 0x218A, 0x6600, 0xFCC2, 0x4FEF, 0xFF00,
    0x284F, 0x363C, 0x007F, 0x18DD, 0x51CB, 0xFFFC, 0x363C, 0x007F, 0x18DE, 0x51CB, 0xFFFC, 0x284F, 0x303C, 0x0456, 0x720C, 0x2C3C,
    0x0000, 0x0100, 0x6100, 0x081C, 0x4FEF, 0x0100, 0x2039, 0x00FB, 0x2130, 0x4CDF, 0x7CFC, 0x4E73, 0x2828, 0x0008, 0x3628, 0x000C,
    0x3A28, 0x000E, 0xC6BC, 0x0000, 0xFFFF, 0xB6B9, 0x00FB, 0x2180, 0x6D00, 0xFC6A, 0x720C, 0x303C, 0x0442, 0x6100, 0x06B8, 0x2039,
    0x00FB, 0x2128, 0x4CDF, 0x7CFC, 0x4E73, 0x2868, 0x0008, 0x3628, 0x000C, 0x3828, 0x000E, 0x0C2C, 0x003A, 0x0001, 0x660E, 0x1014,
    0xB039, 0x00FB, 0x2187, 0x6600, 0xFC34, 0x602A, 0x303C, 0x0403, 0x7200, 0x6100, 0x0680, 0x3F3C, 0x0019, 0x4E41, 0x548F, 0x2F00,
    0x303C, 0x0405, 0x7200, 0x6100, 0x066C, 0x201F, 0xB079, 0x00FB, 0x218A, 0x6600, 0xFC08, 0x303C, 0x0443, 0x720C, 0x2C3C, 0x0000,
    0x0080, 0x6100, 0x077E, 0x2039, 0x00FB, 0x212C, 0x4CDF, 0x7CFC, 0x4E73, 0x2868, 0x0008, 0x3828, 0x000C, 0x3628, 0x000E, 0x2A2C,
    0x0000, 0x2C2C, 0x0004, 0xC6BC, 0x0000, 0xFFFF, 0xC8BC, 0x0000, 0xFFFF, 0x0C2C, 0x003A, 0x0001, 0x660E, 0x1014, 0xB039, 0x00FB,
    0x2187, 0x6600, 0xFBB8, 0x602A, 0x303C, 0x0403, 0x7200, 0x6100, 0x0604, 0x3F3C, 0x0019, 0x4E41, 0x548F, 0x2F00, 0x303C, 0x0405,
    0x7200, 0x6100, 0x05F0, 0x201F, 0xB079, 0x00FB, 0x218A, 0x6600, 0xFB8C, 0x2F0C, 0x7210, 0x303C, 0x0457, 0x6100, 0x05D8, 0x285F,
    0x4DF9, 0x00FB, 0x2138, 0x196E, 0x0002, 0x0000, 0x196E, 0x0003, 0x0001, 0x4DF9, 0x00FB, 0x2134, 0x196E, 0x0002, 0x0002, 0x196E,
    0x0003, 0x0003, 0x2039, 0x00FB, 0x213C, 0x4CDF, 0x7CFC, 0x4E73, 0x3628, 0x0008, 0x2828, 0x000A, 0x2868, 0x000E, 0xC6BC, 0x0000,
    0xFFFF, 0xB6B9, 0x00FB, 0x2180, 0x6D00, 0xFB32, 0x6106, 0x4CDF, 0x7CFC, 0x4E73, 0x2A04, 0x4286, 0x4AB9, 0x00FB, 0x218C, 0x6624,
    0x2A79, 0x0000, 0x04C6, 0x48ED, 0x00F8, 0x0100, 0x720C, 0x303C, 0x0481, 0x6100, 0x0560, 0x2A79, 0x0000, 0x04C6, 0x4CED, 0x00F8,
    0x0100, 0x6012, 0x48E7, 0x1F00, 0x720C, 0x303C, 0x0481, 0x6100, 0x0544, 0x4CDF, 0x00F8, 0x4A40, 0x6704, 0x70BF, 0x604E, 0x2039,
    0x00FB, 0x00E4, 0x48C0, 0x6B44, 0x4A80, 0x673E, 0x4BF9, 0x00FB, 0x00E8, 0x2E0C, 0x0807, 0x0000, 0x670C, 0x2E00, 0x5387, 0x18DD,
    0x51CF, 0xFFFC, 0x6014, 0x2E00, 0xE28F, 0x5387, 0x38DD, 0x51CF, 0xFFFC, 0x0800, 0x0000, 0x6702, 0x18DD, 0xDC80, 0xB0BC, 0x0000,
    0x2000, 0x6606, 0x9A80, 0x6A00, 0xFF70, 0x2006, 0x4E75, 0x3628, 0x0008, 0x2828, 0x000A, 0x2868, 0x000E, 0xC6BC, 0x0000, 0xFFFF,
    0xB6B9, 0x00FB, 0x2180, 0x6D00, 0xFA74, 0x6106, 0x4CDF, 0x7CFC, 0x4E73, 0x2A04, 0x4286, 0x3E3C, 0x0003, 0x4A47, 0x6606, 0x70BF,
    0x6000, 0x00E0, 0x4AB9, 0x00FB, 0x218C, 0x662A, 0x2A79, 0x0000, 0x04C6, 0x48ED, 0x10F8, 0x0100, 0x303C, 0x0488, 0x720C, 0x2C3C,
    0x0000, 0x0800, 0x6100, 0x05BC, 0x2A79, 0x0000, 0x04C6, 0x4CED, 0x10F8, 0x0100, 0x6018, 0x48E7, 0x1F08, 0x303C, 0x0488, 0x720C,
    0x2C3C, 0x0000, 0x0800, 0x6100, 0x059A, 0x4CDF, 0x10F8, 0x4A40, 0x6706, 0x70BF, 0x6000, 0x008C, 0x4280, 0x4281, 0x5347, 0x2439,
    0x00FB, 0x20E8, 0x4A82, 0x670A, 0x5382, 0x121C, 0xD081, 0x51CA, 0xFFFA, 0xB0B9, 0x00FB, 0x20EC, 0x6680, 0x4AB9, 0x00FB, 0x218C,
    0x662A, 0x2A79, 0x0000, 0x04C6, 0x48ED, 0x10F8, 0x0100, 0x2839, 0x00FB, 0x20E8, 0x7208, 0x303C, 0x0489, 0x6100, 0x0418, 0x2A79,
    0x0000, 0x04C6, 0x4CED, 0x10F8, 0x0100, 0x6018, 0x48E7, 0x1F08, 0x2839, 0x00FB, 0x20E8, 0x7208, 0x303C, 0x0489, 0x6100, 0x03F6,
    0x4CDF, 0x10F8, 0x2039, 0x00FB, 0x20E8, 0x48C0, 0x6B14, 0x4A80, 0x670E, 0xDC80, 0xB07C, 0x0800, 0x6606, 0x9A80, 0x6A00, 0xFF18,
    0x2006, 0x4E75, 0x2868, 0x0008, 0x3828, 0x000C, 0x0C2C, 0x003A, 0x0001, 0x6600, 0x000C, 0x1014, 0xB039, 0x00FB, 0x2187, 0x672A,
    0x303C, 0x0403, 0x7200, 0x6100, 0x03AC, 0x3F3C, 0x0019, 0x4E41, 0x548F, 0x2F00, 0x303C, 0x0405, 0x7200, 0x6100, 0x0398, 0x201F,
    0xB079, 0x00FB, 0x218A, 0x6600, 0xF934, 0x303C, 0x0403, 0x7200, 0x6100, 0x0382, 0x3F3C, 0x002F, 0x4E41, 0x548F, 0x2F00, 0x303C,
    0x0405, 0x7200, 0x6100, 0x036E, 0x2617, 0x2A0C, 0x303C, 0x044E, 0x720C, 0x2C3C, 0x0000, 0x00C0, 0x6100, 0x0488, 0x2A5F, 0x3039,
    0x00FB, 0x00A4, 0x48C0, 0x49F9, 0x00FB, 0x00A8, 0x243C, 0x0000, 0x002B, 0x1ADC, 0x51CA, 0xFFFC, 0x4CDF, 0x7CFC, 0x4E73, 0x303C,
    0x0403, 0x7200, 0x6100, 0x032E, 0x3F3C, 0x002F, 0x4E41, 0x548F, 0x2F00, 0x303C, 0x0405, 0x7200, 0x6100, 0x031A, 0x2617, 0x7204,
    0x303C, 0x048A, 0x6100, 0x030E, 0x2039, 0x00FB, 0x00D4, 0x4A80, 0x6710, 0x2600, 0x7204, 0x303C, 0x044F, 0x6100, 0x02F8, 0x6000,
    0xFF9C, 0x201F, 0x6000, 0xF896, 0x2808, 0x3628, 0x0008, 0x2868, 0x000A, 0x2A0C, 0x2C28, 0x000E, 0x2E28, 0x0012, 0x0C2C, 0x003A,
    0x0001, 0x660E, 0x1014, 0xB039, 0x00FB, 0x2187, 0x6600, 0xF86E, 0x602A, 0x303C, 0x0403, 0x7200, 0x6100, 0x02BA, 0x3F3C, 0x0019,
    0x4E41, 0x548F, 0x2F00, 0x303C, 0x0405, 0x7200, 0x6100, 0x02A6, 0x201F, 0xB079, 0x00FB, 0x218A, 0x6600, 0xF842, 0x7214, 0x303C,
    0x044B, 0x6100, 0x0290, 0x0C79, 0x0000, 0x00FB, 0x2164, 0x670C, 0x0C79, 0x0003, 0x00FB, 0x2164, 0x6600, 0xF822, 0x4243, 0x303C,
    0x043D, 0x720C, 0x2C3C, 0x0000, 0x0100, 0x6100, 0x0396, 0x2039, 0x00FB, 0x00E0, 0x6B00, 0x0224, 0x3600, 0x283C, 0x0000, 0x001C,
    0x4AB9, 0x00FB, 0x218C, 0x661A, 0x2879, 0x0000, 0x04C6, 0x49EC, 0x0200, 0x6100, 0xFCC0, 0x2879, 0x0000, 0x04C6, 0x49EC, 0x0200,
    0x6010, 0x9FFC, 0x0000, 0x001C, 0x284F, 0x2F0C, 0x6100, 0xFCA6, 0x285F, 0xB0BC, 0x0000, 0x001C, 0x6600, 0x01E6, 0x0C6C, 0x601A,
    0x0000, 0x6600, 0x01DC, 0x303C, 0x0484, 0x720C, 0x2C3C, 0x0000, 0x001C, 0x6100, 0x032E, 0x4AB9, 0x00FB, 0x218C, 0x6706, 0xDFFC,
    0x0000, 0x001C, 0x303C, 0x0403, 0x7200, 0x6100, 0x01E8, 0x2079, 0x00FB, 0x2168, 0x4868, 0x0012, 0x4868, 0x000E, 0x42A7, 0x3F3C,
    0x0005, 0x3F3C, 0x004B, 0x4E41, 0x4FEF, 0x0010, 0x2840, 0x303C, 0x0405, 0x7200, 0x6100, 0x01BE, 0x4BF9, 0x00FB, 0x2100, 0x262D,
    0x0002, 0x282D, 0x0006, 0x2A2D, 0x000A, 0x2C2D, 0x000E, 0x2E0C, 0xDEBC, 0x0000, 0x0100, 0x2947, 0x0008, 0x2943, 0x000C, 0xDE83,
    0x2947, 0x0010, 0x2944, 0x0014, 0xDE84, 0x2947, 0x0018, 0x2945, 0x001C, 0x303C, 0x0483, 0x720C, 0x2C3C, 0x0000, 0x0100, 0x6100,
    0x02A2, 0x4BF9, 0x00FB, 0x2100, 0x49F9, 0x00FB, 0x2278, 0x286C, 0x0008, 0x282D, 0x0002, 0xD8AD, 0x0006, 0xD8AD, 0x000E, 0xD8BC,
    0x0000, 0xFFFF, 0x2639, 0x00FB, 0x00E0, 0x6100, 0xFBC8, 0x2639, 0x00FB, 0x00E0, 0x7202, 0x303C, 0x043E, 0x6100, 0x0138, 0x3039,
    0x00FB, 0x20F4, 0x48C0, 0x6B00, 0x00F2, 0x4BF9, 0x00FB, 0x2278, 0x2A6D, 0x0008, 0x220D, 0x2C4D, 0x49F9, 0x00FB, 0x2100, 0xDBEC,
    0x0002, 0xDBEC, 0x0006, 0xDBEC, 0x000E, 0x4A95, 0x671A, 0x7000, 0xDDDD, 0xD396, 0x101D, 0x6710, 0xB03C, 0x0001, 0x6606, 0xDCFC,
    0x00FE, 0x60F0, 0xDCC0, 0x60EA, 0x2879, 0x00FB, 0x2278, 0x2A6C, 0x0018, 0x2A2C, 0x001C, 0x6100, 0x00D0, 0x0C79, 0x0003, 0x00FB,
    0x2164, 0x6700, 0x0090, 0x2079, 0x00FB, 0x2168, 0x317C, 0x0006, 0x0008, 0x2039, 0x00FB, 0x217C, 0xC0BC, 0x0000, 0xFFFF, 0xB07C,
    0x1500, 0x6228, 0x263C, 0x0000, 0x0000, 0x282F, 0x002E, 0x7208, 0x303C, 0x0487, 0x6100, 0x009E, 0x2F7C, 0x00FA, 0x0F80, 0x002E,
    0x2079, 0x00FB, 0x2168, 0x317C, 0x0004, 0x0008, 0x42A8, 0x000A, 0x2179, 0x00FB, 0x2278, 0x000E, 0x42A8, 0x0012, 0x6000, 0xF61E,
    0x48E7, 0x7FFE, 0x303C, 0x0403, 0x7200, 0x6100, 0x0068, 0x2F39, 0x00FB, 0x2278, 0x3F3C, 0x0049, 0x4E41, 0x5C8F, 0x303C, 0x0405,
    0x7200, 0x6100, 0x0050, 0x48C0, 0x4CDF, 0x7FFE, 0x2F39, 0x00FB, 0x2178, 0x4E75, 0x2039, 0x00FB, 0x2278, 0x4CDF, 0x7CFC, 0x4E73,
    0x4AB9, 0x00FB, 0x218C, 0x6706, 0xDFFC, 0x0000, 0x001C, 0x2639, 0x00FB, 0x00E0, 0x7202, 0x303C, 0x043E, 0x6100, 0x0018, 0x3039,
    0x00FB, 0x20F4, 0x48C0, 0x60D2, 0x4A85, 0x6706, 0x421D, 0x5385, 0x66FA, 0x4E75, 0x205F, 0x2E3C, 0x0000, 0x002A, 0x4AB9, 0x00FB,
    0x218C, 0x6608, 0x2479, 0x0000, 0x04C6, 0x6006, 0x4FEF, 0xFFD6, 0x244F, 0x264A, 0x43F9, 0x00FA, 0x10F8, 0xE44F, 0x5347, 0x24D9,
    0x51CF, 0xFFFC, 0x2448, 0x2439, 0x00FB, 0x0004, 0x5841, 0x207C, 0x00FB, 0x0000, 0x4840, 0x1039, 0x00FB, 0xABCD, 0x4840, 0x2248,
    0xD2C0, 0x1011, 0x2008, 0x8041, 0x2240, 0x1011, 0x4A41, 0x6700, 0x009C, 0x2008, 0x8042, 0x2240, 0x1011, 0xB27C, 0x0002, 0x6700,
    0x008C, 0x4842, 0x2008, 0x8042, 0x2240, 0x1011, 0xB27C, 0x0004, 0x6700, 0x007A, 0x2008, 0x8043, 0x2240, 0x1011, 0xB27C, 0x0006,
    0x6700, 0x006A, 0x4843, 0x2008, 0x8043, 0x2240, 0x1011, 0xB27C, 0x0008, 0x6700, 0x0058, 0x2008, 0x8044, 0x2240, 0x1011, 0xB27C,
    0x000A, 0x6700, 0x0048, 0x4844, 0x2008, 0x8044, 0x2240, 0x1011, 0xB27C, 0x000C, 0x6736, 0x2008, 0x8045, 0x2240, 0x1011, 0xB27C,
    0x000E, 0x6728, 0x4845, 0x2008, 0x8045, 0x2240, 0x1011, 0xB27C, 0x0010, 0x6718, 0x2008, 0x8046, 0x2240, 0x1011, 0xB27C, 0x0012,
    0x670A, 0x4846, 0x2008, 0x8046, 0x2240, 0x1011, 0x4842, 0x2E3C, 0x000F, 0xFFFF, 0x7000, 0x4ED3, 0xB4B9, 0x00FB, 0x0000, 0x6706,
    0x5387, 0x66F4, 0x5380, 0x2E3C, 0x0000, 0x0001, 0x5387, 0x66FC, 0x4AB9, 0x00FB, 0x218C, 0x6704, 0x4FEF, 0x002A, 0x4ED2, 0x4E71,
    0x4E71, 0x205F, 0x2E3C, 0x0000, 0x002A, 0x4AB9, 0x00FB, 0x218C, 0x6608, 0x2479, 0x0000, 0x04C6, 0x6006, 0x4FEF, 0xFFD6, 0x244F,
    0x264A, 0x43F9, 0x00FA, 0x1204, 0xE44F, 0x5347, 0x24D9, 0x51CF, 0xFFFC, 0x2448, 0x2439, 0x00FB, 0x0004, 0x5841, 0xD246, 0x5241,
    0xE249, 0xE349, 0x207C, 0x00FB, 0x0000, 0x4840, 0x1039, 0x00FB, 0xABCD, 0x4840, 0x2248, 0xD2C0, 0x1011, 0x2008, 0x8041, 0x2240,
    0x1011, 0x2008, 0x8042, 0x2240, 0x1011, 0x4842, 0x2008, 0x8042, 0x2240, 0x1011, 0x2008, 0x8043, 0x2240, 0x1011, 0x4843, 0x2008,
    0x8043, 0x2240, 0x1011, 0x2008, 0x8044, 0x2240, 0x1011, 0x4844, 0x2008, 0x8044, 0x2240, 0x1011, 0x2008, 0x8045, 0x2240, 0x1011,
    0x4845, 0x2008, 0x8045, 0x2240, 0x1011, 0xE24E, 0x5346, 0x200C, 0x0800, 0x0000, 0x6714, 0x161C, 0xE14B, 0x161C, 0x2008, 0x8043,
    0x2240, 0x1011, 0x51CE, 0xFFF0, 0x600E, 0x361C, 0x2008, 0x8043, 0x2240, 0x1011, 0x51CE, 0xFFF4, 0x4842, 0x2E3C, 0x000F, 0xFFFF,
    0x7000, 0x4ED3, 0xB4B9, 0x00FB, 0x0000, 0x6706, 0x5387, 0x66F4, 0x5380, 0x2E3C, 0x0000, 0x0001, 0x5387, 0x66FC, 0x4AB9, 0x00FB,
    0x218C, 0x6704, 0x4FEF, 0x002A, 0x4ED2, 0x4E71, 0x4E71, 0x5369, 0x6465, 0x6361, 0x7254, 0x2047, 0x454D, 0x4452, 0x4956, 0x4520,
    0x2D20, 0x7630, 0x2E30, 0x2E31, 0x0D0A, 0x2B0D, 0x0A00, 0x2B2D, 0x2054, 0x4F53, 0x2076, 0x6572, 0x7369, 0x6F6E, 0x3A20, 0x002B,
    0x2D20, 0x5365, 0x7420, 0x7665, 0x6374, 0x6F72, 0x732E, 0x2E2E, 0x002B, 0x2D20, 0x5573, 0x696E, 0x6720, 0x7374, 0x6163, 0x6B20,
    0x6173, 0x2074, 0x656D, 0x7020, 0x6275, 0x6666, 0x6572, 0x2E2E, 0x2E00, 0x2B2D, 0x2055, 0x7369, 0x6E67, 0x205F, 0x6473, 0x6B62,
    0x7566, 0x2061, 0x7320, 0x7465, 0x6D70, 0x2062, 0x7566, 0x6665, 0x722E, 0x2E2E, 0x002B, 0x2D20, 0x4D6F, 0x756E, 0x7469, 0x6E67,
    0x206D, 0x6963, 0x726F, 0x5344, 0x2063, 0x6172, 0x642E, 0x2E2E, 0x002B, 0x2D20, 0x4E65, 0x7477, 0x6F72, 0x6B20, 0x696E, 0x6974,
    0x6961, 0x6C69, 0x7A61, 0x7469, 0x6F6E, 0x2E2E, 0x2E00, 0x2B2D, 0x204E, 0x5450, 0x2073, 0x796E, 0x6368, 0x726F, 0x6E69, 0x7A61,
    0x7469, 0x6F6E, 0x2E2E, 0x2E00, 0x2B2D, 0x2052, 0x5443, 0x2061, 0x6C72, 0x6561, 0x6479, 0x2073, 0x7461, 0x7274, 0x6564, 0x2E0D,
    0x0A00, 0x2B2D, 0x2045, 0x6D75, 0x6C61, 0x7469, 0x6E67, 0x2064, 0x7269, 0x7665, 0x2000, 0x2B2D, 0x2047, 0x454D, 0x4452, 0x4956,
    0x4520, 0x6472, 0x6976, 0x6572, 0x206C, 0x6F61, 0x6465, 0x642E, 0x2E2E, 0x000D, 0x0A53, 0x6964, 0x6563, 0x6172, 0x7420, 0x6572,
    0x726F, 0x7220, 0x636F, 0x6D6D, 0x756E, 0x6963, 0x6174, 0x696F, 0x6E2E, 0x2052, 0x6573, 0x6574, 0x210D, 0x0A00, 0x0808, 0x004F,
    0x4B0D, 0x0A00, 0x5469, 0x6D65, 0x6F75, 0x7421, 0x0D0A, 0x0000, 0x0000, 0x0000
};
uint16_t gemdrvemulROM_length = sizeof(gemdrvemulROM) / sizeof(gemdrvemulROM[0]);

