project("Final Exam")

find_package (Threads)
add_executable(final final.cpp)
target_link_libraries (final ${CMAKE_THREAD_LIBS_INIT})