# Learning source for some stuff: http://www.opengl-tutorial.org/beginners-tutorials

add_library ("GLHelper"
	"SceneObject.h"
	"SceneObject.cpp"
	"ShaderProgram.h"
	"ShaderProgram.cpp"
	"FileReader.h"
	"FileReader.cpp"
	"Texture.h"
	"Texture.cpp"
	"ImageData.h"
	"ImageData.cpp"
	"Camera.h"
	"Camera.cpp"
	"ModelReader.h"
	"ModelReader.cpp"
	"stb_image.h" # Downloaded from https://github.com/nothings/stb/blob/master/stb_image.h
 )
target_link_libraries ("GLHelper" "glm")

# Building examples
# To build the examples, set the GLHELPER_BUILD_EXAMPLES variable to ON.

if (DEFINED GLHELPER_BUILD_EXAMPLES AND GLHELPER_BUILD_EXAMPLES)
	add_subdirectory ("examples")
endif ()