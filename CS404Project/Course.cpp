#include "Course.h"
#include <map>
#include <string>
#include <iostream>

using namespace std;

// Constructor
Course::Course(int course_ID, string course_name)
{
	this->course_ID = course_ID;
	this->course_name = course_name;
	//topic_percent = NULL;
	total_percent = 0;
	is_assigned = false;
}

Course::~Course()
{

}

int Course::getID()
{
	return course_ID;
}

map<int, double>  Course::get_topic_percent()
{
	return topic_percent;
}
void Course::update_topic_percent(int topic_ID, double topic_percent)
{
	this->total_percent += topic_percent;
	if (this->total_percent > 1)
	{
		cout << "The total percent can not exceed 100%";
	}
	else
	{
		this->topic_percent.insert(pair<int, double>(topic_ID, topic_percent));
		cout << "Updated the topic percent" << endl
			<< this->course_ID << '\t' << this->course_name << '\t' << topic_ID << '\t' << topic_percent << endl;
	}
}
// Getters and Setters

	// Print the Topic
void Course::print()
{
	cout << this->course_ID << '\t' << this->course_name << endl;
	map<int, double>::iterator itr;
	for (itr = topic_percent.begin(); itr != topic_percent.end(); ++itr) {
		cout  << itr->first << '\t' << itr->second << '\n';
	}
	cout << endl;
}
