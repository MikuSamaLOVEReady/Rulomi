#pragma once

#include "RulomiCore/Core.h"
#include "RulomiCore/Log.h"
#include	"RulomiCore/Scene/Scene.h"
#include "RulomiCore/Scene/Entity.h"

namespace Rulomi {

	class SceneHierarchyPanel
	{

	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Reference<Scene>& context);

		void SetContext(const Reference<Scene>& context);
		void OnImGuiRender();
		void SelectedEntity(Entity entity);

		Entity GetSelectedEntity() const { return m_SelectEntity; }

	private:
		//节点系统
		void DrawEntityNode(Entity entity);
		//inspector
		void DrawComponents(Entity entity);



	private:
		Reference<Scene> m_context;
		Entity m_SelectEntity;

	};


}


