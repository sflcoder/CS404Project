#pragma once
#ifndef TOPIC_H
#define TOPIC_H

#include <string>
using namespace std;

class Topic
{
public:
	// Constructor
	Topic(int topic_ID, string topic_name);
	~Topic();

	// Print the Topic
	void print();

private:
	int topic_ID;
	string topic_name;
};
#endif

