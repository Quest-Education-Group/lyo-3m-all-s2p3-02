project(Game)

set(MAIN "main" CACHE STRING "Select the program entry point")
set(SOURCEMAIN
    src/${MAIN}.cpp 
)

if (MSVC)
    add_compile_options(/bigobj)
else ()
    #add_compile_options(-Wa,-mbig-obj)
endif ()

add_executable(${PROJECT_NAME} ${SOURCEMAIN})

file(COPY ${PROJECT_SOURCE_DIR}/../res/ 
     DESTINATION ${PROJECT_BINARY_DIR}/../Game/res
)

target_link_libraries(${PROJECT_NAME}  PRIVATE Foundry::library)
