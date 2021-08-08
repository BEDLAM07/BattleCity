#pragma once

#include<glad/glad.h>
#include<string>

namespace Renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader); // создаем конструктур
		~ShaderProgram(); // деструктор
		bool isCompiled() const { return m_isCompiled; }// функция возвращающая флаг
		void use() const; // функция включающая шейдеры

		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;
		ShaderProgram& operator = (ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept; 


	private:
		bool createShader(const std::string& sourse, const GLenum shaderType, GLuint& shaiderID);
		bool m_isCompiled = false; // флаг, который показывает норнально ли скомпилировались шейдеры
		GLuint m_ID = 0;
	};
}