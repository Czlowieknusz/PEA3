//
// Created by Jan Woźniak on 12/29/2018.
//

#ifndef PEA3_GENETICALGORITHM_H
#define PEA3_GENETICALGORITHM_H

#include <random>
#include "AlgorithmTSP.h"

struct GeneticConfiguration {
    unsigned startVertex_ = 0;
};

class GeneticAlgorithm : public AlgorithmTSP {
public:
    explicit GeneticAlgorithm(std::string fileName);

    double CalculatePath(GeneticConfiguration &);

    double InitAlgorithm(GeneticConfiguration &);

    void CreatePopulation(std::vector<Path> &, unsigned);

    void EvaluatePath(Path &);

    void SortPaths(std::vector<Path> &);

    std::random_device random_device_global;
    std::mt19937_64 eng;
};


#endif //PEA3_GENETICALGORITHM_H
