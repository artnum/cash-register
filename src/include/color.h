#ifndef COLOR_H__
#define COLOR_H__

#include <SDL3/SDL_pixels.h>

/* IA generated color list and name */
static const SDL_Color COLORS[] = {
    {0, 0, 0},       // none
    {240, 248, 255}, // aliceblue
    {250, 235, 215}, // antiquewhite
    {0, 255, 255},   // aqua
    {127, 255, 212}, // aquamarine
    {240, 255, 255}, // azure
    {245, 245, 220}, // beige
    {255, 228, 196}, // bisque
    {0, 0, 0},       // black
    {255, 235, 205}, // blanchedalmond
    {0, 0, 255},     // blue
    {138, 43, 226},  // blueviolet
    {165, 42, 42},   // brown
    {222, 184, 135}, // burlywood
    {95, 158, 160},  // cadetblue
    {127, 255, 0},   // chartreuse
    {210, 105, 30},  // chocolate
    {255, 127, 80},  // coral
    {100, 149, 237}, // cornflowerblue
    {255, 248, 220}, // cornsilk
    {220, 20, 60},   // crimson
    {0, 255, 255},   // cyan
    {0, 0, 139},     // darkblue
    {0, 139, 139},   // darkcyan
    {184, 134, 11},  // darkgoldenrod
    {169, 169, 169}, // darkgray
    {0, 100, 0},     // darkgreen
    {169, 169, 169}, // darkgrey
    {189, 183, 107}, // darkkhaki
    {139, 0, 139},   // darkmagenta
    {85, 107, 47},   // darkolivegreen
    {255, 140, 0},   // darkorange
    {153, 50, 204},  // darkorchid
    {139, 0, 0},     // darkred
    {233, 150, 122}, // darksalmon
    {143, 188, 143}, // darkseagreen
    {72, 61, 139},   // darkslateblue
    {47, 79, 79},    // darkslategrey
    {0, 206, 209},   // darkturquoise
    {148, 0, 211},   // darkviolet
    {255, 20, 147},  // deeppink
    {0, 191, 255},   // deepskyblue
    {105, 105, 105}, // dimgray
    {105, 105, 105}, // dimgrey
    {30, 144, 255},  // dodgerblue
    {178, 34, 34},   // firebrick
    {255, 250, 240}, // floralwhite
    {34, 139, 34},   // forestgreen
    {255, 0, 255},   // fuchsia
    {220, 220, 220}, // gainsboro
    {248, 248, 255}, // ghostwhite
    {255, 215, 0},   // gold
    {218, 165, 32},  // goldenrod
    {128, 128, 128}, // gray
    {0, 128, 0},     // green
    {173, 255, 47},  // greenyellow
    {128, 128, 128}, // grey
    {240, 255, 240}, // honeydew
    {255, 105, 180}, // hotpink
    {205, 92, 92},   // indianred
    {75, 0, 130},    // indigo
    {255, 255, 240}, // ivory
    {240, 230, 140}, // khaki
    {230, 230, 250}, // lavender
    {255, 240, 245}, // lavenderblush
    {124, 252, 0},   // lawngreen
    {255, 250, 205}, // lemonchiffon
    {173, 216, 230}, // lightblue
    {240, 128, 128}, // lightcoral
    {224, 255, 255}, // lightcyan
    {250, 250, 210}, // lightgoldenrodyellow
    {211, 211, 211}, // lightgray
    {144, 238, 144}, // lightgreen
    {211, 211, 211}, // lightgrey
    {255, 182, 193}, // lightpink
    {255, 160, 122}, // lightsalmon
    {32, 178, 170},  // lightseagreen
    {135, 206, 250}, // lightskyblue
    {119, 136, 153}, // lightslategray
    {119, 136, 153}, // lightslategrey
    {176, 196, 222}, // lightsteelblue
    {255, 255, 224}, // lightyellow
    {0, 255, 0},     // lime
    {50, 205, 50},   // limegreen
    {250, 240, 230}, // linen
    {255, 0, 255},   // magenta
    {128, 0, 0},     // maroon
    {102, 205, 170}, // mediumaquamarine
    {0, 0, 205},     // mediumblue
    {186, 85, 211},  // mediumorchid
    {147, 112, 219}, // mediumpurple
    {60, 179, 113},  // mediumseagreen
    {123, 104, 238}, // mediumslateblue
    {0, 250, 154},   // mediumspringgreen
    {72, 209, 204},  // mediumturquoise
    {199, 21, 133},  // mediumvioletred
    {25, 25, 112},   // midnightblue
    {245, 245, 245}, // mintcream
    {255, 228, 225}, // mistyrose
    {255, 228, 181}, // moccasin
    {255, 222, 173}, // navajowhite
    {0, 0, 128},     // navy
    {253, 245, 230}, // oldlace
    {128, 128, 0},   // olive
    {107, 142, 35},  // olivedrab
    {255, 165, 0},   // orange
    {255, 69, 0},    // orangered
    {218, 112, 214}, // orchid
    {238, 232, 170}, // palegoldenrod
    {152, 251, 152}, // palegreen
    {175, 238, 238}, // paleturquoise
    {219, 112, 147}, // palevioletred
    {255, 239, 213}, // papayawhip
    {255, 218, 185}, // peachpuff
    {205, 133, 63},  // peru
    {255, 192, 203}, // pink
    {221, 160, 221}, // plum
    {176, 224, 230}, // powderblue
    {128, 0, 128},   // purple
    {255, 0, 0},     // red
    {188, 143, 143}, // rosybrown
    {65, 105, 225},  // royalblue
    {139, 69, 19},   // saddlebrown
    {250, 128, 114}, // salmon
    {244, 164, 96},  // sandybrown
    {46, 139, 87},   // seagreen
    {255, 245, 238}, // seashell
    {160, 82, 45},   // sienna
    {192, 192, 192}, // silver
    {135, 206, 235}, // skyblue
    {106, 90, 205},  // slateblue
    {112, 128, 144}, // slategray
    {112, 128, 144}, // slategrey
    {255, 250, 250}, // snow
    {0, 255, 127},   // springgreen
    {70, 130, 180},  // steelblue
    {210, 180, 140}, // tan
    {0, 128, 128},   // teal
    {216, 191, 216}, // thistle
    {255, 99, 71},   // tomato
    {64, 224, 208},  // turquoise
    {238, 130, 238}, // violet
    {245, 222, 179}, // wheat
    {255, 255, 255}, // white
    {245, 245, 245}, // whitesmoke
    {255, 255, 0},   // yellow
    {154, 205, 50}   // yellowgreen
};

enum Color {
  COLOR_NONE = 0,
  COLOR_ALICEBLUE,
  COLOR_ANTIQUEWHITE,
  COLOR_AQUA,
  COLOR_AQUAMARINE,
  COLOR_AZURE,
  COLOR_BEIGE,
  COLOR_BISQUE,
  COLOR_BLACK,
  COLOR_BLANCHEDALMOND,
  COLOR_BLUE,
  COLOR_BLUEVIOLET,
  COLOR_BROWN,
  COLOR_BURLYWOOD,
  COLOR_CADETBLUE,
  COLOR_CHARTREUSE,
  COLOR_CHOCOLATE,
  COLOR_CORAL,
  COLOR_CORNFLOWERBLUE,
  COLOR_CORNSILK,
  COLOR_CRIMSON,
  COLOR_CYAN,
  COLOR_DARKBLUE,
  COLOR_DARKCYAN,
  COLOR_DARKGOLDENROD,
  COLOR_DARKGRAY,
  COLOR_DARKGREEN,
  COLOR_DARKGREY,
  COLOR_DARKKHAKI,
  COLOR_DARKMAGENTA,
  COLOR_DARKOLIVEGREEN,
  COLOR_DARKORANGE,
  COLOR_DARKORCHID,
  COLOR_DARKRED,
  COLOR_DARKSALMON,
  COLOR_DARKSEAGREEN,
  COLOR_DARKSLATEBLUE,
  COLOR_DARKSLATEGREY,
  COLOR_DARKTURQUOISE,
  COLOR_DARKVIOLET,
  COLOR_DEEPPINK,
  COLOR_DEEPSKYBLUE,
  COLOR_DIMGRAY,
  COLOR_DIMGREY,
  COLOR_DODGERBLUE,
  COLOR_FIREBRICK,
  COLOR_FLORALWHITE,
  COLOR_FORESTGREEN,
  COLOR_FUCHSIA,
  COLOR_GAINSBORO,
  COLOR_GHOSTWHITE,
  COLOR_GOLD,
  COLOR_GOLDENROD,
  COLOR_GRAY,
  COLOR_GREEN,
  COLOR_GREENYELLOW,
  COLOR_GREY,
  COLOR_HONEYDEW,
  COLOR_HOTPINK,
  COLOR_INDIANRED,
  COLOR_INDIGO,
  COLOR_IVORY,
  COLOR_KHAKI,
  COLOR_LAVENDER,
  COLOR_LAVENDERBLUSH,
  COLOR_LAWNGREEN,
  COLOR_LEMONCHIFFON,
  COLOR_LIGHTBLUE,
  COLOR_LIGHTCORAL,
  COLOR_LIGHTCYAN,
  COLOR_LIGHTGOLDENRODYELLOW,
  COLOR_LIGHTGRAY,
  COLOR_LIGHTGREEN,
  COLOR_LIGHTGREY,
  COLOR_LIGHTPINK,
  COLOR_LIGHTSALMON,
  COLOR_LIGHTSEAGREEN,
  COLOR_LIGHTSKYBLUE,
  COLOR_LIGHTSLATEGRAY,
  COLOR_LIGHTSLATEGREY,
  COLOR_LIGHTSTEELBLUE,
  COLOR_LIGHTYELLOW,
  COLOR_LIME,
  COLOR_LIMEGREEN,
  COLOR_LINEN,
  COLOR_MAGENTA,
  COLOR_MAROON,
  COLOR_MEDIUMAQUAMARINE,
  COLOR_MEDIUMBLUE,
  COLOR_MEDIUMORCHID,
  COLOR_MEDIUMPURPLE,
  COLOR_MEDIUMSEAGREEN,
  COLOR_MEDIUMSLATEBLUE,
  COLOR_MEDIUMSPRINGGREEN,
  COLOR_MEDIUMTURQUOISE,
  COLOR_MEDIUMVIOLETRED,
  COLOR_MIDNIGHTBLUE,
  COLOR_MINTCREAM,
  COLOR_MISTYROSE,
  COLOR_MOCCASIN,
  COLOR_NAVAJOWHITE,
  COLOR_NAVY,
  COLOR_OLDLACE,
  COLOR_OLIVE,
  COLOR_OLIVEDRAB,
  COLOR_ORANGE,
  COLOR_ORANGERED,
  COLOR_ORCHID,
  COLOR_PALEGOLDENROD,
  COLOR_PALEGREEN,
  COLOR_PALETURQUOISE,
  COLOR_PALEVIOLETRED,
  COLOR_PAPAYAWHIP,
  COLOR_PEACHPUFF,
  COLOR_PERU,
  COLOR_PINK,
  COLOR_PLUM,
  COLOR_POWDERBLUE,
  COLOR_PURPLE,
  COLOR_RED,
  COLOR_ROSYBROWN,
  COLOR_ROYALBLUE,
  COLOR_SADDLEBROWN,
  COLOR_SALMON,
  COLOR_SANDYBROWN,
  COLOR_SEAGREEN,
  COLOR_SEASHELL,
  COLOR_SIENNA,
  COLOR_SILVER,
  COLOR_SKYBLUE,
  COLOR_SLATEBLUE,
  COLOR_SLATEGRAY,
  COLOR_SLATEGREY,
  COLOR_SNOW,
  COLOR_SPRINGGREEN,
  COLOR_STEELBLUE,
  COLOR_TAN,
  COLOR_TEAL,
  COLOR_THISTLE,
  COLOR_TOMATO,
  COLOR_TURQUOISE,
  COLOR_VIOLET,
  COLOR_WHEAT,
  COLOR_WHITE,
  COLOR_WHITESMOKE,
  COLOR_YELLOW,
  COLOR_YELLOWGREEN
};

#endif /* COLOR_H__ */
