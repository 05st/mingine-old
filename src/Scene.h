#ifndef SCENE_H
#define SCENE_H

#include "entt/entt.hpp"

class Entity;

class Scene {
public:
    Scene();
    ~Scene();

    Entity CreateEntity();
private:
    entt::registry m_Registry;

    friend class Entity;
};

#endif