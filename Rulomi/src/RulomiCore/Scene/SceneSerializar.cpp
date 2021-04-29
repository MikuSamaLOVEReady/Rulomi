#include "RulomiPch.h"
#include "SceneSerializar.h"

#include "Entity.h"
#include "Components.h"
#include <yaml-cpp/yaml.h>
#include <fstream>

namespace YAML {

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

}


namespace Rulomi {



	SceneSerializar::SceneSerializar(const Reference<Scene>& scene)
		:m_Scene(scene)
	{
	}

	void SceneSerializar::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;
		//开启map
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		//开启sequence （理解为列表）
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		m_Scene->m_Registry.each([&](auto& entityID)
			{
				Entity entity = { entityID,m_Scene.get() };
				if (!entity)
					return;
				else
					SerializeEntity(out, entity);
			});

		out << YAML::EndSeq;
		out << YAML::EndMap;
		std::ofstream fout(filepath);
		fout << out.c_str();

	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}



	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap;
		//最好创建一个random 的ID
		out << YAML::Key << "Entity" << YAML::Value << "5436644432";

		if (entity.HasComponet<TagComponent>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap; // TagComponent
			out << YAML::Key << "Tag" << YAML::Value << entity.GetComponent<TagComponent>().Tag;
			out << YAML::EndMap; // TagComponent
		}

		if (entity.HasComponet<TransformComponent>())
		{
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap; // TagComponent

			TransformComponent& tc = entity.GetComponent<TransformComponent>();
			//YAML::Value <<  需要重写
			out << YAML::Key << "Translation" << YAML::Value << tc.position;
			out << YAML::Key << "Rotation" << YAML::Value << tc.rotation;
			out << YAML::Key << "Scale" << YAML::Value << tc.scale;

			out << YAML::EndMap;// TagComponent
		}

		if (entity.HasComponet<CameraComponent>())
		{
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap;

			SceneCamera& camera = entity.GetComponent<CameraComponent>().camera;
			out << YAML::Key << "Camera" << YAML::Value; //这一行很关键 没这行格式不对 虽然不知道为啥
			out << YAML::BeginMap; // Camera
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetCameraType();
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveVerticalFOV();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNear();
			out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthographicFar();
			out << YAML::EndMap; // Camera

			out << YAML::Key << "Main" << YAML::Value << entity.GetComponent<CameraComponent>().main;
			out << YAML::Key << "FixedAspectRation"<< YAML::Value<< entity.GetComponent<CameraComponent>().AspectRatioFix;

			out << YAML::EndMap;
		}

		if (entity.HasComponet<SpriteRendererComponent>())
		{
			out << YAML::Key << "SpriteRendererComponent";
			out << YAML::BeginMap; // SpriteRendererComponent 

			auto& spriteRendererComponent = entity.GetComponent<SpriteRendererComponent>();
			out << YAML::Key << "Color" << YAML::Value << spriteRendererComponent.Color;

			out << YAML::EndMap; // SpriteRendererComponent
		}

	
		out << YAML::EndMap; // Entity
	}




	bool SceneSerializar::DeSerialize(const std::string& filepath)
	{
		//输入stream的obj 对这个程序来说是in
		std::ifstream stream(filepath);
		//将读取的
		std::stringstream ss;
		//stream stream 的rdbuf 作用？-->返回一个stringbuffer
		ss << stream.rdbuf();

		YAML::Node data = YAML::Load(ss.str());
		if (!data["Scene"])
			return false;
		std::string sceneName = data["Scene"].as<std::string>();

		YAML::Node entitiesNodes = data["Entities"];
		if (entitiesNodes)
		{
			for (auto eachNode : entitiesNodes)
			{
				//读取 universal unique identifier (唯一ID)
				uint64_t uuid = eachNode["Entity"].as<uint64_t>();
				// 读取Tag
				auto Tc = eachNode["TagComponent"];
				std::string name;
				if (Tc)
					name = Tc["Tag"].as<std::string>();
				//创建Entity
				Entity entityRead = m_Scene->CreateEntity(name);

				//读取transform组件
				auto Node_tc = eachNode["TransformComponent"];
				if (Node_tc)
				{
					auto& TransC = entityRead.GetComponent<TransformComponent>();
					TransC.position = Node_tc["Translation"].as<glm::vec3>();
					TransC.rotation = Node_tc["Rotation"].as<glm::vec3>();
					TransC.scale = Node_tc["Scale"].as<glm::vec3>();
				}
				//读取相机组件
				auto Node_Camera = eachNode["CameraComponent"];
				if (Node_Camera)
				{
					auto& Cc = entityRead.AddComponent<CameraComponent>();
					SceneCamera& sc = Cc.camera;

					auto& cameraProps = Node_Camera["Camera"];
					sc.setProjectionType((SceneCamera::ProjectionType)cameraProps["ProjectionType"].as<int>());
					sc.SetPerspectiveVerticalFOV(cameraProps["PerspectiveFOV"].as<float>());
					sc.SetPerspectiveNearClip(cameraProps["PerspectiveNear"].as<float>());
					sc.SetPerspectiveFarClip(cameraProps["PerspectiveFar"].as<float>());

					sc.SetOrthographicSize(cameraProps["OrthographicSize"].as<float>());
					sc.SetOrthographicNear(cameraProps["OrthographicNear"].as<float>());
					sc.SetOrthographicFar(cameraProps["OrthographicFar"].as<float>());

					Cc.main = Node_Camera["Main"].as<bool>();
					Cc.AspectRatioFix = Node_Camera["FixedAspectRation"].as<bool>();
				}
				//读取颜色组件
				auto Node_Sprite = eachNode["SpriteRendererComponent"];
				if (Node_Sprite)
				{
					auto& Sprite = entityRead.AddComponent<SpriteRendererComponent>();
					Sprite.Color = Node_Sprite["Color"].as<glm::vec4>();
				}
			}
		}

		return true;
	}

}