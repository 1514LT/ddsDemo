cmake_minimum_required(VERSION 3.12)
project(SatelliteOperationDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT fastrtps_DIR)
    set(fastrtps_DIR $ENV{RTPS2DIR})
endif()
if(NOT fastcdr_DIR)
    set(fastcdr_DIR $ENV{DDS2CDRDIR})
endif()
if(NOT foonathan_memory_DIR)
    set(foonathan_memory_DIR $ENV{DDS2FOONDIR})
endif()

find_package(fastrtps 2.14 REQUIRED) 
find_package(fastcdr 2 REQUIRED)
find_package(foonathan_memory REQUIRED)

list(APPEND SOURCEFILES DataDefine.cxx 
                        DataDefinePubSubTypes.cxx
                        MainnodePublisher.cpp
                        MainnodeSubscriber.cpp
                        SlavenodePublisher.cpp
                        SlavenodeSubscriber.cpp
                        Main.cpp
                        )

add_executable(${PROJECT_NAME} ${SOURCEFILES})

target_include_directories(${PROJECT_NAME} 
                                PRIVATE
                                    ${fastrtps_INCLUDE_DIR}
                                    ${fastcdr_INCLUDE_DIR}
                                    ${foonathan_memory_INCLUDE_DIR}
                                    )

target_link_libraries(${PROJECT_NAME} fastrtps fastcdr foonathan_memory)

