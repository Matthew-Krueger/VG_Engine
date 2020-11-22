
#include "UtilsAPI.hpp"

bool VG::hasStarted = false;

void VG::startEngine(){

    if (!glfwInit()) {
        std::cerr << "Unable to init GLFW\n";
    }

    VG::hasStarted = true;

}

void VG::stopEngine(){

    glfwTerminate();

    VG::hasStarted = false;

}

bool VG::linkTest() {
    return true;
}
