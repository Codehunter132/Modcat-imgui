monoString* (*_getName)(...);
monoString* getName(void *instance)
{
    char buf[128];
    sprintf(buf, "%s", _getName(instance)->get_const_char());
    currentMap = Strdup(buf); 
    return _getName(instance);
}

bool *(*Object_IsNativeObjectAlive)(void *boob);
monoString *(*get_unityVersion)(...);
monoString *(*get_version)(...);
monoString *(*get_productName)(...);
