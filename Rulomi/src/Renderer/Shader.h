#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include "Renderer/ShaderUniform.h"

namespace Rulomi {

	//������ӿ� refclass ������
	class Shader
	{
	public:
		//
		//Shader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		//��Ȼ shaderID Ҳ��Ψһʶ��          ������---��ʱ�����hash ��ͻ
		virtual const std::string& GetName() const = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		static Reference<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		static Reference<Shader> Create(const std::string& path);

	};


	//�ṩһЩcashed shader
	class ShaderLibrary
	{
	public:
		//��chashed shader����� ��cashed shader
		void Add(const Reference<Shader>& shader);
		void Add(const std::string customizedName ,const Reference<Shader>& shader);

		//load ��ʾ��û���Ѿ�����õ�shader
		//��Ҫ��glsl ���� -> ���� ->����
		Reference<Shader> Load(const std::string& path);
		//���� �Զ��建��shader������
		Reference<Shader> Load(const std::string& shaderName, const std::string& path);
		// �ӻ����л�ȡshader
		Reference<Shader> GetShaderByName(const std::string& name);

		bool ShaderCashed(const std::string& shaderName) const;

	private:
		//���� + ָ��Ԥ��shader��ָ��
		std::unordered_map < std::string, Reference<Shader> > m_Shaders;


	};


}