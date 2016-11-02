#include "Testers.h"

void testMakeRecord (void)
{
	Record *newRecord = NULL;

	newRecord = makeRecord ();

	printf ("Artist: %s\n\n", newRecord -> artist);
	printf ("album: %s\n\n", newRecord -> album);
	printf ("song: %s\n\n", newRecord -> song);
	printf ("genre: %s\n\n", newRecord -> genre);
	printf ("length: %d:%d\n\n", newRecord->length.minutes, newRecord->length.seconds);
	printf ("Rating: %d\n\n", newRecord -> rating);
}
void testDisplay (void)
{
	Record *newRecord = NULL;
	Record *recordList [100] = {NULL};
	Boolean success = FALSE;

	newRecord = makeRecord ();
	recordList[0] = newRecord;
//	success = displayRecord (recordList[0]);

	if (!success)
	{
		printf ("Failure\n");
	}
}

void testLoadRecord (void)
{

}

Record* testInsertRecord (void)
{
	Record *newRecord = NULL;
	Record *pMem = NULL;

	pMem = (Record *) malloc (sizeof (Record));

	pMem = makeRecord();
	insertRecord (&newRecord, pMem);
	pMem = makeRecord();
	insertRecord (&newRecord, pMem);
	pMem = makeRecord();
	insertRecord (&newRecord, pMem);
	pMem = makeRecord();
	insertRecord (&newRecord, pMem);
	
	while (newRecord != NULL)
	{
		printf ("--> %s ", newRecord ->song);
		newRecord = newRecord -> pNext;
	}

	printf ("--> NULL\n");
	return newRecord;
}

void testDeleteRecord (void)
{
	Record *newRecord = NULL;
	newRecord = testInsertRecord();

	deleteRecord (&newRecord);

	while (newRecord != NULL)
	{
		printf ("--> %s ", newRecord ->song);
		newRecord = newRecord -> pNext;
	}

	printf ("--> NULL\n");
}

void testDisplayRecord (void)
{

}

void testSortList (Record *pStart)
{
	Record *newRecord = NULL, *pMem = NULL, *pMem2 = NULL, *pMem3 = NULL, *pMem4 = NULL, *pMem5 = NULL;

	pMem = makeRecord();
	pMem2 = makeRecord();
	pMem3 = makeRecord();

	
	insertRecord (&newRecord, pMem);
	insertRecord (&newRecord, pMem2);
	insertRecord (&newRecord, pMem3);
	pMem5 = newRecord;
	
	bubbleSort (&newRecord);
	while (newRecord != NULL)
	{
		printf ("--> %s, %s ", newRecord ->song, newRecord->artist);
		newRecord = newRecord -> pNext;
	}
	printf ("--> NULL\n");
	newRecord = pMem5;
	bubbleSort (&newRecord);
	while (newRecord != NULL)
	{
		printf ("--> %s, %s ", newRecord ->song, newRecord->artist);
		newRecord = newRecord -> pNext;
	}
	printf ("--> NULL\n");
	newRecord = pMem5;
	bubbleSort (&newRecord);
	while (newRecord != NULL)
	{
		printf ("--> %s, %s ", newRecord ->song, newRecord->artist);
		newRecord = newRecord -> pNext;
	}
	printf ("--> NULL\n");
	
	/*
	printf ("\n");
	sortList (&newRecord, pStart);
	while (pMem5 != NULL)
	{
		printf ("--> %s ", newRecord ->song);
		newRecord = newRecord -> pNext;
	}

	printf ("\n");
	sortList (&newRecord, pStart);
	while (pMem5 != NULL)
	{
		printf ("--> %s ", newRecord ->song);
		newRecord = newRecord -> pNext;
	}

	printf ("\n");
	sortList (&newRecord, pStart);
	while (pMem5 != NULL)
	{
		printf ("--> %s ", newRecord ->song);
		newRecord = newRecord -> pNext;
	}
	*/
}

void testRateSong (void)
{

}

void testEditSong (void)
{

}