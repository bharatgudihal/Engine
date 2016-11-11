#include <stdlib.h>

inline void MonsterController::SetActor(Engine::Actor* actor) { monster = actor; }
inline Vector2D MonsterController::GetRandomDirection() const { return Vector2D(static_cast<float>(rand() % 10 - 5), static_cast<float>(rand() % 10 - 5)); }