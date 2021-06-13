/* \file frameBuffer.h */
#pragma once

#include "events/windowEvents.h"
#include "rendering/textures.h"
#include <vector>
#include <memory>

namespace Engine {
	enum class AttachmentType { None, Colour, Depth, Stencil, DepthAndStencil };

	using Attachment = std::pair < AttachmentType, bool>;

	class FrameBufferLayout
	{
	public:
		FrameBufferLayout() {}; //!< Constructor
		FrameBufferLayout(const std::initializer_list<Attachment>& attachments, uint32_t stride = 0) :m_attachments(attachments) {}
		void addAttachment(AttachmentType type, bool sampled = false) {
			m_attachments.push_back(Attachment(type, sampled));
		}
		std::vector<Attachment>::iterator begin() { return m_attachments.begin(); }//!< Begin iterator
		std::vector<Attachment>::iterator end() { return m_attachments.end(); }//!< End iterator
		std::vector<Attachment>::const_iterator begin() const { return m_attachments.begin(); }//!< Begin constant iterator
		std::vector<Attachment>::const_iterator end() const { return m_attachments.end(); }//!< End constant iterator

	private:
		std::vector<Attachment> m_attachments;
	};


	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default; //!< Destructor
		virtual void onWindowResize(WindowResizeEvent& e) = 0;//!< On resize function
		virtual uint32_t getID() = 0; //!< Get API specific render ID
		virtual void use() = 0; //!< Bind the framebuffer
		virtual std::shared_ptr<Textures> getTarget(uint32_t index) = 0; //!< Get the sample target at index

		static FrameBuffer* create(glm::ivec2 size, FrameBufferLayout layout); //!< API agnostic create function
		static FrameBuffer* createDefault(); //!< API agnostic create default frame buffer function

	protected:
		glm::ivec2 m_size; //!< Size of framebuffer
		FrameBufferLayout m_layout; //!< Layout of FBO attachments
		std::vector<std::shared_ptr<Textures>> m_sampledTargets;
	};
}