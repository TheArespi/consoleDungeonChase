#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define dungeonWidth 12
#define dungeonHeight 12

void initDungeon(int dungeon[dungeonHeight][dungeonWidth]){
    int i, j;

    for (i = 0; i < dungeonHeight; i++){
        for (j = 0; j < dungeonWidth; j++){
            dungeon[i][j] = 0;
        }
    }
}

void drawDungeon(int dungeon[dungeonHeight][dungeonWidth]){
    int i, j, connection;
    for (i = 0; i < dungeonHeight; i++){
        printf("\t\t\t");
        for (j = 0; j < dungeonWidth; j++){
            switch(dungeon[i][j]){
                case 0:
                    printf("  ");
                    break;
                case 1:
                    connection = 0;
                    if (dungeon[i - 1][j] == 1 && i > 0)
                        connection += 1;
                    if (dungeon[i][j + 1] == 1 && j < dungeonWidth - 1)
                        connection += 2;
                    if (dungeon[i + 1][j] == 1 && i < dungeonHeight - 1)
                        connection += 4;
                    if (dungeon[i][j - 1] == 1 && j > 0)
                        connection += 8;

                    //printf("%d",connection);
                    switch(connection){
                        case 0:
                            printf("Œ ");
                            break;
                        case 1:
                            printf("∫ ");
                            break;
                        case 4:
                            printf("∫ ");
                            break;
                        case 5:
                            printf("∫ ");
                            break;
                        case 2:
                            printf(" Õ");
                            break;
                        case 3:
                            printf("»Õ");
                            break;
                        case 6:
                            printf("…Õ");
                            break;
                        case 7:
                            printf("ÃÕ");
                            break;
                        case 8:
                            printf("Õ ");
                            break;
                        case 9:
                            printf("º ");
                            break;
                        case 10:
                            printf("ÕÕ");
                            break;
                        case 11:
                            printf(" Õ");
                            break;
                        case 12:
                            printf("ª ");
                            break;
                        case 13:
                            printf("π ");
                            break;
                        case 14:
                            printf("ÀÕ");
                            break;
                        case 15:
                            printf("ŒÕ");
                            break;
                    }
                    break;
                case 2:
                    printf("ﬁ›");
                    break;
                case 3:
                    if (dungeon[i][j - 1] == 1 && dungeon[i][j + 1] == 1)
                        printf("ƒƒ");
                    else
                        printf("≥ ");
                    break;
                case 4:
                    printf("÷È");
                    break;
            }
        }
        printf("\n");
    }
}

void insertWalls(int dungeon[dungeonHeight][dungeonWidth]){
    int i,j;

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

void insertPlayer(int x, int y, int dungeon[dungeonHeight][dungeonWidth]){
    dungeon[y][x] = 2;
}

void movePlayer(char move, int dungeon[dungeonHeight][dungeonWidth], int * playerX, int * playerY, int * haveKey){
    dungeon[*playerY][*playerX] = 0;

    int newX = *playerX;
    int newY = *playerY;
    int gotKey = 0;

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

    *playerX = newX;
    *playerY = newY;
    *haveKey = gotKey;
}

void drawLine(int length){
    int i;
    for (i = 0; i < length; i++){
        printf("-");
    }
}

int main()
{
    char response;
    int playerX = 1;
    int playerY = 1;
    int dungeon[dungeonHeight][dungeonWidth];
    int haveKey = 0;
    initDungeon(dungeon);
    insertWalls(dungeon);
    do {
        system("cls");
        insertPlayer(playerX,playerY,dungeon);
        drawDungeon(dungeon);
        drawLine(80);
        printf("Resopnse: ");
        scanf("%c",&response);
        movePlayer(response,dungeon,&playerX,&playerY,&haveKey);
    }while(response != '0');

    return 0;
}
