#include <VG_Engine/Core.hpp>


int main(int argc, char** argv) {

    VG::startEngine();
    VG_INFO_NOSTRIP("Starting Application");

    VG_INFO_NOSTRIP("Creating window");
    auto* gi = new VG::GraphicsInstance;
	auto* window = new VG::Window(1280, 720, "Window");
    gi->initVulkan("VKGame",0,0,1, window);

	glm::mat4 matrix;
	glm::vec4 vec;
	auto test = matrix * vec;

	while(!window->shouldClose()){

	}

    delete gi;
	delete window;
	VG::stopEngine();

}