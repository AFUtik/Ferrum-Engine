#include "Entity.hpp"
#include "EntityManager.hpp"

EntityManager::~EntityManager() {
    for(Entity* ent : entities) delete ent;
}