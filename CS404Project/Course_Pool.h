#pragma once
#ifndef COURSE_POOL_H
#define COURSE_POOL_H
#include <vector>
#include "Course.h"
#include <string>
#include <list>
#include <fstream>
#include <iostream>

class Course_Pool
{
public:

	// Construct an empty Class_Pool.
	Course_Pool();
	// Construct a Class_Pool with a input file.
	Course_Pool(ifstream codeFile);

	// Destructor
	~Course_Pool();

	// Getters and Setters
	int get_course_num();
	vector<Course> get_course_pool();

	// Update the course topic
	void update_course_topic(ifstream codeFile);

	// Print the class pool
	void print();

private:
	vector<Course> course_pool;
};
#endif

