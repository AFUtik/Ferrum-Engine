#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

class Entity;

class EntityManager {
private:
    std::vector<Entity*> entities;
    int max_render_entites = 256;
public:
    EntityManager();
    ~EntityManager();

    void create_entity(Entity* ent, glm::vec3 pos);

    void delete_entity(unsigned int ent_id);

    //void despawn(float cooldown, double min_distance, glm::vec3 cur_pos);

    std::vector<Entity*> find_all_by_tag(std::string tag);

    Entity* find_by_pos(glm::vec3 pos);
};

#endif