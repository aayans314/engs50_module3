/* 
 * list_test2.c --- this tests putting items to non-empty list, applying functions to non empty lists, and all variations of remove() in non-empty lists
 * 
 * Author: Aayan Shah
 * Created: 10-01-2026
 * Version: 1.0
 * 
 * Description: as explained
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
	car_t *cp = make_car("ABC123", 20000.0, 2015);
	car_t *cp2 = make_car("XYZ987", 50000.0, 2026);

	lput(cp);
	
	if (lput(cp2) != 0) {
		printf("lput failed on a non-empty list\n");
		free(cp);
		free(cp2);
		exit(EXIT_FAILURE);
	}

	lapply(doublePrice);
	
	if (cp->price != 40000.0 && cp2->price != 100000.0) {
		printf("lapply did not function\n");
		free(cp);
		free(cp2);
		exit(EXIT_FAILURE);
	}

	car_t *cp3 = make_car("DIU654", 30000.0, 2020);
	car_t *cp4 = make_car("DPO456", 40000.0, 2021);
	car_t *cp5= make_car("UID689", 60000.0, 2022);
	car_t *cp6 = make_car("KUM504", 10000.0, 2023);

	lput(cp3);
	lput(cp4);
	lput(cp5);
	lput(cp6);

	if (lremove("KUM5040") != cp6) {
		printf("couldn't remove from start\n");
		free(cp);
		free(cp2);
		free(cp3);
		free(cp4);
		free(cp5);
		free(cp6);
		exit(EXIT_FAILURE);
	}

	if(lremove("ABC123")!=cp){
		printf("couldn't remove from end\n");
		free(cp);
		free(cp2);
		free(cp3);
		free(cp4);
		free(cp5);
		free(cp6);
		exit(EXIT_FAILURE);
	}

	if (lremove("DPO456")!=cp4){
		printf("couldn't remove from middle\n");
		free(cp);
		free(cp2);
		free(cp3);
		free(cp4);
		free(cp5);
		free(cp6);
		exit(EXIT_FAILURE);
	}


	free(cp);
	free(cp2);
	free(cp3);
	free(cp4);
	free(cp5);
	free(cp6);
	
	exit(EXIT_SUCCESS);
}

