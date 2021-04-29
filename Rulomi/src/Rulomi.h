#pragma once
// 游戏工程只用include整个一个总的头文件（这个）就可以了

//#include"RulomiPch.h"
#include"RulomiCore/Application.h"

//在引擎入口前导入所有组件！ 不然识别不上命名空间
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


