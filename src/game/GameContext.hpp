#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include "memory"

#include "../graphics/ResourceManager.hpp"
#include "entity/EntitySystem.hpp"
#include "level/Chunks.hpp"
class GameContext {
private:
    std::shared_ptr<ResourceManager> resource_m;

    std::unique_ptr<EntitySystem> entity_system;
    std::unique_ptr<Chunks> chunks;
public:
    GameContext(ResourceManager* resource_m);
    // virtual ~GameContext();

    EntitySystem* getEntitySystem();
    Chunks* getChunks();
};

#endif