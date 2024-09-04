#ifndef LAPS_H
#define LAPS_H
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * struct Car - Binary search tree
 * @id: id of the car
 * @laps: # of laps
 * @left: pointer to left node
 * @right: pointer to right node
 */

typedef struct Car {
    int id;
    int laps;
    struct Car *left;
    struct Car *right;
} Car;

void print_race_state(Car *node);
void race_state(int *id, size_t size);
void free_car(Car *node);
Car *newCar(int id);
Car *insertCar(Car *node, int id);


#endif
