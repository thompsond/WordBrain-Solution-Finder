// WordBrain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Puzzle.h"

using namespace std;

WordBrain::Puzzle p;

void begin() {
	size_t rows, numOfWords, wordLength;
	cout << "Enter the height of the grid: ";
	cin >> rows;
	vector<vector<char>> puzzle(rows);

	for (size_t row = 0; row < rows; row++) {
		cout << "Enter the items for row " << row + 1 << ": " << endl;
		for (size_t col = 0; col < rows; col++) {
			char c;
			cout << ">";
			cin >> c;
			c = toupper(c);
			puzzle[row].push_back(c);
		}
	}

	cout << endl;

	cout << "How many words do you need to find: ";
	cin >> numOfWords;
	cout << endl;

	vector<size_t> wordLengths;
	for (size_t i = 0; i < numOfWords; i++) {
		cout << "Enter the word length: ";
		cin >> wordLength;
		cout << endl;
		wordLengths.push_back(wordLength);
	}


	p.setPuzzle(puzzle);
	p.start(wordLengths, set< pair<size_t, size_t>>());
}

	int main() {
		cout << "WordBrain Solution Finder\n\n" << endl;
		char ch;
		do {
			begin();
			cout << "New puzzle?: ";
			cin >> ch;
		} while (toupper(ch) != 'N');
		

		return 0;
	}

	

