#pragma once
#include <queue>
#include <vector>
#include "Heuristic Functions.h"
using namespace std;


vector<pair<int**, pair<int, int>>> sorting1(vector<pair<int**, pair<int, int>>> state) {
	pair<int**, pair<int, int> > temp;
	for (int i = 0; i < state.size(); i++) {
		for (int j = i + 1; j < state.size(); j++) {
			if (state[j].second.first + state[j].second.second < state[i].second.first + state[i].second.second) {
				temp = state[i];
				state[i] = state[j];
				state[j] = temp;
			}
		}
	}
	return state;
}

vector<pair<int**, pair<int, int>>> sorting2(vector<pair<int**, pair<int, int>>> state) {
	pair<int**, pair<int, int> > temp;
	for (int i = 0; i < state.size(); i++) {
		for (int j = i + 1; j < state.size(); j++) {
			if (state[j].second.first + state[j].second.second > state[i].second.first - state[i].second.second) {
				temp = state[i];
				state[i] = state[j];
				state[j] = temp;
			}
		}
	}
	return state;
}

void A1(int** matrix) {
	int count_successor = 1;
	int max_size = 0;
	vector<int**> result;
	vector<pair<int**, pair<int, int>>> priority_Q;
	int heuristic = 0;
	pair<int**, pair<int, int>>res_Q;
	bool flag_break = false;
	int g = 1;

	// first step
	if (is_goal(matrix) == true) {
		print_matrix(matrix);
		return;
	}

	for (int i = 2; i < row_count + 2; i++) {
		for (int j = 2; j < column_count + 2; j++) {

			if (check_redundancy(matrix, i, j) == true) {
				result = Successor(matrix, i, j);
				for (int k = 0; k < result.size(); k++) {
					if (is_goal(result[k]) == true) {
						cout << endl;
						cout << "result: " << endl;
						print_matrix(result[k]);
						cout << endl;
						return;
					}
					heuristic = heuristic_1(result[k]);
					priority_Q.push_back(make_pair(result[k], make_pair(heuristic, g)));
				}
				flag_break = true;
				break;
			}
		}
		if (flag_break) {
			break;
		}
	}


	while (priority_Q.empty() != true) {

		if (priority_Q.size() > max_size) {
			max_size = priority_Q.size();
		}

		flag_break = false;

		priority_Q = sorting1(priority_Q);

		//cout << "printing priority Q:" << endl;
		//for (int i = 0; i < priority_Q.size(); i++) {
		//	print_matrix(priority_Q[i].first);
		//	cout <<endl <<priority_Q[i].second<<endl;
		//}

		res_Q = priority_Q.front();
		priority_Q.erase(priority_Q.begin());
		cout << "selected matrix:" << endl;
		print_matrix(res_Q.first);

		for (int i = 2; i < row_count + 2; i++) {
			for (int j = 2; j < column_count + 2; j++) {
				if (check_redundancy(res_Q.first, i, j) == true) {
					result = Successor(res_Q.first, i, j);
					count_successor++;
					for (int k = 0; k < result.size(); k++) {
						if (is_goal(result[k]) == true) {
							cout << endl;
							cout << "result: " << endl;
							print_matrix(result[k]);
							cout << endl;
							cout << "max priority queue size: " << max_size << endl;
							cout << "successor count: " << count_successor << endl;
							return;
						}
						heuristic = heuristic_1(result[k]);
						priority_Q.push_back(make_pair(result[k], make_pair(heuristic, res_Q.second.second + 1)));
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
	cout << "No solution" << endl;

}

void A2(int** matrix) {
	int count_successor = 1;
	int max_size = 0;
	vector<int**> result;
	vector<pair<int**, pair<int, int>>> priority_Q;
	int heuristic = 0;
	pair<int**, pair<int, int>>res_Q;
	bool flag_break = false;
	int g = 1;

	// first step
	if (is_goal(matrix) == true) {
		print_matrix(matrix);
		return;
	}

	for (int i = 2; i < row_count + 2; i++) {
		for (int j = 2; j < column_count + 2; j++) {

			if (check_redundancy(matrix, i, j) == true) {
				result = Successor(matrix, i, j);
				for (int k = 0; k < result.size(); k++) {
					if (is_goal(result[k]) == true) {
						cout << endl;
						cout << "result: " << endl;
						print_matrix(result[k]);
						cout << endl;
						return;
					}
					heuristic = heuristic_2(result[k]);
					priority_Q.push_back(make_pair(result[k], make_pair(heuristic, g)));
				}
				flag_break = true;
				break;
			}
		}
		if (flag_break) {
			break;
		}
	}


	while (priority_Q.empty() != true) {
		if (priority_Q.size() > max_size) {
			max_size = priority_Q.size();
		}

		flag_break = false;

		priority_Q = sorting2(priority_Q);

		//cout << "printing priority Q:" << endl;
		//for (int i = 0; i < priority_Q.size(); i++) {
		//	print_matrix(priority_Q[i].first);
		//	cout <<endl <<priority_Q[i].second<<endl;
		//}

		res_Q = priority_Q.front();
		priority_Q.erase(priority_Q.begin());
		cout << "selected matrix:" << endl;
		print_matrix(res_Q.first);

		for (int i = 2; i < row_count + 2; i++) {
			for (int j = 2; j < column_count + 2; j++) {
				if (check_redundancy(res_Q.first, i, j) == true) {
					result = Successor(res_Q.first, i, j);
					count_successor++;
					for (int k = 0; k < result.size(); k++) {
						if (is_goal(result[k]) == true) {
							cout << endl;
							cout << "result: " << endl;
							print_matrix(result[k]);
							cout << endl;
							cout << "max priority queue size: " << max_size << endl;
							cout << "successor count: " << count_successor << endl;
							return;
						}
						heuristic = heuristic_2(result[k]);
						priority_Q.push_back(make_pair(result[k], make_pair(heuristic, res_Q.second.second + 1)));
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
	cout << "No solution" << endl;
}