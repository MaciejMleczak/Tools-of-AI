#pragma once

#include <string>


class AnalysisController {

public:
    AnalysisController(std::string _name);

    void initialize();
    void save_win_perc(int round, double win_perc);
    void save_win_perc_epsilon(int round, double win_perc, long double epsilon);

private:
    std::string name;
};


