#pragma once

#include "Renderer/OrthographicCamera.h"
#include "Renderer/Texture.h"
#include "Renderer/Camera.h"
#include "Renderer/EditorCamera.h"
#include "RulomiCore/Scene/Components.h"

namespace Rulomi {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		//Flush ���ڳ������ݸ�����Ϻ� �ύ��GPU��Ⱦ
		static void Flush();

		//��ɫ����
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		//������
		static void DrawQuad(const glm::mat4& transform, const Reference<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		//����ID�� ���ƶ���
		//��ɫ����
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);
		//������
		static void DrawQuad(const glm::mat4& transform, const Reference<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f), int entityID = -1);
		static void DrawSprite(const glm::mat4& transform, SpriteRendererComponent& src, int entityID);

		// Stats
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() const { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() const { return QuadCount * 6; }
		};

		static Statistics GetStats();
		//ˢ�³���ͳ��
		static void  ResetStats();

	private:
		static void StartBatch();
		static void NextBatch();

	};
}



