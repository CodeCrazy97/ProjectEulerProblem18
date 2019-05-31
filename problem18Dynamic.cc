// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

int const ITEMS = 15;
void printTwoDimIntArray(int arr[][2*ITEMS-1]);
int solveProblem18(int rowNum, int colPtr);

int numbers[ITEMS][2*ITEMS-1];	// Global 2d array of integers used to store the "triangle" of numbers.
int maxPath = -1;
 
string ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    return string( buffer ).substr( 0, pos);
}

int main () { 
	
	string line;
	
	// Get the path to the text file that contains the numbers triangle.
	string pathToNumbersFile = ExePath();
	
	size_t index = 0;
	while (true) {
		 // Locate the backslash to replace. 
		 index = pathToNumbersFile.find("\\", index);
		 if (index == string::npos) break;

		 // Replace the single backslash with two backslashes.
		 pathToNumbersFile.replace(index, 1, "\\\\");

		 // Advance index forward so the next iteration doesn't pick it up as well. 
		 index += 2;
	}
	
	// Point to the actual file (above we merely got the relative path to the file).
	pathToNumbersFile += "\\\\problem18.txt";
	
	// Open a stream from the file.
	ifstream myfile (pathToNumbersFile);
	

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
	int startNum = ITEMS - 1;  // Points to the location on the current line in the 2-D array where this number should go.
	for (int r = 0; r < ITEMS; r++) {
		for (int c = 0; c < 2*ITEMS-1; c++) {
			numbers[r][c] = 0;
		}	
	}
	
	if (myfile.is_open()) {
		
		while ( getline (myfile,line) ) {
		  int nextNum = startNum;
		  string currentNumber = "";
		  for (int i = 0; i < line.size(); i++){  				// Iterate over the line of characters.	
			  if (line[i] == ' ' || i == line.size() - 1) {  	// Encountered a whitespace in the line OR reached the end of the line. Put the last number in the array.
				if (currentNumber != "") { 		// There was already a number present. Try placing it into the array.					
					numbers[currLine][nextNum] = stoi(currentNumber); // Convert the string number to an integral number.
				}
				currentNumber = ""; 	// Reset the string that holds the number.
				nextNum += 2;  			// Point to the location of the next number - two spots ahead of the current.
			  } else {
				currentNumber += line[i];	// Get the next character.
			  }
		  }
		  // Reset the pointers to look at the next correct row and starting column.
		  startNum--;
		  currLine++;
		}
		myfile.close();
	}
	else cout << "Unable to open file"; 
	
	// Show the array of numbers.
	printTwoDimIntArray(numbers);
	
	// Now actually solve problem 18.
	cout << "\n\nMax. total from top to bottom: " << solveProblem18(ITEMS - 2, 2*ITEMS - 3) << "\n";
	
  return 0;
}

void printTwoDimIntArray(int arr[][2*ITEMS-1]) {
	for (int r = 0; r < ITEMS; r++) {
		cout << "\n";
		for (int c = 0; c < 2*ITEMS-1; c++) {
			printf("%3d ", arr[r][c]);
		}
	}
}

int solveProblem18(int rowNum, int colPtr) {		
	for (int i = ITEMS - rowNum - 1; i <= colPtr; i+=2) {
		numbers[rowNum][i] += max(numbers[rowNum+1][i-1],numbers[rowNum+1][i+1]); 
	}
	if (rowNum == 0) {
		return numbers[0][ITEMS - 1];
	} else {
		return solveProblem18(rowNum - 1, colPtr - 1);
	}
}
