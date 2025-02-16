#include "Entity.hpp"
#include "PlayerEntity.hpp"
#include "EntitySystem.hpp"

#include <iostream>

void EntitySystem::createEntity(Entity* entity) {
	entity_map[entity->object_id].emplace(entity, std::unique_ptr<Entity>(entity));
	entity->system = this;

	entity->onCreate();
}

void EntitySystem::deleteEntity(Entity* entity) {
	m_entitiesToDestroy.emplace(entity);
}

void EntitySystem::update(float delta) {
    for (auto e : m_entitiesToDestroy) {
		entity_map[e->object_id].erase(0);
	}
	m_entitiesToDestroy.clear();
    for (auto&& [tag, entities] : entity_map) {
		for (auto&& [ptr, entity] : entities) {
			entity->onUpdate(delta);
		}
	}
}