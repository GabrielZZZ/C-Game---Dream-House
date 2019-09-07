//
//  levels.cpp
//  GAME
//
//  Created by Gabriel Z on 2019/5/5.
//  Copyright © 2019 Gabriel. All rights reserved.
//

#include <stdio.h>

class Level{
public:
    
    char levelWall[18][60];//map_height, map_width//contains the wall and also the key and items
    
    int x1,x2,y1,y2;//the border of the barrier
    
    int door_x1,door_x2,door_y;//coordinate of the door
    
    void initLevelWall(){
        for (int i = 0; i < 18; i++) {
            for (int j = 0 ; j < 60; j++) {
                levelWall[i][j] = ' ';
            }
        }
        x1=44;
        x2=60;
        y1=1;
        y2=3;
        door_x1 = 49;
        door_x2 = 53;
        door_y = 3;
        
        //add level specified walls
        for (int a = 1; a < 16; a++) {
            levelWall[4][a] = '#';
        }
        
        for (int a = 1; a < 18; a++) {
            levelWall[8][a] = '#';
        }
        
        for (int a = 36; a < 60; a++) {
            levelWall[6][a] = '#';
        }
        
        for (int a = 1; a < 14; a++) {
            levelWall[a][31] = '#';
        }
        
        for (int a = 9; a < 13; a++) {
            levelWall[a][17] = '#';
        }
        
        for (int a = 7; a < 18; a++) {
            levelWall[13][a] = '#';
        }
        
        for (int a = 7; a < 14; a++) {
            levelWall[11][a] = '#';
        }
        
        for (int a = 41; a < 61; a++) {
            levelWall[10][a] = '#';
        }
        
        for (int a = 41; a < 61; a++) {
            levelWall[15][a] = '#';
        }
        
        
//        levelWall[15][51] = '-';
//        levelWall[15][52] = '-';
//        levelWall[15][53] = '-';
//        levelWall[15][54] = '-';
        levelWall[1][15] = '#';
        levelWall[12][7] = '#';
        levelWall[3][15] = '#';
        levelWall[11][41] = '#';
        levelWall[12][41] = '#';
        levelWall[13][41] = '#';
        levelWall[14][41] = '#';
        levelWall[12][50] = '#';
        levelWall[13][50] = '#';
        levelWall[14][50] = '#';
        levelWall[12][55] = '#';
        levelWall[13][55] = '#';
        levelWall[14][55] = '#';
    }
    
    //contains the position of item and npcs
    void level1(bool key_fetch, bool item_fetch){
        initLevelWall();
        
        if(key_fetch == false){
            //specify the key position
            levelWall[1][3] = '$';
        }
        
        if(item_fetch == false){
            //specify the item position
            levelWall[14][56] = '@';
        }
        
        levelWall[15][51] = '-';
        levelWall[15][52] = '-';
        levelWall[15][53] = '-';
        levelWall[15][54] = '-';
        
    }
    
    void level2(bool key_fetch, bool item_fetch){
        initLevelWall();
        if(key_fetch == false){
            
            //specify the key position
           
            levelWall[3][7] = '$';
            
        }
        if(item_fetch == false){
            //specify the item position
            levelWall[17][56] = '@';
        }
        
        levelWall[6][32] = '-';
        levelWall[6][33] = '-';
        levelWall[6][34] = '-';
        levelWall[6][35] = '-';
        
        levelWall[4][5] = '-';
        levelWall[4][6] = '-';
        
        levelWall[2][15] = '#';
        
    }
    
    void level3(bool key_fetch, bool item_fetch){
        initLevelWall();
        if(key_fetch == false){
            levelWall[12][9] = '$';
        }
        if(item_fetch == false){
            //specify the key position
            levelWall[17][56] = '@';
        }
        
        levelWall[6][32] = '-';
        levelWall[6][33] = '-';
        levelWall[6][34] = '-';
        levelWall[6][35] = '-';
        
        
    }
    
    void level4(bool key_fetch, bool item_fetch){
        initLevelWall();
        if(key_fetch == false){
            //specify the key position
            levelWall[1][3] = '$';
        }
        if(item_fetch == false){
            //specify the key position
            levelWall[17][56] = '@';
        }
        
        levelWall[6][32] = '-';
        levelWall[6][33] = '-';
        levelWall[6][34] = '-';
        levelWall[6][35] = '-';
    }
    
    void level5(bool key_fetch, bool item_fetch){
        initLevelWall();
        if(key_fetch == false){
            //specify the key position
            levelWall[1][3] = '$';
        }
        if(item_fetch == false){
            //specify the key position
            levelWall[17][56] = '@';
        }
        
        levelWall[6][32] = '-';
        levelWall[6][33] = '-';
        levelWall[6][34] = '-';
        levelWall[6][35] = '-';
        
        //exit door position
        levelWall[12][9] = '%';
        
    }
    
    
    int getDoorX1(){
        return door_x1;
    }
    
    int getDoorX2(){
        return door_x2;
    }
    
    int getDoorY(){
        return door_y;
    }
    
    int getX1(){
        return x1;
    }
    
    int getY1(){
        return y1;
    }
    
    int getX2(){
        return x2;
    }
    
    int getY2(){
        return y2;
    }
    
    int draw(int x, int y, int level_index){
      
    
        if(x == x1 && y == y1){
            partI();
        } else if(x == x1 && y == y1+1){
            partII(level_index);
        } else if(x == x1 && y == y2){
            partIII(level_index);
        } else {
            return 0;
        }
        
        return x2;
    }
    
    void partI(){
        cout << "#///UPSTAIRS///#";
    }
    
    void partII(int level_index){
        cout << "#////LEVEL " << level_index << "///#";
    }
    
    void partIII(int level_index){
        if (level_index == 5) {
            cout << "################";
            return;
        }
        cout << "#####[.|.]######";
    }
};
