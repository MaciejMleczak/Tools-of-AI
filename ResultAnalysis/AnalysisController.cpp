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


AnalysisController::AnalysisController(std::string name) : name(std::move(name)) {
}

void AnalysisController::initialize() {
    std::ofstream my_file;

    my_file.open( name );
    if (my_file.is_open()) {
        my_file << "Round"<< ";" ;
        my_file << "Win perc"<< std::endl;
        my_file.close();

    }
    else{
        throw std::exception();
    }
}

void AnalysisController::save_win_perc(int round, double win_perc) {

    std::ofstream my_file(name, std::ios::app);

    if (my_file.is_open()) {
        my_file << round << ";" ;
        my_file<< win_perc << std::endl;
        my_file.close();
    }
    else{
        throw std::exception();
    }
}

void AnalysisController::save_win_perc_epsilon(int round, double win_perc, long double epsilon) {
    std::ofstream my_file(name, std::ios::app);

    if (my_file.is_open()) {
        my_file << round << ";" ;
        my_file<< win_perc << std::endl;
        my_file.close();
    }
    else{
        throw std::exception();
    }
}



