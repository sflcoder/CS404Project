// CS404Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Shufeng Li	16271090
// Assignment2

#include "Topic.h"
#include "Course.h"
#include "Professor.h"
#include "Course_Pool.h"
#include "Professor_List.h"
#include "Match_System.h"
#include <iostream>
#include <fstream>
#include <map>

#include <string>
using namespace std;

int main()
{
	// Construct a Class_Pool object with a file.
	Course_Pool coursePool(ifstream("courses.txt"));
	// Update the course topic with a file.
	coursePool.update_course_topic(ifstream("courseTopics.txt"));

	// Construct a Class_Pool object with a file.
	Professor_List professorList(ifstream("professors.txt"));
	// Update the professor expertise with a file
	professorList.update_professor_expertise(ifstream("professorExpertise.txt"));

	// Construct a match_system object.
	Match_System match_system(coursePool, professorList);
	// Calculate the match score table and build the preference matrix
	match_system.calculate_preference();

	// Mtch the course with professor
	match_system.match();

	// Sort the table according to sum of match score
	// Let the course with lowest match score summary choose first
	match_system.match_sorted();
}

