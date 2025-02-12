cmake_minimum_required(VERSION 3.12)
project(SatelliteGuidanceDemo LANGUAGES CXX)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(DDSBase
            SHARED
            DataDefine.cxx 
            DataDefinePubSubTypes.cxx
            MainNodeAPublisher.cpp
            MainNodeASubscriber.cpp
            SlaveNodeBPublisher.cpp
            SlaveNodeBSubscriber.cpp
            SlaveNodeCPublisher.cpp
            SlaveNodeCSubscriber.cpp)   

add_executable(${PROJECT_NAME} ${DDSBase} Main.cpp)
                               
if(DEFINED ARM64)
link_directories( ${CMAKE_CURRENT_SOURCE_DIR}/lib_arm64)
target_link_libraries(${PROJECT_NAME}
                      DDSBase 
                      ${CMAKE_CURRENT_SOURCE_DIR}/lib_arm64/libfastrtps.so
                      ${CMAKE_CURRENT_SOURCE_DIR}/lib_arm64/libfastcdr.so
                      pthread)
else()
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib_x86)
target_link_libraries(${PROJECT_NAME}
                      DDSBase 
                      ${CMAKE_CURRENT_SOURCE_DIR}/lib_x86/libfastrtps.so
                      ${CMAKE_CURRENT_SOURCE_DIR}/lib_x86/libfastcdr.so
                      ${CMAKE_CURRENT_SOURCE_DIR}/lib_x86/libtinyxml2.so
                      pthread)
endif()


