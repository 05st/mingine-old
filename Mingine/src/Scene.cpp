#include "Scene.h"

#include "Entity.h"
#include "Components.h"

namespace Mingine {
    Scene::Scene() {
    
    }

    Scene::~Scene() {
    
    }

    Entity Scene::CreateEntity(const std::string& tag) {
        Entity entity = { m_Registry.create(), this };
        entity.AddComponent<TagComponent>(tag.empty() ? "Entity" : tag);
        entity.AddComponent<TransformComponent>();
        return entity;
    }

    void Scene::DestroyEntity(Entity entity) {
        m_Registry.destroy(entity);
    }
}
