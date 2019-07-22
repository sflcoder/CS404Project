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
	/*int rows = coursePool.get_course_num();
	int new_rows = 2 * rows;
	int value = 0;
	preference_matrix.resize(new_rows, vector<int>(rows,value));*/
	//preference_matrix(new_rows, vector<int>(rows, value));
	int rows = coursePool.get_course_num();
	int value = 0;
	preference_of_course.resize(rows, vector<int>(rows, value));
	preference_of_professor.resize(rows, vector<int>(rows, value));
}

Match_System::~Match_System()
{
}

// Calculate the preference matrix
vector< vector<int> > Match_System::calculate_preference()
{

	int rows = professorList.get_professor_num();
	int cols = coursePool.get_course_num();
	double val = 0;
	
	// Create a matrix to store the match score and initialize the value to 0
	vector< vector<double> > match_score(rows, vector<double>(cols, val));

	// Get the peofessor list and course pool.
	int professor_num = professorList.get_professor_num();
	vector<Professor> pro = professorList.get_professor_list();
	int course_num = coursePool.get_course_num();
	vector<Course> cour = coursePool.get_course_pool();

	int n_of_matches;
	// Create the match vector for course and professor
	vector <int> match_for_course;
	vector <int> match_for_professor;

	// Calculate the match score and store it to the matrix.
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
						//int m = j + rows;
						//match_score[m][i] += (expertise * topic_percent);
						cout << "Update the preference value of Row: " << i << "  Column: " << j << "  expertise: " << expertise
							<< "  topic_percent: " << topic_percent << "\t" << expertise * topic_percent << "\t" << match_score[i][j] << endl;
					}

				}
			}
		}
	}

	cout << "\t";
	for (int i = 0; i < pro.size(); ++i)
	{
		cout << cour[i].getID() << "\t";
	}
	cout << endl;

	for (int i = 0; i < match_score.size(); ++i) {
		cout << pro[i].getID() << "\t";
		for (int j = 0; j < match_score[i].size(); j++)
			cout << match_score[i][j] << " \t";
		cout << endl;
	}


	//int m = j + rows;
	//match_score[m][i] += (expertise * topic_percent);
	vector<double> v;
	for (int i = 0; i < rows; i++)
	{
		v.clear();
		for (int j = 0; j < cols; j++)
		{
			v.push_back(match_score[j][i]);
		}
		match_score.push_back(v);

	//int m = j + rows;
	//match_score[m][i] += (expertise * topic_percent);
	}

	// Print the match score matrix for test
	for (int i = 0; i < match_score.size(); i++)
	{
		for (int j = 0; j < match_score[i].size(); j++)
			cout << match_score[i][j] << " \t";
		cout << endl;
	}
	cout << endl << endl;

	// Create the preference matrix
	int new_rows = 2 * rows;
	int value = 0;
	vector< vector<int> > preference_matrix(new_rows, vector<int>(cols, value));

	//for (int i = 0; i < match_score.size(); i++)
	for (int i = 0; i < rows; ++i)
	{
		int j = 0;
		for (auto index : sort_indexes(match_score[i]))
		{
			preference_matrix[i][j] = cour[index].getID();
			preference_of_professor[i][j] = cour[index].getID();
			j++;

			// prefer[i][j] = index;
			//cout << index << "\t" << match_score[0][i];
		}
		cout << endl;
	}
	cout << endl << endl;


	for (int i = rows; i < new_rows; ++i)
	{
		int j = 0;
		for (auto index : sort_indexes(match_score[i]))
		{
			//int pre_rows = i + rows;
			preference_matrix[i][j] = pro[index].getID();
			int m = i - rows;
			preference_of_course[m][j] = pro[index].getID();
			// prefer[i][j] = index;
			j++;
			//cout << index << "\t" << match_score[0][i];
		}
		cout << endl;
	}
	cout << endl << endl;

	for (int i = 0; i < preference_matrix.size(); i++) {
		for (int j = 0; j < preference_matrix[i].size(); j++)
			cout << preference_matrix[i][j] << " \t";
		cout << endl;
	}
	cout << endl << endl;

	cout << endl << endl;
	cout << "preference of professor"<< endl;
	for (int i = 0; i < preference_of_professor.size(); i++) {
		for (int j = 0; j < preference_of_professor[i].size(); j++)
			cout << preference_of_professor[i][j] << " \t";
		cout << endl;
	}
	cout << endl << endl;

	cout << endl << endl;
	cout << "preference of course"<< endl;
	for (int i = 0; i < preference_of_course.size(); i++) {
		for (int j = 0; j < preference_of_course[i].size(); j++)
			cout << preference_of_course[i][j] << " \t";
		cout << endl;
	}
	cout << endl << endl;



	return preference_matrix;

	

	// Prints stable matching for N boys and N girls. Boys are numbered as 0 to 
	// N-1. Girls are numbereed as N to 2N-1. 
	// void stableMarriage(int prefer[2 * N][N])
	//vector< vector<int> > v;
	// Stores partner of women. This is our output array that 
	// stores paing information.  The value of wPartner[i] 
	// indicates the partner assigned to woman N+i.  Note that 
	// the woman numbers between N and 2*N-1. The value -1 
	// indicates that (N+i)'th woman is free 
	/*int wPartner[5];


	// An array to store availability of men.  If mFree[i] is 
	// false, then man 'i' is free, otherwise engaged. 
	bool mFree[5];

	// Initialize all men and women as free 
	memset(wPartner, -1, sizeof(wPartner));
	memset(mFree, false, sizeof(mFree));
	int freeCount = 5;

	// While there are free men 
	while (freeCount > 0)
	{
		// Pick the first free man (we could pick any) 
		int m;
		for (m = 0; m < 5; m++)
			if (mFree[m] == false)
				break;

		// One by one go to all women according to m's preferences. 
		// Here m is the picked free man 
		for (int i = 0; i < 5 && mFree[m] == false; i++)
		{
			int w = prefer[m][i];

			// The woman of preference is free, w and m become 
			// partners (Note that the partnership maybe changed 
			// later). So we can say they are engaged not married 
			if (wPartner[w - 5] == -1)
			{
				wPartner[w - 5] = m;
				mFree[m] = true;
				freeCount--;
			}

			else  // If w is not free 
			{
				// Find current engagement of w 
				int m1 = wPartner[w - 5];

				// If w prefers m over her current engagement m1, 
				// then break the engagement between w and m1 and 
				// engage m with w. 
				if (wPrefersM1OverM(prefer, w, m, m1) == false)
				{
					wPartner[w - 5] = m;
					mFree[m] = true;
					mFree[m1] = false;
				}
			} // End of Else 
		} // End of the for loop that goes to all women in m's list 
	} // End of main while loop 


	// Print the solution 
	cout << "Woman   Man" << endl;
	for (int i = 0; i < 5; i++)
		cout << " " << i + 5 << "\t" << wPartner[i] << endl;*/
}



bool Match_System::wPrefersM1OverM(vector< vector<int> > v, int w, int m, int m1)
{
	int n = v[0].size();
	// Check if w prefers m over her current engagment m1 
	for (int i = 0; i < 5; i++)
	{
		// If m1 comes before m in lisr of w, then w prefers her 
		// cirrent engagement, don't do anything 
		if (v[w][i] == m1)
			return true;

		// If m cmes before m1 in w's list, then free her current 
		// engagement and engage her with m 
		if (v[w][i] == m)
			return false;
	}
}

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

// find the first unmatched course or professor 
int first_No_Matches(vector <int> my_array)
{

	int i;
	for (i = 0; i < my_array.size(); i++)
	{
		if (my_array[i] == -1)
		{
			return i;
		}
	}
	return -1;
}


//计算索引排名，如果index1是排在index2前面则返回true，否则返回false 
bool rank_check(vector <int> my_array, int index1, int index2)
{

	int i;
	for (i = 0; i < my_array.size(); i++)
	{
		if (my_array[i] == index1)
		{
			return true;
		}
		else if (my_array[i] == index2)
		{
			return false;
		}
	}
	return false;

}

void Match_System::Gale_Shapley()
{
	int man_index, woman_index;
	int index = 0;
	int n_of_matches = coursePool.get_course_num();
	vector <int> match_for_course;
	vector <int> match_for_professor;
	// 初始化为-1，表示没有匹配 
	for (int i = 0; i < n_of_matches; i++)
	{

		match_for_course.push_back(-1);
		match_for_professor.push_back(-1);
	}

	// Gale-Shapley Algorithm
	//循环取出没有配对的男生 
	while ((man_index = first_No_Matches(match_for_course)) >= 0)
	{

		index = 0;
		//循环读取该男生的喜好列表里的女生 
		while (index < n_of_matches) {
			//得到男生喜好的第index个女生 
			woman_index = preference_of_course[man_index][index];
			//如果该女生还没匹配 ，则双方配对 
			if (match_for_professor[woman_index] == -1)
			{
				match_for_course[man_index] = woman_index;
				match_for_professor[woman_index] = man_index;
				break;
				//如果女生已经配对了，则比较一下两个男生在女生的喜好列表中的排名，如果该男生更受这名女生喜欢，则替换该女生的配对男生 
			}
			else if (rank_check(preference_of_professor[woman_index], man_index, match_for_professor[woman_index]))
			{
				//踢掉原先配对的男生 
				match_for_course[match_for_professor[woman_index]] = -1;
				//重新配对这名男生 
				match_for_professor[woman_index] = man_index;
				//这名男生也配对这名女生 
				match_for_course[man_index] = woman_index;
				break;
				//如果已经配对但是没有更受女生喜好的话，则继续探索男生列表里下一个喜欢的女生 
			}
			else {
				index++;
			}
		}

	}

	cout << "Number of matches" << n_of_matches << endl;
	cout << "Matching  for course" << endl;
	for (int i = 0; i < n_of_matches; i++) {

		cout << "course:" << i << "-> Woman:" << match_for_course[i] << endl;
	}
	std::cout << endl;

}