cmake_minimum_required(VERSION 3.6)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(-DANDROID)

file(GLOB_RECURSE COCOS_SOURCE "*.cpp" "*.c" "*.mm")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/2d/CCAutoPolygon.cpp")

add_library(cocos2d SHARED ${COCOS_SOURCE})

target_include_directories(cocos2d
    PUBLIC ${COCOS2DX_ROOT_PATH}
    PUBLIC ${COCOS2DX_ROOT_PATH}/cocos
    PUBLIC ${COCOS2DX_ROOT_PATH}/extensions
    PUBLIC ${COCOS2DX_ROOT_PATH}/cocos/platform
)

target_link_libraries(cocos2d log android)
