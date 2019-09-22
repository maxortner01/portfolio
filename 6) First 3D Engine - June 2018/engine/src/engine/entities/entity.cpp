#include "entity.h"

Entities::Entity::Entity() {
    
}

void Entities::Entity::process() {
    for (int i = 0; i < components.size(); i++) {
        components[i]->update();
    }
}