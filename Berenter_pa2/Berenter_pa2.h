#ifndef BERENTER_PA2_H
#define BERENTER_PA2_H

/****************************************************************************
* Programmer: Adam Berenter																									*
* Class: CptS 122, Summer 2015; Lab Section 1																		*
* Programming Assignment: #2																								*
* Date: June 23, 2015																													*
* Description: This program	provides organization for a music list								*
* - including loading previously made list, saving list, 														*
* - display record, insert record, delete record, edit record, sort list,								*
* - rate songs, and save as it exits																							*
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct songLength
{
	int minutes;
	int seconds;
} SongLength;

typedef struct record
{
	char artist [MAX_LENGTH];
	char album [MAX_LENGTH];
	char song [MAX_LENGTH];
	char genre [MAX_LENGTH];
	SongLength length;
	int times_played;
	int rating;
	struct record *pPrev;
	struct record *pNext;
} Record;

typedef enum boolean
{
	FALSE, TRUE
} Boolean;

int MainMenu (void);
int runProgram (int choice, Record **RecordList);
FILE * openFile (int action);
Record* makeRecord (void);
Boolean isEmpty (Record *RecordList);
Record* loadRecord (Record **RecordList, FILE * infile);
Boolean insertRecord (Record **RecordList, Record * newRecord);
Boolean deleteRecord (Record **RecordList);
Boolean displayRecord (Record *RecordList, char* songFind);
void bubbleSort (Record **RecordList);
void rateSong (Record **RecordList);
void editSong (Record **RecordList, char *songName);
void storeList (Record *RecordList, FILE * infile);
void exitProgram (Record *RecordList);

#endif