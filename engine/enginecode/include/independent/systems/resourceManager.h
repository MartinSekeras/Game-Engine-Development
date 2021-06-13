/* \file resourceManager.h */
#pragma once

#include "system.h"
namespace Engine
{
	/**
	\class ResourceManager
	A system to manage resources
	*/

	class ResourceManager : public System
	{
	public:
		void start(SystemSignal init = SystemSignal::None, ...)override {}; //!< Start the system
		void stop(SystemSignal close = SystemSignal::None, ...)override {}; //!< Stop the system

		//std::shared_ptr<Shaders>addShader(const char* filepath);//!< Add a shader
		//std::shared_ptr<Textures>addTexture(const char* filepath);//!< Add a texture by loading from file name
		//std::shared_ptr<Textures>addTexture(const char* name,unsigned int width, unsigned int height, unsigned int channels, unsigned char * data);//!< Create a texture

	private:
		//assetManager<Shaders>m_shaders;//!< Shaders
		//assetManager<Textures>m_textures;//!< Textures
		//const char* parseFilePath(const char* filepath);//!< Strip preceeding dirs and file extension
	};

}