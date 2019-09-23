#ifndef SCREEN_H_
#define SCREEN_H_

namespace Controllers {
    
    /**
     * @brief Super class used to implement a variety of different screens
     * Subordinate classes use this framework to implement their various functions
     * as to act seperate from each other. 
     */
    class Screen
    {
    public:
        /**
         * @brief Construct a new Screen object
         * 
         */
        Screen();

        ///Render to screen
        virtual void render();
        ///Update variables
        virtual void update();
    };

}

#endif /* SCREEN_H_ */