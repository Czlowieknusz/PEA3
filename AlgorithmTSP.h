#ifndef PEA_ALGORITHMTSP_H
#define PEA_ALGORITHMTSP_H

#include "DataLoader.h"
#include <iostream>
#include <vector>
#include <iterator>

struct Path {
    std::vector<unsigned> path_;
    unsigned cost_;
    unsigned startVertex_;

    Path() = default;

    Path(unsigned cost) : cost_(cost) {}

    Path(unsigned startVertex, unsigned graphSize) : startVertex_(startVertex),
                                                              cost_(0), path_(graphSize) {}

    void PrintPath() {
        std::copy(path_.begin(), path_.end(), std::ostream_iterator<unsigned>(std::cout, " "));
    }

    explicit Path(const Path &path) {
        cost_ = path.cost_;
//        startVertex_ = path.startVertex_;
        path_ = path.path_;
    }

    Path &operator=(const Path &other) {
        cost_ = other.cost_;
        path_ = other.path_;
        startVertex_ = other.startVertex_;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Path &path);
};

inline std::ostream &operator<<(std::ostream &os, const Path &path) {
    os << "For path: ";
    os << path.startVertex_ << " -> ";
    for (auto vertex : path.path_) {
        os << vertex << " -> ";
    }
    os << path.startVertex_ << std::endl;
    os << "cost is equal to " << path.cost_;
    return os;
}

class AlgorithmTSP {
public:
    virtual ~AlgorithmTSP() {
        for (int i = 0; i < graphSize_; ++i) {
            delete[] graph_[i];
        }
        delete[] graph_;
    };

    AlgorithmTSP(bool isTsp, std::string fileName) {
        DataLoader dataLoader(std::move(fileName));
        graphSize_ = dataLoader.GetGraphSizeFromFileATSP();
        ReserveMemoryForGraph();
        //std::cout << "halo" << std::endl;
        dataLoader.AddEdgesFromFileToGraphATSP(graph_, graphSize_);
        //std::cout << "halo4" << std::endl;
    }

    AlgorithmTSP(std::string fileName, bool isTsp) {
        DataLoader dataLoader(std::move(fileName));
        graphSize_ = dataLoader.GetGraphSizeFromFile();
        ReserveMemoryForGraph();
        dataLoader.AddEdgesFromFileToGraphTSPLIB(graph_, graphSize_);
    }

    explicit AlgorithmTSP(std::string fileName) {
        DataLoader dataLoader(std::move(fileName));
        graphSize_ = dataLoader.GetGraphSizeFromFile();
        ReserveMemoryForGraph();
        dataLoader.AddEdgesFromFileToGraph(graph_, graphSize_);
    }

    void ReserveMemoryForGraph() {
        graph_ = new unsigned *[graphSize_];
        for (int i = 0; i < graphSize_; ++i) {
            graph_[i] = new unsigned[graphSize_];
        }
    }

    void PrintGraph() {
        for (int i = 0; i < graphSize_; ++i) {
            for (int j = 0; j < graphSize_; ++j) {
                std::cout << graph_[i][j] << "; ";
            }
            std::cout << std::endl;
        }
    }

    unsigned **graph_;
    unsigned graphSize_;
};

#endif //PEA_ALGORITHMTSP_H
