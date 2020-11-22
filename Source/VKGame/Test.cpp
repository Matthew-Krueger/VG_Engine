#include <VG_Engine/Core.hpp>


int main(int argc, char** argv) {

    VG::startEngine();
	VG::Window window(1280, 720, "Window");

	glm::mat4 matrix;
	glm::vec4 vec;
	auto test = matrix * vec;

	while(!window.shouldClose()){

	}

	VG::stopEngine();

}