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
		//第一个参数是插入的位置
		//第二参数是插入的对象
		//emplace  旧iterator元素**之前**返回新元素
		m_Layers.emplace(m_Layers.begin()+m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		//返回指向所找obj的指针 ---循序查找
		std::vector<Layer*>::iterator  it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}

	}


	void LayerStack::PushOverLayer(Layer* overlayer)
	{
		//在容器尾部，vector尾部
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