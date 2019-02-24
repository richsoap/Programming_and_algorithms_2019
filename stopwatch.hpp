#include<time.h>
class StopWatch {
    unsigned long startTime;
    public:
    void start() {
        startTime = GetTickCount();
    }
    unsigned long pause() {
        return GetTickCount() - startTime;
    }

#ifdef __linux__
    unsigned long GetTickCount() {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return ts.tv_sec*1000 + ts.tv_nsec / 1000000;
    }
#endif

};
