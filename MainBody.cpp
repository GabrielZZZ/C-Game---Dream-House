//
//  MainBody.cpp
//  GAME
//
//  Created by Gabriel Z on 2019/5/11.
//  Copyright © 2019 Gabriel. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <iterator>
#include <algorithm>


#include "input.cpp"
#include "npc.cpp"
#include "levels.cpp"
using namespace std;

class MainBody{
private:
    enum Constants
    {
        DIRECTION_LEFT = 1,
        DIRECTION_RIGHT = 2,
        DIRECTION_UP = 3,
        DIRECTION_DOWN = 4
    };
    
    
    
    int SCORE;
    
    // current direction of the snake
    int DIRECTION;
    
    // size of the map
    int MAP_WIDTH;
    int MAP_HEIGHT;
    
    // character of the snake body
    string SNAKE_BODY;
    
    // array of the available characters for food
    string NPC_SYMBOLS;
    string KEY_SYMBOLS;
    string ITEM_SYMBOLS;
    string DOOR_SYMBOLS;
    string EXIT_SYMBOLS;
    // current coordinates of npc
    int NPC_X;
    int NPC_Y;
    
    // current coordinates of key
    int KEY_X;
    int KEY_Y;
    bool KEY_FETCH[5];
    
    
    // current coordinates of item
    int ITEM_X;
    int ITEM_Y;
    bool ITEM_FETCH;
    
    //go upstairs and downstairs
    bool UPSTAIRS;
    bool DOWNSTAIRS;
    
    
    int KEY_NUM;//count the number of keys that the snack gets
    int ITEM_NUM;
    bool door_breaked[5];
    
    char wall[18][60];
    // current food's index
    int FOOD_SYMBOL_NUM;
    
    //the exit
    int EXIT_X;
    int EXIT_Y;
    bool vanish_exit;
    
    
    Level l1;
    
    void initWall(int level){
        /* wall looks like:
         ##############
         #            #
         #            #
         #            #
         ##############
         */
        
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                if (i == 0 || i == MAP_HEIGHT-1) {
                    wall[i][j] = '#';
                }else{
                    wall[i][j] = ' ';
                }
                
                if (j == 0 || j == MAP_WIDTH - 1) {
                    wall[i][j] = '#';
                }
                
            }
        }
        
        if (level == 1) {
            return;
        }
        for (int m = 5; m < 20; m++) {
            wall[MAP_HEIGHT-1][m] = ' ';
        }
    }
    
    
    // cell of the snake's body
    struct snake_body {
        int x;
        int y;
    };
    
    // array of cells of the snake's body
    vector<snake_body> snake;
    
    // creates the primary snake
    void init_snake() {
        for (int i(0); i < 3; i++) {
            snake_body body;
            body.x = -10;
            body.y = -10;
            
            snake.push_back(body);
        }
        
        snake[0].x = 5;
        snake[0].y = 3;
    }
    
    // checks if the snake has eaten itself
    
    
    // checks if the snake's body overlaps with coordinates
    bool is_snake_body(int x, int y) {
        for (int k(0); k < snake.size(); k++) {
            if (snake[k].y == y && snake[k].x == x) {
                return true;
            }
        }
        
        return false;
    }
    
    // checks if the coordinates are border of the map
    bool is_map_border(int x, int y) {
        
        
        if ((x >= 8 || x <= 4) && (y == MAP_HEIGHT-1)) {
            return true;
        }
        
        
        if (wall[y][x] == '#') {
            return true;
        }
        return false;
        
        
    }
    
    // checks if the coordinates match the coordinates of food
    bool is_npc(int x, int y) {
        return NPC_X == x && NPC_Y == y;
    }
    
    // checks if the snake's body overlaps with food
    bool snake_ate_food() {
        for (int i(0); i < snake.size(); i++) {
            if ((snake[i].x-1 == NPC_X && snake[i].y == NPC_Y) || (snake[i].x+1 == NPC_X && snake[i].y == NPC_Y) || (snake[i].x == NPC_X && snake[i].y-1 == NPC_Y) || (snake[i].x == NPC_X && snake[i].y+1 == NPC_Y)){
                return true;
            }
        }
        
        return false;
    }
    
    bool snake_get_key() {
        for (int i(0); i < snake.size(); i++) {
            int x = snake[i].x;
            int y = snake[i].y;
            if (wall[y][x] == '$') {
                
                return true;
            }
        }
        
        return false;
    }
    
    bool snake_get_item() {
        for (int i(0); i < snake.size(); i++) {
            if (snake[i].x == ITEM_X && snake[i].y == ITEM_Y) {
                return true;
            }
        }
        
        return false;
    }
    
    
    
    // checks if the snake is out of map
    bool is_out_of_border() {
        return snake[0].x == 0 || snake[0].y == 0 || snake[0].x == MAP_WIDTH || snake[0].y == MAP_HEIGHT;
    }
    
    bool is_reach_the_door(int x, int y) {
        if (wall[y][x] == '-') {
            return true;
        }
        return false;
    }
    
    // generates new coordinates for food
    void generate_food_coord() {
        srand( time( 0 ) );
        
        NPC_X = 3;
        NPC_Y = 3;
    }
    
    // generates a new food character
    void generate_food_symbol() {
        FOOD_SYMBOL_NUM = 0;
    }
    
    // prints score
    void print_score() {
        printf("\n###### DIALOGUE ######\n\n");
    }
    
    void addLevelWall(){
        for (int i = l1.getY1(); i <= l1.getY2(); i++) {
            
            wall[i][l1.getX1()] = '#';
            wall[i][l1.getX2()] = '#';
            
            if (i == l1.getY2()) {
                for (int j = l1.getX1(); j <= l1.getX2(); j++) {
                    wall[i][j] = '#';
                    
                    if (j >= l1.getDoorX1() && j <= l1.getDoorX2()) {
                        wall[i][j] = '?';//it is the door, not wall
                    }
                    
                    
                }
            }
            
        }
        
        for (int m = 0; m < MAP_HEIGHT; m++) {
            for (int n = 0; n < MAP_WIDTH; n++) {
                if (l1.levelWall[m][n] == '#') {
                    wall[m][n] = '#';
                }
                
                if (l1.levelWall[m][n] == '$') {//'$' represent key
                    wall[m][n] = '$';
                }
                
                if (l1.levelWall[m][n] == '-') {//'-' represent the door that needs key
                    wall[m][n] = '-';
                }
                
                
                if (l1.levelWall[m][n] == '@') {//'@' represent the item
                    wall[m][n] = '@';
                }
                
                if (l1.levelWall[m][n] == '%') {//'@' represent the exit
                    
                    
                    if (vanish_exit == false) {
                        wall[m][n] = '%';
                        EXIT_X = n;
                        EXIT_Y = m;
                        
                    }else{
                        
                    }
                    
                    
                }
                
            }
        }
    }
    
    void drawLevel(int level_index, int*x, int*y){
        
        if(level_index == 1){
            l1.level1(KEY_FETCH[level_index-1], ITEM_FETCH);
        } else if (level_index == 2){
            l1.level2(KEY_FETCH[level_index-1], ITEM_FETCH);
        } else if (level_index == 3){
            l1.level3(KEY_FETCH[level_index-1], ITEM_FETCH);
        } else if (level_index == 4){
            l1.level4(KEY_FETCH[level_index-1], ITEM_FETCH);
        } else if (level_index == 5){
            l1.level5(KEY_FETCH[level_index-1], ITEM_FETCH);
        }
        initWall(level_index);
        addLevelWall();
        int judge = l1.draw(*x, *y, level_index);
        
        if (judge != 0) {
            *x = judge;
        }
        
        
        
        
    }
    
    bool is_key(int x, int y) {
        
        if (wall[y][x] == '$') {//'$' represents key
            //        KEY_X = x;
            //        KEY_Y = y;
            return true;
        }
        return false;
        
        
    }
    
    bool is_item(int x, int y) {
        
        if (wall[y][x] == '@') {//'$' represents key
            ITEM_X = x;
            ITEM_Y = y;
            return true;
        }
        return false;
        
        
    }
    
    
    // draws a map and snake
    void draw(int level) {
        system("clear");
        
        cout << "IMPORTANT: please ENTER FULL SCREEN to play the game!\n\n";
        cout << "Game Hints: Every key can open all the door in this level, except the one that going upstairs, which will take another one key. Therefore, think CAREFULLY before making any move that needs the key! Besides, take every chance to get as many keys as possible, such as talking to NPCs, or gathering all the keys in the level at first.\n\n";
        
        cout << "Another important note: some NPCs will appear after you finish talking with the previous one, so try to talk to every NPC in the map!\n";
        // draws the map
        for (int i=0; i <= MAP_HEIGHT; i++) {
            for (int j=0; j <= MAP_WIDTH; j++) {
                
                drawLevel(level, &j, &i);
                
                if (j == 5 && i == MAP_HEIGHT-1) {
                    //draw the downstairs
                    
                    if (level != 1) {
                        cout << DOOR_SYMBOLS << "<- DOWNSTAIRS" << flush;
                        j =19;
                    } else {
                        cout <<'#'<<'#'<<'#'<<flush;
                        j = 8;
                    }
                    
                    
                }
                
                
                
                if (is_map_border(j, i)) {
                    cout << '#' << flush;
                    //                    continue;
                    
                } else if (is_snake_body(j, i)) {
                    cout << SNAKE_BODY << flush;
                    
                } else if (is_npc(j, i)) {
                    cout << NPC_SYMBOLS << flush;
                    
                    //adjust the wall so that it is not change shape
                    continue;
                    
                } else if (is_key(j, i)) {
                    cout << KEY_SYMBOLS << flush;
                    //adjust the wall so that it is not change shape
                    //                j++;
                    continue;
                    
                    
                } else if (is_item(j, i)) {
                    cout << ITEM_SYMBOLS << flush;
                    //adjust the wall so that it is not change shape
                    //                j++;
                    continue;
                    
                    
                } else if (wall[i][j] == '%') {
                    cout << EXIT_SYMBOLS << flush;
                    
                } else if (wall[i][j] == '-') {
                    if (door_breaked[level-1] == false) {
                        cout << '-' << flush;
                    }else{
                        cout << ' ' << flush;
                    }
                } else {
                    cout << ' ' << flush;
                }
                
                if (j == MAP_WIDTH && i == 0) {
                    
                    cout << "     ";
                    
                    for (int m = 0; m < 26; m++) {
                        if (m >= 9 && m <= 17) {
                            cout << "KNAPSACK";
                            m = 17;
                        }
                        
                        cout << "#";
                        
                    }
                }
                
                if (j == MAP_WIDTH && i == 1) {
                    
                    cout << "     ";
                    
                    cout << "key Number: " << KEY_NUM;
                }
                
                if (j == MAP_WIDTH && i == 2 && ITEM_FETCH) {
                    
                    cout << "     ";
                    
                    cout << "Item Number: " << ITEM_NUM;
                }
                
            }
            
            cout << "\n";
        }
        
        print_score();
    }
    
    // moves the snake and its body
    void move_snake() {
        int _x = snake[0].x;
        int _y = snake[0].y;
        int last_x, last_y;
        
        // changing the head coordinates
        switch (DIRECTION) {
            case DIRECTION_DOWN: snake[0].y++; break;
            case DIRECTION_LEFT: snake[0].x--; break;
            case DIRECTION_UP:   snake[0].y--; break;
            case DIRECTION_RIGHT:snake[0].x++; break;
            default:break;
        }
        
        // each next cell gets coordinates of the previous cell
        for (int i(1); i < snake.size(); i++) {
            last_x = snake[i].x;
            last_y = snake[i].y;
            
            snake[i].x = _x;
            snake[i].y = _y;
            
            _x = last_x;
            _y = last_y;
        }
    }
    
    // will be called on 'Esc'
    void exit() {
        input_off();
        
        cout << "\nYou Lose!\n";
        printf("\n\n###### THANK YOU FOR GAME ######\n\n");
    }
    
public:
    
    MainBody(){
        SCORE = 0;
        DIRECTION = DIRECTION_DOWN;
        MAP_WIDTH = 60;
        MAP_HEIGHT = 18;
        SNAKE_BODY = "*";
        NPC_SYMBOLS = "🕵";
        KEY_SYMBOLS = "🔑";
        ITEM_SYMBOLS = "💎";
        DOOR_SYMBOLS = "🚪";
        EXIT_SYMBOLS = "⛩";// use % in the wall[][];
        NPC_X = 0;
        NPC_Y = 0;
        
        // current coordinates of key
        KEY_X = 0;
        KEY_Y = 0;
        for (int i = 0; i < 5; i++) {
            KEY_FETCH[i] = false;
            door_breaked[i] = false;
        }
        
        
        
        // current coordinates of item
        ITEM_X = 0;
        ITEM_Y = 0;
        ITEM_FETCH = false;
        
        //go upstairs and downstairs
        UPSTAIRS = false;
        DOWNSTAIRS = false;
        
        
        KEY_NUM = 0;//count the number of keys that the snack gets
        ITEM_NUM = 0;
        
        
        // current food's index
        FOOD_SYMBOL_NUM = 0;
        vanish_exit = false;
    }
    
    
    int run(){
        fd_set rfds;
        timeval timeout;
        
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;
        
        int level = 1;
        input_on();
        initWall(level);
        generate_food_coord();
        generate_food_symbol();
        init_snake();
        bool judge = true;
        
        
        int npc_count = 1;//count which npc should be on
        
        
        Npc npc_class;
        bool can_i_exit = false;
        while (true) {
            //        npc_class.npc1();
            
            if (npc_count == 1) {
                npc_class.npc1();
                NPC_X = npc_class.getX();
                NPC_Y = npc_class.getY();
                
            } else if (npc_count == 2){
                npc_class.npc2(ITEM_FETCH);
                NPC_X = npc_class.getX();
                NPC_Y = npc_class.getY();
                
            } else if (npc_count == 3 && level == 2){
                npc_class.npc3();
                NPC_X = npc_class.getX();
                NPC_Y = npc_class.getY();
                
            } else if (npc_count == 4 && level == 2){
                npc_class.npc4();
                NPC_X = npc_class.getX();
                NPC_Y = npc_class.getY();
                
            } else if (npc_count == 5 && level == 2){
                //            npc_count = 5;
                npc_class.npc5();
                NPC_X = npc_class.getX();
                NPC_Y = npc_class.getY();
                
            } else if (level == 3){
                npc_count = 6;
                if (door_breaked[2] == false) {
                    npc_class.npc6();
                    NPC_X = npc_class.getX();
                    NPC_Y = npc_class.getY();
                    
                }
            } else if (level == 5){
                
                npc_count = 7;
                npc_class.npc7();
                
                if (can_i_exit == false) {
                    NPC_X = npc_class.getX();
                    NPC_Y = npc_class.getY();
                }
//                NPC_X = npc_class.getX();
//                NPC_Y = npc_class.getY();
            }
            
            
            
            if (judge == true) {
                
                
                if (UPSTAIRS == true) {
                    //reposition snake
                    for (int i = 0; i < snake.size(); i++) {
                        snake[i].y = 4;
                        snake[i].x = 55 + i;
                    }
                } else if (DOWNSTAIRS == true) {
                    //reposition snake
                    for (int i = 0; i < snake.size(); i++) {
                        snake[i].y = 16;
                        snake[i].x = 5 + i;
                    }
                }
                
                draw(level);
                
            }
            
            UPSTAIRS = false;
            DOWNSTAIRS = false;
            
            FD_ZERO(&rfds);
            FD_SET(STDIN_FILENO, &rfds);
            
            switch (getchar()) {
                    
                case 100:
                    if (is_reach_the_door(snake[0].x+1, snake[0].y) && door_breaked[level-1] == false) {
                        if (KEY_NUM > 0) {
                            KEY_NUM--;
                            door_breaked[level-1] = true;
                            l1.levelWall[snake[0].y][snake[0].x+1] = ' ';
                        } else {
                            DIRECTION = 0;
                        }
                    } else if (!is_map_border(snake[0].x+1, snake[0].y)){
                        DIRECTION = DIRECTION_RIGHT;
                        move_snake();
                    } else {
                        DIRECTION = 0;
                    }
                    judge = true;
                    
                    break;
                    
                    //            case 83:
                case 115:
                    if (is_reach_the_door(snake[0].x, snake[0].y+1) && door_breaked[level-1] == false) {
                        if (KEY_NUM > 0) {
                            KEY_NUM--;
                            door_breaked[level-1] = true;
                            l1.levelWall[snake[0].y+1][snake[0].x] = ' ';
                        } else {
                            DIRECTION = 0;
                        }
                    } else if (!is_map_border(snake[0].x, snake[0].y+1)){
                        DIRECTION = DIRECTION_DOWN;
                        move_snake();
                    } else {
                        DIRECTION = 0;
                    }
                    judge = true;
                    break;
                    //            case 65:
                case 97:
                    if (is_reach_the_door(snake[0].x-1, snake[0].y) && door_breaked[level-1] == false) {
                        if (KEY_NUM > 0) {
                            KEY_NUM--;
                            door_breaked[level-1] = true;
                            l1.levelWall[snake[0].y][snake[0].x-1] = ' ';
                        } else {
                            DIRECTION = 0;
                        }
                    } else if (!is_map_border(snake[0].x-1, snake[0].y)){
                        DIRECTION = DIRECTION_LEFT;
                        move_snake();
                    } else {
                        DIRECTION = 0;
                    }
                    judge = true;
                    break;
                    //            case 87:
                case 119:
                    if (is_reach_the_door(snake[0].x, snake[0].y-1) && door_breaked[level-1] == false) {
                        if (KEY_NUM > 0) {
                            KEY_NUM--;
                            door_breaked[level-1] = true;
                            l1.levelWall[snake[0].y-1][snake[0].x] = ' ';
                        } else {
                            DIRECTION = 0;
                        }
                    } else if (!is_map_border(snake[0].x, snake[0].y-1)){
                        DIRECTION = DIRECTION_UP;
                        move_snake();
                    } else {
                        DIRECTION = 0;
                    }
                    judge = true;
                    break;
                    
                case 27:
                    cout << "If you quit, you will lose the game, are you sure? (y/n)";
                    char input;
                    cin >> input;
                    
                    if (input == 'y') {
                        exit();
                        return 0;
                    }
                    
                    break;
                    //                exit();
                    //                return 0;
                default: judge = false; break;
            }
            
            cout << "\n";
            
            
            if (snake_ate_food()) {
                
                std::string str = " ";
                
                
                int wrong_answer_count = 0;//if player answers 3 times wrong, then he screw up.
                
                if (npc_count == 6){
                    cout << "Ok,now I gonna shut the door.\n";
                    door_breaked[2] = false;
                    bool result = npc_class.game_npc6();
                    
                    if (result == true) {
                        //user win the game
                        KEY_NUM += 2;
                        if (snake[0].x == NPC_X) {
                            //they are in a vertical line
                            for (int i = 0; i < snake.size(); i++) {
                                snake[i].y++;
                            }
                        } else if (snake[0].y == NPC_Y){
                            //they are in a hoizontal line
                            for (int i = 0; i < snake.size(); i++) {
                                snake[i].x++;
                            }
                        }
                        NPC_X = 0;
                        NPC_Y = 0;
                        npc_count++;
                        door_breaked[2] = true;
                        continue;
                    }else {
                        door_breaked[level-1] = false;
                        if (snake[0].x == NPC_X) {
                            //they are in a vertical line
                            for (int i = 0; i < snake.size(); i++) {
                                snake[i].y++;
                            }
                        } else if (snake[0].y == NPC_Y){
                            //they are in a hoizontal line
                            for (int i = 0; i < snake.size(); i++) {
                                snake[i].x++;
                            }
                        }
                        continue;
                    }
                }
                
                if (npc_count == 5 || npc_count == 7) {
                    cout << npc_class.dialogoue[" "] << "\n";
                    getline(cin, str);
                    
                    
                }
                
                while (!str.empty()) {
                    
                    string answer;
                    if (npc_count != 5 && npc_count != 7) {
                        answer = npc_class.searchForAnswer(str);
                        cout << answer;
                    }else if (npc_count == 7){
                        answer = "name";
                    }else if (npc_count == 5){
                        answer = "smoke";
                    }
//                    answer = npc_class.searchForAnswer(str);
                    
                    
                    
                    
                    if (npc_count == 5 || npc_count == 7) {
                        
                        if (wrong_answer_count == 2) {
                            door_breaked[level-1] = false;
                            
                            if(npc_count == 7){
                                //vanish the exit door
                                can_i_exit = true;
                                vanish_exit = true;
                                
                                EXIT_Y = 0;
                                EXIT_X = 0;
                            }
                            
                            break;
                            
                        }
                        
                        if (answer == str) {
                            cout << "correct!\n";
                            KEY_NUM += 3;
                            if(npc_count == 7){
                                can_i_exit = true;
                            }
                            break;
                        }
                        else{
                            cout << "Incorrect! Your answer: " << str << "\n";
                            wrong_answer_count++;
                        }
                    }
                    
                    
                    str.clear();
                    getline(cin, str);
                    
                }
                
                if (npc_count == 2 && ITEM_FETCH == true) {
                    if (ITEM_NUM > 0) {
                        ITEM_NUM--;
                        KEY_NUM+=2;
                    }
                    
                    if (snake[0].x == NPC_X) {
                        //they are in a vertical line
                        for (int i = 0; i < snake.size(); i++) {
                            snake[i].y++;
                        }
                    } else if (snake[0].y == NPC_Y){
                        //they are in a hoizontal line
                        for (int i = 0; i < snake.size(); i++) {
                            snake[i].x++;
                        }
                    }
                    NPC_X = 0;
                    NPC_Y = 0;
                    npc_count++;
                    
                    continue;
                }
                
                if(npc_count == 1 || npc_count == 3 || npc_count == 4 || npc_count == 5 || npc_count == 7){
                    //dispear
                    if (snake[0].x == NPC_X) {
                        //they are in a vertical line
                        for (int i = 0; i < snake.size(); i++) {
                            snake[i].y++;
                        }
                    } else if (snake[0].y == NPC_Y){
                        //they are in a hoizontal line
                        for (int i = 0; i < snake.size(); i++) {
                            snake[i].x++;
                        }
                    }
                    NPC_X = 0;
                    NPC_Y = 0;
                    
                    if (npc_count == 3) {
                        //lock the door
                        door_breaked[level-1] = false;
                    }
                    
                    npc_count++;
                    continue;
                }
                
                
                
                //make snack move back in case it is stuck
                if (snake[0].x == NPC_X) {
                    //they are in a vertical line
                    for (int i = 0; i < snake.size(); i++) {
                        snake[i].y++;
                    }
                } else if (snake[0].y == NPC_Y){
                    //they are in a hoizontal line
                    for (int i = 0; i < snake.size(); i++) {
                        snake[i].x++;
                    }
                }
                
            }
            
            if (snake[0].x == 10 && snake[0].y == 12 && level == 5 && vanish_exit == false) {
                // the snake found its way out
                //                std::ifstream f("exit.txt");
                //
                //                if (f.is_open()){
                //                    system("clear");
                //                    std::cout << f.rdbuf();
                //                    f.close();
                //                    return 0;
                //                }
                
                system("clear");
                
                cout << "YOU WIN!\n";
                return 0;
            }
            
            
            if (snake_get_key()) {
                
                
                KEY_FETCH[level-1] = true;
                wall[KEY_Y][KEY_X] = ' ';
                
                KEY_NUM++;
            }
            
            if (snake_get_item()) {
                
                //dispear
                ITEM_X = 0;
                ITEM_Y = 0;
                ITEM_FETCH = true;
                wall[ITEM_Y][ITEM_X] = ' ';
                
                ITEM_NUM++;
            }
            
            // the snake reaches the wall
            if (judge) {
                
                if ((level > 1 && snake[0].y == MAP_HEIGHT-1 && snake[0].x <= 7 && snake[0].x >= 5)){
                    //Go downstairs
                    level--;
                    DOWNSTAIRS = true;
                    
                    //adjust NPC
                    npc_count = level+1;
                    NPC_X = 0;
                    NPC_Y = 0;
                } else if (level < 5 && snake[0].y == l1.getDoorY() && snake[0].x <= l1.getDoorX2() && snake[0].x >= l1.getDoorX1()){
                    
                    if (KEY_NUM >= 1) {
                        //Go upstairs
                        level++;
                        UPSTAIRS = true;
                        npc_count = level+1;
                        NPC_X = 0;
                        NPC_Y = 0;
                        KEY_NUM--;
                    }else {
                        
                    }
                    
                }
                
                
                
            }
            //usleep(100000);
        }
        
        input_off();
        return 0;
    }
};

