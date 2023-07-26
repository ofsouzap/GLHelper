add_executable ("terrainscene" "terrainscene.cpp" "gl.c")
target_link_libraries ("terrainscene" "glfw" "GLHelper")

configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/terrain.obj" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/terrain_texture.bmp" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/creature.obj" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/creature_texture.bmp" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/vert_shader.glsl" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/frag_shader.glsl" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)