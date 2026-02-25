project(Foundry)

find_package(unofficial-enet CONFIG REQUIRED)
find_package(ReactPhysics3D REQUIRED)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} SHARED
    ${SOURCES}
)

target_precompile_headers(${PROJECT_NAME} INTERFACE
	"${PROJECT_SOURCE_DIR}/include/Define.h"
	"${PROJECT_SOURCE_DIR}/include/Debug.h"
)

add_library(Foundry::library ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/
)

target_link_libraries(${PROJECT_NAME} PRIVATE ReactPhysics3D::ReactPhysics3D)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::enet::enet)
target_link_libraries(${PROJECT_NAME} PRIVATE Ore::library)

