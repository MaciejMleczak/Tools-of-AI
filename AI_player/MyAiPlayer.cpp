#include "MyAiPlayer.h"

MyAiPlayer::MyAiPlayer()
{
	alpha = 0.5;
	gamma = 0.5;
    q_table = new MyQTable();
    post_move_position = new int[16];
}

MyAiPlayer::MyAiPlayer(long double _alpha, long double _gamma)
{
	alpha = _alpha;
	gamma = _gamma;
    q_table = new MyQTable();
    post_move_position = new int[16];
}

int MyAiPlayer::make_decision()
{
    int valid_moves[4];
    int valid_count = 0;

    for (int i = 0; i < 4; i++)
    {
        if (is_valid_move(i))
        {
            valid_moves[valid_count] = i;  //save index of piece which has valid move
            valid_count++;
        }
    }

    //no moves allowed
    if (valid_count == 0){
        post_move_learning(MyQTable::STATE_HOME, MyQTable::STATE_HOME, MyQTable::NOTHING);
        return -1;
    }

    //only one move allowed
    if (valid_count == 1) {
        int moved_pin = valid_moves[0];
        calc_post_move_position(moved_pin);

        post_move_learning(calculate_state(position[moved_pin]),
                           calculate_state(post_move_position[moved_pin]),
                                                calculate_action(moved_pin));
        return valid_moves[0];
    }

    long double max_q_value = -1.0;

    int current_states[valid_count];
    int possible_states[valid_count];
    int possible_actions[valid_count];

    long double q_value = -1.0;
    int max_count = 0;
    int moving_piece[4];
    
    for (int i = 0; i < valid_count; i++) {
        int piece = valid_moves[i];
        calc_post_move_position(piece);

        current_states[piece] = calculate_state(position[piece]);
        possible_states[piece] = calculate_state(post_move_position[piece]);
        possible_actions[piece] = calculate_action(piece);

        q_value = q_table->get_value(current_states[piece], possible_actions[piece]);

        if (q_value > max_q_value)
        {
            max_q_value = q_value;
            moving_piece[0] = piece;
            max_count = 1;
        }
        else if (q_value == max_q_value)
        {
            moving_piece[max_count] = piece;
            max_count++;
        }
    }

    //if there is one with the most valuable move
    if (max_count < 1) {
        throw std::exception();
    }
    if (max_count == 1) {
        calc_post_move_position(moving_piece[0]);
        post_move_learning(current_states[moving_piece[0]], possible_states[moving_piece[0]],
                           possible_actions[moving_piece[0]]);
        return moving_piece[0];
    }

    //if there is more we random
    int random_number = rand() % (max_count);
    calc_post_move_position(moving_piece[random_number]);

    post_move_learning(current_states[moving_piece[random_number]], 
        possible_states[moving_piece[random_number]], possible_actions[moving_piece[random_number]]);

    return moving_piece[random_number];

}

void MyAiPlayer::calc_post_move_position(int move_piece)
{
    for (int i = 0; i < 16; i++)
        post_move_position[i] = position[i];

    if (move_piece == -1)
        return;

    int square = position[move_piece];

    if (square == -1)
        move_start(move_piece);
    else
    {
        int target = square + dice;
        target += is_star(target);

        if (target == 56) //if going to goal
            post_move_position[move_piece] = 99;
        else if (target > 50 && target < 56) //if moving close to goal inside our safe area
            post_move_position[move_piece] = target;
        else if (target > 55)  //if target is over 56 that means we have to bounce off 56
            post_move_position[move_piece] = 112 - target;
        else if (target > 0 && target < 51)
        {
            int opponents = count_opponents(target);

            if (opponents == 0) //if there is no opponents we move
                post_move_position[move_piece] = target;
            else if (opponents == 1)
            {
                if (is_globe(target)) //if we land on globe and there is an opponent we go home
                    post_move_position[move_piece] = -1;
                else  //if its not globe we send them home
                {
                    post_move_position[move_piece] = target;
                    send_them_home(target);
                }
            }
            else //if there is more than one oponent that would mean we go home
                post_move_position[move_piece] = -1;
        }
        else
            throw std::exception();
    }
}

void MyAiPlayer::move_start(int piece)
{
    if (post_move_position[piece] == -1 && dice == 6)
    {
        post_move_position[piece] = 0;
        send_them_home(0);
    }
    else
        throw std::exception();
}

void MyAiPlayer::send_them_home(int square)
{
    for (int i = 4; i < 16; i++) {
        if (post_move_position[i] == square)
            post_move_position[i] = -1;
    }
}

int MyAiPlayer::count_opponents(int square)
{
    int count = 0;

    for (int i = 4; i < 16; i++) {
        if (position[i] == square)
            count++;
    }
    return count;
}

int MyAiPlayer::is_globe(int square)
{
    return ( (square % 13) == 0 || (square % 13) == 8 );
}

int MyAiPlayer::calculate_state(int square)
{
    if (is_globe(square)) 
        return MyQTable::STATE_SAFE;
    else if (square > 51 && square < 56)
        return MyQTable::STATE_SAFE;
    else if (square == -1)
        return MyQTable::STATE_HOME;
    else if (square == 99)
        return MyQTable::STATE_GOAL;
    else
        return MyQTable::STATE_DANGER;
}

int MyAiPlayer::calculate_action(int move_piece)
{
    int square = position[move_piece];
    int next_possible_square = post_move_position[move_piece];


    if (next_possible_square == 99)
        return MyQTable::IN_GOAL;
    else if (is_star(next_possible_square)) {
        return MyQTable::STAR;
    }
    else if (next_possible_square > 50 && next_possible_square < 56) {
        return MyQTable::GOAL_ZONE;
    }
    else if (next_possible_square == -1) {
        return MyQTable::DIE;
    }
    else if (next_possible_square == 0) {
        return MyQTable::MOVE_OUT;
    }

    else if (next_possible_square > 0 && next_possible_square < 51)
    {
        int opponents = count_opponents(next_possible_square);

        if (opponents == 0) {
            if (is_globe(next_possible_square)) {       //if there is no oponents and its globe we are sfe
                return MyQTable::GLOBE;
            }
            return MyQTable::NORMAL;                    //if there is no opponent and its not globe we are doing normal
        }
        else if (opponents == 1)
        {
            if (is_globe(next_possible_square)) {         //if there is one opponent and its globe, we die
                return MyQTable::DIE;
            }
            return MyQTable::KILL;                      //if there is one opponent and its not a globe we kill
        }
        else 
            return MyQTable::DIE;
    }
    else
        throw std::exception();
    
}

int MyAiPlayer::is_star(int square) const
{
    switch (square)
    {
    case 5:  return 6;
    case 18: return 6;
    case 31: return 6;
    case 44: return 6;

    case 11: return 7;
    case 24: return 7;
    case 37: return 7;

    case 50: return 6; //jump to goal

    default: return 0;
    }
}

void MyAiPlayer::post_move_learning(int current_state, int next_state, int action_performed)
{
    long double delta_q = alpha * (q_table->get_reward(action_performed) + gamma * q_table->get_max_q(next_state)
        - q_table->get_value(current_state, action_performed));

    q_table->set_value(current_state, action_performed, q_table->get_value(current_state,
                                                                         action_performed) + delta_q);
}

void MyAiPlayer::print_table()
{
    q_table->print_q_table();
}

MyAiPlayer::~MyAiPlayer() {
    delete[] post_move_position;
    delete q_table;
}
