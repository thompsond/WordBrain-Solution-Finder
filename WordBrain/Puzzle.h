#pragma once
#include <vector>
#include <string>
#include <set>
#include <utility>

namespace WordBrain {
	using namespace std;

	class Puzzle {
	public:
		Puzzle();
		vector<vector<char>> puzzle;
		set<string> dictWords;
		set<string> words;
		int counter = 0;

		enum Direction : int {
			N,
			S,
			E,
			W,
			NE,
			NW,
			SE,
			SW,
			LAST
		};

		void start(vector<size_t> wordLengths, set<pair<size_t, size_t>> usedLocations);
		void getSolutions(size_t row, size_t col, string word, size_t wordLength, set<pair<size_t, size_t>> usedLocations);
		void setPuzzle(vector< vector<char> >& puzzle);
		bool isValid(size_t row, size_t col, set<pair<size_t, size_t>> usedLocations);

	};
}
