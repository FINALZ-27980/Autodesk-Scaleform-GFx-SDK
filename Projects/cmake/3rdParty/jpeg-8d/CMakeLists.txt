project(libjpeg)

include(../BuildOptions.cmake)

add_definitions(-D_LIB -D_CRT_SECURE_NO_WARNINGS -D_MBCS)
if (MSVC)
    add_compile_options(/W3 /EHsc)
endif()

set(SRC_FILES
    "../../../../3rdParty/jpeg-8d/jaricom.c"
    "../../../../3rdParty/jpeg-8d/jcapimin.c"
    "../../../../3rdParty/jpeg-8d/jcapistd.c"
    "../../../../3rdParty/jpeg-8d/jcarith.c"
    "../../../../3rdParty/jpeg-8d/jccoefct.c"
    "../../../../3rdParty/jpeg-8d/jccolor.c"
    "../../../../3rdParty/jpeg-8d/jcdctmgr.c"
    "../../../../3rdParty/jpeg-8d/jchuff.c"
    "../../../../3rdParty/jpeg-8d/jcinit.c"
    "../../../../3rdParty/jpeg-8d/jcmainct.c"
    "../../../../3rdParty/jpeg-8d/jcmarker.c"
    "../../../../3rdParty/jpeg-8d/jcmaster.c"
    "../../../../3rdParty/jpeg-8d/jcomapi.c"
    "../../../../3rdParty/jpeg-8d/jcparam.c"
    "../../../../3rdParty/jpeg-8d/jcprepct.c"
    "../../../../3rdParty/jpeg-8d/jcsample.c"
    "../../../../3rdParty/jpeg-8d/jctrans.c"
    "../../../../3rdParty/jpeg-8d/jdapimin.c"
    "../../../../3rdParty/jpeg-8d/jdapistd.c"
    "../../../../3rdParty/jpeg-8d/jdarith.c"
    "../../../../3rdParty/jpeg-8d/jdatadst.c"
    "../../../../3rdParty/jpeg-8d/jdatasrc.c"
    "../../../../3rdParty/jpeg-8d/jdcoefct.c"
    "../../../../3rdParty/jpeg-8d/jdcolor.c"
    "../../../../3rdParty/jpeg-8d/jddctmgr.c"
    "../../../../3rdParty/jpeg-8d/jdhuff.c"
    "../../../../3rdParty/jpeg-8d/jdinput.c"
    "../../../../3rdParty/jpeg-8d/jdmainct.c"
    "../../../../3rdParty/jpeg-8d/jdmarker.c"
    "../../../../3rdParty/jpeg-8d/jdmaster.c"
    "../../../../3rdParty/jpeg-8d/jdmerge.c"
    "../../../../3rdParty/jpeg-8d/jdpostct.c"
    "../../../../3rdParty/jpeg-8d/jdsample.c"
    "../../../../3rdParty/jpeg-8d/jdtrans.c"
    "../../../../3rdParty/jpeg-8d/jerror.c"
    "../../../../3rdParty/jpeg-8d/jfdctflt.c"
    "../../../../3rdParty/jpeg-8d/jfdctfst.c"
    "../../../../3rdParty/jpeg-8d/jfdctint.c"
    "../../../../3rdParty/jpeg-8d/jidctflt.c"
    "../../../../3rdParty/jpeg-8d/jidctfst.c"
    "../../../../3rdParty/jpeg-8d/jidctint.c"
    "../../../../3rdParty/jpeg-8d/jmemmgr.c"
    "../../../../3rdParty/jpeg-8d/jmemnobs.c"
    "../../../../3rdParty/jpeg-8d/jpegtran.c"
    "../../../../3rdParty/jpeg-8d/jquant1.c"
    "../../../../3rdParty/jpeg-8d/jquant2.c"
    "../../../../3rdParty/jpeg-8d/jutils.c"
)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_link_libraries(${PROJECT_NAME})
