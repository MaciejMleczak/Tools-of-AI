#include "MyQTable.h"

#include <iostream>
#include <exception>

#include <iostream>
#include <fstream>


using namespace std;

MyQTable::MyQTable()
{
    q_table = new long double *[STATES];
    for (int i = 0; i < STATES; i++)
    {
        q_table[i] = new long double[ACTIONS];
    }

    for (int i = 0; i < STATES; i++)
    {
        for (int j = 0; j < ACTIONS; j++)
        {
            q_table[i][j] = 0.0;
            //q_table[i][j] = (long double)rand() / RAND_MAX;
        }
    }

    reward_table = new long double[ACTIONS];
    
    reward_table[MOVE_OUT] = 0.25;
    reward_table[NORMAL] = 0.2;
    reward_table[IN_GOAL] = 0.8;
    reward_table[STAR] = 0.6;
    reward_table[GLOBE] = 0.4;
    reward_table[PROTECT] = 0.3;
    reward_table[KILL] = 0.3;
    reward_table[DIE] = 0.01;
    reward_table[GOAL_ZONE] = 0.4;
    reward_table[NOTHING] = 0;
}

long double MyQTable::get_value(int state, int action)
{
    return q_table[state][action];
}

void MyQTable::set_value(int state, int action, long double value)
{
    q_table[state][action] = value;
}

long double MyQTable::get_max_q(int state)
{
    long double max_value = -2;
    for (int i = 0; i < ACTIONS; i++) {
        if (q_table[state][i] > max_value) {
            max_value = q_table[state][i];
        }
    }
    return max_value;
}

void MyQTable::save(const std::string& name)
{
    ofstream myfile;
    myfile.open(name);
    if (myfile.is_open() == false)
        throw exception();

    for (int i = 0; i < STATES; i++)
    {
        for (int j = 0; j < ACTIONS; j++)
        {
            myfile << q_table[i][j] << "\n";
        }
    }
    myfile << 1.0 << "\n"; //ie. won state

    myfile.close();
}

bool MyQTable::load(const string& name)
{
    ifstream myfile;
    myfile.open(name);
    if (myfile.is_open() == false)
        std::cout << "Could not open file" << std::endl;

    double num = 0.0;
    for (int i = 0; i < STATES; i++)
    {
        for (int j = 0; j < ACTIONS; j++)
        {
            myfile >> num;
            q_table[i][j] = num;
        }
    }
    myfile.close();
    return true;
}

long double MyQTable::get_reward(int state)
{
    return reward_table[state];
}

void MyQTable::copy_values_to(MyQTable& destination)
{
    for (int i = 0; i < STATES; i++)
    {
        for (int j = 0; j < ACTIONS; j++)
        {
            destination.q_table[i][j] = this->q_table[i][j];
        }
    }
}

double MyQTable::difference(MyQTable& other_table)
{
    double dif = 0;

    for (int i = 0; i < STATES; i++)
    {
        for (int j = 0; j < ACTIONS; j++)
        {
            dif += abs(other_table.q_table[i][j] - this->q_table[i][j]);
        }
    }
    return dif;
}

void MyQTable::print_q_table()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            std::cout << q_table[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

MyQTable::~MyQTable() {

    for (int i = 0; i < STATES; i++)
    {
        delete[] q_table[i];
    }

    delete q_table;
}


