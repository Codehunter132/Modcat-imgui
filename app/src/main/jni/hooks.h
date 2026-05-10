
/*hook goes here*/

float speed = 1.0f;
bool feature1, feature2, featureHookToggle, Health, godmode;

// Hooking examples. Assuming you know how to write hook
void (*AddMoneyExample)(void *instance, int amount);

bool (*old_get_BoolExample)(void *instance);
bool get_BoolExample(void *instance) {
    if (instance != NULL && featureHookToggle) {
        return true;
    }
    return old_get_BoolExample(instance);
}

float (*old_get_FloatExample)(void *instance);
float get_FloatExample(void *instance) {
    if (instance != NULL && sliderValue > 1) {
        return (float) sliderValue;
    }
    return old_get_FloatExample(instance);
}

int (*old_Level)(void *instance);
int Level(void *instance) {
    if (instance != NULL && level) {
        return (int) level;
    }
    return old_Level(instance);
}

void (*old_FunctionExample)(void *instance);
void FunctionExample(void *instance) {
    instanceBtn = instance;
    if (instance != NULL) {
        if (Health) {
            *(int *) ((uint64_t) instance + 0x48) = 999;
        }
    }
    return old_FunctionExample(instance);
}




/*offsets goes here*/


void *hack_thread(void *)
{ 
    while (!il2cpp) {
        il2cpp = GetBaseAddress("libil2cpp.so");
        unity = GetBaseAddress("libunity.so");
		
        sleep(1);
    }
    auto addr = (uintptr_t)dlsym(RTLD_NEXT, "eglSwapBuffers");
    sleep(5);
    Il2CppAttach();
	
	
	  #if defined(__aarch64__)   
	  
	  // for 64 bit
	    //----------------------------------- Hook Method ------------------------------------//
	SetResolution = (void (*)(int, int, bool))((uintptr_t)Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Screen", "SetResolution", 3));
    set_timeScale = (void (*)(float))((uintptr_t)Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Time", "set_timeScale", 1));;
    Camera_main = (void *(*)())(Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Camera", "get_main", 0));
    WorldToScreenPoint = (Vector3(*)(void *, Vector3))(Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Camera", "WorldToScreenPoint", 1)); 
    getTransform = (void *(*)(void *))(Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Component", "get_transform", 0));  
    get_position = (Vector3(*)(void *))(Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Transform", "get_position", 0));
    set_position = (void (*)(void *, Vector3))(Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Transform", "set_position", 1));
    Object_IsNativeObjectAlive = (bool *(*)(void *))(Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Object", "IsNativeObjectAlive", 1));  
   Tools::Hookl(Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Component", "get_transform", 0), (void *) FunctionExample, (void **) &old_FunctionExample);
   
   
	#else
	
	
	//for 32 bit
	SetResolution = (void (*)(int, int, bool))((uintptr_t)Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Screen", "SetResolution", 3));
    set_timeScale = (void (*)(float))((uintptr_t)Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Time", "set_timeScale", 1));;
    Camera_main = (void *(*)())(Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Camera", "get_main", 0));
    WorldToScreenPoint = (Vector3(*)(void *, Vector3))(Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Camera", "WorldToScreenPoint", 1)); 
    getTransform = (void *(*)(void *))(Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Component", "get_transform", 0));  
    get_position = (Vector3(*)(void *))(Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Transform", "get_position", 0));
    set_position = (void (*)(void *, Vector3))(Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Transform", "set_position", 1));
    Object_IsNativeObjectAlive = (bool *(*)(void *))(Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Object", "IsNativeObjectAlive", 1));  
   Tools::Hookl(Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Component", "get_transform", 0), (void *) FunctionExample, (void **) &old_FunctionExample);
  #endif
	
    //----------------------------------- Hook Method ------------------------------------//
    
    return NULL;
}
