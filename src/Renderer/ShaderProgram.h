#pragma once

#include<string>

namespace Renderer {
	class ShaderProgram {
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
	};
}