#pragma once
#ifndef MATCH_SYSTEM_H
#define MATCH_SYSTEM_H
#include "Course.h"
#include "Professor.h"
#include "Course_Pool.h"
#include "Professor_List.h"
#include <string>
#include <list>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

class Match_System
{
public:

	// Constructor and distructor
	Match_System(Course_Pool coursePool, Professor_List professorList);
	~Match_System();

	// Calculate the preference matrix
	void calculate_preference();

	// Match the course wit professor
	void match();
	void match_sorted();

	// Sort the index
	template <typename T>
	vector<size_t> sort_indexes(const vector<T>& v);

private:
	Course_Pool coursePool;
	Professor_List professorList;
	vector< vector<double> > match_score;
	vector< vector<int> > preference_of_course;
	vector< vector<int> > preference_of_course_sorted;
	vector< vector<int> > preference_of_professor;
	vector<double> sum;
};
#endif

