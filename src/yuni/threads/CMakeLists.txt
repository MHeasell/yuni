
Include(FindThreads)
IF(NOT CMAKE_USE_PTHREADS_INIT)
    MESSAGE(FATAL_ERROR "PThreads is required.")
ENDIF(NOT CMAKE_USE_PTHREADS_INIT)


ADD_LIBRARY(yuni-threads STATIC
                mutex.h mutex.cpp
                abstract.thread.h abstract.thread.cpp
                thread.h thread.cpp
                timer.h timer.cpp
                jobs.abstract.h jobs.abstract.cpp
                cpu.cpp)

