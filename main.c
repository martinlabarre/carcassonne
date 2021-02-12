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

#define N 5 //N
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

struct tile_t init_tile()
{
  struct tile_t tile;
  for(int i=0;i<TILE_SIDES;i++)
  {
    tile.colors[i]=BLUE;
  }
};

struct cell_t init_cell()
{
    struct cell_t cell = {.tile=NULL};
    return cell;
};

void init_board()
{
  struct board_t board;
  for(int i=0; i<BOARD_SIZE;i++)
    for(int j=0; j<BOARD_SIZE;j++)
    {
      board.cells[i][j]=init_cell();
    }
}

void fill_cell(struct board_t board, int x, int y, struct tile_t tile)
{
    *(board.cells[x][y].tile) = tile;
    //*(cell.tile) = tile;
}



int main()
{
    int x=(BOARD_SIZE/2+1);
    int y=(BOARD_SIZE/2+1);
    struct board_t plateau;
    struct tile_t tuile;
    fill_cell(plateau,x,y,tuile);
    int i,j;
    for(i=0;i<BOARD_SIZE;i++)
    {
      printf("| ");
      for(j=0;j<BOARD_SIZE;j++)
      {
        printf("| ");
      }
      printf("\n");
    }
    return 0;
}
