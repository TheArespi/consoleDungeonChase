#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#define dungeonWidth 12
#define dungeonHeight 12

/*
    Console Game: Dungeon Chase
    Written by: Reimon Pingol

    This is a game where you need to exit the dungeon without getting caught by the enemy

    dungeon code sheet:
    +--------+---------+
    | number | value   |
    +--------+---------+
    |   0    | Space   |
    +--------+---------+
    |   1    | Walls   |
    +--------+---------+
    |   2    | Player  |
    +--------+---------+
    |   3    | Door    |
    +--------+---------+
    |   4    | Key     |
    +--------+---------+
    |   5    | Enemy   |
    +--------+---------+
*/

//a function to initialize the dungeon
void initDungeon(int dungeon[dungeonHeight][dungeonWidth]){
    int i, j;

    //sets every location of the dungeon to 0
    for (i = 0; i < dungeonHeight; i++){
        for (j = 0; j < dungeonWidth; j++){
            dungeon[i][j] = 0;
        }
    }
}

//a function that would draw the dungeon
void drawDungeon(int dungeon[dungeonHeight][dungeonWidth]){
    int i, j, connection;
    //this loop looks through the dungeon array and draw the corresponding entity based on the code sheet in the above comment
    for (i = 0; i < dungeonHeight; i++){
        printf("\t\t\t");
        for (j = 0; j < dungeonWidth; j++){
            switch(dungeon[i][j]){
                case 0:
                    //if the code is 0 then it prints a space
                    printf("  ");
                    break;
                case 1:
                    //if thhe code is 1 then it prints a wall
                    //The connection is a system to know where the current wall where building is connected to another wall
                    connection = 0;
                    if (dungeon[i - 1][j] == 1 && i > 0)
                        connection += 1;
                    if (dungeon[i][j + 1] == 1 && j < dungeonWidth - 1)
                        connection += 2;
                    if (dungeon[i + 1][j] == 1 && i < dungeonHeight - 1)
                        connection += 4;
                    if (dungeon[i][j - 1] == 1 && j > 0)
                        connection += 8;

                    /*
                        Each connection has a unique number based on where does it have a connection.

                        If the wall has a connection above, the connection variable would be added 1.
                        If the wall has a connection on its right, the connection variable would be added 2.
                        If the wall has a connection below, the connection variable would be added 4.
                        If the wall has a connection on its left, the connection variable would be added 8.

                        A combination of these combination has a unique numerical value
                        (ex. if the wall has another wall above and on the right the numerical value of this connection is: 3)
                    */

                    //this switch statement prints a wall depending on what connections it have
                    switch(connection){
                        case 0:
                            printf("Î ");
                            break;
                        case 1:
                            printf("º ");
                            break;
                        case 4:
                            printf("º ");
                            break;
                        case 5:
                            printf("º ");
                            break;
                        case 2:
                            printf(" Í");
                            break;
                        case 3:
                            printf("ÈÍ");
                            break;
                        case 6:
                            printf("ÉÍ");
                            break;
                        case 7:
                            printf("ÌÍ");
                            break;
                        case 8:
                            printf("Í ");
                            break;
                        case 9:
                            printf("¼ ");
                            break;
                        case 10:
                            printf("ÍÍ");
                            break;
                        case 11:
                            printf("ÊÍ");
                            break;
                        case 12:
                            printf("» ");
                            break;
                        case 13:
                            printf("¹ ");
                            break;
                        case 14:
                            printf("ËÍ");
                            break;
                        case 15:
                            printf("ÎÍ");
                            break;
                    }
                    break;
                case 2:
                    //if the code is 2 then it prints the player
                    printf("ÞÝ");
                    break;
                case 3:
                    //if the code is 3 then it prints a door
                    //if the door has walls on its left and right then it prints a horizontal door
                    if (dungeon[i][j - 1] == 1 && dungeon[i][j + 1] == 1)
                        printf("ÄÄ");
                    //if not it prints a vertical door
                    else
                        printf("³ ");
                    break;
                case 4:
                    //if the code is 4 then it prints a key
                    printf("Öé");
                    break;
                case 5:
                    //if the code is 5 then it prints the enemy
                    printf("Øè");
                    break;
            }
        }
        printf("\n");
    }
}

//add walls to the dungeon
void insertWalls(int dungeon[dungeonHeight][dungeonWidth]){
    /*

        Note: change this  in the future so that it needs to read a file to load a specific level

    */
    int i;

    for (i = 0; i < dungeonWidth; i++){
        dungeon[0][i] = 1;
        dungeon[dungeonWidth - 1][i] = 1;
        dungeon[i][0] = 1;
        dungeon[i][dungeonHeight - 1] = 1;

        dungeon[i][3] = 1;
        dungeon[i][7] = 1;

        dungeon[3][i] = 1;
        dungeon[7][i] = 1;
    }

    //first line
    dungeon[2][3] = 0;
    dungeon[2][7] = 0;

    //second line
    dungeon[3][2] = 0;
    dungeon[3][5] = 0;
    dungeon[3][9] = 0;

    //third line
    dungeon[5][3] = 0;
    dungeon[5][7] = 0;

    //fourth line
    dungeon[7][2] = 0;
    dungeon[7][5] = 0;
    dungeon[7][9] = 0;

    //fifth line
    dungeon[9][3] = 0;
    dungeon[9][7] = 0;

    dungeon[dungeonHeight-1][dungeonWidth - 3] = 3;
    dungeon[2][9] = 4;
}

//inserts a character in the dungeon one at a time
void insertCharacter(int x, int y, int dungeon[dungeonHeight][dungeonWidth],int character){
    dungeon[y][x] = character;
}

//moves the player based on the character the user enters
void movePlayer(char move, int dungeon[dungeonHeight][dungeonWidth], int * playerX, int * playerY, int * haveKey){
    //erasing the previous position of the player
    dungeon[*playerY][*playerX] = 0;

    int newX = *playerX;
    int newY = *playerY;
    int gotKey = *haveKey;

    if (move == 'w' && *playerY > 0){
        switch(dungeon[*playerY - 1][*playerX]){
            case 0:
                newY--;
                break;
            case 3:
                if (*haveKey)
                    newY--;
                break;
            case 4:
                newY--;
                gotKey = 1;
                break;

        }
    } else if (move == 'd' && *playerX < dungeonWidth - 1){
        switch(dungeon[*playerY][*playerX + 1]){
            case 0:
               newX++;
                break;
            case 3:
                if (*haveKey)
                    newY--;
                break;
            case 4:
                newX++;
                gotKey = 1;
                break;

        }
    } else if (move == 's' && *playerY < dungeonHeight - 1){
        switch(dungeon[*playerY + 1][*playerX]){
            case 0:
               newY++;
                break;
            case 3:
                if (*haveKey)
                    newY++;
                break;
            case 4:
                newY++;
                gotKey = 1;
                break;

        }
    } else if (move == 'a' && *playerX  > 0){
        switch(dungeon[*playerY][*playerX - 1]){
            case 0:
                newX--;
                break;
            case 3:
                if (*haveKey)
                    newX--;
                break;
            case 4:
                newX--;;
                gotKey = 1;
                break;

        }
    }

    //sets the new value of the variables
    *playerX = newX;
    *playerY = newY;
    *haveKey = gotKey;
}

//moves the enemy so that it looks like the enemy is following the player
void moveEnemy(int dungeon[dungeonHeight][dungeonWidth], int * enemyX, int * enemyY, int playerX, int playerY){
    dungeon[*enemyY][*enemyX] = 0;

    int newX = *enemyX;
    int newY = *enemyY;

    int xdistance = abs(newX - playerX);
    int ydistance = abs(newY - playerY);

    if (xdistance > ydistance){
        if (newX > playerX){
            //go left because player is on left
            if (dungeon[newY][newX - 1] == 0)
                newX--;
            else{
                if (newY > playerY)
                    newY--;
                else if (newY < playerY)
                    newY++;
            }
        } else {
            //go right
            if (dungeon[newY][newX + 1] == 0)
                newX++;
            else{
                if (newY > playerY)
                    newY--;
                else if (newY < playerY)
                    newY++;
            }
        }
    } else {
        if (newY > playerY){
            //go up because player is above
            if (dungeon[newY - 1][newX] == 0)
                newY--;
            else{
                if (newX > playerX)
                    newX--;
                else if (newX < playerX)
                    newX++;
            }
        } else {
            //go down
            if (dungeon[newY + 1][newX] == 0)
                newY++;
            else{
                if (newX > playerX)
                    newX--;
                else if (newX < playerX)
                    newX++;
            }
        }
    }

    *enemyX = newX;
    *enemyY = newY;
}

//a function that draws a line based on the length given in the argument
void drawLine(int length){
    int i;
    for (i = 0; i < length; i++){
        printf("-");
    }
}

int main()
{
    char response;
    char responses[10];
    //setting the player's startng point
    int playerX = 1;
    int playerY = 1;
    //setting the enemy's starting point
    int enemyX = 6;
    int enemyY = 6;
    //declaring the dungeon array
    int dungeon[dungeonHeight][dungeonWidth];
    //if the player have the key
    int haveKey = 0;
    //initializing what's inside  the dungeon
    initDungeon(dungeon);
    insertWalls(dungeon);
    //game loop
    do {
        system("cls");
        insertCharacter(playerX,playerY,dungeon,2);
        insertCharacter(enemyX,enemyY,dungeon,5);
        drawDungeon(dungeon);
        drawLine(80);
        printf("Resopnse: ");
        scanf("%s",&responses);
        response = responses[0];
        movePlayer(response,dungeon,&playerX,&playerY,&haveKey);
        moveEnemy(dungeon,&enemyX,&enemyY,playerX,playerY);
    } while(response != '0');

    return 0;
}
