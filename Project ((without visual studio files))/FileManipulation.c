#include "FileManipulation.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>




///
/// FILE SECURITY / UI 
/// 
int passwordChecker(int mode) {
	FILE* passwordPtr;
	int c;
	char password[20], typedPassword[20];
	if (mode == 0) {

		passwordPtr = fopen("Note/Data/password.txt", "r");
		fscanf(passwordPtr, "%s", password);
		fclose(passwordPtr);

		clear();
		printf("\t\t\t\t\tPLEASE ENTER THE PASSWORD!\t\t\t\t\t\n\n\n\t\t\t|The password:");
		scanf("%16s", typedPassword);
		if (strcmp(password, typedPassword) == 0) {
			return 0;
		}
	}
	else if (mode == 1) {
		int c;
		clear();
		printf("PLEASE SET THE PASSWORD! (keep it under 16 characters)\n");
		passwordPtr = fopen("Note/Data/password.txt", "w");
		if (scanf("%16s", password) == 1) {
			fprintf(passwordPtr, "%s", password);
		}
		fclose(passwordPtr);
		return 0;
	}
	return -1;
}

void clear() { // I wanted to use system("cls") but i thought that you Sir wouldn't be using a machine running an OS from "The empire of evil" hehe,so i searched for a more universal approach and found this one on Stack overflow
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#endif
}
///
///
/// 









///
/// FILE HANDLING
/// 

int createNewNote() {
	int c, noteTemplateNumber;
	char location[LOCATION_SIZE_MAX];

	//Create a template for a new Note
	noteTemplateNumber = CheckNoteCount(OVERWRITE);
	snprintf(location, sizeof(location), "Note/Notes/Note%d.txt", noteTemplateNumber); // I asked chatgpt about a function that would create a new file every itteration(with no other context) and it's resolution contained snprintf so i researched about it and decided snsprintf

	writeNote(location, noteTemplateNumber, OVERWRITE);
	return 0;
}


int viewNotes(int mode) {
	clear();
	int c, userPick;

	//while user doesn't quit,display the contents of the given note
	while ((c = getchar()) != EOF) {
		int NoteAmount, swapper;
		char NoteName[LOCATION_SIZE_MAX], NoteNameNew[LOCATION_SIZE_MAX];
		NoteAmount = CheckNoteCount(READ_ONLY);
		printf("List of Available notes:\n");

		//Prints a list of all existing notes
		for (int i = 1; i <= NoteAmount; i++) {
			snprintf(NoteName, sizeof(NoteName), "Note%d.txt\n", i);
			printf(NoteName);
		}
		//Providing the ability to read, if that was the argument that the function was called with
		if (mode == 0) {
			printf("Please enter the Number of the note you want to read: ");
			if (scanf("%3d", &userPick) == 1) {
				ifExistsRead(userPick);
				return 0;
			}
			else {
				clear();
			}
		}
		//Providing the ability to overwrite, if that was the argument that the function was called with
		else if (mode == 1) {
			printf("Please enter the Number of the note you want to overwrite: ");
			if (scanf("%3d", &userPick) == 1) {
				if (userPick <= NoteAmount && userPick > 0) {
					snprintf(NoteName, sizeof(NoteName), "Note/Notes/Note%d.txt", userPick);
					writeNote(NoteName, userPick, OVERWRITE);
					return 0;
				}
				else {
					clear();
				}
			}
			else {
				clear();
			}
		}
		//Providing the ability to append, if that was the argument that the function was called with
		else if (mode == 2) {
			printf("Please enter the Number of the note you want to append to: ");
			if (scanf("%3d", &userPick) == 1) {
				if (userPick <= NoteAmount && userPick>0) {
					snprintf(NoteName, sizeof(NoteName), "Note/Notes/Note%d.txt", userPick);
					writeNote(NoteName, userPick, APPEND);
					return 0;
				}
				else {
					clear();
				}
			}
			else {
				clear();
			}
		}
		//Providing the ability to delete, if that was the argument that the function was called with
		else if (mode == 3) {
			printf("Please enter the Number of the note you want to delete: ");
			if (scanf("%3d", &userPick) == 1) {
				//removes the destined name
				snprintf(NoteName, sizeof(NoteName), "Note/Notes/Note%d.txt", userPick);
				remove(NoteName);

				//updates the indexes of other files to keep the order
				for (int i = userPick; i <= NoteAmount; i++) {
					snprintf(NoteName, sizeof(NoteName), "Note/Notes/Note%d.txt",i+1);
					snprintf(NoteNameNew, sizeof(NoteName), "Note/Notes/Note%d.txt",i);
					rename(NoteName, NoteNameNew);
				}
				CheckNoteCount(DELETE);
				return 0;
			}
			else {
				clear();
			}
		}

	}
	return -1;
}


int CheckNoteCount(int mode) {
	int noteCount;
	FILE* GenericPtr;
	//reads the content
	GenericPtr = fopen("Note/Data/count.txt", "r");
	fscanf(GenericPtr, "%d", &noteCount);
	fclose(GenericPtr);

	//overwrites it with the new value if the right command is received
	if (mode == 1) {
		noteCount++;
		GenericPtr = fopen("Note/Data/count.txt", "w");
		fprintf(GenericPtr, "%d", noteCount);
		fclose(GenericPtr);
	}
	else if (mode == 3) {
		if (noteCount > 0) {
			noteCount--;
			GenericPtr = fopen("Note/Data/count.txt", "w");
			fprintf(GenericPtr, "%d", noteCount);
		}
		fclose(GenericPtr);
	}
	return noteCount;
}


int ifExistsRead(int fileNumber) {
	FILE* ptr;
	char searchedNote[LOCATION_SIZE_MAX];
	int readLetter, c;
	clear();
	snprintf(searchedNote, sizeof(searchedNote), "Note/Notes/Note%d.txt", fileNumber);
	printf("[a-left] \t\t\t\t\t%s\t\t\t\t\t [d-right]\n", searchedNote);
	// Check if a file exists, if yes prints its contents. While user doesn't quit,displays the contents of the given note

	if ((ptr = fopen(searchedNote, "r"))) { // looked up how to check whether a file exists, and i found in my opinion the most errorless and universal solution on stack, to just try to open it and then close it
		while ((readLetter = fgetc(ptr)) != EOF) {
			putchar(readLetter);
		};
		fclose(ptr);

		// lets the user input commands to switch pages using recursion of this programme,if it encounters EOF, it breaks the recursion and returns to interface (Note that if you try to open a file that doesnt exist, the programme will ask you to input EOF twice, once for accepting the fact and once for leaving);
		while ((c = getchar()) != EOF) {
			if (c == 'a') {
				fileNumber--;
				if (ifExistsRead(fileNumber, c) == 0 || ifExistsRead(fileNumber, c) == 1) {
					return 0;
				}
			}
			else if (c == 'd') {
				fileNumber++;
				if (ifExistsRead(fileNumber, c) == 0 || ifExistsRead(fileNumber, c) == 1) {
					return 0;
				}
			}

		}
		
	}
	else {
		printf("\n\n\t\t\t\t\t-------FILE NOT FOUND!-------\t\t\t\t\t\n\n");
		while ((c = getchar()) != EOF) {
			;
		}
		return 1;
	}

	return 0;
}

	int writeNote(char location[], int noteNumber, int mode) {
		int readLetter, c;
		char instruction[3]; // asked chat gpt how could i dynamically change the modes in which i open the files with and it told me that i should use a array and strcpy
		clear();
		if (mode == 1) {
			strcpy(instruction, "w");
		}
		else if (mode == 2) {
			strcpy(instruction, "a+");
		}

		//Allow user to write content/append onto the Note
		FILE* NotePtr;
		printf("Note number %d\n", noteNumber);
		NotePtr = fopen(location, instruction);

		//If the selected mode is APPEND it will print the file contents;
		if (mode == 2) {
			while ((readLetter = fgetc(NotePtr)) != EOF) {
				putchar(readLetter);
			};
		}
		if (NotePtr == NULL) {
			printf("SORRY SOMETHING WENT WRONG! I RECOMMEND CHECKING THE PATH TO NOTEPAD DIRECTORY!");
			exit(EXIT_FAILURE);
		}

		//Gets the char from input and writes it onto the file.
		while ((c = getchar()) != EOF) {
			fputc(c, NotePtr);
		}
		fclose(NotePtr);
		return 0;
	}

///
///
/// 