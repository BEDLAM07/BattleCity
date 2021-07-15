#pragma.once

#include <string>
#include <memory>
#include<map>

namespace Renderer
{
	class ShaderProgram;
}
class ResourceManager {
public:
	ResourceManager(const std::string& executablePath); // конструктор путь к экзешнику
	~ResourceManager() = default; // деструктор

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;
	ResourceManager& operator =(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	// функция для загрузки шейдеров
	std::shared_ptr<Renderer::ShaderProgram> loadShader(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	// функция получения шейдера
	std::shared_ptr<Renderer::ShaderProgram> getShader(const std::string& shaderName);

private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>>ShaderProgramsMap;
	static ShaderProgramsMap m_shaderPrograms;

	std::string m_path;
};