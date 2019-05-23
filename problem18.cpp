// reading a text file
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int const ITEMS = 15;

int main () {
	int numbers[ITEMS][2*ITEMS-1];
	
	
	string line;
	ifstream myfile ("C:\\Users\\A521646\\OneDrive - Valvoline\\Documents\\Projects\\C++\\Project Euler 18\\problem18.txt");

	// Place all the numbers in a two dimensional array.
	/*
	Assuming the numbers are in a triangle inside the text file, like so:
	75
	95 64
	17 47 82
	18 35 87 10

	They will be placed into an array like this:
	
	0	0	0	75	0	0	0
	0	0	95	0	64	0	0
	0	17	0	47	0	82	0
	18 	0	35	0	87	0	10

	This will make the numbers processable by the algorithm.
	
	*/
	
	int currLine = 0;
	int nextNum = ITEMS - 1;  // Points to the location on the current line in the 2-D array where this number should go.
	if (myfile.is_open()) {
		while ( getline (myfile,line) ) {
		  string currentNumber = "";
		  for (int i = 0; i < line.size(); i++){  // Iterate over the line of characters.
			  cout << line[i] << "\n";
			  if (line[i] == ' ') {  	// Encountered a whitespace in the line.
				  if (currentNumber != "") {  // There was already a number present. Try placing it into the array.
					 numbers[currLine][nextNum] = stoi(currentNumber);
				  }
				  currentNumber = ""; 	// Reset the string that holds the number.
				  nextNum += 2;  		// Point to the location of the next number - two spots ahead of the current.
			  } else {
				  currentNumber += line[i];	// Get the character.
			  }
		  }
		  // Reset the pointers to look at the next correct row and starting column.
		  nextNum--;
		  currLine++;
		}
		myfile.close();
	}

	else cout << "Unable to open file"; 

  return 0;
}
