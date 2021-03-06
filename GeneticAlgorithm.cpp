//
// Created by Jan Woźniak on 12/29/2018.
//

#include "GeneticAlgorithm.h"
#include <vector>
#include <algorithm>
#include "Timer.h"

double GeneticAlgorithm::InitAlgorithm(GeneticConfiguration &geneticConfiguration) {
    //PrintGraph();
    Timer t;
    t.StartCounter();
    CalculatePath(geneticConfiguration);
    double time = t.GetCounter();
    return time;
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
 *  3. these phases including:
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
    sizeOfPopulation = geneticConfiguration.sizeOfPopultion_;
    population_.resize(sizeOfPopulation);
    nextPopulation_.resize(sizeOfPopulation);

    CreatePopulation(population_, geneticConfiguration.startVertex_);
    CreateRankingTab();

    rankingMax_ = (graphSize_ * graphSize_ + graphSize_) / 2;
    numberOfSelectedPaths = geneticConfiguration.numberOfSelections;

    sizeOfElite_ = sizeOfPopulation * 0.1;

    SortPaths(population_);

    const unsigned numberOfGenerations = 1000;
    probabilityOfMutation = 0.1;

    for (int generationIndex = 0; generationIndex < numberOfGenerations; ++generationIndex) {
        indexOfNextGeneration = 0;
        // Selection
        //std::cout << "h";
        CreateCrossover();
        //std::cout << "c";

        for (unsigned i = 0; i < sizeOfElite_; ++i) {
            AddPathToNextGeneration(population_[i]);
        }

        // Crossover

        // Mutation

        MakeMutations();

        population_ = nextPopulation_;
        SortPaths(population_);
    }
    std::cout << "Best: " << population_[0] << std::endl;
    return 0;
}

void GeneticAlgorithm::EvaluatePath(Path &path) {

    path.cost_ = graph_[path.startVertex_][path.path_[0]];
    for (unsigned i = 0; i < path.path_.size() - 1; ++i) {
        path.cost_ += graph_[path.path_[i]][path.path_[i + 1]];
    }
    path.cost_ += graph_[path.path_[path.path_.size() - 1]][path.startVertex_];
}

void GeneticAlgorithm::SortPaths(std::vector<Path> &population) {
    std::sort(population.begin(), population.end(), [](const Path &l, const Path &r) {
        return l.cost_ < r.cost_;
    });
}

void GeneticAlgorithm::CreateCrossover() {
    unsigned numberOfCrossovers = sizeOfPopulation - sizeOfElite_;
    std::uniform_int_distribution<unsigned> distributionProbability(0, graphSize_ - 2);

    std::uniform_int_distribution<unsigned> dist(0, rankingMax_);
    /*
    *  Crossover
    */
    //std::cout << "tutaj";
    for (unsigned crossoverIndex = 0; crossoverIndex < numberOfCrossovers; ++crossoverIndex) {
        //std::cout << crossoverIndex << ";";
        unsigned beginIndex = distributionProbability(eng), endIndex = distributionProbability(eng);
        if (beginIndex > endIndex) {
            std::swap(beginIndex, endIndex);
        }
        /*if(endIndex >= graphSize_) {
            std::cout << "gotcha~!";
        }*/
        unsigned indexFirstParent = 0;
        unsigned indexSecondParent = 1;
        unsigned randomIndex = dist(eng);

        for (unsigned i = 0; i < sizeOfPopulation-1; ++i) {
            if (randomIndex <= rankingTab_[i]) {
                indexFirstParent = i;
                break;
            }
        }
        do {
            randomIndex = dist(eng);
            for (unsigned i = 0; i < sizeOfPopulation-1; ++i) {
                if (randomIndex <= rankingTab_[i]) {
                    indexSecondParent = i;
                    break;
                }
            }
        } while (indexFirstParent == indexSecondParent  );

        Path &firstParent = population_[indexFirstParent];
        Path &secondParent = population_[indexSecondParent];
        Path child = firstParent;

        /*if (crossoverIndex == 97)
            std::cout << child << std::endl;*/
        for (unsigned index = beginIndex; index <= endIndex; ++index) {
            std::swap(child.path_[index], child.path_[FindIndexOfNode(child.path_, secondParent.path_[index])]);
        }
        // Add child to new generation
        /*std::cout << "ev";
        if (crossoverIndex == 97)
            std::cout << child << std::endl;
        std::cout << "y";*/
        EvaluatePath(child);
        //std::cout << "r";
        AddPathToNextGeneration(child);
        //std::cout << "t";
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
}

GeneticAlgorithm::GeneticAlgorithm(std::string fileName, bool isAtsp) : AlgorithmTSP(isAtsp, fileName) {

}

void GeneticAlgorithm::MakeMutations() {
    std::uniform_real_distribution<double> distributionProbabilityReal(0, 1);
    std::uniform_int_distribution<unsigned> distributionProbabilityInt(0, graphSize_-2);
    for (unsigned i = 0; i < sizeOfPopulation; ++i) {
        if (distributionProbabilityReal(eng) < probabilityOfMutation) {
            std::swap(nextPopulation_[i].path_[distributionProbabilityInt(eng)],
                      nextPopulation_[i].path_[distributionProbabilityInt(eng)]);
        }
    }
}

void GeneticAlgorithm::CreateRankingTab() {
    rankingTab_.resize(sizeOfPopulation);
    rankingTab_[0] = graphSize_;
    for (unsigned i = 1; i < graphSize_; ++i) {
        rankingTab_[i] = graphSize_ - i + rankingTab_[i - 1];
    }
}
