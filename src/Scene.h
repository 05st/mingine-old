#ifndef SCENE_H
#define SCENE_H

#include <entt/entt.hpp>

class Entity;
class Renderer;

class Scene {
public:
    Scene();
    ~Scene();

    Entity CreateEntity(const std::string& tag = std::string());
    void DestroyEntity(Entity entity);

    void Update();
private:
    entt::registry m_Registry;

    friend class Entity;
    friend class Renderer;
};

#endif