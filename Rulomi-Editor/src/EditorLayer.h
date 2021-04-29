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

		//三角形
		std::shared_ptr<Shader> m_Shader;
		Reference<VertexBuffer> m_VertexBuffer;
		Reference<IndexBuffer> m_IndexBuffer;
		Reference<VertexArray> m_VertexArray;

		//纹理矩形
		std::shared_ptr<Shader> m_FlatColorShader;
		std::shared_ptr<VertexArray> m_SquareVA;
		Reference<Texture2D> m_Texture2D;

		//Framebuffer 
		Reference <Framebuffer> m_FrameBuffer;
		//shader 缓存
		ShaderLibrary m_CashedShader;
	
		//摄像机系统
		glm::vec3 m_Color = { 0.2f, 0.3f, 0.8f };
		OrthographicCameraController m_orthographicCameraControler;

		EditorCamera m_EditorCamera;


		//viewport 状态
		bool m_viewportFocused = false, m_viewportHovered = false;

		//viewPort 窗口大小
		glm::vec2 m_ViewportSize = { 0.0f , 0.0f };
		//视窗的边界
		glm::vec2 m_ViewportBounds[2];

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		
		//场景系统
		Reference<Scene> m_Scene;

		//
		int m_GizmoType = -1;


		//暂时使用
		Entity m_firstEntity;
		//摄像机系统测试
		Entity main_cam;
		Entity second_cam;
		Entity m_SquareEntity;
		Entity m_HoveredEntity;

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

	};



}


