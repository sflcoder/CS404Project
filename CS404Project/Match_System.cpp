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

Match_System::Match_System(Course_Pool coursePool, Professor_List professorList)
{
	this->coursePool = coursePool;
	this->professorList = professorList;
}

void Match_System::calculate_prefer()
{

	int rows = professorList.get_professor_num();
	int cols = coursePool.get_course_num();
	double val = 0;
	vector< vector<double> > match_score(rows, vector<double>(cols, val));

	int professor_num = professorList.get_professor_num();
	vector<Professor> pro = professorList.get_professor_list();
	for (int i = 0; i < professor_num; ++i)
	{
		cout << "\nThe Rows of the array:" << rows;
		map<int, double>::iterator itr_p;
		map<int, double> expertise_map = pro[i].get_professor_expertise();
		for (itr_p = expertise_map.begin(); itr_p != expertise_map.end(); ++itr_p)
		{
			cout << endl << pro[i].getID() << endl
				<< itr_p->first << '\t' << itr_p->second << '\n' << endl;
			int topic_ID_pro = itr_p->first;
			double expertise = itr_p->second;

			int n;
			int course_num = coursePool.get_course_num();
			vector<Course> cour = coursePool.get_course_pool();

			for (int j = 0; j < course_num; j++)
			{
				map<int, double>::iterator itr_c;
				map<int, double> course_map = cour[j].get_topic_percent();
				for (itr_c = course_map.begin(); itr_c != course_map.end(); ++itr_c)
				{
					int topic_ID_course = itr_c->first;
					double topic_percent = itr_c->second;

					if (topic_ID_pro == topic_ID_course)
					{
						match_score[i][j] += (expertise * topic_percent);
						cout << "Update the prefer value of Row: " << i << "  Column: " << j << "  expertise: " << expertise
							<< "  topic_percent: " << topic_percent << "\t" << expertise * topic_percent << "\t" << match_score[i][j] << endl;
					}

				}

			}
		}
	}

	for (int i = 0; i < match_score.size(); i++) {
		for (int j = 0; j < match_score[i].size(); j++)
			cout << match_score[i][j] << " \t";
		cout << endl;
	}

}
