#include "Match_System.h"
#include "Course.h"
#include "Professor.h"
#include "Course_Pool.h"
#include "Professor_List.h"
#include <iostream>
#include <list>
#include <vector>
#include <map>

using namespace std;

// Constructor and distructor
Match_System::Match_System(Course_Pool coursePool, Professor_List professorList)
{
	this->coursePool = coursePool;
	this->professorList = professorList;
	int rows = coursePool.get_course_num();
	int value = 0;
	double val = 0;
	match_score.resize(rows, vector<double>(rows, val));
	preference_of_course.resize(rows, vector<int>(rows, value));
	preference_of_course_sorted.resize(0, vector<int>(0, value));
	preference_of_professor.resize(rows, vector<int>(rows, value));
	sum.resize(rows, 0);
}

Match_System::~Match_System()
{
}

// Calculate the match score table and build the preference matrix
void Match_System::calculate_preference()
{
	int rows = professorList.get_professor_num();
	int cols = coursePool.get_course_num();
	double val = 0;

	// Create a matrix to store the match score and initialize the value to 0
	vector< vector<double> > match_score_sym(rows, vector<double>(cols, val));

	// Get the peofessor list and course pool.
	int professor_num = professorList.get_professor_num();
	vector<Professor> pro = professorList.get_professor_list();
	int course_num = coursePool.get_course_num();
	vector<Course> cour = coursePool.get_course_pool();

	// Calculate the match score and store it to the matrix.
	for (int i = 0; i < professor_num; ++i)
	{
		//cout << "\nThe Rows of the array:" << rows;
		map<int, double>::iterator itr_p;
		map<int, double> expertise_map = pro[i].get_professor_expertise();
		for (itr_p = expertise_map.begin(); itr_p != expertise_map.end(); ++itr_p)
		{
			//cout << endl << pro[i].getID() << endl
				//<< itr_p->first << '\t' << itr_p->second << '\n' << endl;
			int topic_ID_pro = itr_p->first;
			double expertise = itr_p->second;

			for (int j = 0; j < course_num; ++j)
			{
				map<int, double>::iterator itr_c;
				map<int, double> course_map = cour[j].get_topic_percent();
				for (itr_c = course_map.begin(); itr_c != course_map.end(); ++itr_c)
				{
					int topic_ID_course = itr_c->first;
					double topic_percent = itr_c->second;

					// Update the match score if the professor has knowledge about this topic
					if (topic_ID_pro == topic_ID_course)
					{
						match_score[i][j] += (expertise * topic_percent);
					}
				}
			}
		}
	}

	// Build the symmetry match score table
	for (int i = 0; i < match_score_sym.size(); ++i)
	{
		for (int j = 0; j < match_score_sym[i].size(); ++j)
			match_score_sym[i][j] = match_score[j][i];
	}

	// Sort the index
	for (int i = 0; i < rows; ++i)
	{
		int j = 0;
		for (auto index : sort_indexes(match_score[i]))
		{
			preference_of_professor[i][j] = index;
			j++;
		}
	}

	// Sort the index
	for (int i = 0; i < rows; ++i)
	{
		int j = 0;
		for (auto index : sort_indexes(match_score_sym[i]))
		{
			preference_of_course[i][j] = index;
			j++;
		}
	}

	for (int i = 0; i < sum.size(); i++)
	{
		for (int j = 0; j < sum.size(); j++)
		{
			sum[i] += match_score_sym[i][j];

		}
	}

	vector<double> total;
	for (int i = 0; i < sum.size(); i++)
	{
		total.push_back(sum[i]);
	}

	cout << endl << "\t" << "The match score table" << endl;
	cout << "\t";
	for (int i = 0; i < pro.size(); ++i)
	{
		cout << cour[i].getID() << "\t";
	}
	cout << endl;

	for (int i = 0; i < match_score.size(); ++i)
	{
		cout << pro[i].getID() << "\t";
		for (int j = 0; j < match_score[i].size(); j++)
			cout << match_score[i][j] << " \t";
		cout << endl;
	}


	//Print the preference of professor
	cout << endl << endl;
	cout << "ID" << "\t" << "preference of professor" << endl;
	for (int i = 0; i < preference_of_professor.size(); i++) {
		cout << pro[i].getID() << "\t";
		for (int j = 0; j < preference_of_professor[i].size(); j++)
			cout << preference_of_professor[i][j] << " \t";
		cout << endl;
	}
	cout << endl << endl;

	cout << "\t" << "The match score table" << endl;
	cout << "\t";
	for (int i = 0; i < cour.size(); ++i)
	{
		cout << pro[i].getID() << "\t";
	}
	cout << "sum" << endl;

	for (int i = 0; i < match_score_sym.size(); ++i) {
		cout << cour[i].getID() << "\t";
		for (int j = 0; j < match_score_sym[i].size(); j++)
			cout << match_score_sym[i][j] << " \t";
		cout << sum[i] << endl;
	}

	// Print the preference of course
	cout << endl<< endl << "ID" << "\t" << "preference of course" << endl;
	for (int i = 0; i < preference_of_course.size(); i++) {
		cout << cour[i].getID() << "\t";
		for (int j = 0; j < preference_of_course[i].size(); j++)
			cout << preference_of_course[i][j] << " \t";
		cout << endl;
	}
	cout << endl;


	// Sort the index
	for (int i = 0; i < sum.size(); ++i)
	{
		int j = 0;
		for (auto index : sort_indexes(sum))
		{
			sum[j] = index;
			j++;
		}
	}

	for (int i = (preference_of_course.size() - 1); i >= 0; i--)
	{
		int n = sum[i];
		preference_of_course_sorted.push_back(preference_of_course[n]);
	}

	cout << endl << endl << "Sort the table according to sum of match score" << endl << endl;
	cout << "\t" << "The match score table" << endl;
	cout << "\t";
	for (int i = 0; i < cour.size(); ++i)
	{
		cout << pro[i].getID() << "\t";
	}
	cout << "sum" << endl;

	
	for (int i = 0; i < match_score_sym.size(); ++i) {
		int m = preference_of_course_sorted.size() - 1 - i;
		int n = sum[m];
		cout << cour[n].getID() << "\t";
		for (int j = 0; j < match_score_sym[i].size(); j++)
			cout << match_score_sym[i][j] << " \t";
		cout << total[n] << endl;
	}

	// Print the sorted preference of course
	cout << endl<< endl << "ID" << "\t" << "preference of course" << endl;
	for (int i = 0; i < preference_of_course_sorted.size(); i++) {
		int m = preference_of_course_sorted.size() - 1 - i;
		int n = sum[m];
		cout << cour[n].getID() << "\t";
		for (int j = 0; j < preference_of_course_sorted[i].size(); j++)
			cout << preference_of_course_sorted[i][j] << " \t";
		cout << endl;
	}
	cout << endl;
}

// find the first unmatched course or professor 
int first_No_Matches(vector <int> preference_array)
{
	int i;
	for (i = 0; i < preference_array.size(); i++)
	{
		if (preference_array[i] == -1)
		{
			return i;
		}
	}
	return -1;
}

// check the preference rank, return true if index1 list in fornt of index2
bool rank_check(vector <int> preference_array, int index1, int index2)
{
	int i;
	for (i = 0; i < preference_array.size(); i++)
	{
		if (preference_array[i] == index1)
		{
			return true;
		}
		else if (preference_array[i] == index2)
		{
			return false;
		}
	}
	return false;
}

// Mtch the course with professor
void Match_System::match()
{
	int course_index, professor_index;
	int index = 0;
	int n_of_matches = coursePool.get_course_num();
	vector <int> match_for_course;
	vector <int> match_for_professor;

	// initinalize the value to -1 indicate the course and professor are unmatched. 
	for (int i = 0; i < n_of_matches; i++)
	{
		match_for_course.push_back(-1);
		match_for_professor.push_back(-1);
	}

	// Gale-Shapley Algorithm
	//Find the unmatched course 
	while ((course_index = first_No_Matches(match_for_course)) >= 0)
	{
		index = 0;
		//match the professor in the preference list of course  
		while (index < n_of_matches) {
			//find the nth professor 
			professor_index = preference_of_course[course_index][index];
			//match with the professor if the professor has not been assigned a course
			if (match_for_professor[professor_index] == -1)
			{
				match_for_course[course_index] = professor_index;
				match_for_professor[professor_index] = course_index;
				break;
			}
			// If the professor already has been assigned a course
			// Check if professor prefer new course over current course
			else if (rank_check(preference_of_professor[professor_index], course_index, match_for_professor[professor_index]))
			{
				// Set the old curse as unmatched 
				match_for_course[match_for_professor[professor_index]] = -1;
				// Match the professor with the new course 
				match_for_professor[professor_index] = course_index;
				match_for_course[course_index] = professor_index;
				break;
			}
			else {
				// if the professor prefer the current course over the new course
				// do nothing and the course continue to check the next professor.
				index++;
			}
		}
	}

	vector<Professor> pro = professorList.get_professor_list();
	vector<Course> cour = coursePool.get_course_pool();
	cout << endl << "The allocation of professors and courses: " << endl << endl;
	cout << "match score" << "\t" << "professor:" << "\t" << "\t" << "course:" << endl;
	for (int i = 0; i < n_of_matches; i++) {
		int j = match_for_course[i];
		cout << match_score[j][i] << "\t" << pro[j].get_name() << "\t" << cour[i].get_name() << endl;
	}
	cout << endl;
}

// Mtch the course with professor
void Match_System::match_sorted()
{
	int course_index, professor_index;
	int index = 0;
	int n_of_matches = coursePool.get_course_num();
	vector <int> match_for_course;
	vector <int> match_for_professor;

	// initinalize the value to -1 indicate the course and professor are unmatched. 
	for (int i = 0; i < n_of_matches; i++)
	{
		match_for_course.push_back(-1);
		match_for_professor.push_back(-1);
	}

	// Gale-Shapley Algorithm
	//Find the unmatched course 
	while ((course_index = first_No_Matches(match_for_course)) >= 0)
	{
		index = 0;
		//match the professor in the preference list of course  
		while (index < n_of_matches) {
			//find the nth professor 
			professor_index = preference_of_course_sorted[course_index][index];
			//match with the professor if the professor has not been assigned a course
			if (match_for_professor[professor_index] == -1)
			{
				match_for_course[course_index] = professor_index;
				match_for_professor[professor_index] = course_index;
				break;
			}
			// If the professor already has been assigned a course
			// Check if professor prefer new course over current course
			else if (rank_check(preference_of_professor[professor_index], course_index, match_for_professor[professor_index]))
			{
				// Set the old curse as unmatched 
				match_for_course[match_for_professor[professor_index]] = -1;
				// Match the professor with the new course 
				match_for_professor[professor_index] = course_index;
				match_for_course[course_index] = professor_index;
				break;
			}
			else {
				// if the professor prefer the current course over the new course
				// do nothing and the course continue to check the next professor.
				index++;
			}
		}
	}

	vector<Professor> pro = professorList.get_professor_list();
	vector<Course> cour = coursePool.get_course_pool();
	cout << endl << "The allocation of professors and courses: " << endl;
	cout << "(Let the course with lowest match score summary choose first) " << endl << endl;

	/*for (int i = 0; i < n_of_matches; i++) {
		int n = (n_of_matches - 1 - i);
		cout << "course:" << sum[n] << "-> professor:" << match_for_course[i] << endl;
	}
	cout << endl;*/

	cout << "match score" << "\t" << "professor:" << "\t" << "\t" << "course:" << endl;
	for (int i = 0; i < n_of_matches; i++) {
		int n = (n_of_matches - 1 - i);
		int index = sum[n];
		int j = match_for_course[i];
		cout << match_score[j][index] << "\t" << pro[j].get_name() << "\t" << cour[index].get_name() << endl;
	}
	cout << endl;
}

// sort the index
template <typename T>
vector<size_t> Match_System::sort_indexes(const vector<T>& v) {

	// initialize original index locations
	vector<size_t> idx(v.size());
	iota(idx.begin(), idx.end(), 0);

	// sort indexes based on comparing values in v
	sort(idx.begin(), idx.end(),
		[&v](size_t i1, size_t i2) {return v[i1] > v[i2]; });
	return idx;
}