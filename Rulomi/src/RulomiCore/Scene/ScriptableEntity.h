#pragma once
#include "Entity.h"


namespace Rulomi {

	// ����һ��Entity ����composite ��ϵ����һ��entity�����в���
	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {};

		template<typename T>
		T& GetComponent() 
		{
			return entityID.GetComponent<T>();
		}

		//
	protected:
		virtual void  OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(TimeInterval deltTIme) {}


	private:
		Entity entityID;
		//Ϊ ��ǰ��Scrptable Entity Ϊ Scene �ṩȫ���ķ���Ȩ�ޡ�
		friend class Scene;
	};



}

