#pragma once

#include <entt/entt.hpp>

namespace Mingine {
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
}
