#ifndef ENTITYSYSTEM_HPP
#define ENTITYSYSTEM_HPP

#include <memory>
#include <vector>
#include <string>

#include <map>
#include <set>

#include "Entity.hpp"

typedef std::map<size_t, std::map<Entity*, std::unique_ptr<Entity>>> EntityMap;

class EntitySystem {
protected:
    EntityMap entity_map;
	std::set<Entity*> m_entitiesToDestroy;
    //static std::vector<Entity> registered;

    friend class Entity;
    friend class EntityRenderer;
public:
    //static void register_entity(size_t id, Entity entity);
    EntitySystem() {};
    // ~EntitySystem();

    void createEntity(Entity* entity);

    void deleteEntity(Entity* entity);

    void update(float delta);

    //std::vector<Entity*> find_all_by_tag(std::string tag);

    //Entity* find_by_pos(glm::vec3 pos);
};

#endif