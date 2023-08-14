cmake_minimum_required(VERSION 3.18)

project(zombie_arena)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/laust/vcpkg/scripts/buildsystems/vcpkg.cmake")
#set(VCPKG_TARGET_TRIPLET x64-windows-static)


find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_executable(${CMAKE_PROJECT_NAME})
target_sources(${CMAKE_PROJECT_NAME} PRIVATE 
    main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-system sfml-graphics sfml-window)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
                       "${CMAKE_CURRENT_SOURCE_DIR}/assets"
                       $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/assets)