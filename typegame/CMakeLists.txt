cmake_minimum_required(VERSION 3.10)

if(WIN32)
    set(CMAKE_SYSTEM_VERSION "10.0.18362.0")
endif()

project(typegame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Multimedia)

if(WIN32)
    set(CMAKE_SYSTEM_VERSION "10.0.18362.0")
    # 设置UTF-8编码以避免乱码
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /utf-8")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()

# ==============================================
# 自动遍历 src 目录下所有 .cpp .h .qrc 文件
# ==============================================
file(GLOB_RECURSE TYPEGAME_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE TYPEGAME_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

file(GLOB_RECURSE TYPEGAME_QRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.qrc
)

set(TYPEGAME_QRC
    src/app/resources/typegame_assets.qrc

)

add_executable(typegame
    ${TYPEGAME_SOURCES}
    ${TYPEGAME_HEADERS}
    ${TYPEGAME_QRC}
)

target_include_directories(typegame
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(typegame
    PRIVATE
        Qt5::Widgets
        Qt5::Gui
        Qt5::Core
        Qt5::Multimedia
)

# 可选：便于 VS 工程中按目录查看
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    ${TYPEGAME_SOURCES}
    ${TYPEGAME_HEADERS}
)