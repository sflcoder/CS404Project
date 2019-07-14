#include "Course_Pool.h"
#include <iostream>
#include <fstream>
using namespace std;

Course_Pool::Course_Pool()
{

}

Course_Pool::Course_Pool(ifstream courseFile)
{
	
	int next_int;
	string next_str;
	while (courseFile.good())
	{
		courseFile >> next_int;
		//courseFile >> next_str;
		getline(courseFile, next_str);
		Course new_course(next_int, next_str);
		course_pool.push_back(new_course);
	}
}

Course_Pool::~Course_Pool()
{

}

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
		//getline(courseTopicFile, topic_percent);
		getline(courseTopicFile, topic_percent);
		cout << endl << "stod(topic_percent)" << stod(topic_percent) << endl << endl;

		percent = stod(topic_percent) / 100;
		cout << endl << "percent" << percent << endl << endl;
		list<Course> ::iterator iter;
		for (iter = course_pool.begin(); iter != course_pool.end(); ++iter)
		{
			if (iter->getID() == courseID)
			{
				iter->update_topic_percent(topicID, percent);
			}
			
			iter->print();
			//cout << iter->getTitle() << endl;
		}
		cout << endl;
	}
}

int Course_Pool::get_course_num()
{
	return course_pool.size();
}

list<Course> Course_Pool::get_course_pool()
{
	return course_pool;
}

void Course_Pool::print()
{
	// Print the class pool
	cout << "The size of class pool:" << this->get_course_num()<< endl;
	list<Course> ::iterator iter;
	for (iter = course_pool.begin(); iter != course_pool.end(); ++iter)
	{
		iter->print();
		//cout << iter->getTitle() << endl;
	}
	cout << endl;
}