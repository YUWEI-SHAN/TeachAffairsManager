#pragma once
/*
* project: �������ϵͳ
* file   : Student.h
* Copyright <c> ciallo all right reserved.
*/
#define STUDENT
#include "PublicHead.h"
#include "CourseList.h"
#include "File.h"

/**�����Ͷ���**/
typedef int StuID;

/**�ṹ�����Ͷ���**/

//ѧ��������Ϣ�ṹ��
struct StudentInformation {
	sex Sex;//�Ա�
	char* Hometown;//����
	Date Birthday;//����
	char* IDCard;//���֤
	char *Photo;//��Ƭ·��
	char* Mail;//����
	char* PhoneNumber;//�绰
};

// ѧ���ṹ��
struct Student
{
	int Id;//ѧ��
	char* name;//����
	StudentInformation Inf;//ѧ��������Ϣ
	bool remove;//ɾ����ʶ
	Courses CS;
};

/**ȫ�ֱ�������**/
//�����ȡ����ѧ��ȫ����Ϣ
extern Student* AllStus;

/**��������**/

/**�ļ��������**/
/*
��ʼ��ѧ���ļ�������һ����ѧ���ļ�������AllStus
����1 �ļ�·��
*/
void InitialStudents(const char* FilePath);
/*
���ļ��м���ѧ��������AllStus
����1 �ļ�·��
����ֵ -1:�ļ���ʧ�ܻ����ļ�ͷ����-2:�ڴ����ʧ��
*/
int LoadStudentFromFile(const char *FilePath);
/*
����ȡѧ����Ϣ���浽�ļ��У������ͷ�AllStus
����1 �ļ�·��
����ֵ -1:�ļ���ʧ��
*/
int SaveStudentToFile(const char* FilePath);

/**�ṹ������򻯺���**/
/*
���ٴ���StudentInformation�ṹ�壬��ȥ�ֶ�Alloc
����N �ṹ����Ϣ���μ�StudentInformation
����ֵ �����õ�StudentInformation ���󷵻��Ա�Ϊothers�Ľṹ��
*/
StudentInformation MakeStudentInformation(sex _sex,const Date birthday, const char* hometown,
	const char* idcard, const char* mail, const char* PhoneNumber, const char* Photo);
/*
��������StudentInformation�ṹ�壬��ȥ�ֶ�Free
����1 StudentInformationָ��
*/
void DeConstructStudentInformation(StudentInformation *StuInf);
/*
���ٴ���Student�ṹ�壬��ȥ�ֶ�Alloc
����1 StudentInformation
����2 ѧ������
����3 �����ѧ��ID(�������0)
����ֵ �����õ�Student ���󷵻�����Ϊnullptr�Ľṹ��
*/
Student MakeStudent(StudentInformation StuInf, const char* name, const StuID NewID);
/*
��������Student�ṹ�壬��ȥ�ֶ�Free
����1 Studentָ��
*/
void DeConstructStudent(Student* student);

/**AllStus���ݿ��������**/
/*
��ȡAllStus����ЧStudents����
����ֵ Students����
*/
int GetNumOfStudents();
/*
�����ݿ����һ��ѧ��
����1 Student�ṹ��(StuID�������0)
����ֵ Student ID -1:�����ڴ�ʧ�ܻ�������Ϸ� -2:����ѧ��ID�ظ� 
*/
StuID NewStudent(Student* NewStu);
/*
�����ݿ�ɾ��һ��ѧ��
����1 StudentID(StuID�������0)
����ֵ Student ID -1:�����ڴ�ʧ�ܻ�������Ϸ�
*/
StuID DeleteStudent(StuID Id);
/*
�����ݿ����һ��ѧ��
����1 Student�ṹ��(StuID�������0)
����ֵ Student ID NULL:û�ҵ�ѧ����������Ϸ���Ҳ������AllStusû�г�ʼ��
*/
Student* SeekStudent(StuID SeekStu);
/*
ö�����ݿ���ѧ��
����1 Indexָ�룬���ڱ�ʶö�ٽ��ȣ�ÿ��Iterate�������һ����ʼӦ���趨indexΪ-1
����ֵ Student ID -1:�����ڴ�ʧ�ܻ�������Ϸ� -2:����ѧ��ID�ظ�
*/
inline Student* IterateStudent(int *Index);
