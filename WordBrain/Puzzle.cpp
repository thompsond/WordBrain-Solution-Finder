#include "stdafx.h"
#include "Puzzle.h"
#include <fstream>

namespace WordBrain {
	using namespace std;

	Puzzle::Puzzle() {
		string line;
		ifstream fin;
		fin.open("words.txt");
		// Put all of the dictionary words into a set
		while (fin) {
			getline(fin, line);
			for (size_t i = 0; i < line.size(); i++) {
				line[i] = toupper(line[i]);
			}
			dictWords.insert(line);
		}
		fin.close();
	}
	
	void Puzzle::start(vector<size_t> wordLengths, set<pair<size_t, size_t>> usedLocations) {
		// Iterate through all entered wordLengths
		for (size_t i = 0; i < wordLengths.size(); i++) {
			size_t wordLength = wordLengths[i];
			// Go to the next iteration if the given word length is out of bounds
			if (wordLength < 0 || wordLength >(puzzle.size() * puzzle.size())) {
				cout << "Invalid word length" << endl;
				continue;
			}
			// Iterate through the entire puzzle
			for (size_t row = 0; row < puzzle.size(); row++) {
				for (size_t col = 0; col < puzzle[row].size(); col++) {
					if (!isValid(row, col, set<pair<size_t, size_t>>())) {
						continue;
					}
					string word = "";
					word += puzzle[row][col];
					// call getSolutions with the first character each time
					getSolutions(row, col, word, wordLength, usedLocations);
				}
			}
		}
		for (auto w : words) {
			cout << w << endl;
		}
	}

	void Puzzle::getSolutions(size_t row, size_t col, string word, size_t wordLength, set<pair<size_t, size_t>> usedLocations) {
		usedLocations.insert(pair<size_t, size_t>(row, col));
		// Stop when we have found a word the size of wordLength
		if (word.size() == wordLength) {
			// Add the word to the set if it is in the dictionary
			if (dictWords.find(word) != dictWords.end()) {
				words.insert(word);
			}
			return;
		}
		else {
			// Look for a neighbor in each possible direction
			for (size_t d = Direction::N; d != Direction::LAST; d++) {
				size_t neighborRow, neighborCol;
				switch (d) {
					case Puzzle::N:
						neighborRow = row - 1;
						neighborCol = col;
						break;
					case Puzzle::S:
						neighborRow = row + 1;
						neighborCol = col;
						break;
					case Puzzle::E:
						neighborRow = row;
						neighborCol = col + 1;
						break;
					case Puzzle::W:
						neighborRow = row;
						neighborCol = col - 1;
						break;
					case Puzzle::NE:
						neighborRow = row - 1;
						neighborCol = col + 1;
						break;
					case Puzzle::NW:
						neighborRow = row - 1;
						neighborCol = col - 1;
						break;
					case Puzzle::SE:
						neighborRow = row + 1;
						neighborCol = col + 1;
						break;
					case Puzzle::SW:
						neighborRow = row + 1;
						neighborCol = col - 1;
						break;
					case Puzzle::LAST:
						return;
						break;
				}

				if (isValid(neighborRow, neighborCol, usedLocations)) {
					word += puzzle[neighborRow][neighborCol]; // choose
					getSolutions(neighborRow, neighborCol, word, wordLength, usedLocations); // explore
					word.pop_back(); // unchoose
				}
				else {
					continue;
				}
			}
		}
	}

	bool Puzzle::isValid(size_t row, size_t col, set<pair<size_t, size_t>> usedLocations) {
		// A piece is valid if it is not out of the bounds of the puzzle and it has not already been used
		if (row < 0 || row >= puzzle.size() || col < 0 || col >= puzzle.size() || puzzle[row][col] == '-' || ( usedLocations.find(pair<size_t, size_t>(row, col)) != usedLocations.end()) ) {
			return false;
		}
		return true;
	}

	void Puzzle::setPuzzle(vector< vector<char> >& puzzle) {
		this->puzzle = puzzle;
		words.clear();
	}

}