cmake_minimum_required(VERSION 3.26)
project(homeworks)

set(CMAKE_CXX_STANDARD 17)

add_executable(forward_List FL_constructor.cpp)
add_executable(doublyLL doublyll.cpp)

add_executable(CircularDLL main.cpp)
add_executable(sentin doublyC.cpp)

add_executable(pilaDinamic pila.cpp)
add_executable(pilaStatic pilados.cpp)
add_executable(colaDinamic cola.cpp)
add_executable(colaStatic colados.cpp)

add_executable(hashmapOg hash.cpp)
add_executable(hashmapNw hashmap.cpp)

add_executable(arbol tree.cpp)
add_executable(arbolBST bst.cpp)

add_executable(prueba aaa.cpp)

add_executable(linked a.cpp)

