#include "laps.h"

/* static variable for the binary search tree*/

static Car *root = NULL;

/**
 * newCar - creates a new car
 * @id: id of the car
 */

Car *newCar(int id)
{
	Car *car = malloc(sizeof(Car));
    car->id = id;
    car->laps = 0;
    car->left = NULL;
    car->right = NULL;
    return car;
}

/**
 * insertCar - inserts car into the race
 * @node: node
 * @id: id of the car
 */

Car *insertCar(Car *node, int id)
{
	if (node == NULL) {
		printf("Car %d has joined the race\n", id);
        node = newCar(id);
        return node;
    }

    if (id < node->id) {
        node->left = insertCar(node->left, id);
    } else if (id > node->id) {
        node->right = insertCar(node->right, id);
    } else {
        node->laps++;
    }

    return node;
}

/**
 * print_race_state - prints the state of the race sorted by car id's
 * @node: node
 */

void print_race_state(Car *node)
{
	if (node != NULL) {
        print_race_state(node->left);
        printf("Car %d [%d laps]\n", node->id, node->laps);
        print_race_state(node->right);
    }
}

/**
 * freeCar - will free memory
 * @node: node
 */

void free_car(Car *node)
{
	if (node != NULL) {
        free_car(node->left);
        free_car(node->right);
        free(node);
    }
}

/**
 * race_state - keeps track of the number of laps made by cars in a race
 * @id: represents the identifier of each car
 * @size: size of the array
 * Return: # of laps car 'x' has made
 */

void race_state(int *id, size_t size)
{
	if (size == 0) {
		free_car(root);
		root = NULL;
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		int car_id = id[i];
		Car *new_car = insertCar(root, car_id);
		root = new_car;
	}

	printf("Race state:\n");
	print_race_state(root);
}
