#pragma once
#include "Rulomi.h"
#include "panels/SceneHierarchyPanel.h"

namespace Rulomi {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(TimeInterval ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

	private:
		//
		bool OnKeyPressed(KeyPressedEvent& e);

		bool OnMousePressed(MouseButtonPressedEvent& e);

		//������
		std::shared_ptr<Shader> m_Shader;
		Reference<VertexBuffer> m_VertexBuffer;
		Reference<IndexBuffer> m_IndexBuffer;
		Reference<VertexArray> m_VertexArray;

		//�������
		std::shared_ptr<Shader> m_FlatColorShader;
		std::shared_ptr<VertexArray> m_SquareVA;
		Reference<Texture2D> m_Texture2D;

		//Framebuffer 
		Reference <Framebuffer> m_FrameBuffer;
		//shader ����
		ShaderLibrary m_CashedShader;
	
		//�����ϵͳ
		glm::vec3 m_Color = { 0.2f, 0.3f, 0.8f };
		OrthographicCameraController m_orthographicCameraControler;

		EditorCamera m_EditorCamera;


		//viewport ״̬
		bool m_viewportFocused = false, m_viewportHovered = false;

		//viewPort ���ڴ�С
		glm::vec2 m_ViewportSize = { 0.0f , 0.0f };
		//�Ӵ��ı߽�
		glm::vec2 m_ViewportBounds[2];

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		
		//����ϵͳ
		Reference<Scene> m_Scene;

		//
		int m_GizmoType = -1;


		//��ʱʹ��
		Entity m_firstEntity;
		//�����ϵͳ����
		Entity main_cam;
		Entity second_cam;
		Entity m_SquareEntity;
		Entity m_HoveredEntity;

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

	};



}


