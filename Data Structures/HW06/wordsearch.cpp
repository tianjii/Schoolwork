#include <iostream>
#include <vector>
#include <fstream>


const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

//Prints board row by row
void printboard(int row, int col, std::vector<std::vector<char> >&board, std::ostream &outfile) {
	outfile<<"Board:"<<std::endl;
	for (unsigned int i = 0; i < row; i++) {
		outfile<<"  ";
		for (unsigned int j = 0; j < col; j++) {
			outfile<<board[i][j];
		}
		outfile<<std::endl;
	}
}

//Checks stored solutions for duplicates before adding a new solution
bool insols(std::vector<std::vector<char> >&board, std::vector<std::vector<std::vector<char> > > &sols) {
	for (unsigned int i = 0; i < sols.size(); i++) {
		if (board == sols[i]) {
			return false;
		}
	}
	return true;
}

//Checks a board once all the valid words have bee placed
//Recursively checks blank spaces and fills with all letters of the alphabet
//Checks for words that should not be in the board
bool notfound(int row, int col, std::vector<std::vector<char> >board, 
	std::vector<std::string> &minus, std::vector<std::vector<std::vector<char> > > &sols, bool &findone) {
	std::vector<std::vector<char> > newboard;

	//Loops through minus words and searches for them in board - returns false if it finds one
	for (unsigned int i = 0; i < minus.size(); i++) {
		std::string word = minus[i];
		int size = word.size();
		for (int y = 0; y < row; y++) {
 			for (int x = 0; x < col; x++) {

 		if (board[y][x] == word[0]) {
 		//Divide up Board
		bool left = true;
		bool right = true;
		bool up = true;
		bool down = true;
		//There has to be an easier way to do this
		//Bools determine which direction a word can travel in

		if (x - (size-1) < 0) {
			left = false; }
		if (x + (size-1) > col-1) {
			right = false; }
		if (y - (size-1) < 0) {
			up = false; }
		if (y + (size-1) > row-1) {
		down = false; }

		bool valid;

		//Isolate left half of the board, searches for illegal word in horizontal and  diagonal directions
		if (left) {
			valid = true;
			for (unsigned int i = 0; i < word.size(); i++) {
				if (board[y][x-i] != word[i]) {
					valid = false; 
					break; }
			}

			if (valid)
				return false;

			if (up) {
				valid = true;
				for (unsigned int i = 0; i < word.size(); i++) {
					if (board[y-i][x-i] != word[i]) {
					valid = false; 
					break; }
			}

			if (valid)
				return false;

			}

			if (down) {
				valid = true;
				for (unsigned int i = 0; i < word.size(); i++) {
					if (board[y+i][x-i] != word[i]) {
					valid = false; 
					break; }
			}
			if (valid)
				return false;

			}


		} //if left

		//Checks right half of board, searches for illegal word in right and diagonal directions
		if (right) {
			valid = true;
			for (unsigned int i = 0; i < word.size(); i++) {
				if (board[y][x+i] != word[i]) {
					valid = false; 
					break; }
			}
			if (valid)
				return false;

			if (up) {
				valid = true;
				for (unsigned int i = 0; i < word.size(); i++) {
					if (board[y-i][x+i] != word[i]) {
					valid = false; 
					break; }
			}
			if (valid)
				return false;

			}

			if (down) {
				valid = true;
				for (unsigned int i = 0; i < word.size(); i++) {
					if (board[y+i][x+i] != word[i]) {
					valid = false; 
					break; }
			}
			if (valid)
				return false;

			}


		} //if right

		//Search in up and down directions
		if (up) {
				valid = true;
				for (unsigned int i = 0; i < word.size(); i++) {
					if (board[y-i][x] != word[i]) {
					valid = false; 
					break; }
			}
			if (valid)
				return false;

			}

		if (down) {
				valid = true;
				for (unsigned int i = 0; i < word.size(); i++) {
					if (board[y+i][x] != word[i]) {
					valid = false; 
					break; }
			}
			if (valid)
				return false;

			}
 		}
	}
	
} 

}
	//If board has blank space, add a letter to it and call notfound function again, 
	//go through all letters in the alphabet for each blank space
	for (int y = 0; y < row; y++) {
 			for (int x = 0; x < col; x++) {
 		if (board[y][x] == '.') {
 			for (unsigned int i = 0; i < alphabet.size(); i++) {
 				if (findone == true && sols.size() == 1) {
 					return false;
 				}
 				newboard = board;
 				newboard[y][x] = alphabet[i];
 				if (notfound(row,col, newboard, minus, sols, findone)) {
 					if (insols(newboard, sols)) {
 					sols.push_back(newboard);
 					std::cout<<sols.size()<<std::endl;
 	
 				}
 				}
 					
 				}
 				return false;
 			}
 		}
 	} 

return true;

}

void setboard(int row, int col, std::vector<std::vector<char> > &board,
 std::vector<std::string> &plus, std::vector<std::string> &minus, 
 std::vector<std::vector<std::vector<char> > > &sols, int wordnum, bool &findone) {

	//if past end of vector, test the board which should be complete
	if (wordnum == plus.size()) {
		if (notfound(row, col, board, minus, sols, findone)) {
			std::vector<std::vector<char> > newboard = board;
			if (insols(board,sols)) {
			sols.push_back(newboard); }
		}
		return;
	}

 	std::string word = plus[wordnum];
 	int size = word.size();
 	for (int y = 0; y < row; y++) {
 		for (int x = 0; x < col; x++) {
 		if (board[y][x] == word[0] || board[y][x] == '.') {
 		//Divide up Board using bools
		std::vector<std::vector<char> > newboard;
		bool left = true;
		bool right = true;
		bool up = true;
		bool down = true;

		//If there is not enough room on the board, direction becomes false

		if (x - (size-1) < 0) {
			left = false; }
		if (x + (size-1) > col-1) {
			right = false; }
		if (y - (size-1) < 0) {
			up = false; }
		if (y + (size-1) > row-1) {
		down = false; }

		bool valid;

		//Check each direction, attempt to replace letters, 
		//if there is an existing different letter in a spot the word will not fit
		if (left ) {
			if (findone == true && sols.size() >= 1) {
				return;
			}
			valid = true;
			newboard = board;
			for (unsigned int i = 0; i < word.size(); i++) {
				if (newboard[y][x-i] == '.') {
				newboard[y][x-i] = word[i];
				}
				else if (newboard[y][x-i] != word[i]) {
					valid = false; 
					break;}
			}
			if (valid)
				setboard(row, col, newboard, plus, minus, sols, wordnum+1, findone);

			if (up) {
				if (findone == true && sols.size() >= 1) {
				return;
				}
				valid = true;
				newboard = board;
				for (unsigned int i = 0; i < word.size(); i++) {
					if (newboard[y-i][x-i] == '.') {
						newboard[y-i][x-i] = word[i];
					}
					else if (newboard[y-i][x-i] != word[i]) {
					valid = false; 
					break; }
			}

			if (valid)
				setboard(row, col, newboard, plus, minus, sols, wordnum+1, findone);

			}

			if (down) {
				if (findone == true && sols.size() >= 1) {
				return;
			}	
				valid = true;
				newboard = board;
				for (unsigned int i = 0; i < word.size(); i++) {
					if (newboard[y+i][x-i] == '.') {
						newboard[y+i][x-i] = word[i];
					}
				else if (newboard[y+i][x-i] != word[i]) {
					valid = false; 
					break; }
			}
			if (valid)
				setboard(row, col, newboard, plus, minus, sols, wordnum+1, findone);

			}


		} //if left

		if (right) {
			if (findone == true && sols.size() >= 1) {
				return;
			}
			valid = true;
			newboard = board;
			for (unsigned int i = 0; i < word.size(); i++) {
				if (newboard[y][x+i] == '.') {
				newboard[y][x+i] = word[i];
				}
				else if (newboard[y][x+i] != word[i]) {
					valid = false; 
					break; }
			}
			if (valid)
				setboard(row, col, newboard, plus, minus, sols, wordnum+1, findone);

			if (up) {
				if (findone == true && sols.size() >= 1) {
				return;
				}
				valid = true;
				newboard = board;
				for (unsigned int i = 0; i < word.size(); i++) {
					if (newboard[y-i][x+i] == '.') {
						newboard[y-i][x+i] = word[i];
					}
				else if (newboard[y-i][x+i] != word[i]) {
					valid = false; 
					break; }
			}
			if (valid)
				setboard(row, col, newboard, plus, minus, sols, wordnum+1, findone);

			}

			if (down) {
				if (findone == true && sols.size() >= 1) {
				return;
				}
				valid = true;
				newboard = board;
				for (unsigned int i = 0; i < word.size(); i++) {
					if (newboard[y+i][x+i] == '.') {
						newboard[y+i][x+i] = word[i];
					}
				else if (newboard[y+i][x+i] != word[i]) {
					valid = false; 
					break; }
			}
			if (valid)
				setboard(row, col, newboard, plus, minus, sols, wordnum+1, findone);

			}


		} //if right

		if (up) {
				if (findone == true && sols.size() >= 1) {
				return;
				}
				valid = true;
				newboard = board;
				for (unsigned int i = 0; i < word.size(); i++) {
					if (newboard[y-i][x] == '.') {
						newboard[y-i][x] = word[i];
					}
				else if (newboard[y-i][x] != word[i]) {
					valid = false; 
					break; }
			}
			if (valid)
				setboard(row, col, newboard, plus, minus, sols, wordnum+1, findone);

			}

			if (down) {
				if (findone == true && sols.size() >= 1) {
				return;
				}
				valid = true;
				newboard = board;
				for (unsigned int i = 0; i < word.size(); i++) {
					if (newboard[y+i][x] == '.') {
						newboard[y+i][x] = word[i];
					}
				else if (newboard[y+i][x] != word[i]) {
					valid = false; 
					break; }
			}
			if (valid)
				setboard(row, col, newboard, plus, minus, sols, wordnum+1, findone);

			}
 		}
	}
	}
}


int main(int argc, char* argv[]) {

	std::ifstream puzzle(argv[1]);
	std::ofstream outfile(argv[2]);
	int col;
	int row;
	std::vector<std::string> plus;
	std::vector<std::string> minus;
	puzzle>>col>>row;
	std::string tmp;
	while (puzzle >> tmp) {
		if (tmp == "+") {
			puzzle >> tmp;
			plus.push_back(tmp);
		}
		else if (tmp == "-") {
			puzzle >> tmp;
			minus.push_back(tmp);
		}
	}

//Create 2D Vector
	std::vector<std::vector<std::vector<char> > > sols;
	std::vector<std::vector<char> > board;
	std::vector<char> row_vec;
	bool findone;
	std::string command = argv[3];
	for (unsigned int i = 0; i < row; i++) {
		for (unsigned int j = 0; j < col; j++) {
			row_vec.push_back('.');
		}
		board.push_back(row_vec);
	}
//Change output depending on command
	if (command == "all_solutions") {
		findone = false;
		setboard(row, col, board, plus, minus, sols, 0, findone);

		outfile<<sols.size()<<" solution(s)"<<std::endl;
		for (unsigned int i = 0; i < sols.size(); i++) {
			printboard(row,col,sols[i], outfile);
		}
	}

	 else if (command == "one_solution") {
	 	findone = true;
	 	setboard(row, col, board, plus, minus, sols, 0, findone);
			printboard(row,col,sols[0], outfile);

	 }




}
