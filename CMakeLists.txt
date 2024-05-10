cmake_minimum_required(VERSION 3.10)
project(Game)

set(CMAKE_CXX_STANDARD 17)

include_directories(sdl/Include)
include_directories(include)

set(CXXFLAGS "-std=c++17")
set(LDFLAGS "")

if (WIN32)
    set(CXXFLAGS "${CXXFLAGS} -mwindows")
    set(LDFLAGS "${LDFLAGS} -mwindows")
endif ()

set(LIBS mingw32 SDL2main SDL2)

set(SOURCE_FILES main.cpp)

add_executable(game ${SOURCE_FILES})

target_compile_options(game PRIVATE ${CXXFLAGS})
target_link_libraries(game PRIVATE ${LIBS})
