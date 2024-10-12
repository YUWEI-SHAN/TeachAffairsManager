#pragma once
/*
* project: �������ϵͳ
* file   : Teacher.h
* Copyright <c> ciallo all right reserved.
*/
#define TEACHER
#include "PublicHead.h"
#include "CourseList.h"
#include "File.h"

/**�����Ͷ���**/
typedef int TeaID;

/**�ṹ�����Ͷ���**/
//��ʦ������Ϣ�ṹ��
struct TeacherInformation {
	sex Sex;//�Ա�
	char* Hometown;//����
	Date Birthday;//����
	char* IDCard;//���֤
	char *Photo;//��Ƭ·��
	char* Mail;//����
	char* PhoneNumber;//�绰
	char* Title;//ְ�� 
	char* PersonalInf;//���˼�� 
};

//��ʦ�ṹ��
struct Teacher
{
	int Id;//���� 
	char* name;//����
	TeacherInformation Inf;//��ʦ������Ϣ
	bool remove;
};

/**ȫ�ֱ�������**/
extern Teacher* AllTeas;

/**��������**/
void InitialTeachers(const char* FilePath);
int LoadTeacherFromFile(const char *FilePath);
int SaveTeacherToFile(const char* FilePath);

TeacherInformation MakeTeacherInformation(sex _sex, const Date birthday, const char* hometown,
	const char* idcard, const char* mail, const char* PhoneNumber, const char* Photo,const char* Title,const char* PersonalInf);
void DeConstructTeacherInformation(TeacherInformation *TeaInf);
Teacher MakeTeacher(TeacherInformation TeaInf, const char* name, const TeaID NewID);
void DeConstructTeacher(Teacher* teacher);

int GetNumOfTeachers();
TeaID NewTeacher(Teacher* NewTea);
TeaID DeleteTeacher(TeaID Id);
Teacher* SeekTeacher(TeaID SeekTea);
inline Teacher* IterateTeacher(int *Index);
