cmake_minimum_required(VERSION 3.10)

project(TesseractSearchEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)
find_package(Threads REQUIRED)
find_package(SQLite3 REQUIRED)

find_path(GUMBO_INCLUDE_DIR NAMES gumbo.h)
find_library(GUMBO_LIBRARY NAMES gumbo)
if(NOT GUMBO_INCLUDE_DIR OR NOT GUMBO_LIBRARY)
    message(FATAL_ERROR "Gumbo library not found. Please ensure it is installed via pacman.")
endif()

find_library(SQLITE3_LIBRARY NAMES sqlite3)
if(NOT SQLITE3_LIBRARY)
    message(FATAL_ERROR "SQLite3 library file not found. Please ensure it is installed via pacman.")
endif()

set(SHARED_SOURCES
    src/database/database.cpp
)

add_executable(indexer
    src/indexer.cpp
    src/network/HTTP_client.cpp
    src/parsing/HTML_parser.cpp
    src/concurrency/concurrent_queue.cpp
    src/crawler/crawler.cpp
    ${SHARED_SOURCES}
)

add_executable(search
    src/search.cpp
    src/search/query_engine.cpp
    src/search/retriever.cpp   
    src/search/ranker.cpp      
    ${SHARED_SOURCES}
)

target_include_directories(indexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(search PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(indexer PRIVATE
    ${CURL_INCLUDE_DIRS}
    ${GUMBO_INCLUDE_DIR}
    ${SQLITE3_INCLUDE_DIRS}
)

target_include_directories(search PRIVATE
    ${SQLITE3_INCLUDE_DIRS}
)

target_link_libraries(indexer PRIVATE
    ${CURL_LIBRARIES}
    ${GUMBO_LIBRARY}
    ${SQLITE3_LIBRARY}
    Threads::Threads
)

target_link_libraries(search PRIVATE
    ${SQLITE3_LIBRARY}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})