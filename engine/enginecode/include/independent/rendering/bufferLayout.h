/** \file bufferLayout.h */
#pragma once

#include "shaderDataType.h"
#include <vector>

namespace Engine
{
	/** \class VertexBufferElement
	*	\brief Class to take data for each individual element that the vertex buffer layout is made up of. Things like the data type, the size of the take data type, normalised, offset of data type.
	*/
	class VertexBufferElement
	{
	public:
		ShaderDataType m_dataType;		//!< what type of data is this element (float, int etc)
		uint32_t m_size;				//!< int for the size.
		uint32_t m_offset;				//!< int for the length of the offset.
		bool m_normalised;				//!< bool for whether buffer is normalised.

		VertexBufferElement() {};		//!< default constructor.
		VertexBufferElement(ShaderDataType dataType, bool normalised = false) :
			m_dataType(dataType),
			m_size(SDT::size(dataType)),
			m_offset(0),
			m_normalised(normalised)
		{} //!< constructor with params. Takes dataType and whether it is normalised (set to false, so if left blank will be default set to false); with initialisor list linked to above vars (offset init to 0 as this will need calculating).
	private:

	};

	/** \class UniformBufferElement
	*	\brief Class to take data for each element that the uniform buffer layout is made up of. Such as data type, the size of the take data type, normalised, offset of data type.
	*/
	class UniformBufferElement
	{
	public:
		ShaderDataType m_dataType;		//!< what type of data is this element (float, int etc)
		uint32_t m_size;				//!< int for the size.
		uint32_t m_offset;				//!< int for the length of the offset.
		const char *m_name;				//!< name so we can search for it.

		UniformBufferElement() {};		//!< default constructor.
		UniformBufferElement(const char * name, ShaderDataType dataType) :
			m_name(name),
			m_dataType(dataType),
			m_size(SDT::std140align(dataType)),
			m_offset(0)
		{} //!< constructor with params. Takes name and dataType; with initialisor list linked to above vars (offset init to 0 as this will need calculating).
	private:

	};

	/*	\class BufferLayout
	*	\brief Class that's an abstraction of the notion of a buffer layout.
	*/
	template <class G>
	class BufferLayout
	{
	public:
		BufferLayout<G>() {};		//!< default constructor.
		BufferLayout<G>(const std::initializer_list<G>& element, uint32_t stride = 0) :
			m_elements(element),
			m_stride(stride)
		{
			calculateStrideAndOffset();
		}							//!< constructor with params, returns the calculation of stride and offset.
		inline uint32_t getStride() const { return m_stride; }		//!< get the length of the stride.
		void addBufferElement(G element);							//!< add a buffer element.
		inline typename std::vector<G>::iterator begin() { return m_elements.begin(); }				//!< begin, taking first element.
		inline typename std::vector<G>::iterator end() { return m_elements.end(); }					//!< end, taking last element.
		inline typename std::vector<G>::const_iterator begin() const { return m_elements.begin(); }	//!< const begin, taking first element.
		inline typename std::vector<G>::const_iterator end() const { return m_elements.end(); }		//!< const end, taking last element.
	private:
		std::vector<G> m_elements;				//!< buffer elements.
		uint32_t m_stride;						//!< width in bytes of a buffer line.
		void calculateStrideAndOffset();		//!< calculate the stride and offset based on the elements. 
	}; 

	template <class G>
	void BufferLayout<G>::addBufferElement(G element)
	{
		m_elements.push_back(element);
		calculateStrideAndOffset();
	}

	template <class G>
	void BufferLayout<G>::calculateStrideAndOffset()
	{
		/* WHAT THIS NEEDS TO DO:
		* needs to iterate over the elements in the buffer and work out for each element.
		* first offset 0, so set local offset var to 0.
		* next offset will be the accumulation of whatever the sizes were.
		* following one will be the size of all the previous elements added up.
		* stride is the size of all the previous elements added up, plus the last one.
		* EXTRA
		* for new shorter packing of stride using shorts and floats rather than just floats.
		* now initialised stride to 0, if stride has a none 0 value, need to leave it.
		*/

		//create local offset variable and set to 0
		uint32_t l_offset = 0;

		//range based loop
		for (auto& element : m_elements)
		{
			//set class offset to this local offset.
			element.m_offset = l_offset;
			//calculate the offset, add the size of this element to the offset.
			l_offset += element.m_size;
		}

		//if stride is equal to 0, then set the stride to the calculated value of local offset.
		if (m_stride == 0)
		{
			m_stride = l_offset;
		}
	}
	using VertexBufferLayout = BufferLayout<VertexBufferElement>;	//type alias whenever use VertexBufferLayout this what is meant.
	using UniformBufferLayout = BufferLayout<UniformBufferElement>;	//type alias whenever use UniformBufferLayout this what is meant.
}
