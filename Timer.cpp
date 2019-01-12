//
// Created by Jan Woźniak on 30.11.2018.
//

#include "Timer.h"
#include <iostream>

void Timer::StartCounter() {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        std::cout << "QueryPerformanceFrequency Failed!" << std::endl;

    PCFreq = double(li.QuadPart) / 1.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double Timer::GetCounter() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}