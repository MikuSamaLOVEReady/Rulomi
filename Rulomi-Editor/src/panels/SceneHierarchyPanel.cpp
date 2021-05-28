#include "SceneHierarchyPanel.h"
#include <imgui/imgui.h>
#include "RulomiCore/Scene/Components.h"
#include "glm/gtc/type_ptr.hpp"

#include "imgui/imgui_internal.h"

namespace Rulomi {

	SceneHierarchyPanel::SceneHierarchyPanel(const Reference<Scene>& scene)
	{
		SetContext(scene);
	}

	void SceneHierarchyPanel::SetContext(const Reference<Scene>& scene)
	{
		m_context = scene;
		m_SelectEntity = {};
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		// 層級UI
		ImGui::Begin("Scene Hierarchy");
			m_context->m_Registry.each([&](auto entityID)
				{
						Entity entity{ entityID , m_context.get() };
						DrawEntityNode(entity);
				});
			//在這層反應 如果别的点击 则将选中的item 换成空
			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
				m_SelectEntity = {};
			
			// 第三个参数表示在item之上不open ImGuiPopupFlags_NoOpenOverItems
			//第二个参数表示 点击鼠标右键
			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::MenuItem("Create Empty"))
				{
					m_context->CreateEntity("Empty item");
				}

				ImGui::EndPopup();
			}

		ImGui::End();

		//组件详情UI
		ImGui::Begin("Properties	");
		if (m_SelectEntity)
		{
			//绘制开始
			DrawComponents(m_SelectEntity);

			//添加组件(open 与 begin 是通过 所绑定的字符串相互识别的)
			if (ImGui::Button("Add New Component"))
				ImGui::OpenPopup("Add Components");
			if (ImGui::BeginPopup("Add Components"))
			{
				if (ImGui::MenuItem("Sprite Renderer"))
				{
					m_SelectEntity.AddComponent<SpriteRendererComponent>();
					//ImGui::EndPopup(); 这里不能直接调用它 不然在最后会和重复 pop
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Camera"))
				{
					m_SelectEntity.AddComponent<CameraComponent>();
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}

		ImGui::End();

	}

	void SceneHierarchyPanel::SelectedEntity(Entity entity)
	{
		m_SelectEntity = entity;
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		std::string tag = entity.GetComponent<TagComponent>().Tag;
		//RLM_CORE_DEBUG("{ 0 }", tag);

		//provide some flags？为当前所需要绘制节点增加一些设定
		ImGuiTreeNodeFlags flags = ((m_SelectEntity==entity)? ImGuiTreeNodeFlags_Selected:0) | ImGuiTreeNodeFlags_OpenOnArrow| ImGuiTreeNodeFlags_SpanAvailWidth;

		//imgui 需要一个唯一的ID 来识别这个节点，这里我们可以直接用entity的节点
		//返回一个这个节点是否以及被展开
		bool NodeExpended =	ImGui::TreeNodeEx((void*)(uint32_t)entity, flags,tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectEntity = entity;
		}
		if (NodeExpended)
		{
			//设置下级菜单而已
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)555555, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("delete"))
			{
				entityDeleted = true;
			}
			ImGui::EndPopup();
		}

		if (entityDeleted)
		{
			m_context->DestoryEntity(entity);
			//如果删除的是当前选中的 则要清空属性栏
			if (m_SelectEntity == entity)
				m_SelectEntity = {};
		}
			

	}

	//transform 组件
	static void DrawTransformUI(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGui::PushID(label.c_str());
		//创建俩个colum
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
			//右侧数据显示界面
			ImGui::NextColumn();	
			ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

			//设置按钮 style与响应
			//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
			//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			if (ImGui::Button("X", buttonSize))
				values.x = resetValue;
			//ImGui::PopStyleColor(3);
			//设置数据内容
			ImGui::SameLine();
			//加## 就不显示label
			ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
			//PopItemWidth《---》对应push了3个width 现在pop第一个
			ImGui::PopItemWidth();

			ImGui::SameLine();
			//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
			//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			if (ImGui::Button("Y", buttonSize))
				values.y = resetValue;
			//ImGui::PopStyleColor(3);
			ImGui::SameLine();
			ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();


			ImGui::SameLine();
			//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
			//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			if (ImGui::Button("Z", buttonSize))
				values.z = resetValue;
			//ImGui::PopStyleColor(3);
			ImGui::SameLine();
			ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();
			
			ImGui::PopStyleVar();

			//重新设置成默认值1个
			ImGui::Columns(1);
	
			ImGui::PopID();
	}

	template<typename T, typename CompontFunction>
	//tage 名字 第二个是当前所选entity 第三个是负责显示components属性
	static void DrawEachComponent(const std::string& name, Entity entity, CompontFunction fun)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		if (entity.HasComponet<T>())
		{
			auto& component = entity.GetComponent<T>();
			//获取当 rect的右下角坐标
			ImVec2 rowRegionAvaliable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool childNode = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
			ImGui::PopStyleVar();
			//offset
			ImGui::SameLine(rowRegionAvaliable.x - lineHeight * 0.5f);
			if (ImGui::Button("...", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove"))
					removeComponent = true;
				ImGui::EndPopup();
			}

			if (childNode)
			{
				fun(component);
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<T>();
		}


	}


	//entity 详情界面（）
	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponet<TagComponent>())
		{
			std::string tag = entity.GetComponent<TagComponent>().Tag;
			char buffer[512];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer) ) )
			{
				tag = std::string(buffer);
			}
		}

		if (entity.HasComponet<TransformComponent>())
		{
			//如果所給的ID唯一可用 (void*)typeid(TransformComponent).hash_code()
			bool NodeExpended = ImGui::TreeNodeEx( (void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen,"Transform" );

			if (NodeExpended)
			{
				auto& transformComponent = entity.GetComponent<TransformComponent>();
				DrawTransformUI("Position", transformComponent.position);
				//rotation(三个轴 float 表示 radians) ---> 显示的时候是角度显示
				glm::vec3 rotation = glm::degrees(transformComponent.rotation);
				//这里只是对临时变量（rotation）的修改 --》需要转回去
				DrawTransformUI("Rotation", rotation);
				transformComponent.rotation = glm::radians(rotation);
				DrawTransformUI("Scale", transformComponent.scale, 1.0f);
				//ImGui::DragFloat3("Transform", glm::value_ptr(transform[3]), 0.1f);
				ImGui::TreePop();
			}
		}

		DrawEachComponent<CameraComponent>("Camera", entity, [](auto& component) 
			{
					auto& camera = component.camera;

					//根据 提供的Bool型来判断 TF 设定场景的主相机
					ImGui::Checkbox("Primary", &component.main);

					const char* cameraTypes[] = { "Perspective","Orthographic" };
					const char* currentCameraType = cameraTypes[(int)camera.GetCameraType()];

					//只有点击带有相机组件的obj的时候才会展开 监听
					if (ImGui::BeginCombo("Projection", currentCameraType))
					{
						//每次判断当前选择的类型是 列表中的哪个?
						for (int index = 0; index < 2; index++)
						{
							//如果找到当前选中的类型
							bool isSelected = currentCameraType == cameraTypes[index];
							//selectable 就是下拉菜单中任意一个选项(Imgui 加If 就是表示监听点击事件 判断是否有点击发生）
							//点击展开过后才会一直挂着监听
							if (ImGui::Selectable(cameraTypes[index]))
							{
								currentCameraType = cameraTypes[index];
								camera.setProjectionType((SceneCamera::ProjectionType)index);
							}
							//difault？？干什么的？没用a
							if (isSelected) ImGui::SetItemDefaultFocus();
						}
						//上面的for循环 selectable 就是在向这个Combox添加内容
						ImGui::EndCombo();
					}

					if (camera.GetCameraType() == SceneCamera::ProjectionType::orthographic)
					{
						float OrthographicSize = camera.GetOrthographicSize();
						if (ImGui::DragFloat("Size", &OrthographicSize))
						{
							camera.SetOrthographicSize(OrthographicSize);
						}

						float OrthographicNear = camera.GetOrthographicNear();
						if (ImGui::DragFloat("NearClip", &OrthographicNear))
						{
							camera.SetOrthographicNear(OrthographicNear);
						}

						float OrthographicFar = camera.GetOrthographicFar();
						if (ImGui::DragFloat("FarClip", &OrthographicFar))
						{
							camera.SetOrthographicFar(OrthographicFar);
						}
						ImGui::Checkbox("Fixed AspectRatio", &component.AspectRatioFix);
					}
					else
					{
						//转化成角度
						float verticalFov = glm::degrees(camera.GetPerspectiveVerticalFOV());
						if (ImGui::DragFloat("Vertical FOV", &verticalFov))
							camera.SetPerspectiveVerticalFOV(glm::radians(verticalFov));

						float orthoNear = camera.GetPerspectiveNearClip();
						if (ImGui::DragFloat("Near", &orthoNear))
							camera.SetPerspectiveNearClip(orthoNear);

						float orthoFar = camera.GetPerspectiveFarClip();
						if (ImGui::DragFloat("Far", &orthoFar))
							camera.SetPerspectiveFarClip(orthoFar);

					}
				
			});

		DrawEachComponent<SpriteRendererComponent>("Sprite", entity, [](auto& component)
			{
				auto& sprite = component.Color;
				ImGui::ColorEdit4("Sprite", glm::value_ptr(sprite));
			});


	}






	


}
