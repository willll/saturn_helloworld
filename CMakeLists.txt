cmake_minimum_required(VERSION 3.0)

set(CMAKE_SYSTEM_NAME Generic)

set(HELLOWWORLD_DESTINATION helloworld)
set(INSTALL_DESTINATION ${HELLOWWORLD_DESTINATION})

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "")

set(SEGALIB $ENV{SATURN_SBL}/segalib)
set(SEGASGL $ENV{SATURN_SGL})

set(SATURN_COMMON $ENV{SATURN_COMMON})
set(SATURN_CMAKE $ENV{SATURN_CMAKE})

project( helloworld VERSION 1.0
                  DESCRIPTION "Sega Saturn Hello World"
                  LANGUAGES C ASM)

set(as_flags )
set(c_flags -Wall -m2 -MMD)


set(SOURCES
  ${SATURN_COMMON}/crt0.s
  src/helloworld.c
  src/v_blank/v_blank.c
  src/v_blank/set_vb.c
  )

set(CD_FILES
      0.bin
    )

set(TARGET_NAME helloworld)

add_compile_definitions(MODEL_S _SH)

cmake_path(NORMAL_PATH CMAKE_SOURCE_DIR OUTPUT_VARIABLE PROJECT_ROOT_NORMALIZED)

add_compile_options(
   "$<$<COMPILE_LANGUAGE:C>:${c_flags}>"
   "$<$<COMPILE_LANGUAGE:C>:-ffile-prefix-map=${PROJECT_ROOT_NORMALIZED}=.>"
   "$<$<CONFIG:DEBUG>:-g>"
   "$<$<CONFIG:RELEASE>:-Os>"
)

add_executable( ${TARGET_NAME}.elf ${SOURCES} )

target_include_directories(${TARGET_NAME}.elf PUBLIC
    ${SEGALIB}/include
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src/smpclib)

target_compile_options(${TARGET_NAME}.elf PUBLIC $<$<COMPILE_LANGUAGE:C>:${c_flags}>
                                                 $<$<COMPILE_LANGUAGE:ASM>:${as_flags}> )

target_link_options(${TARGET_NAME}.elf PUBLIC
    "SHELL:-Xlinker -Map -Xlinker ${TARGET_NAME}.map"
    "$<$<CONFIG:RELEASE>:SHELL:-Xlinker --strip-debug>"
    "SHELL:-m2 -nostartfiles"
    "SHELL:-T${SATURN_COMMON}/Saturn.lnk"
    "SHELL: --specs=nosys.specs"
    "SHELL:-Xlinker -z -Xlinker muldefs"
)

target_link_libraries(${TARGET_NAME}.elf PUBLIC ${SEGALIB}/lib/sega_int.a )
target_link_libraries(${TARGET_NAME}.elf PUBLIC ${SEGALIB}/lib/sega_per.a )
target_link_libraries(${TARGET_NAME}.elf PUBLIC ${SEGALIB}/lib/sega_sat.a )

add_custom_target(run_${TARGET_NAME} ALL DEPENDS ${TARGET_NAME}.elf ${TARGET_NAME}.bin IP.BIN)

add_custom_command(OUTPUT ${TARGET_NAME}.bin
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   COMMAND ${CMAKE_OBJCOPY}
                   ARGS -O binary ${TARGET_NAME}.elf ${TARGET_NAME}.bin )

add_custom_command(OUTPUT IP.BIN
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  COMMAND $ENV{SATURN_IPMAKER}/IPMaker
                  ARGS -v -o ${CMAKE_CURRENT_BINARY_DIR}/IP.BIN
                        -t ${TARGET_NAME} -p 2 )

message (${CMAKE_CURRENT_SOURCE_DIR})

include(${SATURN_CMAKE}/install.cmake)
include(${SATURN_CMAKE}/create_cd.cmake)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  install(TARGETS ${TARGET_NAME}.elf
          LIBRARY
            COMPONENT Runtime
            NAMELINK_COMPONENT Development
          ARCHIVE
            COMPONENT Development
            DESTINATION lib/static )
          #PUBLIC_HEADER DESTINATION ${INSTALL_DESTINATION}/${TARGET_PATH}/src/include  )
endif()
