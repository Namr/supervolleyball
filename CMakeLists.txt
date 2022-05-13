cmake_minimum_required(VERSION 3.15)
project(supervolleyball)

find_package(raylib 3.0 REQUIRED)
find_package(glfw3 REQUIRED)
set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} game.cpp court.cpp player.cpp)

find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(supervolleyball PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(supervolleyball "${CMAKE_THREAD_LIBS_INIT}")
endif()

target_link_libraries(${PROJECT_NAME} raylib ${GLFW3_LIBRARY} m ${CMAKE_DL_LIBS} Threads::Threads)
