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

//-------------------- Logging system--------------------//
#include"RulomiCore/Log.h"

//-------------------- Entry Point------------------//
#include"RulomiCore/EntryPoint.h"


