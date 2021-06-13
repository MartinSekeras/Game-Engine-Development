/** \file shaders.h */
#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Engine
{
	/** \class Shaders
	*	\brief A class for an API agnostic shaders.
	*/
	class Shaders
	{
	public:
		virtual ~Shaders() = default;					//!< destructor.
		virtual uint32_t getID() const = 0;				//!< gets and returns the renderer ID.
		 
		virtual void uploadInt(const char* name, int value) = 0;					//!< uploading a texture (just an int) 
		virtual void uploadFloat(const char* name, float value) = 0;				//!< upload single float.
		virtual void uploadFloat2(const char* name, const glm::vec2& value) = 0;	//!< upload 2 float combination.
		virtual void uploadFloat3(const char* name, const glm::vec3& value) = 0;	//!< upload 3 float combination.
		virtual void uploadFloat4(const char* name, const glm::vec4& value) = 0;	//!< upload 4 float combination.
		virtual void uploadMat4(const char* name, const glm::mat4& value) = 0;		//!< upload model matrices.

		static Shaders* create(const char* vertexFilePath, const char* fragmentFilePath);	//!< constructor, takes the filepaths for text files; NOTE declared renderAPI.cpp.
		static Shaders* create(const char* filePath);	//!< constructor, takes a single file path, can put all shaders into a single file; NOTE declared renderAPI.cpp.

	private:

	};
}