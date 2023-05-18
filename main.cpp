#include <iostream>
#include <iomanip>
#include "Domain_Code/game.h"
#include "Domain_Code/test_game.h"
#include "Players/player_random.h"
#include "AI_player/MyAiPlayer.h"
#include "Players/player_random_safe.h"
#include "Players/player_aggro_fast.h"


using namespace std;

int main()
{
    srand(time(NULL));
    //Run the unit tests
    test_game tester;
    tester.run_all_tests();


    //Create players
    MyAiPlayer player_0(0.1, 0.5, 0.7);
//    MyAiPlayer player_1(0.1, 0.7);
//    MyAiPlayer player_2(0.1, 0.7);
//    player_random_safe player_2;
//    player_random player_0;
    player_random player_1;
//    player_aggro_fast player_1;
    player_random player_2;
    player_random player_3;
//    player_aggro_fast player_3;

    player_0.print_table();

    //Play a game of Ludo
    game g(&player_0, &player_1, &player_2, &player_3);
    g.play_game();
    cout << "Player " << g.get_winner() << " won the game!" << endl << endl;

    //Play many games of Ludo
    int wins[] = {0, 0, 0, 0};
    for(int i = 0; i < 10000; i++) {
        g.reset();
        g.set_first(i % 4); //alternate who starts the game
        g.play_game();
        wins[g.get_winner()]++;
        if (i < 500) {
            player_0.decrease_epsilon(0.0014);
        }
    }
    for(int i = 0; i < 4; i++)
        cout << "Player " << i << " won " << wins[i] << " games." << endl << endl;


    player_0.print_table();
    cout<<endl;
//    player_1.print_table();

    cout << "End of main" << endl;
    return 0;
}
