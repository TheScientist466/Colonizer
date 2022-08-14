cmake_minimum_required(VERSION 3.0.0)
project(Colonizer VERSION 0.1.0)

include(CTest)
enable_testing()

file(
    GLOB
    src_files
    "Colonizer/src/*.cpp"
)


find_package(SFML COMPONENTS graphics audio system window REQUIRED)

include_directories("Colonizer/src/Headers")

add_executable(${PROJECT_NAME} ${src_files})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-system sfml-window)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

file(COPY "Colonizer/Assets" DESTINATION ".")