cmake_minimum_required(VERSION 3.5)

project(jokenipo VERSION 1.0.0 LANGUAGES C)

add_executable(jokenipo "main.c" "items.c" "arena.c" "combat.c" "enemy.c" "audio.c" "load.c" "sprites.c" "screens.c")

find_package(tmx REQUIRED)

target_include_directories(jokenipo PUBLIC "include/")
target_link_libraries(jokenipo PRIVATE tmx raylib)

# The following libs should be transitively imported by raylib...
find_package(Threads REQUIRED)
target_link_libraries(jokenipo PRIVATE Threads::Threads)
if(UNIX)
  find_package(X11 REQUIRED)
  target_link_libraries(jokenipo PRIVATE X11::X11)
endif()
