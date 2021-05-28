#pragma once
// ��Ϸ����ֻ��include����һ���ܵ�ͷ�ļ���������Ϳ�����

//#include"RulomiPch.h"
#include"RulomiCore/Application.h"

//���������ǰ������������� ��Ȼʶ���������ռ�
//-------------------- Layer system--------------------//
#include "RulomiCore/Layer.h"
#include "RulomiCore/ImGui/ImGuiLayer.h"
#include "RulomiCore/Input.h"
#include "RulomiCore/Keycodes.h"
#include "RulomiCore/MouseButtonKeycode.h"
#include "RulomiCore/OrthographicCameraController.h"

//-------------------- Logging system--------------------//
#include"RulomiCore/Log.h"

//-------------------- Rendering system--------------------//
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Texture.h"
#include "Renderer/Framebuffer.h"


//-------------------- ECS  --------------------//
#include"RulomiCore/Scene/Components.h"
#include"RulomiCore/Scene/Entity.h"
#include"RulomiCore/Scene/Scene.h"


