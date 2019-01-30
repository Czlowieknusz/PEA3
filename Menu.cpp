//
// Created by Jan Woźniak on 30.11.2018.
//

#include "Menu.h"
#include "Test.h"
#include <iostream>

Menu::Menu(std::string fileName) : geneticAlgorithm(std::move(fileName)) {
    MainMenu();
}

void Menu::PrintMainMenu() {
    std::cout << std::endl << std::endl;
    std::cout << "---------- Main menu ----------" << std::endl;
    std::cout << "1. Print loaded Graph." << std::endl;
    std::cout << "2. Calculate path graphs from Dr Mierzwa." << std::endl;
    std::cout << "3. Calculate path graphs from elib.zib." << std::endl;
    std::cout << "4. Test." << std::endl;
    std::cout << "0. Finish executing program." << std::endl;
}

void Menu::MainMenu() {
    while (true) {
        PrintMainMenu();
        int userOption = -1;
        while (userOption < 0 || userOption > 3) {
            std::cout << "Your option: ";
            std::cin >> userOption;
        }
        switch (userOption) {
            case 0:
                return;
            case 1:
                std::cout << "Printing Graph..." << std::endl;
                geneticAlgorithm.PrintGraph();
                break;
            case 2: {
                unsigned startVertex = 0;
                std::cout << "Which vertex do u want to start from?" << std::endl;
                std::cin >> startVertex;
                GeneticConfiguration geneticConfiguration;
                geneticConfiguration.startVertex_ = 0;
                geneticAlgorithm.InitAlgorithm(geneticConfiguration);
                break;
            }
            case 3: {
                std::cout << "Name of file: ";
                std::string fileName;
                std::cin >> fileName;
                GeneticAlgorithm geneticAlgorithmATSP(std::move(fileName), true);
                std::cout << "Which vertex do u want to start from?" << std::endl;
                GeneticConfiguration geneticConfigurationATSP;
                std::cin >> geneticConfigurationATSP.startVertex_;
                double time = geneticAlgorithmATSP.InitAlgorithm(geneticConfigurationATSP);
                std::cout << "Solution found in: " << time << std::endl;
                break;
            }
            case 4: {
                Test test;
                test.MakeTests();
                break;
            }
            default:
                break;
        }
    }
}

GeneticConfiguration Menu::CreateConfiguration() {
    return GeneticConfiguration();
}