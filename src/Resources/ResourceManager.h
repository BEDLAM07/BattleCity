#pragma.once

#include <string>
#include <memory>
#include<map>

namespace Renderer
{
	class ShaderProgram;
	class Texture2D;
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
	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);

	// функция получения шейдера
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);

	//функция для загрузки текстур
	static std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
	static std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);

private:
	
	std::string getFileString(const std::string& relativeFilePath) const;

	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>>ShaderProgramsMap;
	ShaderProgramsMap m_shaderPrograms;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	TexturesMap m_textures;

	std::string m_path;
};