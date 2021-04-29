workspace "Rulomi"
            architecture "x64"
            startproject "SandBox"

            configurations
            {
                "Debug",
                "Release",
                "Dist"
			}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- 相对于sln目录的include 顺序
IncludeDir ={}
IncludeDir["GLFW"] = "Rulomi/vendor/GLFW/include"
IncludeDir["GLAD"] = "Rulomi/vendor/GLAD/include"
IncludeDir["ImGui"] = "Rulomi/vendor/imgui"
IncludeDir["glm"] = "Rulomi/vendor/glm"
IncludeDir["stb_image"] = "Rulomi/vendor/stb_image"
IncludeDir["entt"] = "Rulomi/vendor/entt/include"
IncludeDir["yaml_cpp"] = "Rulomi/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "Rulomi/vendor/ImGuizmo"


--include GLFW的 premake file 为Rulomi 添加reference
include "Rulomi/vendor/GLFW"
include "Rulomi/vendor/GLAD" 
include "Rulomi/vendor/imgui"
include "Rulomi/vendor/yaml-cpp"

project "Rulomi"
         location "Rulomi"
         kind "StaticLib"
         language "C++" 
         cppdialect "C++17"
         --staticruntime 表示开启静态链接
         staticruntime "on"

         targetdir("bin/"..outputdir.."/%{prj.name}")
         objdir("bin-int/"..outputdir.."/%{prj.name}")
         pchheader "RulomiPch.h"
         pchsource  "Rulomi/src/RulomiPch.cpp"

         files
         {
                  "%{prj.name}/src/**.h",
                  "%{prj.name}/src/**.cpp",
                  "%{prj.name}/vendor/stb_image/**.h",
		          "%{prj.name}/vendor/stb_image/**.cpp",
                  "%{prj.name}/vendor/glm/glm/**.hpp",
                  "%{prj.name}/vendor/glm/glm/**.inl",
                  "%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
                  "%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
		 }
            
         defines
         {
             "_CRT_SECURE_NO_WARNINGS"
		 }
         

         includedirs
         {
                  "%{prj.name}/vendor/spdlog/include",
                  "%{prj.name}/src",
                  "%{IncludeDir.GLFW}",
                  "%{IncludeDir.GLAD}",
                  "%{IncludeDir.ImGui}",
                  "%{IncludeDir.stb_image}",
                  "%{prj.name}/vendor/assimp/include",
                  "%{IncludeDir.glm}",
                  "%{IncludeDir.entt}",
                  "%{IncludeDir.yaml_cpp}",
                  "%{IncludeDir.ImGuizmo}"
		 }

           links
         {
                "GLFW",
                "GLAD",
                "ImGui",
                "yaml-cpp",
                "opengl32.lib"
		 }

         filter "files:%{prj.name}/vendor/ImGuizmo/**.cpp"
	        flags { "NoPCH" }

         filter "system:windows"
              systemversion "latest"

              defines
              {
                     "RLM_PLATFORM_WINDOWS",
                     "RLM_BUILD_DLL",
                     "GLFW_INCLUDE_NONE"
                     --"RLM_ENABLE_ASSERTS"
			  }

             --postbuildcommands {("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")--("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/SandBox")}

         filter "configurations:Debug"
                        defines "Rulomi_DEBUG"
                        runtime "Debug"
                        symbols "On"

         filter "configurations:Release"
                        defines "Rulomi_RELEASE"
                        runtime "Release"
                        optimize "On"

         filter "configurations:Dist"
                        defines "Rulomi_DIST"
                         runtime "Release"
                        optimize "On"

project "SandBox"
         location "SandBox"
         kind "ConsoleApp"
         language "C++"
         cppdialect "C++17"
         staticruntime "on"


         targetdir("bin/"..outputdir.."/%{prj.name}")
         objdir("bin-int/"..outputdir.."/%{prj.name}")

         files
         {
                  "%{prj.name}/src/**.h",
                  "%{prj.name}/src/**.cpp"
		 }

         includedirs
         {
                  "Rulomi/vendor/spdlog/include",
                  "Rulomi/src",
                  "Rulomi/vendor",
                  "%{IncludeDir.glm}",
                  "%{IncludeDir.entt}"
		 }

         links
         {
                "Rulomi"
		 }

         filter "system:windows"
              systemversion "latest"

              defines
              {
                     "RLM_PLATFORM_WINDOWS"
			  }

         filter "configurations:Debug"
                        defines "Rulomi_DEBUG"
                        runtime "Debug"
                        symbols "On"
            links
		    {
			    "Rulomi/vendor/assimp/bin/Debug/assimp-vc141-mtd.lib"
		    }

	    	postbuildcommands 
	    	{
			'{COPY} "../Rulomi/vendor/assimp/bin/Debug/assimp-vc141-mtd.dll" "%{cfg.targetdir}"'
		    }

         filter "configurations:Release"
                        defines "Rulomi_RELEASE"
                         runtime "Release"
                        optimize "On"
            links
		    {
			    "Rulomi/vendor/assimp/bin/Release/assimp-vc141-mt.lib"
		    }

		    postbuildcommands 
		    {
			    '{COPY} "../Rulomi/vendor/assimp/bin/Release/assimp-vc141-mt.dll" "%{cfg.targetdir}"'
		    }

         filter "configurations:Dist"
                        defines "Rulomi_DIST"
                         runtime "Release"
                        optimize "On"

                links
		        {
			        "Rulomi/vendor/assimp/bin/Release/assimp-vc141-mt.lib"
		        }

		        postbuildcommands 
		        {
			        '{COPY} "../Rulomi/vendor/assimp/bin/Release/assimp-vc141-mt.dll" "%{cfg.targetdir}"'
		        }

project "Rulomi-Editor"
	location "Rulomi-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		 "Rulomi/vendor/spdlog/include",
         "Rulomi/src",
         "Rulomi/vendor",
         "%{IncludeDir.glm}",
         "%{IncludeDir.entt}"
	}

	links
	{
		"Rulomi"
	}

	filter "system:windows"
		systemversion "latest"
         defines
         {
                "RLM_PLATFORM_WINDOWS"
	     }
		
	filter "configurations:Debug"
		defines "Rulomi_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "Rulomi_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "Rulomi_DIST"
		runtime "Release"
		optimize "on"