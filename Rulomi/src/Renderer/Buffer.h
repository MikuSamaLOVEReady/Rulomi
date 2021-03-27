#pragma once

// ����� Index Buff + Vertex Buffer

namespace Rulomi {
	//����ÿ������ ����Ӧ���͵� ��Ӧ�ֽڴ�С
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	// ÿ��������ռ���ֽڵ�ӳ��
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


	//ÿ�� �������� �� ��ϸ��Ϣ 
	struct BufferElement  
	{
		std::string Name;            
		ShaderDataType Type;
		uint32_t Size;             //������Դ���ռ���������������������Ķ����ֽ�( Stride
		uint32_t Offset;         //��������� �ڶ��������Գ����е���ʼλ��
		bool Normalized;


		//Ĭ�Ϲ��캯�� 
		//BufferElement() {}

		//�е�
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		//��ȡ ������Ԫ�صĸ����� �����������ռbytes������ͬ
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

	// BufferLayout ���Ŀ���ǽ� ֮ǰVB�� ÿ�����Ե�offset���ú� Ȼ��� �����stride����������Ҳ�����ˡ�
	class BufferLayout
	{
	public:
		//default cosntuctor ΪʲôҪ��/?
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		//���ӿ����ڻ�ȡ��Ա����
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
				//BufferElement �ڹ����ʱ��offset ����Ĭ��Ϊ0
				element.Offset = offset;
				//��offset ����Ϊ ��ǰ���Եĳ���+֮ǰ���Եĳ���
				offset += element.Size;
				//stride ����Ȼ����ǰ���Ե��ܳ��ۼ�
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;

	};


	//Ϊ��ƽ̨���� �����һ������ӿ� û������ �������class�Ľӿ�
	//ֻ���ǹ�����������(
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

	//����˳��IB
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