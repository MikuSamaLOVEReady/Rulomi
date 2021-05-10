#pragma once

#include <glm/glm.hpp>
#include "Renderer/Texture.h"


namespace Assimp {
	class Importer;
}

namespace Rulomi {

	//顶点data
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec3 Tangent;
		glm::vec3 Binormal;
		glm::vec2 Texcoord;
	};
	//图元 顺序
	struct IndexGroup
	{
		uint32_t V1, V2, V3;
	};
	//三角形片元
	struct Triangle
	{
		Vertex V0, V1, V2;

		Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
			: V0(v0), V1(v1), V2(v2) {}
	};

	//用于统计每个mesh的顶点个数
	class Submesh
	{
	public:
		uint32_t BaseVertex;
		uint32_t BaseIndex;
		uint32_t MaterialIndex;
		uint32_t IndexCount;

		glm::mat4 Transform;
		//AABB BoundingBox;

		std::string NodeName, MeshName;
	};

	class Mesh
	{
	public:
		Mesh(const std::string& filename);
		~Mesh() = default;

	private:

		//void TraverseNodes(aiNode* node, const glm::mat4& parentTransform = glm::mat4(1.0f), uint32_t level = 0);

		//assimp场景 真正的mesh对象
		std::vector<Submesh> m_Submeshes;

		std::string m_FilePath;
		//assimp 所提供的模型加载器
		std::unique_ptr<Assimp::Importer> m_Importer;
		//所读入模型的根节点
		//const aiScene* m_Scene;

		//每个obj的顶点data
		std::vector<Vertex> m_StaticVertices;
		//以及绘制顺序  (他是按照图元为index么？ 每一个图元为一个ID？)
		std::vector<IndexGroup> m_Indices;
		//（）
		std::unordered_map<uint32_t, std::vector<Triangle>> m_TriangleCache;

		//存储所有 纹理 和 法线
		std::vector<Reference<Texture2D>> m_Textures;
		std::vector<Reference<Texture2D>>m_NormalMaps;
		//std::vector<Reference<MaterialInstance>> m_Materials;

	};


}

