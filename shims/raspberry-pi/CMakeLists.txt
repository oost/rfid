cmake_minimum_required(VERSION 3.7) # first version with add_compile_options()
project(MFRC522)

message (STATUS "CMake version: ${CMAKE_VERSION}")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Print CXX compiler information
message (STATUS "CMAKE_CXX_COMPILER '${CMAKE_CXX_COMPILER}' '${CMAKE_CXX_COMPILER_ID}' '${CMAKE_CXX_COMPILER_VERSION}'")

# Print CXX FLAGS
message (STATUS "CMAKE_CXX_FLAGS                '${CMAKE_CXX_FLAGS}'")
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    message (STATUS "CMAKE_CXX_FLAGS_DEBUG          '${CMAKE_CXX_FLAGS_DEBUG}'")
elseif (CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
    message (STATUS "CMAKE_CXX_FLAGS_RELWITHDEBINFO '${CMAKE_CXX_FLAGS_RELWITHDEBINFO}'")
elseif (CMAKE_BUILD_TYPE STREQUAL MinSizeRel)
    message (STATUS "CMAKE_CXX_FLAGS_MINSIZEREL     '${CMAKE_CXX_FLAGS_MINSIZEREL}'")
else ()
    message (STATUS "CMAKE_CXX_FLAGS_RELEASE        '${CMAKE_CXX_FLAGS_RELEASE}'")
endif ()


# list of sources files of the library
set(MFRC522_SRC
    ${PROJECT_SOURCE_DIR}/../../src/MFRC522Extended.cpp
    ${PROJECT_SOURCE_DIR}/../../src/MFRC522.cpp
    ${PROJECT_SOURCE_DIR}/Arduino/SPI.cpp
    ${PROJECT_SOURCE_DIR}/Arduino/src/Serial.cpp
)
source_group(src FILES ${MFRC522_SRC})

# list of header files of the library
set(MFRC522_INC
    ${PROJECT_SOURCE_DIR}/../../src/MFRC522.h
    ${PROJECT_SOURCE_DIR}/../../src/MFRC522Extended.h
    ${PROJECT_SOURCE_DIR}/../../src/require_cpp11.h
    ${PROJECT_SOURCE_DIR}/Arduino/src/Arduino.h
    ${PROJECT_SOURCE_DIR}/Arduino/src/Serial.h
    ${PROJECT_SOURCE_DIR}/Arduino/src/SPI.h

)
source_group(include FILES ${MFRC522_INC})

# list of test files of the library
set(MFRC522_TESTS
  test/MFRC522_test.cpp
)
source_group(tests FILES ${MFRC522_TESTS})

# list of script files of the library
set(MFRC522_SCRIPT
  build.sh
)
source_group(scripts FILES ${MFRC522_SCRIPT})

# All includes are relative to the "include" directory
include_directories("${PROJECT_SOURCE_DIR}/Arduino")

# add sources 
add_library(mfrc522 ${MFRC522_SRC} ${MFRC522_INC})
target_link_libraries(mfrc522 wiringPi)
target_compile_options(mfrc522 PRIVATE -Wall -Wextra -Werror -pedantic -Wconversion -Wsign-conversion)
target_include_directories(mfrc522 SYSTEM PUBLIC ${PROJECT_SOURCE_DIR}/Ardunio)


option(MFRC522_BUILD_TESTS "Build tests." OFF)
if (MFRC522_BUILD_TESTS)

    add_executable(MFRC522_test ${MFRC522_TESTS})
    target_link_libraries(MFRC522_test mfrc522 )
    # target_include_directories(MFRC522_test PUBLIC ${PROJECT_SOURCE_DIR}/src)

else (MFRC522_BUILD_TESTS)
    message(STATUS "MFRC522_BUILD_TESTS OFF")
endif (MFRC522_BUILD_TESTS)
