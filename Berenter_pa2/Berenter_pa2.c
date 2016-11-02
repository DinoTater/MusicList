#include "Berenter_pa2.h"

// Allow user to navigate through the song list
// Include options for load list, save list, display song, insert song, delete song,
// Edit song, sort list and rate a song
int MainMenu (void)
{
	int choice = 0;

	printf ("Please select an option for your music list:\n\n");
	printf ("1.	Load a new song list\n");
	printf ("2.	Display a song\n");
	printf ("3.	Save song list\n");
	printf ("4.	Insert a song\n");
	printf ("5.	Delete a song\n");
	printf ("6.	Edit a song\n");
	printf ("7.	Sort all songs\n");
	printf ("8.	Rate a song\n");
	printf ("9.	Exit\n\n");
	scanf ("%d", &choice);
	return choice;
}

// Run program based on user input
int runProgram (int choice, Record **RecordList)
{
	Record * pMem = NULL;
	char again = '\0';
	int menu = -1;
	FILE * infile = NULL;
	Boolean success = FALSE;
	char songFind[100] = "";

	pMem = (Record *) malloc (sizeof (Record));

	if (choice == 1)
	{
		infile = openFile (0);
		do
		{
			pMem = loadRecord (RecordList, infile);
			insertRecord (RecordList, pMem);
		} while (!feof (infile));

		fclose (infile);
		printf ("\n\nWould you like to upload another file (y/n) ?   ");
		fflush (stdin);
		scanf ("%c", &again);

		if (again == 'y')
		{
			choice = 1;
			runProgram (choice, RecordList);
		}
		else
		{
			menu = 1;
		}
	}
	
	else if (choice == 2)
	{
		printf ("Enter the name of the song you would like to display: ");
		fflush (stdin);
		gets(songFind);
		success = displayRecord (*RecordList, songFind);
		if (!success)
		{
			printf ("This song is not in the list.\n");
		}
		printf ("\n\nWould you like to display the information for another song (y/n) ?   ");
		fflush (stdin);
		scanf ("%c", &again);

		if (again == 'y')
		{
			system ("CLS");
			choice = 2;
			runProgram (choice, RecordList);
		}
		else
		{
			menu = 1;
		}
	}
	
	else if (choice == 3)
	{
		infile = openFile (1);
		storeList (*RecordList, infile);
		menu = 1;
	}
	
	else if (choice == 4)
	{
		if (pMem != NULL)
		{
			pMem = makeRecord();
			insertRecord (RecordList, pMem);
		}
		else
		{
			printf ("Cannot complete command. Please try again.");
		}

		printf ("\n\nWould you like to input another song (y/n) ?   ");
		fflush (stdin);
		scanf ("%c", &again);

		if (again == 'y')
		{
			system ("CLS");
			choice = 4;
			runProgram (choice, RecordList);
		}
		else
		{
			menu = 1;
		}
	}
	
	else if (choice == 5)
	{
		deleteRecord (RecordList);
		printf ("\n\nWould you like to delete another song (y/n) ?   ");
		fflush (stdin);
		scanf ("%c", &again);

		if (again == 'y')
		{
			system ("CLS");
			choice = 5;
			runProgram (choice, RecordList);
		}
		else
		{
			menu = 1;
		}
	}
	
	else if (choice == 6)
	{
		
		printf ("Enter the name of the song you would like to edit: ");
		fflush (stdin);
		gets (songFind);
		editSong (RecordList, songFind);
		printf ("\n\nWould you like to edit another song (y/n) ?   ");
		fflush (stdin);
		scanf ("%c", &again);

		if (again == 'y')
		{
			system ("CLS");
			choice = 6;
			runProgram (choice, RecordList);
		}
		else
		{
			menu = 1;
		}
	}
	
	else if (choice == 7)
	{
		bubbleSort (RecordList);
		menu = 1;
	}
	
	else if (choice == 8)
	{
		rateSong (RecordList);
		printf ("\n\nWould you like to rate another song (y/n) ?   ");
		fflush (stdin);
		scanf ("%c", &again);

		if (again == 'y')
		{
			system ("CLS");
			choice = 8;
			runProgram (choice, RecordList);
		}
		else
		{
			menu = 1;
		}
	}

	else if (choice == 9)
	{
		exitProgram(*RecordList);
	}
	if (menu == 1)
	{
		return;
	}
	return choice;
}

// Open file if user wants to read songs from a file into the list or write song list into a save file
FILE * openFile (int action) // action is 0, read into program, if 1 write from program
{
	FILE *infile = NULL;
	char fileOpen[100];
	
	if (action == 0)
	{
		printf ("What is the name of the file you would like to copy over?  ");
		fflush (stdin);
		scanf ("%s", fileOpen);

		infile = fopen (fileOpen, "r");
	}
	else
	{
		printf ("What is the name of the file you would like to save to?  If the name is in use, the old file will be overwritten.  ");
		fflush (stdin);
		gets (fileOpen);

		infile = fopen (fileOpen, "w");
	}
	return infile;
}

// Create song node for use in any function
Record* makeRecord (void)
{
	Record *pMem = NULL;
	int rate = 0, minutes = 0, seconds = 0;

	// Allocate memory for new song:
	pMem = (Record *) malloc (sizeof(Record));
	pMem->pPrev = NULL;
	pMem->pNext = NULL;

	printf ("Please enter the artist's name: ");
	fflush(stdin);
	gets (pMem -> artist);
	printf ("Please enter the album name: ");
	fflush(stdin);
	gets(pMem -> album);
	printf ("Please enter the song name: ");
	fflush(stdin);
	gets(pMem -> song);
	printf ("Please enter the genre: ");
	fflush(stdin);
	gets(pMem -> genre);
	printf ("Please enter the song length, (mm:ss) : ");
	fflush(stdin);
	scanf ("%d:%d", &minutes, &seconds);
	while (seconds >= 60)
	{
		minutes = 0;
		seconds = 0;
		printf ("Invalid song length.\n");
		printf ("Please enter a valid song length, (mm:ss) : ");
		fflush(stdin);
		scanf ("%d:%d", &minutes, &seconds);
	}
	pMem->length.minutes = minutes;
	pMem->length.seconds = seconds;
	printf ("Please enter the current number of times the song has been played: ");
	fflush(stdin);
	scanf ("%d", &(pMem -> times_played));
	printf ("Please rate the song, 1-5 (otherwise default is zero): ");
	fflush(stdin);
	scanf ("%d", &(pMem->rating));
	if ((pMem->rating != 1) && (pMem->rating != 2) && (pMem->rating != 3) && (pMem->rating != 4) && (pMem->rating != 5))
	{
		pMem->rating = 0;
	}
	
	return pMem;
}

// Check if list is empty
Boolean isEmpty (Record *RecordList)
{
	Boolean state = FALSE; // false means list is not empty

	if (RecordList == NULL) // is list empty?
	{
		state = TRUE;
	}
	return state;
}

// Allow user to view information of any song in the list, searching by song name
Boolean displayRecord (Record *RecordList, char* songFind)
{
	Record *pCur = NULL, *pTemp = NULL;
	Boolean success = FALSE;

	pCur = RecordList;

	while (pCur != NULL && (strcmp(pCur->song, songFind) != 0)) // Search through songs to find correct node
	{
		pCur = pCur->pNext;
	}
	if (pCur != NULL)  // Found correct node
	{
		success = TRUE;
		printf ("\n\nArtist: %s\n\n", pCur -> artist);
		printf ("Album: %s\n\n", pCur -> album);
		printf ("Song: %s\n\n", pCur -> song);
		printf ("Genre: %s\n\n", pCur -> genre);
		printf ("Length: %d:%.2d\n\n", pCur->length.minutes, pCur->length.seconds);
		printf ("Times Played: %d\n\n", pCur -> times_played);
		printf ("Rating: %d\n\n", pCur -> rating);
	}
	return success;
}

// Allow user to input a song into the list, sorted by song name
Boolean insertRecord (Record **RecordList, Record * newRecord)
{
	Record *pMem = NULL, *pCur = NULL, *pPrior = NULL;
	Boolean empty = FALSE;

	//pMem = newRecord;
	empty = isEmpty(*RecordList);

	if (empty) // Empty list
	{
		*RecordList = newRecord;
	}
	else // list is not empty
	{
		pCur = *RecordList; // Start at the beginning of the list
			
		// Find the spot we're looking for
		while((pCur != NULL) && strcmp(newRecord->song, pCur->song) > 0)
		{
			pPrior = pCur;
			pCur = pCur->pNext;
		}

		newRecord->pNext = pCur;
		
		if (pCur == NULL) // at the end of the list
		{
			newRecord->pPrev = pPrior;
			pPrior->pNext = newRecord;
		}

		else if (pPrior != NULL) // Not at the beginning of the list
		{
			newRecord->pPrev = pPrior;
			pPrior->pNext = newRecord;
			pCur->pPrev = newRecord;
		}
		else // Insert at front
		{
			*RecordList = newRecord;
		}
	}
}

// Allow user to input a song list from file into the list, sorted by song name
Record* loadRecord (Record **RecordList, FILE * infile)
{
	Record *pMem = NULL;
	Boolean success = FALSE, isBlank = TRUE;
	char colon[1];
	int check = 0;

	pMem = (Record *) malloc (sizeof(Record));
	pMem->pPrev = NULL;
	pMem->pNext = NULL;

	fflush (stdin);
	fgets (pMem->artist, 100, infile);
	//check = strlen (pMem->artist) - 1;
	(pMem->artist)[strlen(pMem->artist) - 1] = '\0';
	fflush (stdin);
	//fscanf (infile, "%s ", (pMem->album));
	fgets (pMem->album, 100, infile);
	(pMem->album)[strlen(pMem->album) - 1] = '\0';
	fflush (stdin);
	//fscanf (infile, "%s ", (pMem->song));
	fgets (pMem->song, 100, infile);
	(pMem->song)[strlen(pMem->song) - 1] = '\0';
	fflush (stdin);
	//fscanf (infile, "%s ", (pMem->genre));
	fgets (pMem->genre, 100, infile);
	(pMem->genre)[strlen(pMem->genre) - 1] = '\0';
	fflush (stdin);
	fscanf (infile, "%d", &(pMem->length.minutes));
	fflush (stdin);
	fscanf(infile, "%c", &colon);
	fflush (stdin);
	fscanf (infile, "%d", &(pMem->length.seconds));
	fflush (stdin);
	fscanf (infile, "%d", &(pMem->times_played));
	fflush (stdin);
	fscanf (infile, "%d ", &(pMem->rating));
	fflush (stdin);
	if ((pMem->rating != 1) && (pMem->rating != 2) && (pMem->rating != 3) && (pMem->rating != 4) && (pMem->rating != 5))
	{
		pMem->rating = 0;
	}

	//insertRecord (RecordList, pMem);
	//pMem = NULL;
	/*pMem->pPrev = NULL;
	pMem->pNext = NULL;*/

	
	
	return pMem;
}

// Allow user to delete a song from the list
Boolean deleteRecord (Record **RecordList) // Delete by song title; if two, deletes first
{
	Record *pCur = NULL, *pPrior = NULL, *pSucc = NULL;
	char deletedSong[MAX_LENGTH];
	Boolean empty = FALSE, success = FALSE;

	empty = isEmpty (*RecordList);

	if (empty)
	{
		printf ("List is empty, nothing to delete.");
		return success;
	}
	if (!empty)
	{
		printf ("Enter the name of the song you would like to delete: ");
		fflush (stdin);
		gets (deletedSong);

		pCur = *RecordList;

		while ((pCur != NULL) && (strcmp(pCur->song, deletedSong) != 0)) // Search through songs to find correct node
		{
			pPrior = pCur;
			pCur = pCur->pNext;
		}
		if (pCur != NULL) // Found what we were looking for
		{
			pSucc = pCur->pNext;
			if (pSucc == NULL) // End of the list
			{
				pPrior->pNext = NULL;
			}
			else if (pPrior != NULL) // Not first node
			{
				pPrior->pNext = pSucc;
				pSucc->pPrev = pPrior;
			}
			else // Delete first node
			{
				*RecordList = pCur->pNext;
			}

			free (pCur); // deallocate memory from correct node
		}
	}
	return success;
}

// Sort song based on user's choice
void bubbleSort (Record **RecordList)
{
	Record *pCur = NULL, *pTemp = NULL, *pPrior = NULL, *pSucc = NULL;
	int choice = 0, count = 0, passes = 0, start = 0;

	pTemp = (Record *) malloc (sizeof(Record));

	system ("CLS");
	printf ("Options to sort the music list:\n\n");
	printf ("1.	Alphabetically by artist\n");
	printf ("2.	Alphabetically by album\n");
	printf ("3.	Alphabetically by song\n");
	printf ("4.	Alphabetically by genre\n");
	printf ("5.	Numerically by times played (High to Low)\n");
	printf ("6.	Numerically by rating\n");
	printf ("Enter a choice: ");
	scanf ("%d", &choice);
	
	pCur = *RecordList;

	while (pCur != NULL)
	{
		pCur = pCur->pNext;
		count++;
	}
	pCur = *RecordList;

	while (passes < count)
	{
		start = 0;
		pCur = *RecordList; // concern
		pPrior = NULL;
		
		if (start == 0)
		{
			pPrior = pCur;
			pCur = pCur->pNext;
		}
	
		while (pCur != NULL)
		{
			if (choice == 1)
			{
				if (strcmp ((pCur->artist), (pPrior->artist)) < 0)
				{
					strcpy (pTemp->artist, pCur->artist);
					strcpy (pTemp->album, pCur->album);
					strcpy (pTemp->song, pCur->song);
					strcpy (pTemp->genre, pCur->genre);
					pTemp->length = pCur->length;
					pTemp->rating = pCur->rating;
					pTemp->times_played = pCur->times_played;
					
					strcpy (pCur->artist, pPrior->artist);
					strcpy (pCur->album, pPrior->album);
					strcpy (pCur->song, pPrior->song);
					strcpy (pCur->genre, pPrior->genre);
					pCur->length = pPrior->length;
					pCur->rating = pPrior->rating;
					pCur->times_played = pPrior->times_played;

					strcpy (pPrior->artist, pTemp->artist);
					strcpy (pPrior->album, pTemp->album);
					strcpy (pPrior->song, pTemp->song);
					strcpy (pPrior->genre, pTemp->genre);
					pPrior->length = pTemp->length;
					pPrior->rating = pTemp->rating;
					pPrior->times_played = pTemp->times_played;
				}
			}

			else if (choice == 2)
			{
				if (strcmp ((pCur->album), (pPrior->album)) < 0)
				{
					strcpy (pTemp->artist, pCur->artist);
					strcpy (pTemp->album, pCur->album);
					strcpy (pTemp->song, pCur->song);
					strcpy (pTemp->genre, pCur->genre);
					pTemp->length = pCur->length;
					pTemp->rating = pCur->rating;
					pTemp->times_played = pCur->times_played;
					
					strcpy (pCur->artist, pPrior->artist);
					strcpy (pCur->album, pPrior->album);
					strcpy (pCur->song, pPrior->song);
					strcpy (pCur->genre, pPrior->genre);
					pCur->length = pPrior->length;
					pCur->rating = pPrior->rating;
					pCur->times_played = pPrior->times_played;

					strcpy (pPrior->artist, pTemp->artist);
					strcpy (pPrior->album, pTemp->album);
					strcpy (pPrior->song, pTemp->song);
					strcpy (pPrior->genre, pTemp->genre);
					pPrior->length = pTemp->length;
					pPrior->rating = pTemp->rating;
					pPrior->times_played = pTemp->times_played;
				}
			}

			else if (choice == 3)
			{
				if (strcmp ((pCur->song), (pPrior->song)) < 0)
				{
					strcpy (pTemp->artist, pCur->artist);
					strcpy (pTemp->album, pCur->album);
					strcpy (pTemp->song, pCur->song);
					strcpy (pTemp->genre, pCur->genre);
					pTemp->length = pCur->length;
					pTemp->rating = pCur->rating;
					pTemp->times_played = pCur->times_played;
					
					strcpy (pCur->artist, pPrior->artist);
					strcpy (pCur->album, pPrior->album);
					strcpy (pCur->song, pPrior->song);
					strcpy (pCur->genre, pPrior->genre);
					pCur->length = pPrior->length;
					pCur->rating = pPrior->rating;
					pCur->times_played = pPrior->times_played;

					strcpy (pPrior->artist, pTemp->artist);
					strcpy (pPrior->album, pTemp->album);
					strcpy (pPrior->song, pTemp->song);
					strcpy (pPrior->genre, pTemp->genre);
					pPrior->length = pTemp->length;
					pPrior->rating = pTemp->rating;
					pPrior->times_played = pTemp->times_played;
				}
			}

			else if (choice == 4)
			{
				if (strcmp ((pCur->genre), (pPrior->genre)) < 0)
				{
					strcpy (pTemp->artist, pCur->artist);
					strcpy (pTemp->album, pCur->album);
					strcpy (pTemp->song, pCur->song);
					strcpy (pTemp->genre, pCur->genre);
					pTemp->length = pCur->length;
					pTemp->rating = pCur->rating;
					pTemp->times_played = pCur->times_played;
					
					strcpy (pCur->artist, pPrior->artist);
					strcpy (pCur->album, pPrior->album);
					strcpy (pCur->song, pPrior->song);
					strcpy (pCur->genre, pPrior->genre);
					pCur->length = pPrior->length;
					pCur->rating = pPrior->rating;
					pCur->times_played = pPrior->times_played;

					strcpy (pPrior->artist, pTemp->artist);
					strcpy (pPrior->album, pTemp->album);
					strcpy (pPrior->song, pTemp->song);
					strcpy (pPrior->genre, pTemp->genre);
					pPrior->length = pTemp->length;
					pPrior->rating = pTemp->rating;
					pPrior->times_played = pTemp->times_played;
				}
			}

			else if (choice == 5)
			{
				if ((pCur->times_played) < (pPrior->times_played))
				{
					strcpy (pTemp->artist, pCur->artist);
					strcpy (pTemp->album, pCur->album);
					strcpy (pTemp->song, pCur->song);
					strcpy (pTemp->genre, pCur->genre);
					pTemp->length = pCur->length;
					pTemp->rating = pCur->rating;
					pTemp->times_played = pCur->times_played;
					
					strcpy (pCur->artist, pPrior->artist);
					strcpy (pCur->album, pPrior->album);
					strcpy (pCur->song, pPrior->song);
					strcpy (pCur->genre, pPrior->genre);
					pCur->length = pPrior->length;
					pCur->rating = pPrior->rating;
					pCur->times_played = pPrior->times_played;

					strcpy (pPrior->artist, pTemp->artist);
					strcpy (pPrior->album, pTemp->album);
					strcpy (pPrior->song, pTemp->song);
					strcpy (pPrior->genre, pTemp->genre);
					pPrior->length = pTemp->length;
					pPrior->rating = pTemp->rating;
					pPrior->times_played = pTemp->times_played;
				}
			}
			else if (choice == 6)
			{
				if ((pCur->rating) < (pPrior->rating))
				{
					strcpy (pTemp->artist, pCur->artist);
					strcpy (pTemp->album, pCur->album);
					strcpy (pTemp->song, pCur->song);
					strcpy (pTemp->genre, pCur->genre);
					pTemp->length = pCur->length;
					pTemp->rating = pCur->rating;
					pTemp->times_played = pCur->times_played;
					
					strcpy (pCur->artist, pPrior->artist);
					strcpy (pCur->album, pPrior->album);
					strcpy (pCur->song, pPrior->song);
					strcpy (pCur->genre, pPrior->genre);
					pCur->length = pPrior->length;
					pCur->rating = pPrior->rating;
					pCur->times_played = pPrior->times_played;

					strcpy (pPrior->artist, pTemp->artist);
					strcpy (pPrior->album, pTemp->album);
					strcpy (pPrior->song, pTemp->song);
					strcpy (pPrior->genre, pTemp->genre);
					pPrior->length = pTemp->length;
					pPrior->rating = pTemp->rating;
					pPrior->times_played = pTemp->times_played;
				}
			}
			
			pPrior = pCur;
			pCur = pCur->pNext;

			start++;
		}

		pCur = *RecordList;
		passes++;
	}

	count = 1;
	system ("CLS");
	printf ("The music list is now in the following order:\n\n");
	while (pCur != NULL)
	{
		printf ("%d.	%s\n", count, pCur->song);
		pCur = pCur->pNext;
		count++;
	}
	putchar ('\n');
	system ("Pause");
}

// Allow user to rate a song
void rateSong (Record **RecordList)
{
	char songName[MAX_LENGTH] = "";
	Record *pCur = NULL;

	pCur = *RecordList;

	printf ("Enter the name of the song you would like to rate: ");
	fflush (stdin);
	gets (songName);

	// Go through list to find the song:
	while (pCur != NULL && (strcmp(pCur->song, songName) != 0))
	{
		pCur = pCur->pNext;
	}
	
	if (pCur == NULL) // not in the list
	{
		printf ("The song is not in the list.\n");
	}
	else
	{
		printf ("The current rating for %s is %d.\n\n", pCur->song, pCur->rating);
	}

	if (pCur!= NULL) // Found the right song, now rate it!
	{
		printf ("Enter the rating (1-5) for '%s': ", songName);
		fflush(stdin);
		scanf ("%d", &(pCur->rating));
		while ((pCur->rating != 1) && (pCur->rating != 2) && (pCur->rating != 3) && (pCur->rating != 4) && (pCur->rating != 5))
		{
			printf ("Invalid rating.\n");
			printf ("Please enter a valid rating (1-5) : ");
			fflush(stdin);
			scanf ("%d", &(pCur->rating));
		}
	}

	system ("CLS");
	printf ("The new information for %s:\n", songName);
	displayRecord (*RecordList, songName);

}

// Edit song: edit any part of the song. Once edited, ask if user wants to edit another part of that song
// Ask if user wants to edit another song
void editSong (Record **RecordList, char *songName)
{
	char again = '\0';
	int edit = 0;
	Record *pCur = NULL;

	pCur = *RecordList;

	system ("CLS");

	// Go through list to find the song:
	while (pCur != NULL && (strcmp(pCur->song, songName) != 0))
	{
		pCur = pCur->pNext;
	}

	if (pCur == NULL) // not in the list
	{
		printf ("The song is not in the list.\n");
	}

	if (pCur!= NULL) // Found the right song, now edit it!
	{
		printf ("The current information for %s is:\n", songName);
		displayRecord (*RecordList, songName);
		printf ("What would you like to edit?\n"); // artist, album, song, genre, length, times played, rating
		printf ("1.	Artist\n");
		printf ("2.	Album\n");
		printf ("3.	Song Title\n");
		printf ("4.	Genre\n");
		printf ("5.	Song Length\n");
		printf ("6.	Times Played\n");
		printf ("7.	Rating\n");
		printf ("Enter the number of which information you would like to edit?  ");
		fflush (stdin);
		scanf ("%d", &edit);

		if (edit == 1)
		{
			printf ("Enter the artist name: ");
			fflush (stdin);
			gets(pCur->artist);
		}
		else if (edit == 2)
		{
			printf ("Enter the album name: ");
			fflush (stdin);
			gets(pCur->album);
		}
		else if (edit == 3)
		{
			printf ("Enter the song name: ");
			fflush (stdin);
			gets(pCur->song);
			songName = pCur->song;
		}
		else if (edit == 4)
		{
			printf ("Enter the genre: ");
			fflush (stdin);
			gets(pCur->genre);
		}
		else if (edit == 5)
		{
			printf ("Enter the song length (mm:ss): ");
			fflush (stdin);
			scanf ("%d:%d", &pCur->length.minutes, &pCur->length.seconds);
		}
		else if (edit == 6)
		{
			printf ("Enter the number of times played: ");
			fflush (stdin);
			scanf ("%d", &(pCur->times_played));
		}
		else if (edit == 7)
		{
			printf ("Enter the new song rating (1-5): ");
			fflush (stdin);
			scanf ("%d", &(pCur->rating));
		}

		system ("CLS");
		printf ("The new information for %s:\n", songName);
		displayRecord (*RecordList, songName);
		printf ("\n\nWould you like to edit another part of this song (y/n) ?  ");
		fflush (stdin);
		scanf ("%c", &again);
		if (again == 'y')
		{
			system ("CLS");
			editSong (RecordList, songName);
		}
	}

}

// Store list: save list to a file
void storeList (Record *RecordList, FILE * infile)
{
	Record * printedRecord = NULL;

	printedRecord = RecordList;

	if (RecordList == NULL) // list is empty
	{
		printf ("Your music list is empty. A blank file has been created for future use.\n\n");
		fclose (infile);
	}

	else
	{
		do
		{
			fprintf (infile, "%s\n", printedRecord->artist);
			fprintf (infile, "%s\n", printedRecord ->album);
			fprintf (infile, "%s\n", printedRecord ->song);
			fprintf (infile, "%s\n", printedRecord ->genre);
			fprintf (infile, "%d:%02d\n", printedRecord ->length.minutes, printedRecord->length.seconds);
			fprintf (infile, "%d\n", printedRecord ->times_played);
			fprintf (infile, "%d\n\n", printedRecord ->rating);
			printedRecord = printedRecord -> pNext;
		} while (printedRecord != NULL);

		fclose (infile);	
	}
}

// Exit program. Give user the option to save current list to file
void exitProgram (Record *RecordList)
{
	FILE * infile = NULL;
	char again = '\0';

	printf ("Would you like to save your list to a file (y/n) ?  ");
	fflush (stdin);
	scanf ("%c", &again);
	if (again == 'y')
	{
		system ("CLS");
		infile = openFile (1);
		storeList (RecordList, infile);
	}
}