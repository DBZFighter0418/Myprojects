/*
* This program allows display and editing of text art (also called ASCII art).
*/

#include <iostream>
#include <fstream>
#include <cctype>
#include <windows.h>
#include <conio.h>
#include "Definitions.h"
using namespace std;


int main()
{
	char choice, canvas[MAXROWS][MAXCOLS], Copycanvas[MAXROWS][MAXCOLS];
	char menu[] = "<E>dit / <M>ove / <R>eplace / <D>raw / <C>lear / <U>ndo / <L>oad / <S>ave / <Q>uit: ";
	bool Animate = false;
	int menulength = strlen(menu) + 20;

	initCanvas(canvas);
	copyCanvas(Copycanvas, canvas);
	do
	{

		displayCanvas(canvas);

		cout << menu;

		// Get the numeric entry from the menu lowercase or uppercase.
		cin >> choice;
		choice = (char)toupper(choice);
		// Makes the 'enter' key that was pressed after the numeric entry be ignored.
		// Should be used after getting any numeric input from the keyboard.
		cin.ignore();

		clearLine(MAXROWS + 1, menulength);

		switch (choice)
		{
		case 'D':
			copyCanvas(Copycanvas, canvas);
			menuTwo(canvas, Copycanvas, Animate);
			break;
		case 'C':
			copyCanvas(Copycanvas, canvas);
			initCanvas(canvas);
			break;
		case 'E':
			copyCanvas(Copycanvas, canvas);
			cout << "Press ESC to leave Edit";
			editCanvas(canvas);
			break;
		case 'M':
			copyCanvas(Copycanvas, canvas);
			int Row;
			int Col;
			cout << "How many columns do you want to move left(-) or right(+)?(use interger only) ";
			cin >> Col;
			cin.ignore();
			cout << "How many rows do you want to move up(-) or down(+)?(use interger only)  ";
			cin >> Row;
			cin.ignore();
			moveCanvas(canvas, Row, Col);
			break;
		case 'R':
			copyCanvas(Copycanvas, canvas);
			char oldc;
			char newc;
			cout << "What character would you like to replace? ";
			cin.get(oldc);
			cin.ignore();
			cout << "What would you like to replace the selected character with? ";
			cin.get(newc);
			cin.ignore();
			replace(canvas, oldc, newc);
			break;
		case 'U':
			copyCanvas(canvas, Copycanvas);
			break;
		case 'L':
			loadCanvas(canvas);
			break;
		case 'S':
			saveCanvas(canvas);
			break;
		}
		// Clears canvas of specified lines.
		clearLine(MAXROWS + 1, menulength);
		clearLine(MAXROWS + 2, menulength);
		clearLine(MAXROWS + 3, menulength);
	} while (choice != 'Q');

	return 0;
}


void gotoxy(short row, short col)
{
	// Allows user to move cursor.
	COORD pos = { col, row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void clearLine(int lineNum, int numOfChars)
{
	// Move cursor to the beginning of the specified line on the console.
	gotoxy(lineNum, 0);

	// Write a specified number of spaces to overwrite characters.
	for (int x = 0; x < numOfChars; x++)
		cout << " ";

	// Move cursor back to the beginning of the line.
	gotoxy(lineNum, 0);
}


void replace(char canvas[][MAXCOLS], char oldCh, char newCh)
{
	// Causes all occurrences of a specified character to be replaced by some other character.
	for (int i = 0; i < MAXROWS; i++)
	{
		for (int y = 0; y < MAXCOLS; y++)
		{
			if (canvas[i][y] == oldCh)
			{
				canvas[i][y] = newCh;
			}

		}
	}
}


void editCanvas(char canvas[][MAXCOLS])
{
	char input;
	int row = 0, col = 0;

	// Move cursor to row,col and then get a single character from the keyboard.
	gotoxy(row, col);
	input = _getch();

	while (input != ESC)
	{
		// 'if' statement moves the selected position if the user inputs an arrow key.
		if (input == SPECIAL)
		{
			input = _getch();

			switch (input)
			{
			case LEFTARROW:
				if (col > 0)
				{
					col--;
				}
				break;
			case RIGHTARROW:
				if (col < MAXCOLS - 1)
				{
					col++;
				}
				break;
			case UPARROW:
				if (row > 0)
				{
					row--;
				}
				break;
			case DOWNARROW:
				if (row < MAXROWS - 1)
				{
					row++;
				}
				break;
			}
		}
		// If a key was a special condition.
		else if (input == '\0')
		{
			input = _getch();
		}
		// Prints a letter in the Position of the cursor.
		else if (32 <= input && input <= 126)
		{
			canvas[row][col] = input;
			printf("%c", input);
		}

		gotoxy(row, col);
		input = _getch();
	}

}


void moveCanvas(char canvas[][MAXCOLS], int rowValue, int colValue)
{
	// Shifts all contents of the canvas in a new direction.
	char NewCanvas[MAXROWS][MAXCOLS];
	initCanvas(NewCanvas);

	for (int i = 0; i < MAXROWS; i++)
	{
		for (int y = 0; y < MAXCOLS; y++)
		{
			// If the row and columns are between the canvas space it will set the new canvas in the correct position.
			if (i + (rowValue) < MAXROWS && y + (colValue) > -1 && i + (rowValue) > -1 && y + (colValue) < MAXCOLS)
			{
				NewCanvas[i + rowValue][y + colValue] = canvas[i][y];
			}

		}

	}
	// Saves a copy of the canvas.
	copyCanvas(canvas, NewCanvas);
}


void initCanvas(char canvas[][MAXCOLS])
{
	// Initiate the blank canvas.
	for (int i = 0; i < MAXROWS; i++)
	{
		for (int y = 0; y < MAXCOLS; y++)
		{
			canvas[i][y] = ' ';
		}
	}

}


void displayCanvas(char canvas[][MAXCOLS])
{
	// Starts the display at the beginning position of the terminal.
	gotoxy(0, 0);

	// Displays the contents of canvas.
	for (int i = 0; i < MAXROWS; i++)
	{
		for (int y = 0; y < MAXCOLS; y++)
		{
			printf("%c", canvas[i][y]);
		}
		printf("|\n");
	}


	for (int y = 0; y < MAXCOLS; y++)
	{
		printf("-");
	}
	printf("\n");
}

void copyCanvas(char to[][MAXCOLS], char from[][MAXCOLS])
{
	// copy(from, to);
	for (int r = 0; r < MAXROWS; ++r)
	{
		for (int c = 0; c < MAXCOLS; ++c)
		{
			to[r][c] = from[r][c];
		}
	}
}

void saveCanvas(char canvas[][MAXCOLS])
{
	// Saves the copy of canvas with users filename input.
	char fileName[FILENAMESIZE];
	char filepath[FILENAMESIZE];

	cout << "Enter the filename (don't enter 'txt'): ";
	cin.getline(fileName, FILENAMESIZE - 15);

	snprintf(filepath, FILENAMESIZE, "SavedFiles\\%s.txt", fileName);

	ofstream outFile;

	outFile.open(filepath);

	// Checks if file cannot be opened or created.
	if (!outFile)
	{
		cout << "Error: File cannot be written.\n";
		system("pause");
		return;
	}

	// Prints copy of canvas to the file.
	for (int i = 0; i < MAXROWS; i++)
	{
		for (int y = 0; y < MAXCOLS; y++)
		{
			outFile << canvas[i][y];
		}
		outFile << "\n";
	}

	outFile.close();
	cout << "File Saved!\n";
	system("pause");
}


void loadCanvas(char canvas[][MAXCOLS])
{
	// Reads and saves the contents of the user-specifed file into the canvas.

	char fileName[FILENAMESIZE];
	char filepath[FILENAMESIZE];

	cout << "Enter the filename (don't enter 'txt'): ";
	cin.getline(fileName, FILENAMESIZE - 15);

	snprintf(filepath, FILENAMESIZE, "SavedFiles\\%s.txt", fileName);

	ifstream inFile;

	inFile.open(filepath);

	// Checks if file cannot be opened or created.
	if (!inFile)
	{
		cout << "Error: File cannot be read.\n";
		system("pause");
		return;
	}

	initCanvas(canvas);
	char buffer[MAXCOLS + 1];
	inFile.getline(buffer, MAXCOLS + 1);

	for (int r = 0; r < MAXROWS && !inFile.eof(); r++)
	{
		if (inFile.fail())
		{
			inFile.clear();
			inFile.ignore((numeric_limits<streamsize>::max)(), '\n');
		}

		for (int c = 0; buffer[c] != '\0'; c++)
		{
			canvas[r][c] = buffer[c];
		}
		// Makes sure the file does not exceed 80 columns.
		inFile.getline(buffer, MAXCOLS + 1);

	}

	inFile.close();
}

