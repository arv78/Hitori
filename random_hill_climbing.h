#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include "Heuristic Functions.h"
using namespace std;

void random_hill_climbing1(int** matrix) {
	int count_successor = 1;
	int max_size = 0;
	vector<int**> result;
	vector<pair<int**, float>> local_min;
	int heuristic = 0;
	pair<int**, float >res_Q;
	bool flag_break = false;
	int heuristic_matrix = 0;

	// first step
	if (is_goal(matrix) == true) {
		print_matrix(matrix);
		return;
	}

	for (int i = 2; i < row_count + 2; i++) {
		for (int j = 2; j < column_count + 2; j++) {

			if (check_redundancy(matrix, i, j) == true) {
				result = Successor(matrix, i, j);
				int sum = 0;
				float random = 0;
				for (int k = 0; k < result.size(); k++) {
					if (is_goal(result[k]) == true) {
						cout << endl;
						cout << "result: " << endl;
						print_matrix(result[k]);
						cout << endl;
						cout << "max priority queue size: " << max_size + 1 << endl;
						cout << "successor count: " << count_successor << endl;
						return;
					}
					heuristic = heuristic_1(result[k]);
					local_min.push_back(make_pair(result[k], heuristic));
					sum += heuristic;
				}
				local_min[0].second = 1 - (local_min[0].second / sum);
				//cout << "the periods are: ";
				//cout << "0 ";
				//cout << local_min[0].second << " ";
				for (int k = 1; k < local_min.size(); k++) {
					local_min[k].second = 1 - (local_min[k].second / sum);
					local_min[k].second += local_min[k - 1].second;
					//cout << local_min[k].second << " ";
				}
				//cout << endl;
				// random
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_real_distribution<> dis(0, local_min.size() - 1);//uniform distribution between 0 and local_min.size() - 1
				random = dis(gen);
				//cout << "the random number: " << random << " which should be in the range of 0 : " << local_min.size() - 1 << endl;
				
				if (random <= local_min[0].second) {
					res_Q = local_min[0];
					local_min.clear();
					local_min.push_back(res_Q);
					/*cout << "selected matrix:" << endl;
					print_matrix(local_min[0].first);
					cout << "and it's heuristic is: " << local_min[0].second << endl;*/
				}
				else {
					for (int k = 0; k < local_min.size() - 1; k++) {
						if (local_min[k].second < random && local_min[k + 1].second >= random) {
							res_Q = local_min[k + 1];
							local_min.clear();
							local_min.push_back(res_Q);
						}
					}
					/*cout << "selected matrix:" << endl;
					print_matrix(local_min[0].first);
					cout << "and it's heuristic is: " << local_min[0].second << endl;*/
				}
				flag_break = true;
				break;
			}
		}
		if (flag_break) {
			break;
		}
	}


	while (local_min.empty() != true) {
		cout << local_min.size() << endl;
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
		local_min.clear();
		cout << "selected matrix:" << endl;
		print_matrix(res_Q.first);

		for (int i = 2; i < row_count + 2; i++) {
			for (int j = 2; j < column_count + 2; j++) {
				if (check_redundancy(res_Q.first, i, j) == true) {
					result = Successor(res_Q.first, i, j);
					count_successor++;
					if (result.empty()) {
						cout << "No solution" << endl;
						return;
					}
					int sum = 0;
					float random = 0;
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
						local_min.push_back(make_pair(result[k], heuristic));
						sum += heuristic;
					}

					local_min[0].second = 1 - (local_min[0].second / sum);
					/*cout << "the periods are: ";
					cout << "0 ";
					cout << local_min[0].second << " ";*/
					for (int k = 1; k < local_min.size(); k++) {
						local_min[k].second = 1 - (local_min[k].second / sum);
						local_min[k].second += local_min[k - 1].second;
						//cout << local_min[k].second << " ";
					}
					//cout << endl;
					// random
					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_real_distribution<> dis(0, local_min.size() - 1);//uniform distribution between 0 and local_min.size() - 1
					random = dis(gen);
					//cout << "the random number: " << random << " which should be in the range of 0 : " << local_min.size() - 1 << endl;

					if (random <= local_min[0].second) {
						res_Q = local_min[0];
						local_min.clear();
						local_min.push_back(res_Q);
						/*cout << "selected matrix:" << endl;
						print_matrix(local_min[0].first);
						cout << "and it's heuristic is: " << local_min[0].second << endl;*/
					}
					else {
						for (int k = 0; k < local_min.size() - 1; k++) {
							if (local_min[k].second < random && local_min[k + 1].second >= random) {
								res_Q = local_min[k + 1];
								local_min.clear();
								local_min.push_back(res_Q);
							}
						}
						/*cout << "selected matrix:" << endl;
						print_matrix(local_min[0].first);
						cout << "and it's heuristic is: " << local_min[0].second << endl;*/
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

void random_hill_climbing2(int** matrix) {
	int count_successor = 1;
	int max_size = 0;
	vector<int**> result;
	vector<pair<int**, float>> local_min;
	int heuristic = 0;
	pair<int**, float >res_Q;
	bool flag_break = false;
	int heuristic_matrix = 0;


	// first step
	if (is_goal(matrix) == true) {
		print_matrix(matrix);
		return;
	}

	for (int i = 2; i < row_count + 2; i++) {
		for (int j = 2; j < column_count + 2; j++) {

			if (check_redundancy(matrix, i, j) == true) {
				result = Successor(matrix, i, j);
				int sum = 0;
				float random = 0;
				for (int k = 0; k < result.size(); k++) {
					if (is_goal(result[k]) == true) {
						cout << endl;
						cout << "result: " << endl;
						print_matrix(result[k]);
						cout << endl;
						cout << "max priority queue size: " << max_size + 1 << endl;
						cout << "successor count: " << count_successor << endl;
						return;
					}
					heuristic = heuristic_2(result[k]);
					local_min.push_back(make_pair(result[k], heuristic));
					sum += heuristic;
				}
				local_min[0].second = local_min[0].second / sum;
				for (int k = 1; k < local_min.size(); k++) {
					local_min[k].second = local_min[k].second / sum;
					local_min[k].second += local_min[k - 1].second;
				}
				// random
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_real_distribution<> dis(0, 1);//uniform distribution between 0 and 1
				random = dis(gen);

				if (random <= local_min[0].second) {
					res_Q = local_min[0];
					local_min.clear();
					local_min.push_back(res_Q);
					//cout << "selected matrix:" << endl;
					//print_matrix(local_min[0].first);
					//cout << local_min[0].second << endl;
				}
				else {
					for (int k = 0; k < local_min.size() - 1; k++) {
						if (local_min[k].second < random && local_min[k + 1].second >= random) {
							res_Q = local_min[k + 1];
							local_min.clear();
							local_min.push_back(res_Q);
							//cout << "selected matrix:" << endl;
							//print_matrix(local_min[0].first);
							//cout << local_min[0].second << endl;
						}
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
		local_min.clear();
		cout << "selected matrix:" << endl;
		print_matrix(res_Q.first);

		for (int i = 2; i < row_count + 2; i++) {
			for (int j = 2; j < column_count + 2; j++) {
				if (check_redundancy(res_Q.first, i, j) == true) {
					result = Successor(res_Q.first, i, j);
					count_successor++;
					if (result.empty()) {
						cout << "No solution" << endl;
						return;
					}
					int sum = 0;
					float random = 0;
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
						local_min.push_back(make_pair(result[k], heuristic));
						sum += heuristic;
					}
					local_min[0].second = local_min[0].second / sum;
					for (int k = 1; k < local_min.size(); k++) {
						local_min[k].second = local_min[k].second / sum;
						local_min[k].second += local_min[k - 1].second;
					}
					// random
					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_real_distribution<> dis(0, 1);//uniform distribution between 0 and 1
					random = dis(gen);

					if (random <= local_min[0].second) {
						res_Q = local_min[0];
						local_min.clear();
						local_min.push_back(res_Q);
						//cout << "selected matrix:" << endl;
						//print_matrix(local_min[0].first);
						//cout << local_min[0].second << endl;
					}
					else {
						for (int k = 0; k < local_min.size() - 1; k++) {
							if (local_min[k].second < random && local_min[k + 1].second >= random) {
								res_Q = local_min[k + 1];
								local_min.erase(local_min.begin(), local_min.end());
								local_min.push_back(res_Q);
								//cout << "selected matrix:" << endl;
								//print_matrix(local_min[0].first);
								//cout << local_min[0].second << endl;
							}
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
	}

	cout << "No solution" << endl;

}