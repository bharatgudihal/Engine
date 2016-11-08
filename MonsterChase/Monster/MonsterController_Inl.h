#include "MonsterController.h"
#include <stdlib.h>

inline void MonsterController::SetActor(Engine::Actor* actor) { monster = actor; }
inline Vector2D MonsterController::GetRandomVector() { return Vector2D((const float)(rand() % 10 - 5), (const float)(rand() % 10 - 5)); }