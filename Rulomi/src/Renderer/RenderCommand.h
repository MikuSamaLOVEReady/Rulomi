#pragma once


// RenderCommand �������� һ��wrapper *����renderer������ַ�����Ӧ��ƽ̨��API)
//��Ҳ����ֱ�ӵ���
//��Ҫ����� RendererAPI �Ļ� ����Ҫ��һ���ⶫ��
#include "RendererAPI.h"

namespace Rulomi {

	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		//�� shader��������ݸ� �����API����
		inline static void DrawVertexs(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawVertexs(vertexArray);
		}
	private:
		//���ṩ���죬 ����Render command ���ɹ�����һ��
		static RendererAPI* s_RendererAPI;
	};


}


