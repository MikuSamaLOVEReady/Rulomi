#pragma once

#include <glm/glm.hpp>
#include "Renderer/Texture.h"


namespace Assimp {
	class Importer;
}

namespace Rulomi {

	//����data
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec3 Tangent;
		glm::vec3 Binormal;
		glm::vec2 Texcoord;
	};
	//ͼԪ ˳��
	struct IndexGroup
	{
		uint32_t V1, V2, V3;
	};
	//������ƬԪ
	struct Triangle
	{
		Vertex V0, V1, V2;

		Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
			: V0(v0), V1(v1), V2(v2) {}
	};

	//����ͳ��ÿ��mesh�Ķ������
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

		//assimp���� ������mesh����
		std::vector<Submesh> m_Submeshes;

		std::string m_FilePath;
		//assimp ���ṩ��ģ�ͼ�����
		std::unique_ptr<Assimp::Importer> m_Importer;
		//������ģ�͵ĸ��ڵ�
		//const aiScene* m_Scene;

		//ÿ��obj�Ķ���data
		std::vector<Vertex> m_StaticVertices;
		//�Լ�����˳��  (���ǰ���ͼԪΪindexô�� ÿһ��ͼԪΪһ��ID��)
		std::vector<IndexGroup> m_Indices;
		//����
		std::unordered_map<uint32_t, std::vector<Triangle>> m_TriangleCache;

		//�洢���� ���� �� ����
		std::vector<Reference<Texture2D>> m_Textures;
		std::vector<Reference<Texture2D>>m_NormalMaps;
		//std::vector<Reference<MaterialInstance>> m_Materials;

	};


}

