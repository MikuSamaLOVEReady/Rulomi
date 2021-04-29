#pragma once


#include "Renderer/Framebuffer.h"

namespace Rulomi {

	class OpenGLFramebuffer:public Framebuffer
	{
	public:
		OpenGLFramebuffer() = default;
		OpenGLFramebuffer(FramebufferSpecification& specifiaction);
		virtual ~OpenGLFramebuffer();

		virtual void ResizeBuffer(uint32_t width, uint32_t height) override;
		void Resize();
		virtual void Bind() override;
		virtual void UnBind() override;
		virtual uint32_t GetColorTextureAttachmentRendererID( uint32_t index =0 ) const override;
		virtual uint32_t GetDepthAttachmentRendererID() const override;
		virtual const FramebufferSpecification& GetSpecification() const override;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;
		virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;


	private:
		uint32_t m_RendererID = 0;
		//����֡�趨
		FramebufferSpecification m_Specification;

		//��Ȼ���  specification �����趨
		std::vector<FramebufferTextureSpecification> m_ColorAttachmentsSpecification;
		FramebufferTextureSpecification m_DepthAttachementsSpecification = FramebufferTextureFmt::None;

		//Attachment��ID
		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachments;


	};

}


