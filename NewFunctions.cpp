#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Definitions.h"
using namespace std;


Point::Point(DrawPoint p)
{
	row = (int)round(p.row);
	col = (int)round(p.col);
}

// https://math.stackexchange.com/questions/39390/determining-end-coordinates-of-line-with-the-specified-length-and-angle
DrawPoint findEndPoint(DrawPoint start, int len, int angle)
{
	DrawPoint end;
	end.col = start.col + len * cos(degree2radian(angle));
	end.row = start.row + len * sin(degree2radian(angle));
	return end;
}


// Use this to draw characters into the canvas, with the option of performing animation
void drawHelper(char canvas[][MAXCOLS], Point p, char ch, bool animate)
{
	// Pause time between steps (in milliseconds)
	const int TIME = 50;

	// Make sure point is within bounds
	if (p.row >= 0 && p.row < MAXROWS && p.col >= 0 && p.col < MAXCOLS)
	{
		// Draw character into the canvas
		canvas[p.row][p.col] = ch;

		// If animation is enabled, draw to screen at same time
		if (animate)
		{
			gotoxy(p.row, p.col);
			printf("%c", ch);
			Sleep(TIME);
		}
	}
}


// Fills gaps in a row caused by mismatch between match calculations and screen coordinates
// (i.e. the resolution of our 'canvas' isn't very good)
void drawLineFillRow(char canvas[][MAXCOLS], int col, int startRow, int endRow, char ch, bool animate)
{
	// Determine if we're counting up or down
	if (startRow <= endRow)
		for (int r = startRow; r <= endRow; r++)
		{
			Point point(r, col);
			drawHelper(canvas, point, ch, animate);
		}
	else
		for (int r = startRow; r >= endRow; r--)
		{
			Point point(r, col);
			drawHelper(canvas, point, ch, animate);
		}
}


// Draw a single line from start point to end point
void drawLine(char canvas[][MAXCOLS], DrawPoint start, DrawPoint end, bool animate)
{
	char ch;

	Point scrStart(start);
	Point scrEnd(end);

	// Vertical line
	if (scrStart.col == scrEnd.col)
	{
		ch = '|';

		drawLineFillRow(canvas, scrStart.col, scrStart.row, scrEnd.row, ch, animate);
	}
	// Non-vertical line
	else
	{
		int row = -1, prevRow;

		// Determine the slope of the line
		double slope = (start.row - end.row) / (start.col - end.col);

		// Choose appropriate characters based on 'steepness' and direction of slope
		if (slope > 1.8)  ch = '|';
		else if (slope > 0.08)  ch = '`';
		else if (slope > -0.08)  ch = '-';
		else if (slope > -1.8) ch = '\'';
		else ch = '|';

		// Determine if columns are counting up or down
		if (scrStart.col <= scrEnd.col)
		{
			// For each column from start to end, calculate row values
			for (int col = scrStart.col; col <= scrEnd.col; col++)
			{
				prevRow = row;
				row = (int)round(slope * (col - start.col) + start.row);

				// Draw from previous row to current row (to fill in row gaps)
				if (prevRow > -1)
				{
					drawLineFillRow(canvas, col, prevRow, row, ch, animate);
				}
			}
		}
		else
		{
			// For each column from start to end, calculate row values
			for (int col = scrStart.col; col >= scrEnd.col; col--)
			{
				prevRow = row;
				row = (int)round(slope * (col - start.col) + start.row);

				// Draw from previous row to current row (to fill in row gaps)
				if (prevRow > -1)
				{
					drawLineFillRow(canvas, col, prevRow, row, ch, animate);
				}
			}
		}
	}
}


// Draws a single box around a center point
void drawBox(char canvas[][MAXCOLS], Point center, int height, bool animate)
{
	int sizeHalf = height / 2;
	int ratio = (int)round(MAXCOLS / (double)MAXROWS * sizeHalf);

	// Calculate where the four corners of the box should be
	DrawPoint points[4];
	points[0] = DrawPoint(center.row - sizeHalf, center.col - ratio);
	points[1] = DrawPoint(center.row - sizeHalf, center.col + ratio);
	points[2] = DrawPoint(center.row + sizeHalf, center.col + ratio);
	points[3] = DrawPoint(center.row + sizeHalf, center.col - ratio);

	// Draw the four lines of the box
	for (int x = 0; x < 3; x++)
	{
		drawLine(canvas, points[x], points[x + 1], animate);
	}
	drawLine(canvas, points[3], points[0], animate);

	// Replace the corners with a better looking character
	for (int x = 0; x < 4; x++)
	{
		drawHelper(canvas, points[x], '+', animate);
	}
}


// Menu for the drawing tools
void menuTwo(char canvas[][MAXCOLS], char backupCanvas[][MAXCOLS], bool& animate)
{
	
	char choice, newch;
	Point start, end;
	int size, angle;

	char drawmenu[] = "<A>nimate: N / <F>ill / <L>ine / <B>ox / <N>ested Boxes / <T>ree / <M>ain Menu: ";
	drawmenu[11] = animate ? 'Y' : 'N';

	int menulength = strlen(drawmenu) + 20;

	do
	{

		displayCanvas(canvas);

		cout << drawmenu;

		// Get the numeric entry from the menu lowercase or uppercase
		cin >> choice;
		choice = (char)toupper(choice);
		// Makes the 'enter' key that was pressed after the numeric entry be ignored
		// Should be used after getting any numeric input from the keyboard
		cin.ignore();

		clearLine(MAXROWS + 1, menulength);

		switch (choice)
		{
		case 'A':
			// Will switch the animate to false or true if A is pressed
			animate = !animate;
			drawmenu[11] = animate ? 'Y' : 'N';
			break;
		case 'F':
		{
			cout << "Enter character to fill with from current location / <ESC> to cancel";

			// Move cursor to row,col and then get a single character from the keyboard
			newch = getPoint(start);
			if (newch == ESC)
			{
				break;
			}

			copyCanvas(backupCanvas, canvas);
			fillRecursive(canvas, start.row, start.col, canvas[start.row][start.col], newch, animate);
			break;
		}
		case 'L':
		{
			cout << "Type any letter to choose start point / <ESC> to cancel ";
			newch = getPoint(start);
			if (newch == ESC)
			{
				break;
			}

			printf("%c", newch);

			clearLine(MAXROWS + 1, menulength);

			cout << "Type any letter to choose end point / <ESC> to cancel ";
			newch = getPoint(end);
			if (newch == ESC)
			{
				break;
			}

			copyCanvas(backupCanvas, canvas);
			drawLine(canvas, start, end, animate);
			break;
		}
		case 'B':
		{
			cout << "Enter size: ";
			cin >> size;
			cin.ignore();

			clearLine(MAXROWS + 1, menulength);

			cout << "Type any letter to choose box center, or <C> for screen center / <ESC> to cancel";
			newch = getPoint(start);
			if (newch == ESC)
			{
				break;
			}
			if (toupper(newch) == 'C')
			{
				start = Point(MAXROWS / 2, MAXCOLS / 2);
			}

			copyCanvas(backupCanvas, canvas);
			drawBox(canvas, start, size, animate);

			break;

		}
		case 'N':
		{
			cout << "Enter size of largest box: ";
			cin >> size;
			cin.ignore();

			clearLine(MAXROWS + 1, menulength);

			cout << "Type any letter to choose box center, or <C> for screen center / <ESC> to cancel";
			newch = getPoint(start);
			if (newch == ESC)
			{
				break;
			}
			if (toupper(newch) == 'C')
			{
				start = Point(MAXROWS / 2, MAXCOLS / 2);
			}

			copyCanvas(backupCanvas, canvas);
			drawBoxesRecursive(canvas, start, size, animate);
			break;
		}
		case 'T':
		{
			cout << "Enter approximate tree height: ";
			cin >> size;
			cin.ignore();

			clearLine(MAXROWS + 1, menulength);

			cout << "Enter integer branch angle: ";
			cin >> angle;
			cin.ignore();

			clearLine(MAXROWS + 1, menulength);
			// Get starting point for tree
			cout << "Type any letter to choose start point, or <C> for bottom center / <ESC> to cancel";
			newch = getPoint(start);
			if (newch == ESC)
			{
				break;
			}
			if (toupper(newch) == 'C')
			{
				start = Point(MAXROWS - 1, MAXCOLS / 2);
			}

			copyCanvas(backupCanvas, canvas);
			treeRecursive(canvas, start, size, 270, angle, animate);
			break;
		}

		}
		// Clears canvas of specified lines
		clearLine(MAXROWS + 1, menulength);
		clearLine(MAXROWS + 2, menulength);
		clearLine(MAXROWS + 3, menulength);
	} while (choice != 'M');
}


// Get a single point from screen, with character entered at that point
char getPoint(Point& pt)
{
	int row = 0, col = 0;
	char input;

	// Move cursor to row,col and then get a single character from the keyboard
	gotoxy(row, col);
	input = _getch();

	while (input != ESC && !(32 <= input && input <= 126))
	{
		// 'if' statement moves the selected position if the user inputs an arrow key
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
		else if (input == '\0')
		{
			input = _getch();
		}
		gotoxy(row, col);
		input = _getch();
	}
	pt = Point(row, col);
	return input;
}


// Recursively fill a section of the screen
void fillRecursive(char canvas[][MAXCOLS], int row, int col, char oldCh, char newCh, bool animate)
{
	// Creates a point with the given row and column
	Point start(row, col);
	// Base case: starts if fill was to go out of bound or character is the same
	if (canvas[row][col] != oldCh || row > MAXROWS || col < 0 || row < 0 || col > MAXCOLS || canvas[row][col] == newCh)
	{
		return;
	}
	// Recursive cases:
	drawHelper(canvas, start, newCh, animate);
	fillRecursive(canvas, row - 1, col, oldCh, newCh, animate);
	fillRecursive(canvas, row + 1, col, oldCh, newCh, animate);
	fillRecursive(canvas, row, col + 1, oldCh, newCh, animate);
	fillRecursive(canvas, row, col - 1, oldCh, newCh, animate);

}



// Recursively draw a tree
void treeRecursive(char canvas[][MAXCOLS], DrawPoint start, int height, int startAngle, int branchAngle, bool animate)
{
	// Base case: start of tree is out of bounds
	if (start.row < 0 || start.col < 0 || start.row >= MAXROWS || start.col >= MAXCOLS)
	{
		return;
	}

	// Base case: tree too small
	if (height < 3)
	{
		return;
	}

	// Recursive cases:
	DrawPoint end = findEndPoint(start, height / 3, startAngle);
	drawLine(canvas, start, end, animate);
	treeRecursive(canvas, end, height - 2, startAngle - branchAngle, branchAngle, animate);
	treeRecursive(canvas, end, height - 2, startAngle + branchAngle, branchAngle, animate);
}


// Recursively draw nested boxes
void drawBoxesRecursive(char canvas[][MAXCOLS], Point center, int height, bool animate)
{
	// Base case: box too small to draw
	if (height < 2)
	{
		return;
	}

	// Recursive cases:
	drawBox(canvas, center, height, animate);
	drawBoxesRecursive(canvas, center, height - 2, animate);
}
