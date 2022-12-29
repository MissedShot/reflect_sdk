cmake_minimum_required(VERSION 3.20)
project(linux_sdk)

# More compile options and summary can be found here: https://gcc.gnu.org/onlinedocs/gcc-12.2.0/gcc/Option-Summary.html#Option-Summary

# -Wno-deprecated-declarations  | Do not warn about uses of functions, variables, and types marked as deprecated by using the deprecated attribute.
# -Wfatal-errors                | causes the compiler to abort compilation on the first error occurred.
set(WARNING_FLAGS "-Wno-deprecated-declarations -Wfatal-errors")

# -march=native         | Specify the name of the target architecture.
# -mtune=native         | Specify the name of the target processor.
# -fvisibility=hidden   | Set the default ELF image symbol visibility.
set(COMPILE_FLAGS "-march=native -mtune=native -fvisibility=hidden")

set(CMAKE_CXX_STANDARD 20)

# -g    | Produce debugging information in the operating system’s native format.
# -O0   | Disable optimization.
set(CMAKE_C_FLAGS_DEBUG "${WARNING_FLAGS} ${COMPILE_FLAGS} -g -O0")

# -std=c++20 | Determine the language standard, also done by CMAKE_CXX_STANDARD above.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c++20")

# -w    | Inhibit all warning messages.
# -O2   | Second level of GCC optimization (can use 3, but it can cause some issues).
set(CMAKE_C_FLAGS_RELEASE "${WARNING_FLAGS} ${COMPILE_FLAGS} -w -O2")

# -fno-rtti     | Disable generation of information about every class.
# -std=c++20    | Determine the language standard, also done by CMAKE_CXX_STANDARD above.
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-rtti -std=c++20")

#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined").

# Include our source files to compile.
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cc")

# Include headers and libs installed in our system (OpenGL, SDL2, etc...).
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Add a library to the project using the specified source files.
add_library(linux_sdk SHARED ${SOURCES})
target_link_libraries(linux_sdk PRIVATE dl pthread SDL2)