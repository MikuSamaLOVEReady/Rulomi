#pragma once



namespace Rulomi {

	//framebuffer的不同类型attachments的不同设置格式
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

	// wrapper struct //TODO：
	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFmt format)
			:TextureFormat(format) {}

		FramebufferTextureFmt  TextureFormat = FramebufferTextureFmt::None;
	};

	//fb attachments specification (容器而已 用于从出多个FB)
	struct FramebufferAttachements
	{
		FramebufferAttachements() = default;
		//接受一个 array其中元素是FramebufferTextureSpecification（指明）
		FramebufferAttachements(std::initializer_list<FramebufferTextureSpecification>attachments)
			:Attachements(attachments) {}
		std::vector<FramebufferTextureSpecification> Attachements;
	};



	//frame buffer 的缓冲属性
	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		FramebufferAttachements Attachements;
		// sample ？ 	
		uint32_t  sample = 1;
		//表示是不是 要把当前这个frame buffer 渲染（交换）到窗口上
		bool SwapChainTarget = false;
	};


	// frambuffer 包含了超多东西, 深度纹理 颜色纹理 
	//接口类
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



