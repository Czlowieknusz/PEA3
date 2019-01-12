//
// Created by Jan Woźniak on 30.11.2018.
//

#ifndef PEA_2_DATALOADER_H
#define PEA_2_DATALOADER_H

#include <fstream>

class DataLoader {
public:
    explicit DataLoader(std::string);

    DataLoader() = default;

    ~DataLoader();

    unsigned GetGraphSizeFromFile();

    unsigned GetGraphSizeFromFileATSP();

    void AddEdgesFromFileToGraph(unsigned **graph, unsigned graphSize);

    void AddEdgesFromFileToGraphTSPLIB(unsigned **graph, unsigned graphSize);

    void AddEdgesFromFileToGraphATSP(unsigned **graph, unsigned &graphSize);

    unsigned GetUnsignedFromFile();

    void ReserveMemoryForGraph(unsigned** graph, unsigned graphSize);

private:
    std::ifstream myFile_;
    std::string line_of_file_;
};

#endif //PEA_2_DATALOADER_H
