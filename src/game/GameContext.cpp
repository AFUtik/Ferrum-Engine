//#include "Chunks.hpp"

//#include "../graphics/ChunkRenderer.hpp"
#include "GameContext.hpp"
#include "../entity/Entity.hpp"
#include "../entity/EntitySystem.hpp"


GameContext::GameContext(ResourceManager* resource_m) : resource_m(resource_m), entity_system(new EntitySystem()), chunks(new Chunks()) {
    
}

EntitySystem* GameContext::getEntitySystem() {
    return entity_system.get();
}

Chunks* GameContext::getChunks() {
    return chunks.get();
}