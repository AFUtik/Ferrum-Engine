//#include "Chunks.hpp"

//#include "../graphics/ChunkRenderer.hpp"
#include "GameContext.hpp"
#include "../entity/Entity.hpp"
#include "../entity/EntitySystem.hpp"


GameContext::GameContext(ResourceManager* resource_m) : resource_m(resource_m) {
    
}

EntitySystem* GameContext::getEntitySystem() {
    return entity_system.get();
}