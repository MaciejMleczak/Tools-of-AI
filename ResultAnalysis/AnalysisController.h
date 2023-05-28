#pragma once

#include <string>


class AnalysisController {

public:
    AnalysisController(bool enable, std::string _name);

    void initialize();
    void save_win_perc(int round, double win_perc);

private:
    bool enable;
    std::string name;
};


