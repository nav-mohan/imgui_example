cmake_minimum_required(VERSION 3.11)
project(SampleDearImgui LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)


add_compile_options($<$<CONFIG:Debug>:-O0> $<$<CONFIG:Debug>:-g>)


# must build GLAD and GLFW before IMGUI
# disable WAYLAND backend for GLFW because I dont have wayland dev-tools
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "build for wayland backend")
add_subdirectory(libs/glfw)
add_subdirectory(libs/glad)

# build-rules for IMGUI (ImGUI source-code does not have a CMakeLists)
set (IMGUI_DIR libs/imgui)
set (IMGUI_ESSENTIALS_SRC  
	${IMGUI_DIR}/imgui.cpp 
	${IMGUI_DIR}/imgui_draw.cpp 
	${IMGUI_DIR}/imgui_widgets.cpp 
	${IMGUI_DIR}/imgui_tables.cpp 
	${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp 
	${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        )
add_library(imgui ${IMGUI_ESSENTIALS_SRC})
target_link_libraries(imgui glfw)
target_include_directories(imgui PUBLIC ${IMGUI_DIR})

# Set FFmpeg paths
set(FFMPEG_ROOT ${CMAKE_SOURCE_DIR}/libs/FFmpeg/build)
include_directories(${FFMPEG_ROOT}/include)
link_directories(${FFMPEG_ROOT}/lib)

set(SOURCES_CPP 
        main.cpp 
        EditableTable.cpp
        ClockWindow.cpp
        table.cpp
        UseImGUI.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCES_CPP})

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad
    imgui
    avutil 
    avformat 
    avdevice
    avcodec 
    swscale
    swresample
    )

# Ensure FFmpeg shared libraries are found at runtime
set_target_properties(${PROJECT_NAME} PROPERTIES
    BUILD_RPATH ${FFMPEG_ROOT}/lib
)