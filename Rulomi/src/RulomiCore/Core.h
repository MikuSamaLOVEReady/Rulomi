#pragma once


#ifdef RLM_PLATFORM_WINDOWS
              #ifdef RLM_BUILD_DLL
                        #define RULOMI_API  __declspec(dllexport)
              #else
                        #define RULOMI_API  __declspec(dllimport)
              #endif
#else
         #error RuidiLoveMiku Engine only support windows 
#endif // RLM_PLATFORM_WINDOWS
