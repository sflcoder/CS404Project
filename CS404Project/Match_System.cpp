#include "Match_System.h"
#include "Course.h"
#include "Professor.h"
#include "Course_Pool.h"
#include "Professor_List.h"
#include <iostream>
#include <list>
#include <map>


using namespace std;

Match_System::Match_System(Course_Pool coursePool, Professor_List professorList)
{
	this->coursePool = coursePool;
	this->professorList = professorList;
}

void Match_System::calculate_prefer()
{
	int columns = coursePool.get_course_num();
	//int rows = 2 * columns;
	int rows = columns;

	// Create the row
	double** match_score = new double* [rows];
	// Create the column
	for (int i = 0; i < rows; i++)
		match_score[i] = new double[columns];

	// initialize the array 
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			match_score[i][j] = 0;
		}
	}

	int m;
	list<Professor>::iterator it_p;
	list<Professor> pro = professorList.get_professor_list();
	for (it_p = pro.begin(), m = 0; it_p != pro.end(); ++it_p, ++m)
	{
		cout << "\nThe Rows of the array:" << rows;

		map<int, double>::iterator itr_p;
		map<int, double> expertise_map = it_p->get_professor_expertise();
		for (itr_p = expertise_map.begin(); itr_p != expertise_map.end(); ++itr_p)
		{
			cout << endl << it_p->getID() << endl
				<< itr_p->first << '\t' << itr_p->second << '\n' << endl;
			int topic_ID_pro = itr_p->first;
			double expertise = itr_p->second;

			int n;
			list<Course>::iterator it_c;
			list<Course> course_list = coursePool.get_course_pool();
			for (it_c = course_list.begin(), n = 0; it_c != course_list.end(); ++it_c, ++n)
			{
				map<int, double>::iterator itr_c;
				map<int, double> course_map = it_c->get_topic_percent();
				for (itr_c = course_map.begin(); itr_c != course_map.end(); ++itr_c)
				{
					int topic_ID_course = itr_c->first;
					double topic_percent = itr_c->second;

					if (topic_ID_pro == topic_ID_course)
					{
						match_score[m][n] += (expertise * topic_percent);
						cout << "Update the prefer value of Row: " << m << "  Column: " << n << "  expertise: " << expertise
							<< "  topic_percent: " << topic_percent << "\t" << expertise * topic_percent << "\t" << match_score[m][n] << endl;
					}
				}
			}
		}
	}

	cout << endl << "Print the Prefer array" << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << match_score[i][j] << "\t";
		}
		cout << endl;
	}





	for (int i = 0; i < rows; i++)
		delete[] match_score[i];
	delete[] match_score;
}
