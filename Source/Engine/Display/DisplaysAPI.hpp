/************************************************************************************
* VG Engine is licensed under a BSD 3-Clause License                                *
*                                                                                   *
* BSD 3-Clause License                                                              *
*                                                                                   *
* Copyright (c) 2020, Matthew Krueger                                               *
* All rights reserved.                                                              *
*                                                                                   *
* Redistribution and use in source and binary forms, with or without                *
* modification, are permitted provided that the following conditions are met:       *
*                                                                                   *
* 1. Redistributions of source code must retain the above copyright notice, this    *
*    list of conditions and the following disclaimer.                               *
*                                                                                   *
* 2. Redistributions in binary form must reproduce the above copyright notice,      *
*    this list of conditions and the following disclaimer in the documentation      *
*    and/or other materials provided with the distribution.                         *
*                                                                                   *
* 3. Neither the name of the copyright holder nor the names of its                  *
*    contributors may be used to endorse or promote products derived from           *
*    this software without specific prior written permission.                       *
*                                                                                   *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"       *
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE         *
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE    *
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE      *
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL        *
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR        *
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER        *
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,     *
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE     *
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.              *
************************************************************************************/

#pragma once
#include "../Win32Exports.hpp"


namespace VG {

    extern bool enableValidationLayers;

    /**
     * Represents a window object
     */
	class VG_API Window {
	private:
		void* window;

	public:
	    /**
	     * Constructs a window object
	     * @param width The width of the window
	     * @param height The height of the window
	     * @param windowTitle The title of the window
	     */
		Window(int width, int height, const std::string& windowTitle);
		~Window();

		/**
		 * Asks the driver if the window should close for any reason.
		 * \note Also polls for updates
		 * @return Whether the window should close.
		 */
		[[nodiscard]] bool shouldClose() const;

	};

	class VG_API GraphicsInstance{
	private:
	    VkInstance instance;
	    void createInstance(const std::string &applicationName, uint32_t appVersion_major,
                            uint32_t appVersion_minor, uint32_t appVersion_patch);

	public:
	    GraphicsInstance() = default;
	    ~GraphicsInstance();


	    void initVulkan(const std::string& applicationName, uint32_t appVersion_major, uint32_t appVersion_minor, uint32_t appVersion_patch);
    };

}