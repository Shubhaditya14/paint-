cmake_minimum_required(VERSION 3.20)
project(Paint VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML 3.0.0 discovery
# Note: SFML 3 uses lowercase component names for targets
find_package(SFML 3.0.0 COMPONENTS Graphics Window System REQUIRED)

add_executable(Paint src/main.cpp)

# Include directories
target_include_directories(Paint PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link SFML libraries
target_link_libraries(Paint PRIVATE SFML::Graphics SFML::Window SFML::System)

# macOS specific configuration
if(APPLE)
    set_target_properties(Paint PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.kilo.paint"
        MACOSX_BUNDLE_BUNDLE_NAME "Paint"
    )
endif()