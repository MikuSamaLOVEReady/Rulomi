#pragma once

// 抽象层 Index Buff + Vertex Buffer

namespace Rulomi {
	//设置每种属性 所对应类型的 对应字节大小
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	// 每种属性所占总字节的映射
	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:			return 4;
		case ShaderDataType::Int2:			 return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		RLM_CORE_ASSERT(false, "Unknown Shader Data Type!");
		return 0;
	}


	//每种 顶点属性 的 详细信息 
	struct BufferElement  
	{
		std::string Name;            
		ShaderDataType Type;
		uint32_t Size;             //这个属性词条占整个顶点所有属性容量的多少字节( Stride
		uint32_t Offset;         //计算该属性 在顶点总属性长度中的起始位置
		bool Normalized;


		//默认构造函数 
		//BufferElement() {}

		//有点
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		//获取 数组中元素的个数。 与计算数据所占bytes容量不同
		//
		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3 * 3;
			case ShaderDataType::Mat4:    return 4 * 4;
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}
			RLM_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	// BufferLayout 类的目的是将 之前VB里 每种属性的offset设置好 然后把 顶点的stride（总容量）也设置了。
	class BufferLayout
	{
	public:
		//default cosntuctor 为什么要加/?
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		//两接口用于获取成员数据
		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				//BufferElement 在构造的时候offset 都是默认为0
				element.Offset = offset;
				//将offset 设置为 当前属性的长度+之前属性的长度
				offset += element.Size;
				//stride 就自然将当前属性的总长累加
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;

	};


	//为了平台独立 这个是一个抽象接口 没有数据 构造这个class的接口
	//只能是构造他的子类(
	class VertexBuffer
	{
	public:
		virtual	~VertexBuffer() {}

		virtual void Bind()	const = 0;
		virtual void Unbind()  const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		//size_t == unsigned long long 
		static VertexBuffer* Create(float* vertices, size_t sizes);

	};

	//绘制顺序IB
	class IndexBuffer
	{
	public:
		virtual	~IndexBuffer() {}

		virtual void Bind()  const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;
		//size_t == unsigned long long 
		// uint32_t == unsigned int 
		static IndexBuffer* Create(uint32_t* vertices, uint32_t sizes);
	};





}