//
// Created by Jan Woźniak on 12/29/2018.
//

#include "GeneticAlgorithm.h"
#include <vector>
#include <algorithm>

double GeneticAlgorithm::InitAlgorithm(GeneticConfiguration &geneticConfiguration) {
    //PrintGraph();
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
        for (unsigned i = 0; i < 100; ++i) {
            std::swap(chromosome.path_[distributionProbability(eng)], chromosome.path_[distributionProbability(eng)]);
        }
        chromosome.startVertex_ = startVertex;
        EvaluatePath(chromosome);
    }
}

double GeneticAlgorithm::CalculatePath(GeneticConfiguration &geneticConfiguration) {

    /*
    unsigned sizeOfPopulation = 10;
    std::vector<Path> population(sizeOfPopulation);
    std::vector<Path> nextPopulation(sizeOfPopulation);
*/
    sizeOfPopulation = geneticConfiguration.sizeOfPopultion_;
    population_.resize(sizeOfPopulation);
    nextPopulation_.resize(sizeOfPopulation);

    CreatePopulation(population_, geneticConfiguration.startVertex_);

    numberOfSelectedPaths = geneticConfiguration.numberOfSelections;

    SortPaths(population_);
    /*for (auto &x : population_) {
        std::cout << "koszt: " << x.cost_ << std::endl;
    }*/

    const unsigned numberOfGenerations = 10000;
    probabilityOfMutation = 0.1;
    //MakeMutations();

    for (int generationIndex = 0; generationIndex < numberOfGenerations; ++generationIndex) {

        //
        indexOfNextGeneration = 0;

        // Selection
        CreateCrossover();

        for (unsigned i = 0; i < 5; ++i) {
            //std::cout << "Size of population: " << nextPopulation.size() << "; sizeofPop-i" << sizeOfPopulation-i << std::endl;
            nextPopulation_[sizeOfPopulation - i - 1] = population_[i];
            // std::cout << "TU PATRZ: " << nextPopulation_[sizeOfPopulation-i-1] << std::endl <<"A teraz tutaj: " << population_[i] << std::endl;
        }
        // Crossover

        // Mutation

        /*for(unsigned i = 0 ; i < sizeOfPopulation; ++i) {
            if(population_[i].cost_ != nextPopulation_[i].cost_) {
                std::cout << "hmmm: " << population_[i].cost_ << "; " << nextPopulation_[i].cost_ <<std::endl;
            }
        }*/

        MakeMutations();

        population_ = nextPopulation_;
        SortPaths(population_);
    }

    std::cout << "Best: " << population_[0] << std::endl;

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

void GeneticAlgorithm::SortPaths(std::vector<Path> &population) {
    std::sort(population.begin(), population.end(), [](const Path &l, const Path &r) {
        return l.cost_ < r.cost_;
    });
}

void GeneticAlgorithm::CreateCrossover() {
    unsigned numberOfCrossovers = sizeOfPopulation - 4;
    std::uniform_int_distribution<unsigned> distributionProbability(0, graphSize_ - 2);

    /*
     * Crossover
     */
    for (unsigned crossoverIndex = 1; crossoverIndex < numberOfCrossovers; ++crossoverIndex) {
        unsigned beginIndex = distributionProbability(eng), endIndex = distributionProbability(eng);
        if (beginIndex > endIndex) {
            std::swap(beginIndex, endIndex);
        }
        Path &firstParent = population_[0];
        Path &secondParent = population_[crossoverIndex];
        Path child = firstParent;

        /*unsigned numberOfCitiesToCopy = endIndex - beginIndex;
        unsigned cityIndex = 0;
        unsigned copiedCities = 0;*/

        for (unsigned index = beginIndex; index <= endIndex; ++index) {
            std::swap(child.path_[index], child.path_[FindIndexOfNode(child.path_, secondParent.path_[index])]);
        }


        // Add child to new generation
        EvaluatePath(child);
        //std::cout << "TU TERAZ: " << child << std::endl << firstParent << std::endl << secondParent << std::endl;
        AddPathToNextGeneration(child);
    }
}

bool GeneticAlgorithm::CheckIfCityInRange(std::vector<unsigned> path, unsigned beginIndex, unsigned endIndex,
                                          unsigned city) {
    for (unsigned cityIndex = beginIndex; cityIndex < endIndex; ++cityIndex) {
        if (path[cityIndex] == city) {
            return true;
        }
    }
    return false;
}

unsigned GeneticAlgorithm::FindIndexOfNode(std::vector<unsigned> path, unsigned node) {
    for (unsigned i = 0; i < path.size(); ++i) {
        if (path[i] == node) {
            return i;
        }
    }
    return 0;
}

void GeneticAlgorithm::AddPathToNextGeneration(Path path) {
    nextPopulation_[indexOfNextGeneration] = path;
    ++indexOfNextGeneration;
    //std::cout << " next" << nextPopulation_[indexOfNextGeneration] << std::endl;
}

GeneticAlgorithm::GeneticAlgorithm(std::string fileName, bool isAtsp) : AlgorithmTSP(isAtsp, fileName) {

}

void GeneticAlgorithm::MakeMutations() {
    std::uniform_real_distribution<double> distributionProbabilityReal(0, 1);
    std::uniform_int_distribution<unsigned> distributionProbabilityInt(0, 1);
    for (unsigned i = 0; i < sizeOfPopulation; ++i) {
        if (distributionProbabilityReal(eng) < probabilityOfMutation) {
            std::swap(nextPopulation_[i].path_[distributionProbabilityInt(eng)],
                      nextPopulation_[i].path_[distributionProbabilityInt(eng)]);
        }
    }
}
