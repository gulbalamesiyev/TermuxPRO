cmake_minimum_required(VERSION 3.22)
project(lorie)

set(can_use_assembler TRUE)
enable_language(ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

include(TestBigEndian)
include(CheckIncludeFile)
include(CheckSourceCompiles)
include(CheckCCompilerFlag)
include(CheckSymbolExists)
include(CheckFunctionExists)
include(CheckTypeSize)

find_package(Python3 REQUIRED)

function(target_apply_patch patch_target d p)
    # Patches are pre-applied in the embedded source bundle so Windows CMake
    # does not need Bash or the patch executable.
endfunction()

set(test_compile_options
        "-Wall"
        "-Wpointer-arith"
        "-Wmissing-declarations"
        "-Wformat=2"
        "-Winvalid-pch"
        "-Wstrict-prototypes"
        "-Wmissing-prototypes"
        "-Wnested-externs"
        "-Wbad-function-cast"
        "-Wold-style-definition"
        "-Wunused"
        "-Wuninitialized"
        "-Wshadow"
        "-Wmissing-noreturn"
        "-Wmissing-format-attribute"
        "-Wredundant-decls"
        "-Wlogical-op"
        "-Werror=implicit"
        "-Werror=nonnull"
        "-Werror=init-self"
        "-Werror=main"
        "-Werror=missing-braces"
        "-Werror=sequence-point"
        "-Werror=return-type"
        "-Werror=trigraphs"
        "-Werror=array-bounds"
        "-Werror=write-strings"
        "-Werror=address"
        "-Werror=int-to-pointer-cast"
        "-Werror=pointer-to-int-cast"
        "-fno-strict-aliasing"
        "-Wno-unused-but-set-variable"
        "-Wno-unused-parameter"
        "-Wno-unused-variable"
        "-Wno-unused-function"
        "-Wno-missing-prototypes"
        "-Wno-macro-redefined"
        "-Wno-uninitialized"
        "-Wno-shadow")

if (LORIE_EMBEDDED_FAST_BUILD)
    # Android NDK Clang supports this conservative set. Skipping dozens of
    # configure-time compiler probes makes Windows iteration deterministic.
    set(common_compile_options
            "-Wall"
            "-Wpointer-arith"
            "-Wformat=2"
            "-Werror=implicit"
            "-Werror=return-type"
            "-fno-strict-aliasing"
            "-Wno-unused-but-set-variable"
            "-Wno-unused-parameter"
            "-Wno-unused-variable"
            "-Wno-unused-function"
            "-Wno-macro-redefined")
else()
    set(CMAKE_REQUIRED_QUIET_OLD ${CMAKE_REQUIRED_QUIET})
    set(CMAKE_REQUIRED_QUIET 1)
    set(common_compile_options)
    set(I 0)
    foreach (option ${test_compile_options})
        check_c_compiler_flag(${option} COMPILER_TEST_${I})
        if (COMPILER_TEST_${I})
            set(common_compile_options ${common_compile_options} ${option})
        endif()
        MATH(EXPR I "${I}+1")
    endforeach ()
    set(CMAKE_REQUIRED_QUIET ${CMAKE_REQUIRED_QUIET_OLD})
endif()

foreach(project xorgproto fontenc md pixman tirpc xshmfence Xdmcp Xau Xfont2 xkbcomp xserver)
    include(recipes/${project}.cmake)
endforeach()
