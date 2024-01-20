#ifndef FILE_MANIPULATION_INCLUDED
#define FILE_MANIPULATION_INCLUDED
#define MAX_NOTE_CHAR_SIZE 10000
#define MAX_NOTE_AMOUNT 100
#define READ_ONLY 0
#define OVERWRITE 1
#define APPEND 2
#define DELETE 3
#define LOCATION_SIZE_MAX 200

int passwordChecker(int mode);
int createNewNote();
int viewNotes(int mode);
int CheckNoteCount(int mode);
int ifExistsRead(int fileNumber);
int writeNote(char location[], int noteNumber, int mode);
void clear();
#endif