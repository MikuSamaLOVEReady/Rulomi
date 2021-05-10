#include "RulomiPch.h"
#include "OpenGLFramebuffer.h"
#include "glad/glad.h"

namespace Rulomi {

	namespace Utils {
		//attachment ����
		static bool IsDepthFormat(FramebufferTextureFmt format)
		{
			switch (format)
			{
			case FramebufferTextureFmt::DEPTH24STENCIL8:
				return true;
			}
			return false;
		}

		//���ز������� ��
		static GLenum TextureTarget(bool multisampled)
		{
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}
		static void BindTexture(bool multisampled, uint32_t id)
		{
			glBindTexture(TextureTarget(multisampled), id);
		}

		// ���� attachmentID����rendererIDΨһʶ�𣩴�����������
		static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
		{
			glCreateTextures(TextureTarget(multisampled), count, outID);
		}

		static void AttachColorTexture(uint32_t id, int samples, GLenum internalformat,GLenum format, uint32_t width, uint32_t height, int index)
		{
			bool multisampled = samples > 1;
			//���ز���
			if (multisampled)
			{
				//�ڶ�����ʾ�����ĸ���
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				//internalformat
				//format
				glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			//attach the texture to framebuffer GL_COLOR_ATTACHMENT0 ====��������� shader�еڼ���output
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
		}

		static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool multisampled = samples > 1;
			//���ز���
			if (multisampled)
			{
				//�ڶ�����ʾ�����ĸ���
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, format , width, height);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			//attach the depth to framebuffer
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
		}

		static GLenum FindFBColorAttachmentFmt(FramebufferTextureFmt fmt)
		{
			switch (fmt)
			{
				case Rulomi::FramebufferTextureFmt::R_INTERGER:  return GL_RED_INTEGER;
				case Rulomi::FramebufferTextureFmt::RGBA8: return GL_RGBA8;
			}
			return 0;
		}
	

	}
	

	OpenGLFramebuffer::OpenGLFramebuffer(FramebufferSpecification& specifiaction)
		:m_Specification(specifiaction)
	{
		for (auto format : m_Specification.Attachements.Attachements)
		{
			if (!Utils::IsDepthFormat(format.TextureFormat))
				m_ColorAttachmentsSpecification.emplace_back(format);
			else
				m_DepthAttachementsSpecification = format;
		}
		Resize();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachments);
	}

	void OpenGLFramebuffer::ResizeBuffer(uint32_t width, uint32_t height)
	{
		m_Specification.Width = width;
		m_Specification.Height = height;
		//ˢ�´���
		Resize();
	}

	void OpenGLFramebuffer::Resize()
	{
		//������ǳ�ʼ֡
		if (m_RendererID)
		{
			//�����һ֡����
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data() );
			glDeleteTextures(1, &m_DepthAttachments);
			
			m_ColorAttachments.clear();
			m_DepthAttachments = 0;
		}

		//���� framebuffer ----> 
		glCreateFramebuffers(1, &m_RendererID);
			//�󶨵���Ӧ�Ĳ�λ��
			glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
				
			//��ʼΪfb���attachment
			bool multisample = m_Specification.sample > 1;
			if (m_ColorAttachmentsSpecification.size())
			{
				m_ColorAttachments.resize(m_ColorAttachmentsSpecification.size());
				//Ϊ����color attachement����һ�� rendererID
				Utils::CreateTextures(multisample, m_ColorAttachments.data(), m_ColorAttachments.size());
				for (size_t i = 0; i < m_ColorAttachments.size(); i++)
				{
					Utils::BindTexture(multisample, m_ColorAttachments[i]);
					switch (m_ColorAttachmentsSpecification[i].TextureFormat)
					{
						case FramebufferTextureFmt::RGBA8:
							Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.sample, GL_RGBA8, GL_RGBA,m_Specification.Width, m_Specification.Height, i);
							break;
						case FramebufferTextureFmt::R_INTERGER:
							Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.sample, GL_R32I, GL_RED_INTEGER, m_Specification.Width, m_Specification.Height, i);
							break;
					}
				}
			}
			
			if (m_DepthAttachementsSpecification.TextureFormat != FramebufferTextureFmt::None)
			{
				Utils::CreateTextures(multisample, &m_DepthAttachments, 1);
				Utils::BindTexture(multisample, m_DepthAttachments);
				switch (m_DepthAttachementsSpecification.TextureFormat)
				{
					case FramebufferTextureFmt::DEPTH24STENCIL8:
						Utils::AttachDepthTexture(m_DepthAttachments,m_Specification.sample, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT,m_Specification.Width,m_Specification.Height);
						break;
				}
			}

			//��� ���4��colorattachment
			if (m_ColorAttachments.size() > 1)
			{
				RLM_CORE_ASSERT(m_ColorAttachments.size() <= 4, "To much color attachments");
				GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
				//ָ�� fragment  shader�����ղ���������Щbuffer��
				glDrawBuffers(m_ColorAttachments.size(), buffers);
			}
			else if (m_ColorAttachments.empty())
			{
				glDrawBuffer(GL_NONE);
			}

				//�����յ���ɫ���� OpenGLΪ���Ƿ���һ�� colorAttachmentID
				//glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
				//glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
				//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width,
				//	m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
				////�����������ŵ�ʱ��Ĳ���
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				//// GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level
				////�������Ŀ����� attach��frambuffer
				////�ڶ���������   GL_COLOR_ATTACHMENT0 ��ʾ ���FB�еĵڼ���colorATTACHMENT��λ����Ӧ����Ψһʶ���attachment���ͣ�
				////�������� ��attach���������� ���ĸ�����������
				////��һ���� attach��Ŀ�ĵ�
				//// the specified level of the texture object named texture is attached to the framebuffer attachment point named by attachment. 
				//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

				////�����յ��������
				//glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
				//glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
				//glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
				//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

				//RLM_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
			 //glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	//render pass

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);

		int value = -1;
		glClearTexImage(m_ColorAttachments[1], 0, GL_RED_INTEGER, GL_INT, &value);
	}

	void OpenGLFramebuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32_t OpenGLFramebuffer::GetColorTextureAttachmentRendererID(uint32_t index) const
	{
			RLM_CORE_ASSERT(index < m_ColorAttachments.size(), "color attachment index out of range");
			return m_ColorAttachments[index];
	}

	

	uint32_t OpenGLFramebuffer::GetDepthAttachmentRendererID() const
	{
		return m_DepthAttachments;
	}

	const FramebufferSpecification& OpenGLFramebuffer::GetSpecification() const
	{
		return m_Specification;;
	}

	//read pixeldata from texture
	int OpenGLFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		RLM_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size(), "color attachment index out of range");
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);

		return pixelData;
	}

	void OpenGLFramebuffer::ClearAttachment(uint32_t attachmentIndex, int value)
	{
		RLM_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size(), "color attachment index out of range");
		FramebufferTextureFmt colorFmt = m_ColorAttachmentsSpecification[attachmentIndex].TextureFormat;
		//colorFmt GLuint texture, GLint level, GLenum format, GLenum type, const void *data
		//ͨ�����ṩ�� ��clearcolor�� ĳ��color attachment�ı�������ɫ��clear color���õ��� ���ⱻ������ɫ��Ⱦ
		glClearTexImage(m_ColorAttachments[attachmentIndex], 0, Utils::FindFBColorAttachmentFmt(colorFmt), GL_INT, &value);
	}

}