/* 
 * list_test3.c --- this tests putting items to non-empty list, applying functions and removing from empty lists
 * 
 * Author: Aayan Shah
 * Created: 10-01-2026
 * Version: 1.0
 * 
 * Description: as described
 * 
 */

#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* make_car(): allocate and fill in a car; returns NULL if malloc fails */
static car_t *make_car(char *plate, double price, int year) {
	car_t *cp = malloc(sizeof(car_t));

	if (cp != NULL) {
		cp->next = NULL;
		strncpy(cp->plate, plate, MAXREG - 1);
		cp->plate[MAXREG - 1] = '\0';
		cp->price = price;
		cp->year = year;
	}
	return cp;
}

void doublePrice(car_t *car){
	if (car != NULL){
		car->price = car->price * 2;
	}
	
}


int main(void) {
	if(lapply(doublePrice) == NULL){
        printf("Error applying function to empty list");
        exit(EXIT_FAILURE);
    }

    if(lremove("ABC123")!=NULL){
        printf("Error removing from empty list");
        exit(EXIT_FAILURE);
    }

	exit(EXIT_SUCCESS);
}

