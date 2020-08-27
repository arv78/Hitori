#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <random>
using namespace std;

bool check_limit(vector<float> temp) {
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] < 1) {
			return false;
		}
	}
	return true;
}

void simulated_annealing1(int** inital_matrix) {
	int count_successor = 1;
	int length_size = 0;
	int n = row_count * column_count;
	while (n) {
		length_size++;
		n /= 10;
	}
	n = row_count * column_count;

	int T0 = 0;
	// creating the T0
	if (length_size == 1) {
		T0 = n * (pow(10, length_size));
	}
	else {
		T0 = n * (pow(10, length_size - 1));
	}
	int Tn = 1;
	// creating the scheduler
	vector<float> scheduler;
	scheduler.push_back(T0);
	float Tk;
	int temp_minus;
	double cosine;
	for (int i = 1; i <= n; i++) {
		cosine = cos((i * M_PI) / n);
		temp_minus = T0 - Tn;
		Tk = Tn + ((0.5) * (temp_minus) * (1 + cosine));
		scheduler.push_back(Tk);
	}
	cout << "scheduler size is: " << scheduler.size() << endl;
	//for (int i = 0; i < scheduler.size(); i++) {
	//	cout << scheduler[i] << " ";
	//}
	int probability;
	vector<int**> result;
	pair<int**, int >next;
	pair<int**, int >current;
	int heuristic = 0;
	int random;
	bool flag = false;
	pair<int**, int >temp;

	for (int i = 2; i < row_count + 2; i++) {
		for (int j = 2; j < column_count + 2; j++) {
			if (check_redundancy(inital_matrix, i, j) == true) {
				result = Successor(inital_matrix, i, j);
				current.first = inital_matrix;
				heuristic = heuristic_1(inital_matrix);
				current.second = heuristic;
				flag = true;
				break;
			}
		}
		if (flag == true) {
			break;
		}
	}

	for (int t = 0; t < scheduler.size(); t++) {
		if (result.size() == 0){
			break;
		}

		bool flag = false;
		// generating random (for successor)
		std::random_device rd;
		std::mt19937 gen(rd());
		//cout << "result size: " << result.size() << endl;
		std::uniform_real_distribution<> dis(0, result.size());
		random = dis(gen);
		//cout << "random: " << random << endl;
		heuristic = heuristic_1(result[random]);
		next.first = result[random];
		next.second = heuristic;
		cout << "selected matrix: " << endl;
		print_matrix(next.first);

		if (next.second < current.second) {
			current = next;
		}
		else{
			probability = next.second - current.second;
			probability = exp(probability/scheduler[t]) * 100;
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dis(0, 100);
			random = dis(gen);
			if (random <= probability) {
				current = next;
			}
		}

		for (int i = 2; i < row_count + 2; i++) {
			for (int j = 2; j < column_count + 2; j++) {
				if (check_redundancy(next.first, i, j) == true) {
					result = Successor(next.first, i, j);
					count_successor++;
					flag = true;
					break;
				}
			}
			if (flag == true) {	
				break;
			}
		}

	}
	if (is_goal(current.first)) {
		cout << endl;
		cout << "result: " << endl;
		print_matrix(current.first);
		cout << endl;
		cout << "max priority queue size: 1" << endl;
		cout << "successor count: " << count_successor << endl;
	}
	else {
		cout << "No solution!" << endl;
	}
}

void simulated_annealing2(int** inital_matrix) {
	int count_successor = 1;
	int length_size = 0;
	int n = row_count * column_count;
	while (n) {
		length_size++;
		n /= 10;
	}
	n = row_count * column_count;
	int T0 = 0;
	// creating the T0
	if (length_size == 1) {
		T0 = n * (pow(10, length_size));
	}
	else {
		T0 = n * (pow(10, length_size - 1));
	}
	int Tn = 1;
	// creating the scheduler
	vector<float> scheduler;
	scheduler.push_back(T0);
	float Tk;
	int temp_minus;
	double cosine;
	for (int i = 1; i <= n; i++) {
		cosine = cos((i * M_PI) / n);
		temp_minus = T0 - Tn;
		Tk = Tn + ((0.5) * (temp_minus) * (1 + cosine));
		scheduler.push_back(Tk);
	}
	cout << "scheduler size is: " << scheduler.size() << endl;
	//for (int i = 0; i < scheduler.size(); i++) {
	//	cout << scheduler[i] << " ";
	//}
	int probability;
	vector<int**> result;
	pair<int**, int >next;
	pair<int**, int >current;
	int heuristic = 0;
	int random;
	bool flag = false;
	pair<int**, int >temp;

	for (int i = 2; i < row_count + 2; i++) {
		for (int j = 2; j < column_count + 2; j++) {
			if (check_redundancy(inital_matrix, i, j) == true) {
				result = Successor(inital_matrix, i, j);
				current.first = inital_matrix;
				heuristic = heuristic_2(inital_matrix);
				current.second = heuristic;
				flag = true;
				break;
			}
		}
		if (flag == true) {
			break;
		}
	}

	for (int t = 0; t < scheduler.size(); t++) {
		if (result.size() == 0) {
			break;
		}
		bool flag = false;
		// generating random (for successor)
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0, result.size());
		random = dis(gen);
		heuristic = heuristic_2(result[random]);
		next.first = result[random];
		next.second = heuristic;
		cout << "selected matrix: " << endl;
		print_matrix(next.first);

		if (next.second > current.second) {
			current = next;
		}
		else {
			probability = next.second - current.second;
			probability = exp(probability / scheduler[t]) * 100;
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dis(0, 100);
			random = dis(gen);
			if (random <= probability) {
				current = next;
			}
		}

		for (int i = 2; i < row_count + 2; i++) {
			for (int j = 2; j < column_count + 2; j++) {
				if (check_redundancy(next.first, i, j) == true) {
					result = Successor(next.first, i, j);
					count_successor++;
					flag = true;
					break;
				}
			}
			if (flag == true) {
				break;
			}
		}

	}
	if (is_goal(current.first)) {
		cout << endl;
		cout << "result: " << endl;
		print_matrix(current.first);
		cout << endl;
		cout << "max priority queue size: 1" << endl;
		cout << "successor count: " << count_successor << endl;
	}
	else {
		cout << "No solution!" << endl;
	}
}

