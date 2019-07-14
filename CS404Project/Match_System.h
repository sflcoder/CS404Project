#pragma once
#ifndef MATCH_SYSTEM_H
#define MATCH_SYSTEM_H
#include "Course.h"
#include "Professor.h"
#include "Course_Pool.h"
#include "Professor_List.h"
#include <string>
#include <list>
#include <map>
#include <fstream>
#include <iostream>

class Match_System
{
public:
	Match_System(Course_Pool coursePool, Professor_List professorList);

	void calculate_prefer();
private:
	Course_Pool coursePool;
	Professor_List professorList;

};

#endif

