#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>

#include "engine/components/component.h"

using namespace Components;

namespace Entities {
    
    /**
     * @brief Super-class that represents entities.
     */
    class Entity
    {
    protected:
        ///Various Component objects that define specific entitiy
        std::vector<Component*> components;

        ///Automatically iterates through components and updates them
        void process();
        /**
         * @brief Add Component object to component list
         * @param component Component pointer object to add to list
         */
        inline void addComponent(Component* component) { components.push_back(component); }

    public:
        /**
         * @brief Construct a new Entity object
         */
        Entity();

        ///Virtual function to handle rendering
        virtual void render() {}
        ///Virtual function to handle updating
        virtual void update() {}

        /**
         * @brief Get the Components object
         * 
         * @return std::vector<Component*> Component pointer object list
         */
        inline std::vector<Component*> getComponents() const { return components; }
    };

}

#endif /* ENTITY_H_ */