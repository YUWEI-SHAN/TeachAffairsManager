#pragma once
/*
* project: �������ϵͳ
* file   : CourseList.h
* Copyright <c> ciallo all right reserved.
*/
#define COURSELIST
#include "PublicHead.h"
#ifndef TEACHER
#include "Teacher.h"
#endif // !TEACHER
#ifndef STUDENT
#include "Student.h"
#endif // !STUDENT
#include "File.h"

/**�򵥽ṹ�嶨��**/
struct Time {
	int Hour, Min, Sec;
};
struct Period {
	Time Start, End;
};
//�γ̱����ṹ�嶨��
struct Courses {
	
};

/**Period��������**/
Period NewPeriod(Time t1, Time t2);
