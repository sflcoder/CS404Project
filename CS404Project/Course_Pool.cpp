#include "Course_Pool.h"
#include <iostream>
#include <fstream>

using namespace std;

// Construct an empty Class_Pool.
Course_Pool::Course_Pool()
{

}

// Construct a Class_Pool with a input file.
Course_Pool::Course_Pool(ifstream courseFile)
{

	int next_int;
	string next_str;
	while (courseFile.good())
	{
		courseFile >> next_int;
		getline(courseFile, next_str);
		Course new_course(next_int, next_str);
		course_pool.push_back(new_course);
	}
}

// Destructor
Course_Pool::~Course_Pool()
{

}

// Getters and Setters
int Course_Pool::get_course_num()
{
	return int(course_pool.size());
}

vector<Course> Course_Pool::get_course_pool()
{
	return course_pool;
}

// Update the course topic
void Course_Pool::update_course_topic(ifstream courseTopicFile)
{
	int courseID;
	int topicID;
	string topic_percent;
	double percent;
	while (courseTopicFile.good())
	{
		courseTopicFile >> courseID;
		courseTopicFile >> topicID;
		getline(courseTopicFile, topic_percent);
		//cout << endl << "stod(topic_percent)" << stod(topic_percent) << endl << endl;
		percent = stod(topic_percent) / 100;
		//cout << endl << "percent" << percent << endl << endl;

		for (size_t i = 0; i < course_pool.size(); i++)
		{
			if (course_pool[i].getID() == courseID)
			{
				course_pool[i].update_topic_percent(topicID, percent);
			}
			//course_pool[i].print();
		}
		//cout << endl;
	}
}

// Print the class pool
void Course_Pool::print()
{
	// Print the class pool
	cout << "The size of class pool:" << this->get_course_num() << endl;

	for (size_t i = 0; i < course_pool.size(); i++)
	{
		course_pool[i].print();
	}
	cout << endl;
}