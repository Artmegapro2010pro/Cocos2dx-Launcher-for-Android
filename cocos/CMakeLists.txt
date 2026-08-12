cmake_minimum_required(VERSION 3.6)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(-DANDROID)

# Отключаем всё, что вызывает ошибки
add_definitions(-DCC_USE_3D_PHYSICS=0)
add_definitions(-DCC_USE_NAVMESH=0)
add_definitions(-DCamera=void)

# Ищем только .cpp, .c, .mm файлы
file(GLOB_RECURSE COCOS_SOURCE "*.cpp" "*.c" "*.mm")

# Убираем все проблемные файлы вручную
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/2d/CCAutoPolygon.cpp")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/2d/CCFontFreeType.cpp")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/2d/CCFontFreeType.h")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/2d/CCFontAtlas.cpp")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/2d/CCFontAtlasCache.cpp")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/3d/CCAnimate3D.cpp")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/3d/CCAnimate3D.h")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/3d/CCBillBoard.cpp")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/3d/CCBillBoard.h")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/3d/CCBundle3D.cpp")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/3d/CCBundle3D.h")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/3d/CCMesh.cpp")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/3d/CCMesh.h")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/navmesh/CCNavMesh.cpp")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/navmesh/CCNavMesh.h")
list(REMOVE_ITEM COCOS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/audio/linux/AudioEngine-linux.cpp")

add_library(cocos2d SHARED ${COCOS_SOURCE})

target_include_directories(cocos2d
    PUBLIC ${COCOS2DX_ROOT_PATH}
    PUBLIC ${COCOS2DX_ROOT_PATH}/cocos
    PUBLIC ${COCOS2DX_ROOT_PATH}/extensions
    PUBLIC ${COCOS2DX_ROOT_PATH}/cocos/platform
)

target_link_libraries(cocos2d log android)
