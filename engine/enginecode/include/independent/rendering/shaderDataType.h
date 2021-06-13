/** \file shaderDataType.h */
#pragma once
#include <cstdint>

namespace Engine
{
	/*	\enum shaderDataType.h 
	*	\brief Enum class for all the shader data types.
	*/
	enum class ShaderDataType
	{
		None = 0, 
		Float, Float2, Float3, Float4,
		Short, Short2, Short3, Short4,
		Byte2, Byte4,
		Mat3, Mat4,
		Int,
	};

	namespace SDT
	{
		static uint32_t size(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Mat3:   return 4 * 3 * 3;	//size of a mat3 is 36 bytes.
			case ShaderDataType::Mat4:   return 4 * 4 * 4;	//size of a mat4 is 64 bytes.
			case ShaderDataType::Float:  return 4;			//size of a float is 4 bytes.
			case ShaderDataType::Float2: return 4 * 2;		//2 floats is 8 bytes.
			case ShaderDataType::Float3: return 4 * 3;		//3 floats is 12 bytes.
			case ShaderDataType::Float4: return 4 * 4;		//4 floats is 16 bytes.
			case ShaderDataType::Short:  return 2;			//size of a short is 2 bytes.
			case ShaderDataType::Short2: return 2 * 2;		//2 floats is 4 bytes.
			case ShaderDataType::Short3: return 2 * 3;		//3 floats is 6 bytes.
			case ShaderDataType::Short4: return 2 * 4;		//4 floats is 8 bytes.
			case ShaderDataType::Byte2:  return 1 * 2;		//2 bytes.
			case ShaderDataType::Byte4:  return 1 * 4;		//4 bytes.
			case ShaderDataType::Int:    return 4;			//4 bytes.
			default: return 0;
			}
		}

		static uint32_t componentCount(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Mat3:   return 3 * 3;	//component is 9.
			case ShaderDataType::Mat4:   return 4 * 4;	//component is 16.
			case ShaderDataType::Float:  return 1;		//number of componets is 1.
			case ShaderDataType::Float2: return 2;		//component is 2.
			case ShaderDataType::Float3: return 3;		//component is 3.
			case ShaderDataType::Float4: return 4;		//component is 4.
			case ShaderDataType::Short:  return 1;		//number of componets is 1.
			case ShaderDataType::Short2: return 2;		//component is 2.
			case ShaderDataType::Short3: return 3;		//component is 3.
			case ShaderDataType::Short4: return 4;		//component is 4.
			case ShaderDataType::Byte2:  return 2;		//component is 2.
			case ShaderDataType::Byte4:  return 4;		//component is 4.
			case ShaderDataType::Int:    return 1;		//component is 1
			default: return 0;
			}
		}

		static uint32_t std140align(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Mat3:   return 4 * 3 * 3;	//size of a mat3 is 36 bytes.
			case ShaderDataType::Mat4:   return 4 * 4 * 4;	//size of a mat4 is 64 bytes.
			case ShaderDataType::Float:  return 4;			//size of a float is 4 bytes.
			case ShaderDataType::Float2: return 4 * 2;		//2 floats is 8 bytes.
			case ShaderDataType::Float3: return 4 * 4;		//4 floats is 16 bytes.  4! not 3, to do with alignment, must be aligned to N2 or N4.
			case ShaderDataType::Float4: return 4 * 4;		//4 floats is 16 bytes.
			case ShaderDataType::Short:  return 2;			//size of a short is 2 bytes.
			case ShaderDataType::Short2: return 2 * 2;		//2 floats is 4 bytes.
			case ShaderDataType::Short3: return 2 * 4;		//4 floats is 8 bytes. 4! not 3, to do with alignment, must be aligned to N2 or N4.
			case ShaderDataType::Short4: return 2 * 4;		//4 floats is 8 bytes.
			case ShaderDataType::Byte2:  return 1 * 2;		//2 bytes.
			case ShaderDataType::Byte4:  return 1 * 4;		//4 bytes.
			default: return 0;
			}
		}
	}
}
