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

#define N 2 //N
#define BOARD_SIZE (2*N+1) //Dimension du plateau
#define DECK_SIZE 25    //P
#define TILE_SIDES 4    //C
#define MAX_PLAYERS 5

typedef enum { BLUE, RED , GREEN, YELLOW, CYAN, PURPLE, PINK, BLACK, GREY } color_t ;

struct tile_t {
    color_t colors[TILE_SIDES];
};

typedef struct tile_t Tile;

struct file_t {
    int head;
    int queue;
    Tile* suivant;
};

struct player {
    const char *name;
    int tiles_count;
    struct tile_t draw;
};

struct deck_t {
    int size;
    struct tile_t tiles[DECK_SIZE];
};

struct deck2_t {
    int size;
    struct file_t tiles;
};

struct position_t {
    int x;
    int y;
};

struct cell_t {
    struct tile_t* tile;
};

struct board_t {
    struct cell_t cells[BOARD_SIZE][BOARD_SIZE];
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
