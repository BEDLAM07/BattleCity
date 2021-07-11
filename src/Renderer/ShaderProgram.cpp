#include "ShaderProgram.h"

#include<iostream>

namespace Renderer {
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "VERTEX SHADER complite-time error" << std::endl;
			return;
		}
		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "FRAGMENT SHADER complite-time error" << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}

		m_ID = glCreateProgram();
		GLuint shader_program = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success); // проверяем перелинковку
		if (!success)
		{
			GLchar infoLog[1024]; // создаем буфер для записи сообщения об ошибки
			glGetProgramInfoLog(m_ID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Link time error:\n" << infoLog << std::endl;
		}
		else
		{
			m_isCompiled = true;
		}
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	bool ShaderProgram::createShader(const std::string& sourse, const GLenum shaderType, GLuint& shaiderID)
	{
		shaiderID = glCreateShader(shaderType);
		const char* code = sourse.c_str();
		glShaderSource(shaiderID, 1, &code, nullptr);
		glCompileShader(shaiderID);

		GLint success; // переменная для записи инфы
		glGetShaderiv(shaiderID, GL_COMPILE_STATUS, &success); // проверяем ошибки
		if (!success)
		{
			GLchar infoLog[1024]; // создаем буфер для записи сообщения об ошибки
			glGetProgramInfoLog(shaiderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Complite time error:\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}

	// деструктор
	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID);
	}
	void ShaderProgram::use() const
	{
		glUseProgram(m_ID);
	}

	ShaderProgram& ShaderProgram::operator = (ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;
		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;
	}
}