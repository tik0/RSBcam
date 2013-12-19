cmake_minimum_required (VERSION 2.6)

# Set the project name to the name of the folder
string (REGEX MATCH "[^/]+$" PROJECT_NAME "${CMAKE_CURRENT_BINARY_DIR}")
message (STATUS "Set PROJECT_NAME to ${PROJECT_NAME}")

project ("${PROJECT_NAME}")

# Set the include pathe
include_directories(
    /usr/local/include/opencv
#     /usr/local/include
#     /usr/include
    /usr/include/rsb0.9
    /usr/include/rsc0.9
#     /usr/include/c++
    ${RSB_INCLUDE_DIRS}                                             # RSB
    "../includes"                                                # Other includes like converters and stuff
    "${CMAKE_CURRENT_BINARY_DIR}"                                   # add the binary tree to the search path for include files
)

# add the executable
add_executable ("${PROJECT_NAME}" main.cxx)

# Link the executable to the library.
link_directories (
    "$ENV{SDKTARGETSYSROOT}/usr/lib"
)
target_link_libraries (
    "${PROJECT_NAME}"
    rsb
    boost_regex-mt
    boost_date_time-mt
    boost_program_options-mt
    boost_system-mt
    rsc
)

# Get rid of depricated warnings
SET (
    CMAKE_C_FLAGS
    -Wno-deprecated-declarations
)

SET (
    CMAKE_CXX_FLAGS
    -Wno-deprecated-declarations
)