project("Server")

find_package (Threads)
add_executable(run_me final.cpp)
target_link_libraries (run_me ${CMAKE_THREAD_LIBS_INIT})
