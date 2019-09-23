#ifndef COMPONENT_H_
#define COMPONENT_H_

namespace Components {
    
    /**
     * @brief Abstract class used for various implementations
     * Abstract class used to describe properties of an entity. 
     */
    class Component
    {
    public:
        /**
         * @brief Construct a new Component object
         * 
         */
        Component();

        ///Used to update specific properties of an object
        virtual void update() = 0;
    };

}

#endif /* COMPONENT_H_ */