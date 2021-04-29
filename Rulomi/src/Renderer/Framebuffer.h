#pragma once



namespace Rulomi {

	//framebuffer�Ĳ�ͬ����attachments�Ĳ�ͬ���ø�ʽ
	enum class FramebufferTextureFmt
	{
		None = 0,

		//color attachement
		RGBA8,
		R_INTERGER,

		//dephth attachment
		DEPTH24STENCIL8,

		Depth = DEPTH24STENCIL8
	};

	// wrapper struct //TODO��
	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFmt format)
			:TextureFormat(format) {}

		FramebufferTextureFmt  TextureFormat = FramebufferTextureFmt::None;
	};

	//fb attachments specification (�������� ���ڴӳ����FB)
	struct FramebufferAttachements
	{
		FramebufferAttachements() = default;
		//����һ�� array����Ԫ����FramebufferTextureSpecification��ָ����
		FramebufferAttachements(std::initializer_list<FramebufferTextureSpecification>attachments)
			:Attachements(attachments) {}
		std::vector<FramebufferTextureSpecification> Attachements;
	};



	//frame buffer �Ļ�������
	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		FramebufferAttachements Attachements;
		// sample �� 	
		uint32_t  sample = 1;
		//��ʾ�ǲ��� Ҫ�ѵ�ǰ���frame buffer ��Ⱦ����������������
		bool SwapChainTarget = false;
	};


	// frambuffer �����˳��ණ��, ������� ��ɫ���� 
	//�ӿ���
	class Framebuffer
	{
	public:
		virtual void Bind()  = 0;
		virtual void UnBind() =  0;
		virtual ~Framebuffer() = default;
		virtual void ResizeBuffer(uint32_t width, uint32_t height) = 0;
		virtual uint32_t GetColorTextureAttachmentRendererID(uint32_t index = 0) const = 0;
		virtual uint32_t GetDepthAttachmentRendererID() const = 0;
		virtual const FramebufferSpecification& GetSpecification() const = 0;
		//read pixel from GPU to CPU
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;
		//
		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;
	

		static Reference<Framebuffer> Create(FramebufferSpecification& specifiaction);
	};

}



