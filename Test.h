//
// Created by Jan Woźniak on 12/8/2018.
//

#ifndef PEA_2_TEST_H
#define PEA_2_TEST_H

#include <string>

class Test {
public:
    Test() = default;
    void MakeTests();
    void CalculateSimulatedAnnealing(unsigned, std::string);
};
#endif //PEA_2_TEST_H
