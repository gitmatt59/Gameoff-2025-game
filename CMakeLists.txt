cmake_minimum_required(VERSION 3.10)
project(endoparasiticClone)

set(CMAKE_CXX_STANDARD 17)

# Add GLAD
add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include)

# Create executable (with stb_image.cpp)
add_executable(endoparasitic_clone
    src/stb_image.c
    src/main.cpp
)

# Include project headers
target_include_directories(endoparasitic_clone PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(endoparasitic_clone PRIVATE /usr/include/stb)
# Find GLFW
find_package(glfw3 REQUIRED)

# Find GLM (header-only, no linking actually needed)
find_package(glm CONFIG REQUIRED)

# Link everything
target_link_libraries(endoparasitic_clone PRIVATE glad glfw glm::glm)
	
