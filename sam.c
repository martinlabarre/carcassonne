/**
 * -------------------------------------------------
 * CARCASSONNE - Algorithmic and programming project
 * ENSEIRB-MATMECA - RSI 1A
 * -------------------------------------------------
 * Copyright (c) 2021 - Sam VIE
 * All rights reserved.
 * -------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define N 2
#define P 25
#define C 4

#define NBC 4
#define T_SIZE N*2+3

enum color { BLACK, RED, GREEN, YELLOW, BLUE, PINK, CYAN, GREY };
enum player { NONE, PLAYER, COMPUTER };
enum bool { FALSE, TRUE };

struct tile {
    enum color colors[NBC];
    enum player belongs_to;
};

struct cell {
    struct tile *t;
    enum bool playable;
};

struct deck {
    int size;
    struct tile tiles[P];
};

struct tray {
    struct cell cells[T_SIZE][T_SIZE];
};

int rand_int(int max) {
    return rand() % max;
}

void shift_deck(struct deck *d) {
    struct deck temp;
    temp.tiles[0] = d->tiles[d->size - 1];
    for (int i = 0; i < d->size - 1; i++)
        temp.tiles[i + 1] = d->tiles[i];
    for (int i = 0; i < d->size; i++)
        d->tiles[i] = temp.tiles[i];
}

void shift_colors(enum color *colors) {
    enum color tmp[NBC];
    tmp[0] = colors[NBC - 1];
    for (int i = 0; i < NBC; i++)
        tmp[i + 1] = colors[i];
    for (int i = 0; i < NBC; i++)
        colors[i] = tmp[i];
}

struct tile create_tile() {
    struct tile ti;
    ti.belongs_to = NONE;
    for (int i = 0; i < 4; i++) {
        ti.colors[i] = rand_int(C);
    }
    return ti;
}

struct cell create_cell() {
    struct cell c = { .t = NULL, .playable = FALSE };
    return c;
}

struct deck init_deck() {
    struct deck d;
    d.size = P;
    for (int i = 0; i < P; i++) {
        d.tiles[i] = create_tile();
    }
    return d;
}

struct tray init_tray() {
    struct tray t;
    for (int i = 0; i < T_SIZE; i++) {
        for (int j = 0; j < T_SIZE; j++) {
            t.cells[i][j] = create_cell();
        }
    }
    return t;
}

void init_game(struct deck *d, struct tray *t) {
    *d = init_deck();
    *t = init_tray();
    t->cells[N+1][N+1].t = &d->tiles[d->size - 1];
    d->size -= 1;
}

void display_tile(struct tile ti, int i) {
    printf("\nTile %d: ", i);
    for (int j = 0; j < 4; j++) {
        printf("%d ", ti.colors[j]);
    }
}

void display_deck(struct deck d) {
    printf("---------DISPLAY-DECK---------");
    for (int i = 0; i < d.size; i++) {
        display_tile(d.tiles[i], i);
    }
    printf("\n------------------------------\n");
}

void display_tray(struct tray t) {
    printf("---------DISPLAY-TRAY---------\n");
    int k = 0;
    for (int i = 1; i < T_SIZE - 1; i++) {
        for (int j = 1; j < T_SIZE - 1; j++) {
            if (t.cells[i][j].t == NULL) {
                if (t.cells[i][j].playable == TRUE) {
                    k++;
                    printf("|\e[1;36m%d\e[0m", k);
                } else {
                    printf("| ");
                }
            } else {
                if (t.cells[i][j].t->belongs_to == NONE) {
                    printf("|\e[1;33mN\e[0m");
                } else if (t.cells[i][j].t->belongs_to == PLAYER) {
                    printf("|\e[1;34mP\e[0m");
                } else if (t.cells[i][j].t->belongs_to == COMPUTER) {
                    printf("|\e[1;35mC\e[0m");
                }
            }
        }
        printf("|\n");
    }
    printf("------------------------------\n");
}

int scan_cell(struct tile ti, struct tray *t, int x, int y) {

    enum color colors[8];
    for (int i = 0; i < 4; i++) {
        colors[i] = ti.colors[i];
        colors[i + 4] = ti.colors[i];
    }

    if (t->cells[x+1][y].t != NULL || t->cells[x][y+1].t != NULL || t->cells[x-1][y].t != NULL
            || t->cells[x][y-1].t != NULL) {
        for (int i = 0; i < 4; i++) {
            if (t->cells[x - 1][y].t == NULL || colors[i + 0] == t->cells[x - 1][y].t->colors[2])
                if (t->cells[x][y + 1].t == NULL || colors[i + 1] == t->cells[x][y + 1].t->colors[3])
                    if (t->cells[x + 1][y].t == NULL || colors[i + 2] == t->cells[x + 1][y].t->colors[0])
                        if (t->cells[x][y - 1].t == NULL || colors[i + 3] == t->cells[x][y - 1].t->colors[1])
                            return i + 1;
        }
    }

    return 0;
}

int scan_tray(struct tray *t, struct tile ti) {
    int k = 0;
    for (int i = 1; i < T_SIZE - 1; i++) {
        for (int j = 1; j < T_SIZE - 1; j++) {
            if (t->cells[i][j].t == NULL && scan_cell(ti, t, i, j)) {
                t->cells[i][j].playable = TRUE;
                k++;
            }
        }
    }
    return k;
}

void clear_tray(struct tray *t) {
    for (int i = 1; i < T_SIZE - 1; i++) {
        for (int j = 1; j < T_SIZE - 1; j++) {
            t->cells[i][j].playable = FALSE;
        }
    }
}

void count_points(struct tray *t, int *p_pts, int *c_pts) {
    *p_pts = 0;
    *c_pts = 0;
    for (int i = 1; i < T_SIZE - 1; i++) {
        for (int j = 1; j < T_SIZE - 1; j++) {
            if (t->cells[i][j].t != NULL) {
                if (t->cells[i][j].t->belongs_to == PLAYER)
                    *p_pts += 1;
                else if (t->cells[i][j].t->belongs_to == COMPUTER)
                    *c_pts += 1;
            }
        }
    }
}

void play_tile(struct tray *t, struct tile *ti, enum player p, int pos) {
    int k = 0, r;
    for (int i = 0; i < T_SIZE; i++) {
        for (int j = 0; j < T_SIZE; j++) {
            if (t->cells[i][j].t == NULL && t->cells[i][j].playable == TRUE) {
                k++;
                if (k == pos) {
                    r = scan_tray(t, *ti);
                    for (int l = 1; l < r; l++) {
                        shift_colors(ti->colors);
                    }
                    t->cells[i][j].t = ti;
                    t->cells[i][j].t->belongs_to = p;
                }
            }
        }
    }
}

int play(struct tray *t, struct deck *d, enum player p) {
    int k = scan_tray(t, d->tiles[0]);
    int choice;

    if (k == 0) {
        printf("Pas de possibilité de jeu, la carte est renvoyée à la fin du paquet.\n");
        shift_deck(d);
        clear_tray(t);
        return 1;
    }

    if (k == 1) {
        printf("Une seule possibilité de jeu.\n");
        play_tile(t, &d->tiles[d->size - 1], p, k);
        d->size -= 1;
        clear_tray(t);
        return 0;
    }

    if (p == PLAYER) {
        display_tray(*t);
        while (1) {
            printf("\nVeuillez choisir votre position de jeu [1 - %d] ", k);
            scanf("%d", &choice);
            if (choice <= k)
                break;
        }
    } else if (p == COMPUTER) {
        choice = rand_int(k);
    } else {    // This should never happen
        return 2;
    }

    play_tile(t, &d->tiles[d->size - 1], p, choice);
    d->size -= 1;
    clear_tray(t);

    return 0;
}

int main() {
    struct deck d;
    struct tray t;
    int p_status_code, c_status_code;

    srand(time(NULL));

    init_game(&d, &t);
    display_tray(t);

    while (d.size > 0) {

        p_status_code = play(&t, &d, PLAYER);
        if (p_status_code == 2) {
            printf("\nUne erreur s'est produite.\n");
            break;
        }
        display_tray(t);

        c_status_code = play(&t, &d, COMPUTER);
        if (c_status_code == 2) {
            printf("\nUne erreur s'est produite.\n");
            break;
        }
        display_tray(t);

        if (p_status_code == 1 && c_status_code == 1) {
            printf("\nAucun coup possible, la partie est finie.\n");
            break;
        }
    }

    int p_pts, c_pts;
    count_points(&t, &p_pts, &c_pts);
    printf("\nScore: \e[34mPLAYER %d\e[0m - \e[35m%d COMPUTER\e[0m", p_pts, c_pts);

    if (p_pts > c_pts) {
        printf("\n\e[1;34mPLAYER\e[1;0m WINS!\e[0m\n");
    } else if (c_pts > p_pts) {
        printf("\n\e[1;35mCOMPUTER\e[1;0m WINS!\e[0m\n");
    } else {
        printf("\nDRAW!\n");
    }

    return EXIT_SUCCESS;
}
