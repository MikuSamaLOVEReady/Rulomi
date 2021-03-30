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



--include GLFW的 premake file 为Rulomi 添加reference
include "Rulomi/vendor/GLFW"
include "Rulomi/vendor/GLAD" 
include "Rulomi/vendor/imgui" 

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
                  "%{prj.name}/vendor/glm/glm/**.inl"
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
                  "%{IncludeDir.glm}"
		 }

           links
         {
                "GLFW",
                "GLAD",
                "ImGui",
                "opengl32.lib"
		 }

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
                  "%{IncludeDir.glm}"
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

         filter "configurations:Release"
                        defines "Rulomi_RELEASE"
                         runtime "Release"
                        optimize "On"

         filter "configurations:Dist"
                        defines "Rulomi_DIST"
                         runtime "Release"
                        optimize "On"

