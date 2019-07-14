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
		cout << endl << "level" << level << endl << endl;
	
		list<Professor> ::iterator iter;
		for (iter = professor_list.begin(); iter != professor_list.end(); ++iter)
		{
			if (iter->getID() == professorID)
			{
				iter->update_proferror_expertise(topicID, level);
			}

			iter->print();
			//cout << iter->getTitle() << endl;
		}
		cout << endl;
	}
}

int Professor_List::get_professor_num()
{
	return professor_list.size();
}

list<Professor> Professor_List::get_professor_list()
{
	return  professor_list;
}

// Print the class pool
void Professor_List::print() {

	// Print the class pool
	cout << "The professor list" << endl;
	list<Professor> ::iterator iter;
	for (iter = professor_list.begin(); iter != professor_list.end(); ++iter)
	{
		iter->print();
		//cout << iter->getTitle() << endl;
	}
	cout << endl;

}
