#pragma once

#include <string>

class MyQTable
{

public:
    MyQTable();
    ~MyQTable();

    long double get_value(int state, int action);
    void set_value(int state, int action, long double value);

    long double get_max_q(int state);

    void save(const std::string& name);
    bool load(const std::string& name);

    long double get_reward(int state);

    void copy_values_to(MyQTable& destination);
    double difference(MyQTable& other_table);

    void print_q_table();

    static const int STATE_HOME = 0;
    static const int STATE_GOAL = 1;
    static const int STATE_SAFE = 2;
    static const int STATE_DANGER = 3;

    static const int MOVE_OUT = 0;
    static const int NORMAL = 1;
    static const int IN_GOAL = 2;
    static const int STAR = 3;
    static const int GLOBE = 4;
    static const int PROTECT = 5;
    static const int KILL = 6;
    static const int DIE = 7;
    static const int GOAL_ZONE = 8;
    static const int NOTHING = 9;


private:
    static const int STATES = 4;
    static const int ACTIONS = 10;


    long double** q_table;

    long double* reward_table;

};

