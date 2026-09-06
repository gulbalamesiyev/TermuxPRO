# Normally xkbcomp is build as executable, but in our case it is better to embed it.

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/X11")

# These files are generated from upstream X11 inputs when the source bundle is
# prepared. Vendoring them keeps Android Studio on Windows free of Bison/GCC.
set(XKBCOMP_GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/generated")
add_library(xkbcomp STATIC
        "libx11/src/KeyBind.c"
        "libx11/src/KeysymStr.c"
        "libx11/src/Quarks.c"
        "libx11/src/StrKeysym.c"
        "libx11/src/Xrm.c"
        "libx11/src/XlibInt.c"
        "libx11/src/GetPntMap.c"
        "libx11/src/ModMap.c"
        "libx11/src/globals.c"
        "libx11/src/IntAtom.c"
        "libx11/src/InitExt.c"
        "libx11/src/ErrDes.c"
        "libx11/src/GetGeom.c"
        "libx11/src/QuExt.c"
        "libx11/src/XlibAsync.c"
        "lorie/xkbcomp_stubs.c"

        "libx11/src/xkb/XKBGeom.c"
        "libx11/src/xkb/XKBMisc.c"
        "libx11/src/xkb/XKBMAlloc.c"
        "libx11/src/xkb/XKBGAlloc.c"
        "libx11/src/xkb/XKBAlloc.c"
        "libx11/src/xkb/XKBRdBuf.c"
        "libx11/src/xkb/XKBUse.c"

        "libxkbfile/src/xkbatom.c"
        "libxkbfile/src/xkberrs.c"
        "libxkbfile/src/xkbmisc.c"
        "libxkbfile/src/xkbout.c"
        "libxkbfile/src/xkbtext.c"
        "libxkbfile/src/xkmout.c"

        "xkbcomp/action.c"
        "xkbcomp/alias.c"
        "xkbcomp/compat.c"
        "xkbcomp/expr.c"
        "xkbcomp/geometry.c"
        "xkbcomp/indicators.c"
        "xkbcomp/keycodes.c"
        "xkbcomp/keymap.c"
        "xkbcomp/keytypes.c"
        "xkbcomp/listing.c"
        "xkbcomp/misc.c"
        "xkbcomp/parseutils.c"
        "xkbcomp/symbols.c"
        "xkbcomp/utils.c"
        "xkbcomp/vmod.c"
        "xkbcomp/xkbcomp.c"
        "xkbcomp/xkbpath.c"
        "xkbcomp/xkbscan.c"
        "${XKBCOMP_GENERATED_DIR}/ks_tables.h"
        "${XKBCOMP_GENERATED_DIR}/xkbparse.c")
target_include_directories(xkbcomp
        PUBLIC
        "libxkbfile/include"
        PRIVATE
        "xkbcomp"
        "libx11/include"
        "libx11/src"
        "libx11/src/xlibi18n"
        "${XKBCOMP_GENERATED_DIR}"
        "libxkbfile/include/X11/extensions"
        "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(xkbcomp PRIVATE xorgproto)
target_link_options(xkbcomp PRIVATE "-fPIE" "-fPIC")
target_compile_options(xkbcomp PRIVATE ${common_compile_options} "-fvisibility=hidden" "-DHAVE_STRCASECMP" "-DHAVE_STRDUP" "-DDFLT_XKB_CONFIG_ROOT=\"/\"" "-DHAVE_SYS_IOCTL_H" "-fPIE" "-fPIC" "-DPACKAGE_VERSION=\"2.70\"" "-Wno-shadow")
target_apply_patch(xkbcomp "${CMAKE_CURRENT_SOURCE_DIR}/xkbcomp" "${CMAKE_CURRENT_SOURCE_DIR}/patches/xkbcomp.patch")
target_apply_patch(xkbfile "${CMAKE_CURRENT_SOURCE_DIR}/libxkbfile" "${CMAKE_CURRENT_SOURCE_DIR}/patches/xkbfile.patch")
target_apply_patch(X11 "${CMAKE_CURRENT_SOURCE_DIR}/libx11" "${CMAKE_CURRENT_SOURCE_DIR}/patches/x11.patch")
