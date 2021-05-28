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
		// �Ӽ�UI
		ImGui::Begin("Scene Hierarchy");
			m_context->m_Registry.each([&](auto entityID)
				{
						Entity entity{ entityID , m_context.get() };
						DrawEntityNode(entity);
				});
			//���@�ӷ��� �����ĵ�� ��ѡ�е�item ���ɿ�
			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
				m_SelectEntity = {};
			
			// ������������ʾ��item֮�ϲ�open ImGuiPopupFlags_NoOpenOverItems
			//�ڶ���������ʾ �������Ҽ�
			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::MenuItem("Create Empty"))
				{
					m_context->CreateEntity("Empty item");
				}

				ImGui::EndPopup();
			}

		ImGui::End();

		//�������UI
		ImGui::Begin("Properties	");
		if (m_SelectEntity)
		{
			//���ƿ�ʼ
			DrawComponents(m_SelectEntity);

			//������(open �� begin ��ͨ�� ���󶨵��ַ����໥ʶ���)
			if (ImGui::Button("Add New Component"))
				ImGui::OpenPopup("Add Components");
			if (ImGui::BeginPopup("Add Components"))
			{
				if (ImGui::MenuItem("Sprite Renderer"))
				{
					m_SelectEntity.AddComponent<SpriteRendererComponent>();
					//ImGui::EndPopup(); ���ﲻ��ֱ�ӵ����� ��Ȼ��������ظ� pop
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

		//provide some flags��Ϊ��ǰ����Ҫ���ƽڵ�����һЩ�趨
		ImGuiTreeNodeFlags flags = ((m_SelectEntity==entity)? ImGuiTreeNodeFlags_Selected:0) | ImGuiTreeNodeFlags_OpenOnArrow| ImGuiTreeNodeFlags_SpanAvailWidth;

		//imgui ��Ҫһ��Ψһ��ID ��ʶ������ڵ㣬�������ǿ���ֱ����entity�Ľڵ�
		//����һ������ڵ��Ƿ��Լ���չ��
		bool NodeExpended =	ImGui::TreeNodeEx((void*)(uint32_t)entity, flags,tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectEntity = entity;
		}
		if (NodeExpended)
		{
			//�����¼��˵�����
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
			//���ɾ�����ǵ�ǰѡ�е� ��Ҫ���������
			if (m_SelectEntity == entity)
				m_SelectEntity = {};
		}
			

	}

	//transform ���
	static void DrawTransformUI(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGui::PushID(label.c_str());
		//��������colum
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
			//�Ҳ�������ʾ����
			ImGui::NextColumn();	
			ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

			//���ð�ť style����Ӧ
			//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
			//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			if (ImGui::Button("X", buttonSize))
				values.x = resetValue;
			//ImGui::PopStyleColor(3);
			//������������
			ImGui::SameLine();
			//��## �Ͳ���ʾlabel
			ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
			//PopItemWidth��---����Ӧpush��3��width ����pop��һ��
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

			//�������ó�Ĭ��ֵ1��
			ImGui::Columns(1);
	
			ImGui::PopID();
	}

	template<typename T, typename CompontFunction>
	//tage ���� �ڶ����ǵ�ǰ��ѡentity �������Ǹ�����ʾcomponents����
	static void DrawEachComponent(const std::string& name, Entity entity, CompontFunction fun)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		if (entity.HasComponet<T>())
		{
			auto& component = entity.GetComponent<T>();
			//��ȡ�� rect�����½�����
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


	//entity ������棨��
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
			//������o��IDΨһ���� (void*)typeid(TransformComponent).hash_code()
			bool NodeExpended = ImGui::TreeNodeEx( (void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen,"Transform" );

			if (NodeExpended)
			{
				auto& transformComponent = entity.GetComponent<TransformComponent>();
				DrawTransformUI("Position", transformComponent.position);
				//rotation(������ float ��ʾ radians) ---> ��ʾ��ʱ���ǽǶ���ʾ
				glm::vec3 rotation = glm::degrees(transformComponent.rotation);
				//����ֻ�Ƕ���ʱ������rotation�����޸� --����Ҫת��ȥ
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

					//���� �ṩ��Bool�����ж� TF �趨�����������
					ImGui::Checkbox("Primary", &component.main);

					const char* cameraTypes[] = { "Perspective","Orthographic" };
					const char* currentCameraType = cameraTypes[(int)camera.GetCameraType()];

					//ֻ�е��������������obj��ʱ��Ż�չ�� ����
					if (ImGui::BeginCombo("Projection", currentCameraType))
					{
						//ÿ���жϵ�ǰѡ��������� �б��е��ĸ�?
						for (int index = 0; index < 2; index++)
						{
							//����ҵ���ǰѡ�е�����
							bool isSelected = currentCameraType == cameraTypes[index];
							//selectable ���������˵�������һ��ѡ��(Imgui ��If ���Ǳ�ʾ��������¼� �ж��Ƿ��е��������
							//���չ������Ż�һֱ���ż���
							if (ImGui::Selectable(cameraTypes[index]))
							{
								currentCameraType = cameraTypes[index];
								camera.setProjectionType((SceneCamera::ProjectionType)index);
							}
							//difault������ʲô�ģ�û��a
							if (isSelected) ImGui::SetItemDefaultFocus();
						}
						//�����forѭ�� selectable �����������Combox�������
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
						//ת���ɽǶ�
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
