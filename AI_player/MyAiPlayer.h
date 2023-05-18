#pragma once
#include "../Domain_Code/iplayer.h"
#include "MyQTable.h"

class MyAiPlayer : public iplayer
{

public:
	MyAiPlayer();
	MyAiPlayer(long double _alpha, long double _gamma, long double _epsilon, bool _qLearning);
	MyQTable* q_table;

    void decrease_epsilon(long double decrease_value);
	void print_table();
    ~MyAiPlayer();


private:

	long double alpha;
	long double gamma;
	long double epsilon;

    bool qLearning;

	int* post_move_position;  //collect post move position of all pieces

    int* previous_state;
    int* previous_action_performed;


	int make_decision(); //deciding which piece we are moving

	void calc_post_move_position(int move_piece);
	void learn_knocked_pieces();

	

	//help functions
	void move_start(int piece);
	void send_them_home(int square);  //sending home other pieces that were on this square
	int count_opponents(int square);  //calculating how many opponents are on this square
    int count_my_pins(int square);
	int is_globe(int square);  //more like boolean

	int calculate_state(int square);
	int calculate_action(int move_piece);

	int is_star(int square) const;  //returns how many squares we move to next star (if we are currently on the star)
    bool is_overtaking(int current_square, int next_square);

	void post_move_learning(int current_state, int next_state, int action_performed);

    void SARSA_learning(int moving_pin, int current_state, int action_performed);

};

