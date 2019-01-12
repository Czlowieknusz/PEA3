//
// Created by Jan Woźniak on 12/8/2018.
//

#include "Test.h"
#include <vector>
#include <iostream>

void Test::MakeTests() {
    std::vector<std::string> fileNames(
            {/*"Graph_six.txt", "Graph_seven.txt", "Graph_eight.txt", "Graph_nine.txt",*/ "Graph_ten.txt",
                                                                                          "Graph_eleven.txt",
                                                                                          "Graph_twelve.txt",
                                                                                          "Graph_fourteen.txt",
                                                                                          "Graph_fiveteen.txt",
                                                                                          "Graph_sixteen.txt"});
    std::vector<std::string> hmm(
            {"br17.atsp", "ftv33.atsp", "ftv35.atsp",
             "ftv38.atsp", "p43.atsp", "ftv44.atsp", "ftv47.atsp", "ft53.atsp", "ftv55.atsp", "ftv64.atsp",
             "ft70.atsp",

             "kro124p.atsp", "ftv170.atsp", "rbg323.atsp"
                    /*"tsp_10.txt", "tsp_12.txt"*/});

    std::vector<std::string> powaznePomiary(
            {"br17.atsp", "ftv47.atsp", "ft70.atsp", "ftv170.atsp", "rbg323.atsp"});
    for (auto &fileName : powaznePomiary) {
        std::cout << "File name is " << fileName << std::endl;
        CalculateSimulatedAnnealing(1, fileName);
    }
}

void Test::CalculateSimulatedAnnealing(unsigned numberOfTests, std::string fileName) {
}
