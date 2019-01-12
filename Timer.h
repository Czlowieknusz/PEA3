//
// Created by Jan Woźniak on 30.11.2018.
//

#ifndef PEA_2_TIMER_H
#define PEA_2_TIMER_H

#include <windows.h>

class Timer {
public:
    void StartCounter();
    double GetCounter();

    double PCFreq = 0.0;
    __int64 CounterStart = 0;
};


#endif //PEA_2_TIMER_H
