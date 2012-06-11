#ifndef MEH_SYSTEM_H
#define MEH_SYSTEM_H

namespace meh {

class System {
    private:
        static bool initializated;
    protected:
    public:
        /**
         * Initializes the framework.
         *
         * Must be called at the very beginning
         * in order to init every sub-systems (mouse, 
         * keyboard, sound, ...)
         */
        static void init();
    
        /**
         * Returns whether the system has been correctly initializated.
         */
        static bool isInitializated();

        /**
         * Returns a random number between min (inlcuded) and max (excluded).
         */
        static int rnd(int min, int max);
        
        /**
         * Returns a random number between 0 (inlcuded) and max (excluded).
         */
        static int rnd(int max);

        /**
         * Returns since how many milli-seconds the app has been launched.
         */
        static double currentTime();

        /**
         * Waits for the specified number milli-seconds. This tells the
         * system to pause the current thread for the given amount of
         * time.
         */
        static void sleep(unsigned int ms);
};

} // namespace meh

#endif // MEH_SYSTEM_H
