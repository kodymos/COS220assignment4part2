/*
220assignment4part2.cpp
Assignment:  COS220_Assignment4part2
Programmer:  Kody Moseley
Description: This program allows users to buy plane seats
			from a plan of set size. The plane is read in
			from a text file, and stored in a 2d array.
			It also includes functions for displaying the 
			current plane, as well as calculating the statistics
			of the current plane, such as cappacity, etc.
			
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

//const int ROWS = 10;								//const #rows for smaller plane
//const int COLS = 4;								//const #cols for smaller plane
//const int FIRSTCLASSROWS = 2;						//const #first class rows

const int ROWS = 20;								//const #rows for big plane
const int COLS = 6;									//const #cols for big plane
const int FIRSTCLASSROWS = 4;						//const #first class rows


char alphabetArray[] = { 'A','B','C','D','E','F' };	//char array used for alphabet, column headers

//PRE: nrows is the number of first class rows at front of plane
//POST: row and letter are set to an available first class seat
void assignFirstClass(char seats[][COLS], int nrows, int& row, char& letter) {
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < COLS; j++) {
			if (seats[i][j] == '.') {
				seats[i][j] = 'X';
				row = i + 1;
				letter = alphabetArray[j];
				return;
			}
		}
	}
}

//PRE: nrows is the number of first class rows at front of plane
//POST: return true if a seat is available in first class; else false
bool avaibableFirstClass(char seats[][COLS], int rows) {
	int availableSeats = 0;

	//for loop sequentially searches 2d array for '.', records how many open seats
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < COLS; j++) {
			if (seats[i][j] == '.') {
				availableSeats += 1;
			}
		}
	}

	if (availableSeats > 0) {
		return true;
	}
	else {
		return false;
	}
}

//POST: display the seating char (see screen shot for desired ouput)
void display(char seats[][COLS], int rows) {
	
	cout << "Seating chart: " << endl;
	if (COLS % 4 == 0) {
		cout << endl << "   AB CD" << endl;

	}
	else if(COLS % 6 == 0){
		cout << endl << "   ABC DEF" << endl;
	}
	
	for (int i = 0; i < rows; i++) {
		cout << i+1 << "  ";
		for (int j = 0; j < COLS; j++) {
			if (j == (COLS/2)) {
				cout << " ";
			}
			cout << seats[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
//POST: allow the user to purcahse a seat and mark seat as taken
void purchase(char seats[][COLS], int rows) {
	
	string seatChoice;

	int seatChoiceRow;
	char seatChoiceCol = ' ';
	//int seatChoiceColInt;

	cout << "Enter your row number and column letter (ex. 1A) : ";

	cin >> seatChoice;


	if (seatChoice.length() == 3) {//if input is in the format 1A
		seatChoiceRow = stoi(seatChoice.substr(0, 2)) - 1;
		seatChoiceCol = seatChoice[2];


	}
	else if (seatChoice.length() == 2) {//if input is in the format 10A
		seatChoiceRow = stoi(seatChoice.substr(0, 1)) - 1;
		seatChoiceCol = seatChoice[1];
	}

	int seatChoiceColInt = -1;

	for (int i = 0; i < 6; i++) {//sequentially searches alphabet array for correct letter, letter=index
		if (seatChoiceCol == alphabetArray[i]) {
			seatChoiceColInt = i;
		}
	}

	if (seatChoiceRow > ROWS) {//checks for valid row
		cout << "Invalid row - please try again" << endl;
		return;		
	}
	if (seatChoiceColInt == -1) {//checks for valid col
		cout << "Invalid column - please try again" << endl;
		return;
	}

	

	if (seats[seatChoiceRow][seatChoiceColInt] == '.' && seatChoiceRow <= FIRSTCLASSROWS) {//if user seat is first class and available
		seats[seatChoiceRow][seatChoiceColInt] = 'X';
		cout << "First class seat " << seatChoiceRow + 1<< seatChoiceCol << " is available" << endl;
		return;
	}


	else if (seats[seatChoiceRow][seatChoiceColInt] == '.') {//if user seat is business and available
		string userInput;

		cout << "Business class seat " << seatChoiceRow + 1<< seatChoiceCol << " is available." << endl;
		
		if (avaibableFirstClass(seats, FIRSTCLASSROWS) == 1) {//if there is an available first class seat, ask user if they want to upgrade
			cout << "Would you like to upgrade to first class for an additional $75? ";

			cin >> userInput;

			if (userInput == "N") {
				seats[seatChoiceRow][seatChoiceColInt] = 'X';
				return;
			}
			else if (userInput == "Y") {				
				assignFirstClass(seats, FIRSTCLASSROWS, seatChoiceRow, seatChoiceCol);
				cout << "You have been assigned first class seat " << seatChoiceRow << seatChoiceCol;
				return;
			}
		}
		else if (avaibableFirstClass(seats, FIRSTCLASSROWS) == 0) {
			seats[seatChoiceRow][seatChoiceColInt] = 'X';
			return;
		}
		

	}

	else if (seats[seatChoiceRow][seatChoiceColInt] == 'X') {//if user seat is taken
		cout << "Seat " << seatChoiceRow + 1<< seatChoiceCol << " is not available." << endl;
		return;
	}
	
}

//POST: compute and display percent occupancy
void statistics(char seats[][COLS], int rows) {
	double firstClassSeats = 0;
	double businessClassSeats = 0;
	double totalPlaneOcc = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < COLS; j++) {
			if (seats[i][j] == 'X'){
				if (i < FIRSTCLASSROWS)
					firstClassSeats += 1;
				else
					businessClassSeats += 1;
			}	
		}
	}
	
	//calculate current plane statistics
	totalPlaneOcc = firstClassSeats + businessClassSeats;

	totalPlaneOcc = totalPlaneOcc / (rows * COLS);
	businessClassSeats = businessClassSeats / ((rows - FIRSTCLASSROWS) * COLS);
	firstClassSeats = firstClassSeats / (FIRSTCLASSROWS * COLS);

	cout << fixed << setprecision(1);

	cout << "First class percent occupancy is " << firstClassSeats * 100 << "%" << endl;
	cout << "Business class percent occupancy is " << businessClassSeats * 100 << "%" << endl;
	cout << "Overall percent occupancy is " << totalPlaneOcc * 100 << "%" <<endl;

}

int main()
{
	char userInput;

	ifstream input("seats2.txt");//read in file


	char seats[ROWS][COLS];//initialize 2d array
	
	while (!input.eof()) {//read file into 2d array
		for (int i = 0; i < ROWS; i++) {
			if (COLS == 4) {//smaller plane organization
				string seat;

				input >> seat;

				char seat1 = seat[0];
				char seat2 = seat[1];
				char seat3 = seat[2];
				char seat4 = seat[3];

				seats[i][0] = seat1;
				seats[i][1] = seat2;
				seats[i][2] = seat3;
				seats[i][3] = seat4;
			}
			if (COLS == 6) {//larger plane organization
				string seat;

				input >> seat;

				char seat1 = seat[0];
				char seat2 = seat[1];
				char seat3 = seat[2];
				char seat4 = seat[3];
				char seat5 = seat[4];
				char seat6 = seat[5];


				seats[i][0] = seat1;
				seats[i][1] = seat2;
				seats[i][2] = seat3;
				seats[i][3] = seat4;
				seats[i][4] = seat5;
				seats[i][5] = seat6;

			}
		}
	}
	//print header and user options
	cout << "Plane Seats by Kody Moseley" << endl << endl
		<< "Select choice from menu: " << endl
		<< "D to display seat char" << endl
		<< "P to purchase a seat" << endl
		<< "S to compute statistics" << endl
		<< "Q to quit" << endl << endl;

	cin >> userInput;

	while (userInput != 'Q') {//go until 'Q', all functions available
		
		if (userInput == 'D') {
			display(seats, ROWS);
		}

		else if (userInput == 'P') {
			purchase(seats, ROWS);
		}

		else if (userInput == 'S') {
			statistics(seats, ROWS);
		}

		cin >> userInput;
	}

	system("pause");
	return 0;
}