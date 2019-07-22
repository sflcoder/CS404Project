#include "Professor.h"
#include <map>
#include <string>
#include <iostream>

using namespace std;

// Constructor
Professor::Professor(int professor_ID, string professor_name)
{
	this->professor_ID = professor_ID;
	this->professor_name = professor_name;
	this->class_num = 0;
	this->can_accept = true;
}

Professor::~Professor()
{

}

// Getters and Setters
int Professor::getID()
{
	return professor_ID;
}

string Professor::get_name()
{
	return professor_name;
}

map<int, double> Professor::get_professor_expertise()
{
	return professor_expertise;
}

// Update the professor expertise
void Professor::update_proferror_expertise(int topic_ID, int expertise_level)
{
	// Check the input value
	if (expertise_level > 5 || expertise_level < 0)
	{
		cout << "The level of expertise is a number from 0 to 5£¬ Please check your input";
	}
	else
	{
		double expertise_value = expertise_level * 0.2;
		this->professor_expertise.insert(pair<int, double>(topic_ID, expertise_value));
		cout << "Updated the professor expertise" << endl
			<< this->professor_ID << '\t' << this->professor_name << '\t' << topic_ID << '\t' << expertise_value << endl;
	}
}

// Print the Professor
void Professor::print()
{
	cout << this->professor_ID << '\t' << this->professor_name << endl;
	map<int, double>::iterator itr;
	for (itr = professor_expertise.begin(); itr != professor_expertise.end(); ++itr) {
		cout << itr->first << '\t' << itr->second << '\n';
	}
	cout << endl;

}