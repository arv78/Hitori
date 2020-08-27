#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>
#include <random>
#include <chrono>
using namespace std;
using namespace std::chrono;

int row_count = 0;
int column_count = 0;

bool check_redundancy(int** initial_state, int x_position, int y_position) {
	for (int i = 2; i < column_count + 2; i++) {
		if (initial_state[x_position][y_position] == initial_state[x_position][i] && initial_state[x_position][i] != 0 && y_position != i) {
			return true;
		}
	}
	for (int i = 2; i < row_count + 2; i++) {
		if (initial_state[x_position][y_position] == initial_state[i][y_position] && initial_state[i][y_position] != 0 && x_position != i) {
			return true;
		}
	}
	return false;
}

bool is_goal(int** matrix) {
	for (int i = 0; i < row_count; i++) {
		for (int j = 0; j < column_count; j++) {
			if (check_redundancy(matrix, i + 2, j + 2) == true) {
				return false;
			}
		}
	}
	return true;
}

void print_matrix_1(int** matrix) {
	int n;
	for (int i = 0; i < row_count + 4; i++) {
		for (int j = 0; j < column_count + 4; j++) {
			if (i < 2 || j < 2 || i > 1 + column_count || j > 1 + column_count) {
				cout << matrix[i][j] << " ";
			}
			else {
				cout << " " << matrix[i][j] << " ";
			}
		}
		cout << endl;
	}
}
	
void print_matrix(int** matrix) {
	int n;
	for (int i = 2; i < row_count + 2; i++) {
		for (int j = 2; j < column_count + 2; j++) {
			cout << " " << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int** copy_matrix(int** matrix) {
	int** temp_matrix = new int* [row_count + 4];
	for (int i = 0; i < row_count + 4; ++i)
		temp_matrix[i] = new int[column_count + 4];

	for (int i = 0; i < row_count + 4; i++) {
		for (int j = 0; j < column_count + 4; j++) {
			temp_matrix[i][j] = matrix[i][j];
		}
	}
	return temp_matrix;
}

//Successor
vector<int**> Successor(int** initial_state, int x_position, int y_position) {
	vector< int** > result;
	vector< pair<int, int> > redundant;
	for (int i = 2; i < column_count + 2; i++) {
		if (initial_state[x_position][y_position] == initial_state[x_position][i]) {
			if (initial_state[x_position][i + 1] != 0 && initial_state[x_position + 1][i] != 0 && initial_state[x_position][i - 1] != 0 &&
				initial_state[x_position - 1][i] != 0) {
				if (((initial_state[x_position][i + 2] != 0)|| (initial_state[x_position + 1][i + 1] != 0) || (initial_state[x_position - 1][i + 1] != 0))
					&& ((initial_state[x_position][i - 2] != 0) || (initial_state[x_position + 1][i - 1] != 0) || (initial_state[x_position - 1][i - 1] != 0))
					&& ((initial_state[x_position + 2][i] != 0) || (initial_state[x_position + 1][i + 1] != 0) || (initial_state[x_position + 1][i - 1] != 0))
					&& ((initial_state[x_position - 2][i] != 0) || (initial_state[x_position - 1][i + 1] != 0) || (initial_state[x_position - 1][i - 1] != 0))) {
					if ((initial_state[x_position + 1][i + 2] != -1 || initial_state[x_position + 1][i + 1] != 0 || initial_state[x_position][i - 1] != -1) && (initial_state[x_position - 1][i - 1] != 0 || initial_state[x_position - 1][i - 2] != -1 || initial_state[x_position + 1][i] != -1)
						&& (initial_state[x_position + 1][i - 1] != 0 || initial_state[x_position + 1][i - 2] != -1 || initial_state[x_position][i + 1] != -1) && (initial_state[x_position - 1][i + 1] != 0 || initial_state[x_position + 2][i + 1] != -1 || initial_state[x_position + 1][i] != -1)
						&& (initial_state[x_position + 1][i + 1] != 0 || initial_state[x_position + 2][i + 1] != -1 || initial_state[x_position - 1][i] != -1) && (initial_state[x_position - 1][i - 1] != 0 || initial_state[x_position - 2][i - 1] != -1 || initial_state[x_position][i + 1] != -1)
						&& (initial_state[x_position - 1][i + 1] != 0 || initial_state[x_position - 1][i + 2] != -1 || initial_state[x_position][i - 1] != -1) && (initial_state[x_position + 1][i - 1] != 0 || initial_state[x_position + 2][i - 1] != -1 || initial_state[x_position - 1][i] != -1)
						&& (initial_state[x_position][i - 1] != -1 || initial_state[x_position + 1][i + 1] != 0 || initial_state[x_position + 2][i] != 0)
						&& (initial_state[x_position][i - 2] != -1 || initial_state[x_position + 1][i - 1] != 0 || initial_state[x_position - 1][i - 1] != 0)
						&& (initial_state[x_position][i - 1] != -1 || initial_state[x_position - 1][i + 1] != 0 || initial_state[x_position - 2][i] != 0)
						&& (initial_state[x_position - 2][i] != -1 || initial_state[x_position - 1][i - 1] != 0 || initial_state[x_position - 1][i + 1] != 0)
						&& (initial_state[x_position - 1][i] != -1 || initial_state[x_position + 1][i + 1] != 0 || initial_state[x_position][i + 2] != 0)
						&& (initial_state[x_position - 1][i] != -1 || initial_state[x_position + 1][i - 1] != 0 || initial_state[x_position][i - 2] != 0)
						&& (initial_state[x_position][i + 1] != -1 || initial_state[x_position + 1][i - 1] != 0 || initial_state[x_position + 2][i] != 0)
						&& (initial_state[x_position][i + 2] != -1 || initial_state[x_position + 1][i + 1] != 0 || initial_state[x_position - 1][i + 1] != 0)
						&& (initial_state[x_position][i + 1] != -1 || initial_state[x_position - 1][i - 1] != 0 || initial_state[x_position - 2][i] != 0)
						&& (initial_state[x_position + 2][i] != -1 || initial_state[x_position + 1][i + 1] != 0 || initial_state[x_position + 1][i - 1] != 0)
						&& (initial_state[x_position + 1][i] != -1 || initial_state[x_position - 1][i - 1] != 0 || initial_state[x_position][i - 2] != 0)
						&& (initial_state[x_position + 1][i] != -1 || initial_state[x_position - 1][i + 1] != 0 || initial_state[x_position][i + 2] != 0)) {
						redundant.push_back(make_pair(x_position, i));
					}
				}
			}
		}
	}
	for (int i = 3; i < row_count + 2; i++) {
		
		if (i != x_position) {
			if (initial_state[x_position][y_position] == initial_state[i][y_position]) {
				if (initial_state[i][y_position + 1] != 0 && initial_state[i - 1][y_position] != 0 && initial_state[i + 1][y_position] != 0 &&
					initial_state[i][y_position - 1] != 0) {
					if (((initial_state[i][y_position + 2] != 0)|| (initial_state[i + 1][y_position + 1] != 0) || (initial_state[i - 1][y_position + 1] != 0))
						&& ((initial_state[i][y_position - 2] != 0) || (initial_state[i + 1][y_position - 1] != 0) || (initial_state[i - 1][y_position - 1] != 0))
						&& ((initial_state[i + 2][y_position] != 0) || (initial_state[i + 1][y_position + 1] != 0) || (initial_state[i + 1][y_position - 1] != 0))
						&& ((initial_state[i - 2][y_position] != 0) || (initial_state[i - 1][y_position + 1] != 0) || (initial_state[i - 1][y_position - 1] != 0))) {
						if ((initial_state[i + 2][y_position + 1] != -1 || initial_state[i + 1][y_position + 1] != 0 || initial_state[i][y_position - 1] != -1) && (initial_state[i - 1][y_position - 1] != 0 || initial_state[i - 1][y_position - 2] != -1 || initial_state[i + 1][y_position] != -1)
							&& (initial_state[i + 1][y_position - 1] != 0 || initial_state[i + 2][y_position - 1] != -1 || initial_state[i][y_position + 1] != -1) && (initial_state[i - 1][y_position + 1] != 0 || initial_state[i - 1][y_position + 2] != -1 || initial_state[i + 1][y_position] != -1)
							&& (initial_state[i + 1][y_position + 1] != 0 || initial_state[i + 1][y_position + 2] != -1 || initial_state[i - 1][y_position] != -1) && (initial_state[i - 1][y_position - 1] != 0 || initial_state[i - 2][y_position - 1] != -1 || initial_state[i][y_position + 1] != -1)
							&& (initial_state[i - 1][y_position + 1] != 0 || initial_state[i - 2][y_position + 1] != -1 || initial_state[i][y_position - 1] != -1) && (initial_state[i + 1][y_position - 1] != 0 || initial_state[i + 1][y_position - 2] != -1 || initial_state[i - 1][y_position] != -1)
							&& (initial_state[i][y_position - 1] != -1 || initial_state[i + 1][y_position + 1] != 0 || initial_state[i + 2][y_position] != 0)
							&& (initial_state[i][y_position - 2] != -1 || initial_state[i + 1][y_position - 1] != 0 || initial_state[i - 1][y_position - 1] != 0)
							&& (initial_state[i][y_position - 1] != -1 || initial_state[i - 1][y_position + 1] != 0 || initial_state[i - 2][y_position] != 0)
							&& (initial_state[i - 2][y_position] != -1 || initial_state[i - 1][y_position - 1] != 0 || initial_state[i - 1][y_position + 1] != 0)
							&& (initial_state[i - 1][y_position] != -1 || initial_state[i + 1][y_position + 1] != 0 || initial_state[i][y_position + 2] != 0)
							&& (initial_state[i - 1][y_position] != -1 || initial_state[i + 1][y_position - 1] != 0 || initial_state[i][y_position - 2] != 0)
							&& (initial_state[i][y_position + 1] != -1 || initial_state[i + 1][y_position - 1] != 0 || initial_state[i + 2][y_position] != 0)
							&& (initial_state[i][y_position + 2] != -1 || initial_state[i + 1][y_position + 1] != 0 || initial_state[i - 1][y_position + 1] != 0)
							&& (initial_state[i][y_position + 1] != -1 || initial_state[i - 1][y_position - 1] != 0 || initial_state[i - 2][y_position] != 0)
							&& (initial_state[i + 2][y_position] != -1 || initial_state[i + 1][y_position + 1] != 0 || initial_state[i + 1][y_position - 1] != 0)
							&& (initial_state[i + 1][y_position] != -1 || initial_state[i - 1][y_position - 1] != 0 || initial_state[i][y_position - 2] != 0)
							&& (initial_state[i + 1][y_position] != -1 || initial_state[i - 1][y_position + 1] != 0 || initial_state[i][y_position + 2] != 0)) {
							redundant.push_back(make_pair(i, y_position));
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < redundant.size(); i++) {
		int** temp_matrix = copy_matrix(initial_state);
		temp_matrix[redundant[i].first][redundant[i].second] = 0;
		result.push_back(temp_matrix);
	}

	return result;
}

#include "greedy.h"
#include "A_star.h"
#include "hill_climbing.h"
#include "random_hill_climbing.h"
#include "simulated_annealing.h"
#include "Heuristic Functions.h"
#include "BFS.h"

int main() {
	int count_true = 0;
	int** copied_m;
	// reading file
	ifstream infile("sample1.txt");
	if (infile.fail()) {
		cerr << "error" << std::endl;
	}
	infile >> row_count;
	infile >> column_count;
	// creating matrix

	int** matrix = new int* [row_count + 4];
	for (int i = 0; i < row_count + 4; ++i)
		matrix[i] = new int[column_count + 4];
	// showing input
	cout << "input: " << endl;
	for (int i = 0; i < row_count + 4; i++) {
		for (int j = 0; j < column_count + 4; j++) {
			if (i < 2 || j < 2 || i > 1 + column_count || j > 1 + column_count) {
				matrix[i][j] = -1;
				cout << matrix[i][j] << " ";
			}
			else {
				infile >> matrix[i][j];
				cout << " " << matrix[i][j] << " ";
			}
		}
		cout << endl;
	}
	cout << "1.greedy " << "2.A* " << " 3.hill climbing " << " 4.random hill climbing " << " 5.simulated annealing" << endl;
	int mode;
	vector<int**> result;
	cin >> mode;
	auto start = high_resolution_clock::now();
	switch (mode) {
	case 1:
		//BFS(matrix);
		greedy1(matrix);
		//greedy2(matrix);
		break;
	case 2:
		A1(matrix);
		//A2(matrix);

		break;
	case 3:
		hill_climbing1(matrix);
		//hill_climbing2(matrix);
		break;
	case 4:
		random_hill_climbing1(matrix);
		//random_hill_climbing2(matrix);
		break;
	case 5:
		simulated_annealing1(matrix);
		//simulated_annealing2(matrix);
		break;
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "time: " << duration.count()/pow(10,6) << " sec" << endl;
	return 0;
}