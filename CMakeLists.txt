cmake_minimum_required(VERSION 3.0.0)
project(pathfinder VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set (SRCS
    main.cpp
    pathfinder.cpp
    noeud.cpp
    graphe.cpp
    )
set (HEADERS
    pathfinder.h
    noeud.h
    graphe.h
    debug.h
    )

add_executable(pathfinder ${SRCS} ${HEADERS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
