project(Editor)

FetchContent_Declare(
  imgui-filebrowser
  GIT_REPOSITORY https://github.com/AirGuanZ/imgui-filebrowser.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(imgui-filebrowser)

find_package(imgui CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} STATIC
    ${SOURCES})

add_library(Editor::library ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/
        ${PROJECT_BINARY_DIR}/../_deps/imgui-filebrowser-src/
        ${PROJECT_SOURCE_DIR}/Libs/
)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE Foundry::library)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)

