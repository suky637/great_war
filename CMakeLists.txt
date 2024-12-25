cmake_minimum_required(VERSION 3.5.0)
project(ww1_game VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ext/openal-soft-master)

set(SFML_BUILD_AUDIO TRUE)
set(OPENAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/openal-soft-master/include)
set(OPENAL_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/ext/openal-soft-master)

add_subdirectory(ext/SFML-2.6.2)
add_subdirectory(ext/json-develop)


#file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(ww1_game 
    src/main.cpp
    src/gamelogic.cpp
    src/scene_map.cpp
    src/camera_movement.cpp
    src/mainmenu.cpp
    src/choose_save.cpp
    src/myguilib/Button.cpp
    src/myguilib/Component.cpp
    src/myguilib/Frame.cpp
    src/myguilib/GUI.cpp
    src/myguilib/Label.cpp
    src/myguilib/DynLabel.cpp
    src/myguilib/ImageBox.cpp
    src/myguilib/DynImageBox.cpp
    src/engine/EngineFunctions.cpp
    src/engine/Scene.cpp
    src/engine/Script.cpp
    src/engine/time_manager.cpp
    src/engine/string_manip.cpp
    src/Physics/PIP.cpp
    src/scripts/countryManager.cpp
    src/language/gws.cpp
    src/language/global_var.cpp
)

target_link_libraries(ww1_game sfml-audio sfml-graphics sfml-window sfml-system OpenAL nlohmann_json)
target_include_directories(ww1_game PRIVATE ${CMAKE_SOURCE_DIR}/include/)