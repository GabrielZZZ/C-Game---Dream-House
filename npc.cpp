//
//  npc1.cpp
//  GAME
//
//  Created by Gabriel Z on 2019/5/5.
//  Copyright © 2019 Gabriel. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <map>
#include <iterator>
#include "FuzzySearch.cpp"
using namespace std;
class Npc{
public:
    
    //position:
    int x, y;
    
    map<string,string> dialogoue;
    
    int getX(){
        return x;
    }
    
    int getY(){
        return y;
    }
    
    void npc1(){//in the first floor
        //clear dialogue
        dialogoue.clear();
        x = 3;
        y = 3;
//        dialogoue.push_back("Hello.\n");
//        dialogoue.push_back("I am John.\n");
//        dialogoue.push_back("Who is this?\n");
//        dialogoue.push_back("Oh, nice to meet you!\n");
//        dialogoue.push_back("Welcome to the game!");
        dialogoue.insert(pair<string, string>(" ","Hello.\n"));
        dialogoue.insert(pair<string, string>("Hello","Who is this?\n"));
        dialogoue.insert(pair<string, string>("I am xxx","I am John.\nNice to meet you!\nWelcome to the game!\nYou can ask me:\n1. Where you are     2. What you need to do    \n3. How to quit\n"));
        
        dialogoue.insert(pair<string, string>("Where am I","You are in a magic tower.\n"));
        dialogoue.insert(pair<string, string>("What I need to do","Unfortunately. You are trapped. You need to find ways to get out of this tower, or you will die here!\n"));
        dialogoue.insert(pair<string, string>("how to quit","If you want to quit the conversion, just press enter. If you want to quit the game, press ESC button, which I strongly don't advice you to do that!\n"));
    }
    
    string searchForAnswer(string input){
        FuzzySearch FS;
        
        string result = FS.SearchResult(input, dialogoue);
        
        return result;
    }

    
    void npc2(bool ifPlayerHasKey){//in the first floor
        dialogoue.clear();
        
        x = 9;
        y = 12;
        
        dialogoue.insert(pair<string, string>(" ","Hello.\nI am the Dean.\n Now I am going to show you the way.\nFirstly, you need to find the treasure and give back to me. It is in one of the floors. For reward, I will exchange 2 keys with the treasure."));

        if(ifPlayerHasKey){
            dialogoue.erase(" ");
            dialogoue.insert(pair<string, string>(" ","Good! You have the item! Now I am gonna exchange two keys that you may need later with the treasure.\n"));
            
        }
        
    }
    

    
    void npc3(){//in the second floor
        dialogoue.clear();
        
        x = 57;
        y = 8;
        
        dialogoue.insert(pair<string, string>(" ","Hey, I will not let you leave here!"));
    }
    
    
    
    void npc4(){//in the second floor
        dialogoue.clear();
        
        x = 9;
        y = 12;
        
        dialogoue.insert(pair<string, string>(" ","I am Lori, who is also stuck here just like you. But I am tired of finding way out. Hey man, if you plan to get out of here, I will give you a tip:\n You need to open the right door. There is not enough keys and some enemy will shut the door after you pass! Good luck!\n "));
        
    }

    
    void npc5(){//in the third floor//offering riddles
        dialogoue.clear();
        
        x = 2;
        y = 3;
        
        dialogoue.insert(pair<string, string>(" ","If you want to pass from me, you gonna answer the question I am asking. If you answer 3 times wrong, I will shut the door and you will never get out of here! But if you are correct, I will give you two keys as a reward.\nListen up, here is my question: \nI have no feet, no hands, no wings, but I climb to the sky. What am I?"));
        
        dialogoue.insert(pair<string, string>("smoke","right!\n"));

        
    }
    
    int user_choice[3];
    
    void npc6(){
        dialogoue.clear();
        
        x = 2;
        y = 3;
        
        //initialize user_choice
        user_choice[0] = 0;
        user_choice[1] = 0;
        user_choice[2] = 0;
    }
    
    void npc7(){//in the third floor//offering riddles
        dialogoue.clear();
        
        x = 11;
        y = 12;
        
        dialogoue.insert(pair<string, string>(" ","If you want to pass from me, you gonna answer the question I am asking. If you answer 3 times wrong, The exit door will be vanish! But if you are correct, I will ley you go.\nListen up, here is my question: \nWhat belongs to you, but other people use it more than you?"));
        
        dialogoue.insert(pair<string, string>("name","right!\n"));
        dialogoue.insert(pair<string, string>("gheiru","Wrong!\n"));
        
        
    }


    
    bool game_npc6(){
        
        cout << "If you want to pass from me, you gonna play a game with me. It is called rock, paper and scissors. I am sure you know the rules. We will have 7 turns and if you win 4 rounds then you can get my reward.\n";
        
        
        vector<string> options;
        options.push_back("rock");
        options.push_back("paper");
        options.push_back("scissor");
        
        int turns = 6;
        int npc_wins = 0;
        int player_wins = 0;
        int user_input = 0;
        cout << "Now make your choice\n (1) rock     (2) paper     (3) scissor\n";
//        cin >> user_input;
        while (turns >= 0) {
            
            if(player_wins == 2){
                cout << "Oh bad, you win. You can have the keys.\n";
                return true;
            }
            srand(time(0));
            int rand_num = rand()%(options.size());
            
            
            cin >> user_input;
            while (user_input > 3 || user_input < 1) {
                cout << "not acceptable choice. Make again.\n";
                
            }
            
            user_choice[user_input-1]++;
            
            int result = AIPart();
            
            if (result != 666) {
                
                switch (result+1) {
                    case 1:
                        rand_num = 1;
                        break;
                    case 2:
                        rand_num = 2;
                        break;
                    case 3:
                        rand_num = 0;
                        break;
                        
                    default:
                        break;
                }
                
            }
            
            cout << "I put " << options.at(rand_num) << "\n" << "You put " << options.at(user_input-1) << "\n";
            
            if (rand_num == user_input - 1) {
                
                cout << "tie! Next round.\n";
                turns--;
            } else if ((rand_num == 0 && user_input == 3) || (rand_num == 1 && user_input == 1) || (rand_num == 2 && user_input == 2)){
                cout << "I win! Next round.\n";
                turns--;
                npc_wins++;
            } else if ((rand_num == 2 && user_input == 1) || (rand_num == 0 && user_input == 2) || (rand_num == 1 && user_input == 3)){
                cout << "Oh my god... Next round!\n";
                turns--;
                player_wins++;
            }
            
            
        }
        
        cout << "Sorry, you are not passed:( Shut the door!\n";
        return false;//player loose
    }
    
    int AIPart(){
        
        
        for (int i = 0; i < 3; i++) {
            if (user_choice[i] >= 3) {
                //user choose this option more than three times -> user tends to chooose this option
                
                return i;
            }
        }
        
        return 666;
    }
};
