#pragma once
#ifndef PROFESSOR_LIST_H
#define PROFESSOR_LIST_H

#include "Professor.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Professor_List
{
public:

	// Construct an empty Class_Pool.
	Professor_List();

	// Construct a Class_Pool with a input file.
	Professor_List(ifstream codeFile);

	// Destructor
	~Professor_List();

	// Getters and Setters
	vector<Professor> get_professor_list();
	int get_professor_num();

	// Update the professor expertise with a input file
	void update_professor_expertise(ifstream courseTopicFile);

	// Print the professor list
	void print();

private:
	vector<Professor> professor_list;
};
#endif