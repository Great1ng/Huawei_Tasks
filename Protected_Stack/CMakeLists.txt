cmake_minimum_required(VERSION 3.20)
project(Protected_Stack)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS}\
        -Werror\
        -fmax-errors=1\
        -Wall\
        -Wextra\
        -Weffc++\
        -Waggressive-loop-optimizations\
        -Wc++0x-compat\
        -Wc++11-compat\
        -Wc++14-compat\
        -Wcast-align\
        -Wcast-qual\
        -Wchar-subscripts\
        -Wconditionally-supported\
        -Wconversion\
        -Wctor-dtor-privacy\
        -Wempty-body\
        -Wfloat-equal\
        -Wformat-nonliteral\
        -Wformat-security\
        -Wformat-signedness\
        -Wformat=2\
        -Winline\
        -Wlarger-than=8192\
        -Wlogical-op\
        -Wmissing-declarations\
        -Wnon-virtual-dtor\
        -Wopenmp-simd\
        -Woverloaded-virtual\
        -Wpacked\
        -Wpointer-arith\
        -Wredundant-decls\
        -Wshadow\
        -Wsign-conversion\
        -Wsign-promo\
        -Wstack-usage=8192\
        -Wstrict-null-sentinel\
        -Wstrict-overflow=2\
        -Wsuggest-attribute=noreturn\
        -Wsuggest-final-methods\
        -Wsuggest-final-types\
        -Wsuggest-override\
        -Wswitch-default\
        -Wswitch-enum\
        -Wsync-nand\
        -Wundef\
        -Wunreachable-code\
        -Wuseless-cast\
        -Wvariadic-macros\
        -Wno-literal-suffix\
        -Wno-missing-field-initializers\
        -Wno-narrowing\
        -Wno-old-style-cast\
        -Wno-unused\
        -Wno-varargs\
        -fcheck-new\
        -fsized-deallocation\
        -fstack-protector\
        -fstrict-overflow\
        -fsanitize=address\
        -flto-odr-type-merging\
        -fno-omit-frame-pointer\
        -lm\
        -pie\
")

add_executable(Protected_Stack main.cpp stack.cpp stack.h hash.cpp hash.h utils.cpp utils.h stk-config.h)
