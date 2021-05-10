#pragma once

#include "RulomiCore/Core.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "RulomiCore/Buffer.h"

namespace Rulomi {

	enum class MaterialFlag
	{
		None = BITMove(0),
		DepthTest = BITMove(1),
		Blend = BITMove(2)
	};

	class Material
	{
		friend class MaterialInstance;
	public:
		Material(const Reference<Shader>& shader);
		virtual ~Material();

		void Bind() const;

		uint32_t GetFlags() const { return m_MaterialFlags; }
		void SetFlag(MaterialFlag flag) { m_MaterialFlags |= (uint32_t)flag; }

		template <typename T>
		void Set(const std::string& name, const T& value)
		{
			auto decl = FindUniformDeclaration(name);
			// HZ_CORE_ASSERT(decl, "Could not find uniform with name '{0}'", name);
			HZ_CORE_ASSERT(decl, "Could not find uniform with name 'x'");
			auto& buffer = GetUniformBufferTarget(decl);
			buffer.Write((byte*)&value, decl->GetSize(), decl->GetOffset());

			for (auto mi : m_MaterialInstances)
				mi->OnMaterialValueUpdated(decl);
		}

		void Set(const std::string& name, const Reference<Texture>& texture)
		{
			auto decl = FindResourceDeclaration(name);
			uint32_t slot = decl->GetRegister();
			if (m_Textures.size() <= slot)
				m_Textures.resize((size_t)slot + 1);
			m_Textures[slot] = texture;
		}

		void Set(const std::string& name, const Reference<Texture2D>& texture)
		{
			Set(name, (const Reference<Texture>&)texture);
		}

		void Set(const std::string& name, const Reference<TextureCube>& texture)
		{
			Set(name, (const Reference<Texture>&)texture);
		}

	public:
		static Reference<Material> Create(const Reference<Shader>& shader);
	private:
		void AllocateStorage();
		void OnShaderReloaded();
		void BindTextures() const;

		ShaderUniformDeclaration* FindUniformDeclaration(const std::string& name);
		ShaderResourceDeclaration* FindResourceDeclaration(const std::string& name);
		Buffer& GetUniformBufferTarget(ShaderUniformDeclaration* uniformDeclaration);
	private:
		Reference<Shader> m_Shader;
		std::unordered_set<MaterialInstance*> m_MaterialInstances;

		Buffer m_VSUniformStorageBuffer;
		Buffer m_PSUniformStorageBuffer;
		std::vector<Reference<Texture>> m_Textures;

		uint32_t m_MaterialFlags;
	};


	class MaterialInstance
	{
		friend class Material;
	public:
		MaterialInstance(const Reference<Material>& material);
		virtual ~MaterialInstance();

		template <typename T>
		void Set(const std::string& name, const T& value)
		{
			auto decl = m_Material->FindUniformDeclaration(name);
			if (!decl)
				return;
			// HZ_CORE_ASSERT(decl, "Could not find uniform with name '{0}'", name);
			HZ_CORE_ASSERT(decl, "Could not find uniform with name 'x'");
			auto& buffer = GetUniformBufferTarget(decl);
			buffer.Write((byte*)&value, decl->GetSize(), decl->GetOffset());

			m_OverriddenValues.insert(name);
		}

		void Set(const std::string& name, const Reference<Texture>& texture)
		{
			auto decl = m_Material->FindResourceDeclaration(name);
			if (!decl)
				RLM_CORE_WARN("Cannot find material property: ", name);
			uint32_t slot = decl->GetRegister();
			if (m_Textures.size() <= slot)
				m_Textures.resize((size_t)slot + 1);
			m_Textures[slot] = texture;
		}

		void Set(const std::string& name, const Reference<Texture2D>& texture)
		{
			Set(name, (const Reference<Texture>&)texture);
		}

		void Set(const std::string& name, const Reference<TextureCube>& texture)
		{
			Set(name, (const Reference<Texture>&)texture);
		}

		void Bind() const;

		uint32_t GetFlags() const { return m_Material->m_MaterialFlags; }
		bool GetFlag(MaterialFlag flag) const { return (uint32_t)flag & m_Material->m_MaterialFlags; }
		void SetFlag(MaterialFlag flag, bool value = true);

		Reference<Shader >GetShader() { return m_Material->m_Shader; }
	public:
		static Reference<MaterialInstance> Create(const Reference<Material>& material);
	private:
		void AllocateStorage();
		void OnShaderReloaded();
		Buffer& GetUniformBufferTarget(ShaderUniformDeclaration* uniformDeclaration);
		void OnMaterialValueUpdated(ShaderUniformDeclaration* decl);
	private:
		Reference<Material> m_Material;

		Buffer m_VSUniformStorageBuffer;
		Buffer m_PSUniformStorageBuffer;
		std::vector<Reference<Texture>> m_Textures;

		// TODO: This is temporary; come up with a proper system to track overrides
		std::unordered_set<std::string> m_OverriddenValues;
	};

}


