#pragma once
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void BFS(int** matrix) {
	int count_successor = 1;
	int max_size = 0;
	queue<int**> Q;
	Q.push(matrix);
	vector<int** > result;
	bool flag_break = false;
	if (is_goal(matrix) == true) {
		print_matrix(matrix);
		return;
	}
	for (int i = 2; i < row_count + 2; i++) {
		for (int j = 2; j < column_count + 2; j++) {

			if (check_redundancy(matrix, i, j) == true) {
				result = Successor(matrix, i, j);
				for (int k = 0; k < result.size(); k++) {
					Q.push(result[k]);
				}
				flag_break = true;
				break;
			}
		}
		if (flag_break) {
			break;
		}
	}
	int** current_state;
	while (!Q.empty()) {
		if (Q.size() > max_size) {
			max_size = Q.size();
		}
		flag_break = false;
		current_state = Q.front();
		Q.pop();
		if (is_goal(current_state) == true) {
			cout << endl;
			print_matrix(current_state);
			cout << endl;
			cout << "max priority queue size: " << max_size << endl;
			cout << "successor count: " << count_successor << endl;
			return;
		}
		for (int i = 2; i < row_count + 2; i++) {
			for (int j = 2; j < column_count + 2; j++) {

				if (check_redundancy(current_state, i, j) == true) {
					result = Successor(current_state, i, j);
					count_successor++;
					for (int k = 0; k < result.size(); k++) {
						Q.push(result[k]);
					}
					flag_break = true;
					break;
				}
			}
			if (flag_break) {
				break;
			}
		}
	}
	cout << "No solution!" << endl;
}