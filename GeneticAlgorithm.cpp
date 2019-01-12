//
// Created by Jan Woźniak on 12/29/2018.
//

#include "GeneticAlgorithm.h"
#include <vector>
#include <algorithm>

double GeneticAlgorithm::InitAlgorithm(GeneticConfiguration &geneticConfiguration) {
    PrintGraph();
    CalculatePath(geneticConfiguration);
    return 0;
}

GeneticAlgorithm::GeneticAlgorithm(std::string fileName) : AlgorithmTSP(std::move(fileName)),
                                                           eng(random_device_global()) {}
//  ================    Variables   =====================
/*
 * Fitness -> cost
 * Chromosome/genotype -> path
 * Population -> vector of paths
 */

//  ================    Algorithm   =====================
/*
 *  1. Init variables (size of population, population and fitness.
 *  2. Random paths at the beginning.
 *  3. these fckin phases including:
 *      - mutation (swap)
 *      - crossover (we choose a segment and rewrite it into new gene(it was called like that?) at the same position) and the rest from left to right
 */

void GeneticAlgorithm::CreatePopulation(std::vector<Path> &population, unsigned startVertex) {
    for (auto &chromosome : population) {
        for (unsigned i = 0; i < graphSize_; ++i) {
            if (i != startVertex) {
                chromosome.path_.push_back(i);
            }
        }
        std::uniform_int_distribution<unsigned> distributionProbability(0, graphSize_ - 2);
        for (unsigned i = 0; i < 20; ++i) {
            std::swap(chromosome.path_[distributionProbability(eng)], chromosome.path_[distributionProbability(eng)]);
        }
        chromosome.startVertex_ = startVertex;
        EvaluatePath(chromosome);
    }
}


double GeneticAlgorithm::CalculatePath(GeneticConfiguration &geneticConfiguration) {
    unsigned sizeOfPopulation = 10;
    unsigned numberOfSelections = 3;
    std::vector<Path> population(sizeOfPopulation);
    CreatePopulation(population, geneticConfiguration.startVertex_);

    /*
     * Tu wywala
     */
    std::sort(population.begin(), population.end(), [](const Path &l, const Path &r) {
        return l.cost_ < r.cost_;
    });



    for (auto &i : population) {
        std::cout << i << std::endl;
    }

    const unsigned numberOfGenerations = 100;

    for (int generationIndex = 0; generationIndex < numberOfGenerations; ++generationIndex) {
        // Selection
        for (unsigned selectionIndex = 0; selectionIndex < numberOfSelections; ++selectionIndex) {

        }

        // Crossover

        // Mutation
    }

    return 0;
}

void GeneticAlgorithm::EvaluatePath(Path &path) {
    //std::cout << graph_[path.startVertex_][path.path_[0]] << "; ";
    path.cost_ = graph_[path.startVertex_][path.path_[0]];
    for (unsigned i = 0; i < path.path_.size() - 1; ++i) {
//        std::cout << graph_[path.path_[i]][path.path_[i + 1]] << "; ";
        path.cost_ += graph_[path.path_[i]][path.path_[i + 1]];
    }
//    std::cout << graph_[path.path_[path.path_.size() - 1]][path.startVertex_] << "; ";
    path.cost_ += graph_[path.path_[path.path_.size() - 1]][path.startVertex_];
//    std::cout << "For path: ";
//    for (auto i : path.path_) {
//        std::cout << i << "; ";
//    }
//    std::cout << "cost is " << path.cost_ << std::endl;
}
