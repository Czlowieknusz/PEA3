//
// Created by Jan Woźniak on 12/29/2018.
//

#ifndef PEA3_GENETICALGORITHM_H
#define PEA3_GENETICALGORITHM_H

#include <random>
#include "AlgorithmTSP.h"

struct GeneticConfiguration {
    unsigned sizeOfPopultion_ = 1000;
    unsigned startVertex_ = 0;
    unsigned numberOfSelections = 2;
};

class GeneticAlgorithm : public AlgorithmTSP {
public:
    explicit GeneticAlgorithm(std::string fileName);

    GeneticAlgorithm(std::string fileName, bool isAtsp);

    double CalculatePath(GeneticConfiguration &);

    double InitAlgorithm(GeneticConfiguration &);

    void CreatePopulation(std::vector<Path> &, unsigned);

    void EvaluatePath(Path &);

    void SortPaths(std::vector<Path> &);

    void CreateCrossover();

    void MakeMutations();

    void CreateRankingTab();

    bool CheckIfCityInRange(std::vector<unsigned>, unsigned , unsigned, unsigned);

    unsigned FindIndexOfNode(std::vector<unsigned>, unsigned);

    void AddPathToNextGeneration(Path);

    unsigned numberOfSelectedPaths;
    unsigned sizeOfPopulation;
    unsigned indexOfNextGeneration;
    unsigned rankingMax_;
    unsigned sizeOfElite_;
    double probabilityOfMutation;

    std::vector<Path> population_;
    std::vector<Path> nextPopulation_;
    std::vector<unsigned > rankingTab_;

    std::random_device random_device_global;
    std::mt19937_64 eng;
};


#endif //PEA3_GENETICALGORITHM_H
