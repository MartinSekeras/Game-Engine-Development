/** \file OpenGLShader.cpp */

#include "engine_pch.h"
#include <fstream>
#include <string>
#include <array>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLShader.h"
#include "systems/log.h"

namespace Engine
{
	OpenGLShader::OpenGLShader(const char * vertexFilePath, const char * fragmentFilePath)
	{
		//declarations.
		std::string line;
		std::string vertexSource;
		std::string fragmentSource;
		
		//vertex shader file path.
		std::fstream handle(vertexFilePath, std::ios::in);
		//check that it has vertex file path.
		if (handle.is_open())
		{
			//opens fine, so need to read it...
			//whilst open, read it in line by line, adding it to source.
			while (getline(handle, line))
			{
				vertexSource += (line + "\n");
			}
		}
		else
		{
			//otherwise throw error and return.
			Log::error("NOT able to open VERTEX SHADER source: {0}", vertexFilePath);
			return;
		}
		//close the file.
		handle.close();

		//fragment shader file path.
		handle.open(fragmentFilePath, std::ios::in);
		//check that it has fragment filepath
		if (handle.is_open())
		{
			//opens fine, so need to read it...
			//whilst open, read it in line by line, adding it to source.
			while (getline(handle, line))
			{
				fragmentSource += (line + "\n");
			}
		}
		else
		{
			//otherwise throw error and return.
			Log::error("NOT able to open FRAGMENT SHADER source: {0}", fragmentFilePath);
			return;
		}
		//close the file.
		handle.close();

		//got source for each, so compile and link them, converting them to c_strings.
		compileAndLink(vertexSource.c_str(), fragmentSource.c_str());
	}

	OpenGLShader::OpenGLShader(const char * filePath)
	{
		//enum Region for different types of shaders.
		//NOTE - not the best to only declare locally.
		//TO DO - will need to move elsewhere soon.
		enum Region { None = -1, Vertex = 0, Fragment, Geometry, TessellationControl, TessellationEvalution, Compute };

		//declarations.
		std::string line;
		std::array<std::string, Region::Compute + 1> source;		//adding one to Compute (which 5 in the enum) will make an array of 6 elements.
		uint32_t region = Region::None;		// index for which region we are in, initialised to None(-1).

		std::fstream handle(filePath, std::ios::in);
		//check that it has the file path.
		if (handle.is_open())
		{
			//opens fine, so need to read it...
			//whilst open, read it in line by line, adding it to source.
			while (getline(handle, line))
			{
				//which region are we in? 
				//continue is to skip of the #vertex /#fragment etc part of the text document.
				if (line.find("#region Vertex") != std::string::npos) {
					region = Region::Vertex; continue;
				}
				if (line.find("#region Fragment") != std::string::npos) {
					region = Region::Fragment; continue;
				}
				if (line.find("#region Geometry") != std::string::npos) {
					region = Region::Geometry; continue;
				}
				if (line.find("#region TessellationControl") != std::string::npos) {
					region = Region::TessellationControl; continue;
				}
				if (line.find("#region TessellationEvalution") != std::string::npos) {
					region = Region::TessellationEvalution; continue;
				}
				if (line.find("#region Compute") != std::string::npos) {
					region = Region::Compute; continue;
				}

				//if region not = none (it has a value), then stick it into region.
				if(region != Region::None)
				{
					source[region] += (line + "\n");
				}
			}
		}
		else
		{
			//otherwise throw error and return.
			Log::error("NOT able to open SINGLE FILE source: {0}", filePath);
			return;
		}
		//close the file.
		handle.close();

		//got source, so compile and link, converting them to c_strings.
		//TODO: this below will only compile Vertex and Fragment shaders, need expansion to include other shaders.
		//HOW: pass it an array maybe, integar of flags to say which is present, flag system could work.
		compileAndLink(source[Region::Vertex].c_str(), source[Region::Fragment].c_str());
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_OpenGL_ID);
	}

	void OpenGLShader::uploadInt(const char * name, int value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform1i(location, value);
	}

	void OpenGLShader::uploadFloat(const char * name, float value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform1f(location, value);
	}

	void OpenGLShader::uploadFloat2(const char * name, const glm::vec2 & value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::uploadFloat3(const char * name, const glm::vec3 & value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::uploadFloat4(const char * name, const glm::vec4 & value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::uploadMat4(const char * name, const glm::mat4 & value)
	{
		uint32_t location = glGetUniformLocation(m_OpenGL_ID, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));

	}

	void OpenGLShader::compileAndLink(const char * vertexShaderScr, const char * fragmentShaderScr)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		//get the source and compile it.
		const GLchar* source = vertexShaderScr;
		glShaderSource(vertexShader, 1, &source, 0);
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		//check it has compiled, error message if not and delete it.
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			//deleting it here if it has failed to compile.
			glDeleteShader(vertexShader);
			return;
		}

		//fragment shader stuff...
		//create the fragment shader.
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//give it the source and compile it.
		source = fragmentShaderScr;
		glShaderSource(fragmentShader, 1, &source, 0);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		//check that it has been compiled, delete this AND vertex shader if failed to so.
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			//deleting the fragment AND vertex shaders if it has failed to compile.
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			return;
		}

		//got to link them up with the program.
		//all compile fined, so create the final shader program.
		m_OpenGL_ID = glCreateProgram();
		//attach the vertex and fragment shaders and link them.
		glAttachShader(m_OpenGL_ID, vertexShader);
		glAttachShader(m_OpenGL_ID, fragmentShader);
		glLinkProgram(m_OpenGL_ID);

		GLint isLinked = 0;
		glGetProgramiv(m_OpenGL_ID, GL_LINK_STATUS, (int*)&isLinked);

		//check whether they have linked, if not delete all three shaders.
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_OpenGL_ID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_OpenGL_ID, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(m_OpenGL_ID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return;
		}

		//now linked, can deattach shaders as done with them, just need the final FCprogram.
		glDetachShader(m_OpenGL_ID, vertexShader);
		glDetachShader(m_OpenGL_ID, fragmentShader);
	}
}