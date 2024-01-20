#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "FileManipulation.h"


//Function Prototypes(asked chat gpt whether i should also those present in the header file)
int interface();
void redirector(int* controler);
void editSubMenu();

int main() {
	int controler;
	controler = 7;
	if (passwordChecker(READ_ONLY) == 0) {
		while (controler != 0 && controler != -1) {
			clear();
			controler = interface();
			redirector(controler);
		}
		if (controler == 0) {
			return 0;
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

//User interface
int interface() {
	int choice;
	printf("\t\t\t\tLECTURE NOTE PRO - TERMINAL EDITION\t\t\t\t\n");
	printf("\t\t\t\t ----------------------------------\t\t\t\t\n\n");
	printf("\t\tHello! How was your day? here are your options\t\t\t\t\n\n");
	printf("\t\t-WRITE A NEW NOTE [1]\n\n");
	printf("\t\t-READ NOTES [2]\n\n");
	printf("\t\t-EDIT NOTES [3]\n\n");
	printf("\t\t-VIEW SPECIFIC NOTE [4]\n\n");
	printf("\t\t-DELETE SPECIFIC NOTE [5]\n\n");
	printf("\t\t-CHANGE PASSWORD [6]\n\n");
	printf("\t\t-EXIT [0]\n\n");
	printf("\t\t-ENTER YOUR CHOICE:");
	
	if (scanf("%d", &choice) == 1 && choice < 7 && choice >= 0) {
		return choice;
	}

	else {
		printf("\n\t\t-------WRONG INPUT-------\n");
	}
	return -1;
}



void redirector(int* controler) {
	//Directs the user to his destination
	if (controler == 1) {
			createNewNote();
	}
	if (controler == 2) {
			ifExistsRead(1);
	}
	if (controler == 3) {
			editSubMenu();
	}
	if (controler == 4) {
			viewNotes(READ_ONLY);
	}
	if (controler == 5) {
			viewNotes(DELETE);
	}
	if (controler == 6) {
		passwordChecker(OVERWRITE);
	}
}





void editSubMenu() {
	clear();
	int choice;
	printf("\n\t\t\t\t[OPTIONS]\t\t\t\t\n\n\t\t\t\t------------\n\n");
	printf("\t\t\t\t-OVERWRITE [1]\t\t\t\t\n");
	printf("\t\t\t\t-APPEND [2]\t\t\t\t\n\n");
	printf("\t\t\t\t-ENTER YOUR CHOICE:");
	if (scanf("%d", &choice) == 1) {
		if (choice == 1) {
			viewNotes(OVERWRITE);
		}
		if (choice == 2) {
			viewNotes(APPEND);
		}
	}

}

	











