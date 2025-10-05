project(libpng)

include(../BuildOptions.cmake)

if (MSVC)
    add_compile_options(/W3)
endif()

set(SRC_FILES
    "../../../../3rdParty/libpng-1.5.13/png.c"
    "../../../../3rdParty/libpng-1.5.13/pngerror.c"
    "../../../../3rdParty/libpng-1.5.13/pngget.c"
    "../../../../3rdParty/libpng-1.5.13/pngmem.c"
    "../../../../3rdParty/libpng-1.5.13/pngpread.c"
    "../../../../3rdParty/libpng-1.5.13/pngread.c"
    "../../../../3rdParty/libpng-1.5.13/pngrio.c"
    "../../../../3rdParty/libpng-1.5.13/pngrtran.c"
    "../../../../3rdParty/libpng-1.5.13/pngrutil.c"
    "../../../../3rdParty/libpng-1.5.13/pngset.c"
    "../../../../3rdParty/libpng-1.5.13/pngtrans.c"
    "../../../../3rdParty/libpng-1.5.13/pngwio.c"
    "../../../../3rdParty/libpng-1.5.13/pngwrite.c"
    "../../../../3rdParty/libpng-1.5.13/pngwtran.c"
    "../../../../3rdParty/libpng-1.5.13/pngwutil.c"
)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    "../../../../3rdParty/libpng-1.5.13"
    "../../../../3rdParty/zlib-1.2.7"
)

target_link_libraries(${PROJECT_NAME})
