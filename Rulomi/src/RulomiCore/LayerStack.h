#pragma once
#include "Core.h"
#include "Layer.h"

namespace Rulomi {


	class RULOMI_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverLayer(Layer* overlayer);
		void PopOverLayer(Layer* overlayer);

		//���layer stack�Ĳ㼶ָ��
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		//
		std::vector<Layer*> m_Layers;
        // ���ָ����ָ�� ��ǰ ��Ҫ�����λ��
		//std::vector<Layer*> ::iterator m_LayerInsert;
		unsigned int m_LayerInsertIndex = 0;


	};



}

