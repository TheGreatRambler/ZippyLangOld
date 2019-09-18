# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (ZippyLang)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include QuickJS
add_subdirectory(QuickJS)

# glob sources to include all cpp files
file(GLOB SOURCES
    ./*.cpp
)

# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
add_executable (Zippy ${SOURCES})

# Add dir to add link
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/QuickJS)

# link QuickJS to the project
target_link_libraries(Zippy quickjs)
