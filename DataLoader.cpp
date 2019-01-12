//
// Created by Jan Woźniak on 30.11.2018.
//

#include "DataLoader.h"
#include <iostream>
#include <string>
#include <cmath>


DataLoader::DataLoader(std::string fileName) : myFile_(fileName) {
}

DataLoader::~DataLoader() {
    if (myFile_.is_open())
        myFile_.close();
}

unsigned DataLoader::GetGraphSizeFromFile() {
    if (myFile_.is_open()) {
        std::getline(myFile_, line_of_file_, ' ');
        return static_cast<unsigned>(std::stoi(line_of_file_));
    }
    return 0;
}

void DataLoader::AddEdgesFromFileToGraph(unsigned **graph, const unsigned graphSize) {
    if (myFile_.is_open()) {
        for (int i = 0; i < graphSize; ++i) {
            for (int j = 0; j < graphSize; ++j) {
                graph[i][j] = GetUnsignedFromFile();
            }
        }
    } else {
        std::cout << "Couldn't load data." << std::endl;
    }
}

void DataLoader::AddEdgesFromFileToGraphTSPLIB(unsigned **graph, unsigned graphSize) {
    if (myFile_.is_open()) {
        std::cout << "Graphsize = " << graphSize << std::endl;
        std::string line;
        double fractpart, intpart;
        for (unsigned j = 0; j < graphSize; ++j) {
            for (unsigned i = 0; i < graphSize; ++i) {
                std::getline(myFile_, line);
                std::getline(myFile_, line);
                std::getline(myFile_, line, 'e');
                auto buffer = std::stod(line);
                fractpart = std::modf(buffer, &intpart);
                while (fractpart > 0.0) {
                    buffer *= 10;
                    fractpart = std::modf(buffer, &intpart);
                }
                graph[j][i] = static_cast<unsigned >(buffer);
                //std::cout << buffer << std::endl;
            }
            for (unsigned i = 0; i < 5; ++i) {
                std::getline(myFile_, line);
            }
        }
    }
}

void DataLoader::ReserveMemoryForGraph(unsigned **graph, unsigned graphSize) {
    graph = new unsigned *[graphSize];
    for (int i = 0; i < graphSize; ++i) {
        graph[i] = new unsigned[graphSize];
    }
}

unsigned DataLoader::GetGraphSizeFromFileATSP() {
    if (myFile_.is_open()) {
        std::string line;
        do {
            myFile_ >> line;
        } while (line != "DIMENSION:");
        myFile_ >> line;
        auto graphSize = static_cast<unsigned >(std::stoi(line));
        std::cout << graphSize << std::endl;
        return graphSize;
    }
    return 0;
}

void DataLoader::AddEdgesFromFileToGraphATSP(unsigned **graph, unsigned &graphSize) {
    if (myFile_.is_open()) {
        std::string line;
/*
do {
    myFile_ >> line;
} while (line != "DIMENSION:");
myFile_ >> line;
graphSize = static_cast<unsigned >(std::stoi(line));
std::cout << graphSize << std::endl;
 */
        do {
            myFile_ >> line;
        } while (line != "EDGE_WEIGHT_FORMAT:");
        myFile_ >> line;
        if (line == "FULL_MATRIX") {
            do {
                myFile_ >> line;
            } while (line != "EDGE_WEIGHT_SECTION");
            //ReserveMemoryForGraph(graph, graphSize);
            for (unsigned i = 0; i < graphSize; ++i) {
                for (unsigned j = 0; j < graphSize; ++j) {
                    myFile_ >> line;
                    //std::cout << ";" << line << ";" << std::endl;
                    auto cost = static_cast<unsigned >(stoi(line));
                    //std::cout << "line: " << line << "; cost: " << cost << std::endl;
                    if (i != j) {
                        //std::cout << "hmmm" << std::endl;
                        graph[i][j] = cost;
                        //std::cout << "hmmm2" << std::endl;
                    }
                }
            }
        } else {
            std::cout << "Couldn't load data." << std::endl;
        }
    } else {
        std::cout << "There's no such file open." << std::endl;
    }
}


unsigned DataLoader::GetUnsignedFromFile() {
    std::getline(myFile_, line_of_file_, ' ');
    return static_cast<unsigned>(std::stoi(line_of_file_));
}