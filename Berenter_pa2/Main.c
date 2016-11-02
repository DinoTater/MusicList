#include "Berenter_pa2.h"
#include "Testers.h"

int main (void)
{
	Record *RecordList = NULL;
	int choice = 0;

	
	
	do
	{
		choice = MainMenu();
		system ("CLS");
		runProgram(choice, &RecordList);
		system ("CLS");
	} while (choice != 9);
	


	return 0;
}
