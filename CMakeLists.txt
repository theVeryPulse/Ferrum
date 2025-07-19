cmake_minimum_required(VERSION 3.10)
project(Ferrum)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)
# include_directories(include)

# ---- SDL2 Setup ----
if (WIN32)
    # Adjust this to where you extracted SDL2
    set(SDL2_PATH "C:/Libraries/SDL2")  # Change this path!
    
    set(SDL2_INCLUDE_DIR "${SDL2_PATH}/include")
    set(SDL2_LIBRARY     "${SDL2_PATH}/lib/x64/SDL2.lib")
    set(SDL2MAIN_LIBRARY "${SDL2_PATH}/lib/x64/SDL2main.lib")
    
    include_directories(${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_PATH}/lib/x64)
    
    if (MSVC)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
        set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG /INCREMENTAL")
    endif()

    add_executable(${PROJECT_NAME} ${SOURCES})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY})
    
    # Optional: copy SDL2.dll to output folder automatically
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_PATH}/lib/x64/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    
else()
    # For Linux/macOS: use system package
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    
    add_executable(${PROJECT_NAME} ${SOURCES})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif()
