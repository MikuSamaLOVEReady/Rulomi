#pragma once
#include "Entity.h"


namespace Rulomi {

	// 包含一个Entity 这是composite 关系包含一般entity的所有操作
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
		//为 当前类Scrptable Entity 为 Scene 提供全部的访问权限。
		friend class Scene;
	};



}

