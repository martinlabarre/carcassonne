/* 
Les pavages de Carcassonne - Projet Algorithmique et Programmation C 
ENSEIRB-MATMECA - RSI S6 
Maxime GOURGUES, Martin LABARRE
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

#define BOARD_SIZE 2    //N
#define DECK_SIZE 25    //P
#define TILE_SIDES 4    //C
#define MAX_PLAYERS 5

struct file_t {
    int head;
    int queue;
    tile_t* suivant;
}

typedef enum color_t { BLUE, RED , GREEN, YELLOW, CYAN, PURPLE, PINK, BLACK, GREY, WHITE };

struct player {
    const char *name;
    int tiles_count;
    struct tile draw;
};

struct tile_t {
    enum color colors[TILE_SIDES];
};

struct deck_t {
    int size;
    struct tile tiles[DECK_SIZE];
}

struct deck2_t {
    int size;
    struct file_t tiles;
}
struct position_t {
    int x; 
    int y; 
};

struct cell_t {
    struct tile* tile;    
};

struct board_t {
    int range = 2*BOARD_SIZE+1;
    struct cell cells[range][range];
    int size; 
};

struct game {
    const int player_count;
    struct player players[MAX_PLAYERS];
    int score; 
};

int main()
{
    return 0;
}