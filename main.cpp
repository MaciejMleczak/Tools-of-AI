#include <iostream>
#include <iomanip>
#include "Domain_Code/game.h"
#include "Domain_Code/test_game.h"
#include "Players/player_random.h"
#include "AI_player/MyAiPlayer.h"
#include "Players/player_random_safe.h"
#include "Players/player_aggro_fast.h"
#include "ResultAnalysis/AnalysisController.h"
#include "Players/player_fast.h"


using namespace std;

double EPSILON = 0.2;

int main()
{
    srand(time(NULL));
    //Run the unit tests
    test_game tester;
    tester.run_all_tests();

    AnalysisController controller(false, "../ResultData/SARSA/ep05_data.csv");
    controller.initialize();


//    Create players
//    AI AGENTS
    MyAiPlayer player_0(0.5, 0.7, EPSILON, true);
//    MyAiPlayer player_1(0.5, 0.7, EPSILON, false);
//    MyAiPlayer player_2(0.5, 0.7, EPSILON, false);
//    MyAiPlayer player_3(0.5, 0.7, EPSILON, false);

//    RANDOM PLAYERS
    player_random player_1;
    player_random player_2;
    player_random player_3;

//    AGGRESIVE PLAYERS
//    player_aggro_fast player_1;
//    player_aggro_fast player_2;
//    player_aggro_fast player_3;

//    FAST PLAYERS
//    player_fast player_1;
//    player_fast player_2;
//    player_fast player_3;

//    SAFE PLAYERS
//    player_random_safe player_1;
//    player_random_safe player_2;
//    player_random_safe player_3;


//    player_0.print_table();

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

        if(i == 0 || (i+1) % 50 == 0 && i<2500) {
            controller.save_win_perc(i + 1, (double) wins[0] * 100 / (i + 1));
        }
//        if(i == 0 || (i+1) % 2 == 0 && i<2000) {
//            controller.save_win_perc(i + 1, (double) wins[0] * 100 / (i + 1));
//        }
        if (i < 500) {
            player_0.decrease_epsilon((long double)EPSILON/500);
//            player_1.decrease_epsilon((long double)EPSILON/500);
//            player_2.decrease_epsilon((long double)EPSILON/500);
//            player_3.decrease_epsilon((long double)EPSILON/500);
        }
    }
    for(int i = 0; i < 4; i++)
        cout << "Player " << i << " won " << wins[i] << " games." << endl << endl;


//    player_0.print_table();
    cout<<endl;

    cout << "End of main" << endl;
    return 0;
}
