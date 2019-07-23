#include "Professor_List.h"
#include "Professor.h"

// Construct an empty Class_Pool.
Professor_List::Professor_List()
{

}

// Construct a Class_Pool with a input file.
Professor_List::Professor_List(ifstream professorFile)
{
	int next_int;
	string next_str;
	while (professorFile.good())
	{
		professorFile >> next_int;
		//courseFile >> next_str;
		getline(professorFile, next_str);
		Professor new_professor(next_int, next_str);
		professor_list.push_back(new_professor);
	}
}

// Destructor
Professor_List::~Professor_List()
{

}

// Getters and Setters
int Professor_List::get_professor_num()
{
	return professor_list.size();
}

vector<Professor> Professor_List::get_professor_list()
{
	return  professor_list;
}

// Update the professor expertise with a input file
// 
// Let the course with lowest match score summary choose first
void Professor_List::update_professor_expertise(ifstream courseTopicFile)
{
	int topicID;
	int professorID;
	int level;

	while (courseTopicFile.good())
	{
		courseTopicFile >> topicID;
		courseTopicFile >> professorID;
		courseTopicFile >> level;

		for (int i = 0; i < professor_list.size(); ++i)
		{
			if (professor_list[i].getID() == professorID)
			{
				professor_list[i].update_proferror_expertise(topicID, level);
			}
		}
	}
}

// Print the professor list
void Professor_List::print()
{
	cout << "The professor list" << endl;
	for (int i = 0; i < professor_list.size(); i++)
	{
		professor_list[i].print();
	}
	cout << endl;
}
