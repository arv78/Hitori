#pragma once
#include <queue>
#include <vector>
#include "Heuristic Functions.h"
using namespace std;

void hill_climbing1(int** matrix) {
	int count_successor = 1;
	int max_size = 0;
	vector<int**> result;
	vector<pair<int**, int>> local_min;
	int heuristic = 0;
	pair<int**, int >res_Q;
	bool flag_break = false;
	int heuristic_matrix = 0;
	int min = 0;


	// first step
	if (is_goal(matrix) == true) {
		print_matrix(matrix);
		return;
	}

	for (int i = 2; i < row_count + 2; i++) {
		for (int j = 2; j < column_count + 2; j++) {

			if (check_redundancy(matrix, i, j) == true) {
				result = Successor(matrix, i, j);
				heuristic_matrix = heuristic_1(matrix);
				min = heuristic_matrix;
				local_min.push_back(make_pair(matrix, min));
				for (int k = 0; k < result.size(); k++) {
					if (is_goal(result[k]) == true) {
						cout << endl;
						cout << "result: " << endl;
						print_matrix(result[k]);
						cout << endl;
						return;
					}
					heuristic = heuristic_1(result[k]);
					if (heuristic < min) {
						min = heuristic;
						local_min.erase(local_min.begin());
						local_min.push_back(make_pair(result[k], min));
					}
				}
				flag_break = true;
				break;
			}
		}
		if (flag_break) {
			break;
		}
	}
	if (min == heuristic_matrix) {
		local_min.erase(local_min.begin());
	}


	while (local_min.empty() != true) {
		if (local_min.size() > max_size) {
			max_size = local_min.size();
		}

		flag_break = false;

		//cout << "printing priority Q:" << endl;
		//for (int i = 0; i < priority_Q.size(); i++) {
		//	print_matrix(priority_Q[i].first);
		//	cout <<endl <<priority_Q[i].second<<endl;
		//}

		res_Q = local_min.front();
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
						if (heuristic < min) {
							min = heuristic;
							local_min.erase(local_min.begin());
							local_min.push_back(make_pair(result[k], min));
						}
					}
					flag_break = true;
					break;
				}
			}

			if (flag_break) {
				break;
			}
		}
		if (min == res_Q.second) {
			local_min.erase(local_min.begin());
		}
	}

	cout << "No solution" << endl;

}

void hill_climbing2(int** matrix) {
	int count_successor = 1;
	int max_size = 0;
	vector<int**> result;
	vector<pair<int**, int>> local_max;
	int heuristic = 0;
	pair<int**, int >res_Q;
	bool flag_break = false;
	int heuristic_matrix = 0;
	int max;


	// first step
	if (is_goal(matrix) == true) {
		print_matrix(matrix);
		return;
	}

	for (int i = 2; i < row_count + 2; i++) {
		for (int j = 2; j < column_count + 2; j++) {

			if (check_redundancy(matrix, i, j) == true) {
				result = Successor(matrix, i, j);
				heuristic_matrix = heuristic_2(matrix);
				max = heuristic_matrix;
				local_max.push_back(make_pair(matrix, max));
				for (int k = 0; k < result.size(); k++) {
					if (is_goal(result[k]) == true) {
						cout << endl;
						cout << "result: " << endl;
						print_matrix(result[k]);
						cout << endl;
						return;
					}
					heuristic = heuristic_2(result[k]);
					if (heuristic > max) {
						max = heuristic;
						local_max.erase(local_max.begin());
						local_max.push_back(make_pair(result[k], max));

					}
				}
				flag_break = true;
				break;
			}
		}
		if (flag_break) {
			break;
		}
	}
	//cout << "local max: " << endl;
	//for (int i = 0; i < local_max.size(); i++) {
	//	print_matrix(local_max[i].first);
	//	cout << endl << local_max[i].second << endl;
	//}
	if (max == heuristic_matrix) {
		local_max.erase(local_max.begin());
	}


	while (local_max.empty() != true) {
		if (local_max.size() > max_size) {
			max_size = local_max.size();
		}

		flag_break = false;

		//cout << "printing priority Q:" << endl;
		//for (int i = 0; i < priority_Q.size(); i++) {
		//	print_matrix(priority_Q[i].first);
		//	cout <<endl <<priority_Q[i].second<<endl;
		//}

		res_Q = local_max.front();
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
						if (heuristic > max) {
							max = heuristic;
							local_max.erase(local_max.begin());
							local_max.push_back(make_pair(result[k], max));
						}
					}
					//cout << "local max: " << endl;
					//for (int k = 0; k < local_max.size(); k++) {
					//	print_matrix(local_max[k].first);
					//	cout << endl << local_max[k].second << endl;
					//}
					flag_break = true;
					break;
				}
			}

			if (flag_break) {
				break;
			}
		}
		if (max == res_Q.second) {
			local_max.erase(local_max.begin());
		}
	}

	cout << "No solution" << endl;

}