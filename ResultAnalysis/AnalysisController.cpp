//
// Created by macie on 18.05.2023.
//

#include "AnalysisController.h"
#include <iostream>
#include <exception>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <utility>


AnalysisController::AnalysisController(bool enable, std::string name)
    : name(std::move(name)), enable(enable) {
}

void AnalysisController::initialize() {
    if(enable) {
        std::ofstream my_file;

        my_file.open(name);
        if (my_file.is_open()) {
            my_file << "Round" << ";";
            my_file << "Win perc" << std::endl;
            my_file.close();

        } else {
            throw std::exception();
        }
    }
}

void AnalysisController::save_win_perc(int round, double win_perc) {
    if(enable) {
        std::ofstream my_file(name, std::ios::app);

        if (my_file.is_open()) {
            my_file << round << ";";
            my_file << win_perc << std::endl;
            my_file.close();
        } else {
            throw std::exception();
        }
    }
}

void AnalysisController::save_win_perc_epsilon(int round, double win_perc, long double epsilon) {
    if(enable) {
        std::ofstream my_file(name, std::ios::app);

        if (my_file.is_open()) {
            my_file << round << ";";
            my_file << win_perc << std::endl;
            my_file.close();
        } else {
            throw std::exception();
        }
    }
}



