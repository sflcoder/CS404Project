#pragma once
#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <map>
#include <string>
using namespace std;

class Professor
{
public:
	// Constructor
	Professor(int professor_ID, string professor_name);
	~Professor();

	// Getters and Setters

	int getID();
	string get_name();
	map<int, double> get_professor_expertise();

	void update_proferror_expertise(int topic_ID, int expertise_level);
	// Print the Topic
	void print();


private:
	int professor_ID;
	string professor_name;
	map<int, double> professor_expertise;
	int class_num;
	bool can_accept;
};

#endif

