#include "RulomiPch.h"
#include "Mesh.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>

namespace Rulomi {

	struct LogStream : public Assimp::LogStream
	{
		static void Initialize()
		{
			if (Assimp::DefaultLogger::isNullLogger())
			{
				Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
				Assimp::DefaultLogger::get()->attachStream(new LogStream, Assimp::Logger::Err | Assimp::Logger::Warn);
			}
		}

		virtual void write(const char* message) override
		{
			RLM_CORE_ERROR("Assimp error: {0}", message);
		}
	};

	//��ȡmesh������
	static const uint32_t s_MeshImportFlags =
		aiProcess_CalcTangentSpace |        // Create binormals/tangents just in case
		aiProcess_Triangulate |             // Make sure we're triangles
		aiProcess_SortByPType |             // Split meshes by primitive type
		aiProcess_GenNormals |              // Make sure we have legit normals
		aiProcess_GenUVCoords |             // Convert UVs if required 
		aiProcess_OptimizeMeshes |          // Batch draws where possible
		aiProcess_ValidateDataStructure;    // Validation

	// AssimpMat4----> glm::mat4  ��ʽת��
	glm::mat4 Mat4FromAssimpMat4(const aiMatrix4x4& matrix)
	{
		glm::mat4 result;
		//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
		result[0][0] = matrix.a1; result[1][0] = matrix.a2; result[2][0] = matrix.a3; result[3][0] = matrix.a4;
		result[0][1] = matrix.b1; result[1][1] = matrix.b2; result[2][1] = matrix.b3; result[3][1] = matrix.b4;
		result[0][2] = matrix.c1; result[1][2] = matrix.c2; result[2][2] = matrix.c3; result[3][2] = matrix.c4;
		result[0][3] = matrix.d1; result[1][3] = matrix.d2; result[2][3] = matrix.d3; result[3][3] = matrix.d4;
		return result;
	}


	//Mesh::Mesh(const std::string& filename)
	//	:m_FilePath(filename)
	//{
	//	LogStream::Initialize();
	//	RLM_CORE_INFO("Loading mesh: {0}", filename.c_str());

	//	m_Importer =std::make_unique<Assimp::Importer>();
	//	//aiScene ���س����е�mesh��the root structure of the imported data.
	//	const aiScene* scene = m_Importer->ReadFile(filename, s_MeshImportFlags);
	//	if (!scene || !scene->HasMeshes())
	//		RLM_CORE_ERROR("Failed to load mesh file : {0}", filename);
	//	m_Scene = scene;

	//	uint32_t vertexCount = 0;
	//	uint32_t indexCount = 0;
	//	//vectore reserve ��ʾ����������ô��size�Ŀռ�
	//	//m_Submeshes�洢����mesh
	//	m_Submeshes.reserve(scene->mNumMeshes);
	//	for (size_t m = 0; m < scene->mNumMeshes; m++)
	//	{
	//		//ȡ��һ��mesh�ڵ�
	//		aiMesh* mesh = scene->mMeshes[m];
	//		Submesh& submesh = m_Submeshes.emplace_back();
	//		//base ��ʾ��ǰmesh�ṹ�ڵ�� ���ڴ��е���ʼλ��
	//		submesh.BaseVertex = vertexCount; 
	//		submesh.BaseIndex = indexCount;
	//		submesh.MaterialIndex = mesh->mMaterialIndex;
	//		//ͼԪȫ�� triangle
	//		submesh.IndexCount = mesh->mNumFaces * 3;
	//		submesh.MeshName = mesh->mName.C_Str();

	//		vertexCount += mesh->mNumVertices;
	//		indexCount += submesh.IndexCount;

	//		//������ǰscen ��ĳ��mesh ���ҽ����ݴ�mesh�ж���Vertices
	//		// ������λ�á����ߺ���������
	//		for (size_t i = 0; i < mesh->mNumVertices; i++)
	//		{
	//			Vertex vertex;
	//			vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
	//			vertex.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
	//			if (mesh->HasTangentsAndBitangents())
	//			{
	//				vertex.Tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
	//				vertex.Binormal = { mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z };
	//			}
	//			if (mesh->HasTextureCoords(0))
	//				vertex.Texcoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
	//			m_StaticVertices.push_back(vertex);
	//		}

	//		// ��������
	//		//������ǰmesh������faces��Ŀ���� ��ÿ����������vertex����    Indexes
	//		for (size_t i = 0; i < mesh->mNumFaces; i++)
	//		{
	//			RLM_CORE_ASSERT(mesh->mFaces[i].mNumIndices == 3, "Must have 3 indices.");
	//			//ÿ����ض��������� ��˶��������������ID   ���Ҹо�����0,1,2����
	//			IndexGroup index = { mesh->mFaces[i].mIndices[0], mesh->mFaces[i].mIndices[1], mesh->mFaces[i].mIndices[2] };
	//			//����������face �Ļ���˳��indexes��
	//			m_Indices.push_back(index);
	//			//hashmap Key=������mesh��ID  value=ͼԪ��vertex    ����ÿ��������ͼԪ ��vertex��ӳ��ͼ�¼�����
	//			m_TriangleCache[m].emplace_back( m_StaticVertices[index.V1 + submesh.BaseVertex],  m_StaticVertices[index.V2 + submesh.BaseVertex], m_StaticVertices[index.V3 + submesh.BaseVertex]);
	//		}

	//		//�������нڵ㡣 ��Ŀ��Ϊ�Σ�
	//		//TraverseNodes(scene->mRootNode);

	//		// �������
	//		if (scene->HasMaterials())
	//		{
	//			//m_Textures.resize(scene->mNumMaterials);
	//			//m_Materials.resize(scene->mNumMaterials);

	//		}


	//	}


	//	}


	//DFS  ����ÿ���ڵ�  ����Ŀ���Ǹ�ɶ��  �������нڵ��transform Mtrx
	//void Mesh::TraverseNodes(aiNode* node, const glm::mat4& parentTransform, uint32_t level)
	//{
	//	glm::mat4 transform = parentTransform * Mat4FromAssimpMat4(node->mTransformation);
	//	//��ǰ�ڵ�
	//	for (uint32_t i = 0; i < node->mNumMeshes; i++)
	//	{
	//		uint32_t mesh = node->mMeshes[i];  
	//		auto& submesh = m_Submeshes[mesh];
	//		submesh.NodeName = node->mName.C_Str();
	//		submesh.Transform = transform;
	//	}
	//	for (uint32_t i = 0; i < node->mNumChildren; i++)
	//		TraverseNodes(node->mChildren[i], transform, level + 1);
	//}





}

