cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(2048)

# Dependencies
find_package(raylib 4.0.0 QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
	include(FetchContent)
	FetchContent_Declare(
			raylib
			URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
	)
	FetchContent_GetProperties(raylib)
	if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(raylib)
		set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
		add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
	endif()
endif()

set(SRCS
		src/main.cpp)

set(HEADERS
		src/Game/Core.hpp
		src/ECS/EntityManager.hpp
		src/ECS/Component.hpp
		src/MyRayLib/MyRayLib.hpp
		src/Renderer/Renderer.hpp
		src/Renderer/TextRenderer.hpp
		src/Error/Error.hpp)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS} ${RESOURCE_FILES})

target_link_libraries(${PROJECT_NAME} raylib)