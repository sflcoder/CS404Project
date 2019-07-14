#include "Topic.h"

#include <string>
#include <iostream>
using namespace std;

// Constructor
Topic::Topic(int topic_ID, string topic_name)
{
	this->topic_ID = topic_ID;
	this->topic_name = topic_name;
}
Topic::~Topic()
{

}

// Getters and Setters

void Topic::print()
{
	cout << topic_ID << '\t' << topic_name<<endl;
}