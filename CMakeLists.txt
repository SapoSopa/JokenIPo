cmake_minimum_required(VERSION 3.5)

project(jokenipo VERSION 1.0.0 LANGUAGES C)

add_executable(jokenipo "main.c" "items.c" "arena.c" "map.c" "combat.c" "game.c" "enemy.c" "audio.c" "load.c" "canvas.c" "sprites.c" "screens.c")

find_package(tmx REQUIRED)

target_include_directories(jokenipo PUBLIC "include/")

if (UNIX)
  target_link_libraries(jokenipo PRIVATE tmx raylib)
elseif (WIN32)
  # Lembrar de atualizar o binário da raylib
  target_link_libraries(jokenipo ${CMAKE_SOURCE_DIR}/src/lib/libtmx.a ${CMAKE_SOURCE_DIR}/src/lib/libraylib.a)
endif()

# The following libs should be transitively imported by raylib...
find_package(Threads REQUIRED)
target_link_libraries(jokenipo PRIVATE Threads::Threads m)
if(UNIX)
  find_package(X11 REQUIRED)
  target_link_libraries(jokenipo PRIVATE X11::X11)
endif()
