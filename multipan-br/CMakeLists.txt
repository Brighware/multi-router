# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)
set(EXTRA_COMPONENT_DIRS
    /home/sbrigh/projects/esp32/esp-idf/examples/common_components/protocol_examples_common
    )
include(/home/sbrigh/projects/esp32/esp-idf/tools/cmake/project.cmake)
project(multi_router)
