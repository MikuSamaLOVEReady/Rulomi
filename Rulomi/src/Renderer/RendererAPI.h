#pragma once

//�ӿ���
//���ڵ��ø���ͼ�νӿ� ��
//���� ��ӦcPPֻ��Ϊ�� API  s_API;�����Ķ���
#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Rulomi {

    class RendererAPI
    {
    public:
        // enum class ��ֹ enumerator names��ö���������Զ�ת������������
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
        //���ڻ�ȡȫ�ֵ�ǰ�����API����
        static API  s_API;

   };


}