#pragma once
using namespace std;

int count_heuristic(int** matrix) {
	int count_redundant = 0;
	for (int i = 2; i < row_count + 2; i++) {
		for (int j = 2; j < column_count + 2; j++) {
			for (int k = 2; k < row_count + 2; k++) {
				if (i != k) {
					if (matrix[i][j] == matrix[k][j] && matrix[i][j] != 0) {
						count_redundant++;
					}
				}
			}
			for (int l = 2; l < column_count + 2; l++) {
				if (j != l) {
					if (matrix[i][j] == matrix[i][l] && matrix[i][j] != 0) {
						count_redundant++;
					}
				}
			}
		}
	}
	return count_redundant;
}

// the less the better
int heuristic_1(int** new_state) {
	int count_new = count_heuristic(new_state);
	return (count_new);
}

// the more the better
int heuristic_2(int** state) {
	int count_heuristic2 = 0;
	for (int i = 2; i < row_count + 2; i++) {
		for (int j = 2; j < column_count + 2; j++) {
			if (state[i][j] == 0) {
				count_heuristic2++;
			}
		}
	}
	return count_heuristic2;
}