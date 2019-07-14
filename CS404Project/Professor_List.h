#pragma once
#ifndef PROFESSOR_LIST_H
#define PROFESSOR_LIST_H

#include "Professor.h"
#include <iostream>
#include <fstream>
#include <list>
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

	list<Professor> get_professor_list();

	void update_professor_expertise(ifstream courseTopicFile);

	int get_professor_num();


	// Print the class pool
	void print();

private:
	list<Professor> professor_list;
};


#endif