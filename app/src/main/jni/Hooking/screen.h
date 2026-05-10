Vector3 (*WorldToScreenPoint)(void *instance, Vector3 position);
void*(*Camera_main)();

void* (*getTransform)(void *instance);
Vector3 (*get_position)(void  *instance);
void (*set_position)(void *instance, Vector3 Pos);
void *(*get_gameObject)(void *instance);
monoString *(*get_Name)(void *instance);
monoString *(*get_Tag)(void *instance);

void* (*get_transform)(uintptr_t);
Vector3 GetPlayerLocation(void *player) {
    return get_position(getTransform(player));
}
void SetLocation(void *player, Vector3 Pos)
{
	return set_position(getTransform(player), Pos);
}
