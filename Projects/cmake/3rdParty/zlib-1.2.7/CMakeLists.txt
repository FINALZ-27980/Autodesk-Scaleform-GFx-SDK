project(zlib)

include(../BuildOptions.cmake)

if (MSVC)
    add_compile_options(/W3 /EHsc)
endif()

set(SRC_FILES
    "../../../../3rdParty/zlib-1.2.7/adler32.c"
    "../../../../3rdParty/zlib-1.2.7/compress.c"
    "../../../../3rdParty/zlib-1.2.7/crc32.c"
    "../../../../3rdParty/zlib-1.2.7/deflate.c"
    "../../../../3rdParty/zlib-1.2.7/infback.c"
    "../../../../3rdParty/zlib-1.2.7/inffast.c"
    "../../../../3rdParty/zlib-1.2.7/inflate.c"
    "../../../../3rdParty/zlib-1.2.7/inftrees.c"
    "../../../../3rdParty/zlib-1.2.7/trees.c"
    "../../../../3rdParty/zlib-1.2.7/uncompr.c"
    "../../../../3rdParty/zlib-1.2.7/zutil.c"
)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_link_libraries(${PROJECT_NAME})
