# cmake_minimum_required(VERSION 3.10)

# project(TesseractSearchEngine)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)


# # --- SECTION 1: Find External Libraries ---

# find_package(CURL REQUIRED)
# find_package(Threads REQUIRED)
# find_package(SQLite3 REQUIRED)
# find_package(nlohmann_json REQUIRED)      # <-- ADDED

# # Manually Find Gumbo
# find_path(GUMBO_INCLUDE_DIR NAMES gumbo.h)
# find_library(GUMBO_LIBRARY NAMES gumbo)
# if(NOT GUMBO_INCLUDE_DIR OR NOT GUMBO_LIBRARY)
#     message(FATAL_ERROR "Gumbo library not found. Please ensure it is installed via pacman.")
# endif()

# # Manually Find SQLite3 for robust linking
# find_library(SQLITE3_LIBRARY NAMES sqlite3)
# if(NOT SQLITE3_LIBRARY)
#     message(FATAL_ERROR "SQLite3 library file not found. Please ensure it is installed via pacman.")
# endif()


# # --- SECTION 2: Define Shared Source Files ---

# # Shared code used by both executables.
# set(SHARED_SOURCES
#     src/database/database.cpp
# )


# # --- SECTION 3: Define the Executables ---

# # Define the Indexer executable and its specific source files.
# # The entry point is now 'indexer_server.cpp'.
# add_executable(indexer_server
#     src/indexer_server.cpp
#     src/indexer/indexer.cpp
#     src/crawler/crawler.cpp
#     src/network/HTTP_client.cpp
#     src/parsing/HTML_parser.cpp
#     src/concurrency/concurrent_queue.cpp
#     ${SHARED_SOURCES}
# )

# target_compile_definitions(indexer_server PRIVATE _WIN32_WINNT=0x0A00)

# # Define the Search executable and its specific source files.
# # The entry point is now 'search_server.cpp'.
# add_executable(search_server
#     src/search.cpp
#     src/search/query_engine.cpp
#     src/search/retriever.cpp
#     src/search/ranker.cpp
#     ${SHARED_SOURCES}
# )


# # --- SECTION 4: Configure Include Directories ---

# # Both executables need to find headers in the src directory and the vendor directory.
# target_include_directories(indexer_server PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/src
#     ${CMAKE_CURRENT_SOURCE_DIR}/external
# )
# target_include_directories(search_server PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/src
#     ${CMAKE_CURRENT_SOURCE_DIR}/external
# )

# # Add external library include paths for the INDEXER server.
# target_include_directories(indexer_server PRIVATE
#     ${CURL_INCLUDE_DIRS}
#     ${GUMBO_INCLUDE_DIR}
#     ${SQLITE3_INCLUDE_DIRS}
#     ${nlohmann_json_INCLUDE_DIRS}
#     ${LIBMICROHTTPD_INCLUDE_DIR}      # <-- UPDATED
# )

# target_include_directories(search_server PRIVATE
#     ${SQLITE3_INCLUDE_DIRS}
#     ${nlohmann_json_INCLUDE_DIRS}
#     ${LIBMICROHTTPD_INCLUDE_DIR}      # <-- UPDATED
# )


# # --- SECTION 5: Link Libraries ---
# target_link_libraries(indexer_server PRIVATE
#     ${CURL_LIBRARIES}
#     ${GUMBO_LIBRARY}
#     ${SQLITE3_LIBRARY}
#     Threads::Threads
#     nlohmann_json::nlohmann_json
#     ${LIBMICROHTTPD_LIBRARY}          # <-- UPDATED
# )

# target_link_libraries(search_server PRIVATE
#     ${SQLITE3_LIBRARY}
#     nlohmann_json::nlohmann_json
#     ${LIBMICROHTTPD_LIBRARY}          # <-- UPDATED
# )
# # --- SECTION 6: Define Output Directory ---

# # Set the output directory for BOTH final executables.
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

cmake_minimum_required(VERSION 3.10)
project(TesseractSearchEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# --- SECTION 1: Find External Libraries ---

find_package(CURL REQUIRED)
find_package(Threads REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(nlohmann_json REQUIRED)

# Manually Find Gumbo
find_path(GUMBO_INCLUDE_DIR NAMES gumbo.h)
find_library(GUMBO_LIBRARY NAMES gumbo)
if(NOT GUMBO_INCLUDE_DIR OR NOT GUMBO_LIBRARY)
    message(FATAL_ERROR "Gumbo library not found. Please ensure it is installed via pacman.")
endif()

# Manually Find SQLite3 for robust linking
find_library(SQLITE3_LIBRARY NAMES sqlite3)
if(NOT SQLITE3_LIBRARY)
    message(FATAL_ERROR "SQLite3 library file not found. Please ensure it is installed via pacman.")
endif()

# --- THE FIX: Manually Find Libmicrohttpd ---
find_path(LIBMICROHTTPD_INCLUDE_DIR NAMES microhttpd.h)
find_library(LIBMICROHTTPD_LIBRARY NAMES microhttpd)
if(NOT LIBMICROHTTPD_INCLUDE_DIR OR NOT LIBMICROHTTPD_LIBRARY)
    message(FATAL_ERROR "Libmicrohttpd library not found. Please ensure it is installed via pacman.")
endif()


# --- SECTION 2: Define Shared Source Files ---
set(SHARED_SOURCES
    src/database/database.cpp
)


# --- SECTION 3: Define the Executables ---
add_executable(indexer_server
    src/indexer_server.cpp
    src/indexer/indexer.cpp
    src/crawler/crawler.cpp
    src/network/HTTP_client.cpp
    src/parsing/HTML_parser.cpp
    src/concurrency/concurrent_queue.cpp
    ${SHARED_SOURCES}
)

add_executable(search_server
    src/search.cpp
    src/search/query_engine.cpp
    src/search/retriever.cpp
    src/search/ranker.cpp
    ${SHARED_SOURCES}
)


# --- SECTION 4: Configure Include Directories ---
target_include_directories(indexer_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(search_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(indexer_server PRIVATE
    ${CURL_INCLUDE_DIRS}
    ${GUMBO_INCLUDE_DIR}
    ${SQLITE3_INCLUDE_DIRS}
    ${nlohmann_json_INCLUDE_DIRS}
    ${LIBMICROHTTPD_INCLUDE_DIR}      # <-- UPDATED
)

target_include_directories(search_server PRIVATE
    ${SQLITE3_INCLUDE_DIRS}
    ${nlohmann_json_INCLUDE_DIRS}
    ${LIBMICROHTTPD_INCLUDE_DIR}      # <-- UPDATED
)


# --- SECTION 5: Link Libraries ---
target_link_libraries(indexer_server PRIVATE
    ${CURL_LIBRARIES}
    ${GUMBO_LIBRARY}
    ${SQLITE3_LIBRARY}
    Threads::Threads
    nlohmann_json::nlohmann_json
    ${LIBMICROHTTPD_LIBRARY}          # <-- UPDATED
)

target_link_libraries(search_server PRIVATE
    ${SQLITE3_LIBRARY}
    nlohmann_json::nlohmann_json
    ${LIBMICROHTTPD_LIBRARY}          # <-- UPDATED
)


# --- SECTION 6: Define Output Directory ---
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})