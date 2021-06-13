/* \file resourceManager.cpp */

#include "engine_pch.h"
#include "systems/resourceManager.h"
#include "systems/log.h"
#include <cstdarg>

namespace Engine {
	/*void ResourceManager::start(SystemSignal init, ...)
	{
		if (init == SystemSignal::ResourceCount)
		{
			va_list args;
			va_start(args, init);
			uint32_t shadersCapacity = va_arg(args, uint32_t);
			uint32_t texturesCapacity = va_arg(args, uint32_t);

			va_end(args);

			//m_shaders.reserve(shadersCapacity);
			//m_textures.reserve(texturesCapacity);

		}
	}

	void ResourceManager::stop(SystemSignal close, ...)
	{
		//m_shaders.clear();
	}

	std::shared_ptr<Shaders> ResourceManager::addShader(const char* filepath)
	{
		const char* parsedFilePath = parseFilePath(filepath);
		if (m_shaders.contains(parsedFilePath))return m_shaders.get(parsedFilePath);
		else
		{
			std::shared_ptr<Shaders> temp(Shaders::create(filepath));
			m_shaders.add(parsedFilePath, temp);
			return m_shaders.get(parsedFilePath);
		}
	}	
	std::shared_ptr<Textures> ResourceManager::addTexture(const char* filepath)
	{
		const char* parsedFilePath = parseFilePath(filepath);
		if (m_textures.contains(parsedFilePath))return m_textures.get(parsedFilePath);
		else
		{
			std::shared_ptr<Textures> temp(Textures::create(filepath));
			m_textures.add(parsedFilePath, temp);
			return m_textures.get(parsedFilePath);
		}
	}*/
}