
    #pragma once
    #define fourcc_code(a, b, c, d) ((uint32_t)(a) | ((uint32_t)(b) << 8) | ((uint32_t)(c) << 16) | ((uint32_t)(d) << 24))
    #define DRM_FORMAT_RGB565	fourcc_code('R', 'G', '1', '6')
    #define DRM_FORMAT_XRGB8888	fourcc_code('X', 'R', '2', '4')
    #define DRM_FORMAT_XRGB2101010	fourcc_code('X', 'R', '3', '0')
    #define DRM_FORMAT_ARGB8888	fourcc_code('A', 'R', '2', '4')
    #define DRM_FORMAT_MOD_INVALID -1
