#ifndef ENTITY_H
#define ENTITY_H

#include "entt/entt.hpp"

#include "Scene.h"

class Entity {
public:
    Entity() = default;
    Entity(entt::entity handle, Scene* scene);
    Entity(const Entity& other) = default;

    template<typename T>
    bool HasComponent();

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args);

    template<typename T>
    T& GetComponent();

    template<typename T>
    void RemoveComponent();
private:
    entt::entity m_EntityHandle { entt::null };
    Scene* m_Scene = nullptr;
};

#endif