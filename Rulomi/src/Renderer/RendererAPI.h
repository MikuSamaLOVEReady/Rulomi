#pragma once

//接口类
//用于调用各种图形接口 （
//创建 对应cPP只是为了 API  s_API;单例的定义
#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Rulomi {

    class RendererAPI
    {
    public:
        // enum class 阻止 enumerator names（枚举名）被自动转换成其他类型
        //
        enum class API
        {
            None = 0, OpenGL = 1, DX = 2, Metel = 3
        };

    public:
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawVertexs(const std::shared_ptr<VertexArray>& vertexArray) = 0;
        inline static API  GetAPI() { return s_API; }
    private:
        //用于获取全局当前激活的API类型
        static API  s_API;

   };


}