#ifndef game
#define game

void map_reset(int map_no, char R[][10], char **argv);

void rand_(int *xx, int *yy, char **m1);

int remained(char **m);

int finish(char **m);

void destroy_in_advance(char **m1, char **m2, char **mask, int *no1, int *no2, int *mistakes, int *winner, int *move);

void randomize_map(char **m1, int **m3, char aux[][10]);

void match(int argc, char **argv, int *new_round, int *map_no, int *dif, int *mode, char R[][10], int no_);

#endif
