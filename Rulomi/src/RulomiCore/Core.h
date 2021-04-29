#pragma once


#include <memory>
#ifdef RLM_DYNAMIC_LINK
                #ifdef RLM_PLATFORM_WINDOWS
                              #ifdef RLM_BUILD_DLL
                                        #define RULOMI_API  __declspec(dllexport)
                              #else
                                        #define RULOMI_API  __declspec(dllimport)
                              #endif
                #else
                         #error RuidiLoveMiku Engine only support windows 
                #endif // RLM_PLATFORM_WINDOWS
#else  
                #define RULOMI_API
#endif

#ifndef RLM_DEBUG
            #define RLM_ENABLE_ASSERTS
#endif // !RLM_DEBUG



#ifdef RLM_ENABLE_ASSERTS
        #define RLM_ASSERT(x, ...) {  if(  !(x)  )  {    RLM_Client_ERROR( "Assertion Failed: {0}", __VA_ARGS__);__debugbreak();  }}   
        #define RLM_CORE_ASSERT(x, ...){ if(!(x)) { RLM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else 
        #define RLM_ASSERT(x, ...) 
        #define RLM_CORE_ASSERT(x, ...)
#endif // DEBUG



// << in other words left shifting an integer “x” with an integer “y” denoted as ‘(x<<y)’ 
//  1<<   1 << 1 等于 00000001 << 1 等于 00000010 等于十进制 2
//  2 << 1 等于 00000010 << 1 等于 00000100 等于十进制 4
#define BITMove(x)   (1<<x)


// Imgui layer event响应事件
#define RLM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1) 


namespace Rulomi {

    template <typename T>
    using Reference = std::shared_ptr<T>;

    template <typename T, typename...Args>
    //constexpr 可以在编译时计算其返回值的函数。
    constexpr Reference<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Scope = std::unique_ptr<T>;
    template <typename T, typename...Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
   



}