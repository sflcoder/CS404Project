#pragma once
#ifndef COURSE_H
#define COURSE_H
#include <map>
#include <string>
using namespace std;

class Course
{
public:
	// Constructor and dis
	Course(int course_ID, string course_name);
	~Course();

	// Getters and Setters
	int getID();
	string get_name();
	map<int, double> get_topic_percent();

	// Update the topic percent
	void update_topic_percent(int topic_ID, double topic_percent);
	
	// Print the Topic
	void print();

private:
	int course_ID;
	string course_name;
	map<int, double> topic_percent;
	double total_percent;
	bool is_assigned;
};
#endif
