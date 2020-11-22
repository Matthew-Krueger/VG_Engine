
#include "UtilsAPI.hpp"
#include "../Display/DisplaysAPI.hpp"

namespace VG{

    bool hasStarted = false;


    void startEngine(const std::string& logFileLocation){

        VG::Log::Init(logFileLocation);

        VG_CORE_TRACE("Starting windowing system.");
        if (!glfwInit()) {
            VG_CORE_CRITICAL_NOSTRIP("Unable to init GLFW");
        }


        VG::hasStarted = true;

    }

    void stopEngine(){

        glfwTerminate();

        VG::hasStarted = false;

        fflush(stdout);

    }

    bool linkTest() {
        return true;
    }


}