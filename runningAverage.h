#include <stdint.h>

class runningAverage
{
    public:
        void set(uint64_t reading);
        long double getAverage();
        void reset();

        runningAverage()
        {
            count = 0;
            average = 0; 
        };
    

    private:
        long double average;
        int count;
};