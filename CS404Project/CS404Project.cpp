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

	// Test Topic class
	cout << "Test Topic class\n";
	Topic test_topic(1, "Programming");
	test_topic.print();

	// Test Course
	cout << "Test Course class\n";
	Course test_course(303, "Data Structures");
	test_course.update_topic_percent(1, 0.2);
	test_course.update_topic_percent(2, 0.3);
	test_course.print();

	//Test Professor
	cout << "Test Professor class\n";
	Professor test_professor(1, "John Smith");
	test_professor.update_proferror_expertise(1, 2);
	test_professor.update_proferror_expertise(2, 3);
	test_professor.print();

	//Test the Class_Pool clas
	Course_Pool coursePool(ifstream("courses.txt"));
	coursePool.print();
	coursePool.update_course_topic(ifstream("courseTopics.txt"));
	coursePool.print();


	//Test the Professor_List clas
	Professor_List professorList(ifstream("professors.txt"));
	professorList.print();

	professorList.update_professor_expertise(ifstream("professorExpertise.txt"));
	professorList.print();

	coursePool.print();


	Match_System match_system(coursePool, professorList);
	vector< vector<int> > preference_matrix = match_system.calculate_preference();


	// Print the result in the main function
	cout << endl << endl;
	for (int i = 0; i < preference_matrix.size(); i++) {
		for (int j = 0; j < preference_matrix[i].size(); j++)
			cout << preference_matrix[i][j] << " \t";
		cout << endl;
	}

	match_system.Gale_Shapley();

}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
