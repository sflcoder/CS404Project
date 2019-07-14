#include "Course_Pool.h"
#include <iostream>
#include <string>
using namespace std;

Course_Pool::Course_Pool()
{

}

Course_Pool::Course_Pool(ifstream courseFile)
{
	
	int next_int;
	string next_str;
	//char str[255];
	while (courseFile.good())
	{
		courseFile >> next_int;
		//courseFile.getline(str, 255);
		//cout << str;
		//next_str = str;
		//courseFile >> next_str;
		getline(courseFile, next_str);
		Course new_course(next_int, next_str);
		course_pool.push_back(new_course);
	}
}

Course_Pool::~Course_Pool()
{

}

void Course_Pool::print()
{
	// Print the class pool
	cout << "The class pool" << endl;
	list<Course> ::iterator iter;
	for (iter = course_pool.begin(); iter != course_pool.end(); ++iter)
	{
		iter->print();
		//cout << iter->getTitle() << endl;
	}
	cout << endl;
}