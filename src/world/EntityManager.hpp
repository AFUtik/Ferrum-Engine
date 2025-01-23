#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <memory>
#include <vector>
#include <string>

//#include <unordered_map>
#include "glm/glm.hpp"

class Entity;

class EntityManager {
public:
    std::vector<Entity*> entities;
    static std::vector<Entity*> registered_entities;

    static void register_entity(unsigned int unique_id, Entity entity);

    EntityManager();
    ~EntityManager();

    void create_entity(Entity* new_entity);

    void delete_entity(unsigned int unique_id);

    //void despawn(float cooldown, double min_distance, glm::vec3 cur_pos);

    std::vector<Entity*> find_all_by_tag(std::string tag);

    Entity* find_by_pos(glm::vec3 pos);
};

#endif