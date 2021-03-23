#include "RulomiPch.h"
#include "LayerStack.h"


namespace Rulomi {

	LayerStack::LayerStack() 
	{

	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			delete layer;
		}
		
	}


	void LayerStack::PushLayer(Layer* layer)
	{
		//��һ�������ǲ����λ��
		//�ڶ������ǲ���Ķ���
		//emplace  ��iteratorԪ��**֮ǰ**������Ԫ��
		m_Layers.emplace(m_Layers.begin()+m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		//����ָ������obj��ָ�� ---ѭ�����
		std::vector<Layer*>::iterator  it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}

	}


	void LayerStack::PushOverLayer(Layer* overlayer)
	{
		//������β����vectorβ��
		m_Layers.emplace_back(overlayer);
	}

	void LayerStack::PopOverLayer(Layer* overlayer)
	{
		std::vector<Layer*>::iterator it = std::find(m_Layers.begin(), m_Layers.end(), overlayer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}

	}





}