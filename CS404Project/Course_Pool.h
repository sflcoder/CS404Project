#pragma once
#ifndef COURSE_POOL_H
#define COURSE_POOL_H

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

	void update_course_topic(ifstream codeFile);

	int get_course_num();

	list<Course> get_course_pool();

	// Print the class pool
	void print();

private:
	list<Course> course_pool;

};

#endif
