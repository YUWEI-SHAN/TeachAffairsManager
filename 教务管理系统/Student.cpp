/*
* project: �������ϵͳ
* file   : Student.cpp
* Copyright <c> ciallo all right reserved.
*/
#include "Student.h"

/**�ؼ�ȫ�ֱ���**/
int NumOfStudents;//AllStus�б���ѧ����Ŀ
int AllocNumOfStu;//AllStus�ڴ��������
Student* AllStus = NULL;//AllStus����
/**��С��������**/
const int MinAllocSize = 64;//һ��Ԥ����AllStus��С
/**�ļ�ͷ��ʶ**/
const char HeadString[HEAD_LENGTH] = "[Ciallo~ Teaching Affairs Manager][Studentsfile]";
/**�ļ��������**/
void InitialStudents(const char* FilePath)
{
	//�������AllStus�Ѿ����䣬�Ͳ�Ҫ���ã������ڴ�й©
	if (NumOfStudents) {
		return;
	}
	//��ʼ�����к�AllStus�йصı���
	NumOfStudents = 0;
	AllocNumOfStu = 0;
	AllStus = NULL;
	//����һ�ݿ��ļ�������ȱ�ļ�LoadStudentFromFile����
	FILE* fStu = SaveFile(FilePath, HeadString);
	//д��һ��0��ʾ�ļ�����Students��ĿΪ��
	fwrite(&NumOfStudents, sizeof(int), 1, fStu);
	//�ر��ļ�
	fclose(fStu);
}

int LoadStudentFromFile(const char* FilePath)
{
	//���ж�AllStus������Ѿ�����;ܾ���ȡ�������ڴ�й©
	CHECK_NULLANY(AllStus,)else { return -1; }
	//�����ļ�ͷ������
	char ReadHead[HEAD_LENGTH] = "";
	//���ļ�
	FILE* fStu = OpenFile(FilePath, "r", ReadHead);
	//�����Ƿ�ʧ��
	CHECK_NULL(fStu)

	//memcmp����ļ�ͷ�Ƿ�ƥ��
	if (memcmp(ReadHead, HeadString, HEAD_LENGTH) != 0) {
		//��ƥ�����������Ϣ�˳�
		printf("Error: File head is Uncompatible! Suspect invation.\n");
		return -1;
	}
	//����NumOfStudent���������ڴ�
	fread(&NumOfStudents, sizeof(int), 1, fStu);
	//����Ԥ����ֱ�Ӻ���Ŀ���
	AllocNumOfStu = NumOfStudents;

	//�����ڴ�
	AllStus = (Student*)malloc(sizeof(Student) * NumOfStudents);
	CHECK_NULLANY(AllStus, //����������˳�
		printf("Error: Failed to alloc memory.Allocing:%d * %d\n", NumOfStudents, (int)sizeof(Student));return -2;)
	
	//��һ��ѭ����������Students��Ϣƴ�ճ�Student
	for (int a = 0; a < NumOfStudents; a++) {
		//����ID
		fread(&AllStus[a].Id, sizeof(StuID), 1, fStu);
		//��������
		ReadString(fStu, &AllStus[a].name);
		//����ѧ����Ϣ
		fread(&AllStus[a].Inf.Sex, sizeof(sex), 1, fStu);
		fread(&AllStus[a].Inf.Birthday, sizeof(Date), 1, fStu);
		ReadString(fStu, &AllStus[a].Inf.Hometown);
		ReadString(fStu, &AllStus[a].Inf.IDCard);
		ReadString(fStu, &AllStus[a].Inf.Mail);
		ReadString(fStu, &AllStus[a].Inf.PhoneNumber);
		ReadString(fStu, &AllStus[a].Inf.Photo);
	}
	//�ر��ļ�
	fclose(fStu);
	return 0;
}

int SaveStudentToFile(const char* FilePath)
{
	//�ȴ򿪱����ļ��ľ��
	FILE* fStu = SaveFile(FilePath, HeadString);
	CHECK_NULL(fStu)//���򿪳ɹ�û

	//��ȡ��Чѧ���������������
	int RealNum = GetNumOfStudents();
	//��д��һ��ѧ����Ŀ
	fwrite(&RealNum, sizeof(int), 1, fStu);

	//�ô�ѭ��д��ѧ����Ϣ
	for (int a = 0; a < NumOfStudents; a++) {
		if (!AllStus->remove) {//�ж��Ƿ���ɾ��ѧ����ɾ���ľͱ�д����
			//����Ĳ���ע��Ҳ�ܿ�����
			int l = 0;
			fwrite(&AllStus[a].Id, sizeof(StuID), 1, fStu);

			WriteString(fStu, AllStus[a].name);

			fwrite(&AllStus[a].Inf.Sex, sizeof(sex), 1, fStu);
			fwrite(&AllStus[a].Inf.Birthday, sizeof(Date), 1, fStu);
			WriteString(fStu, AllStus[a].Inf.Hometown);
			WriteString(fStu, AllStus[a].Inf.IDCard);
			WriteString(fStu, AllStus[a].Inf.Mail);
			WriteString(fStu, AllStus[a].Inf.PhoneNumber);
			WriteString(fStu, AllStus[a].Inf.Photo);
		}
	}
	//�ر��ļ�
	fclose(fStu);
	//����AllStus�Ա��´�LoadStudentsFrom File��Ҫ���
	free(AllStus);
	AllStus = NULL;
	NumOfStudents = 0;
	AllocNumOfStu = 0;

	return 0;
}

/**�ṹ������򻯺���**/
StudentInformation MakeStudentInformation(sex _sex,Date birthday,const char* hometown,
	const char* idcard, const char* mail, const char* PhoneNumber, const char* Photo)
{
	//�ȴ�����������ʱ����StuInf
	StudentInformation StuInf = { other };
	int len = 0;//len������ʾ�ַ�������
	StuInf.Sex = _sex;//��ֱ�Ӹ�ֵ�ȸ�ֵ
	StuInf.Birthday = birthday;

	/**
	�������֣����ֱ�� = ��ֵ������ַ����׵�ַ��ֵ��ȥ����������Ҫ�����ַ�������
	����Ҫ�ȸ����ַ������ȣ�strlen�������ڴ棬Ȼ����memcpy��ֵ��memcpy����֪���Ȼ��Կ���strcpy��
	**/
	len = strlen(hometown) + 1;
	StuInf.Hometown = (char*)calloc(len, sizeof(char));
	CHECK_NULLANY(StuInf.Hometown,return StuInf)
	memcpy(StuInf.Hometown, hometown, len);
	//�����ͬ��
	len = strlen(idcard) + 1;
	StuInf.IDCard = (char*)calloc(len, sizeof(char));
	CHECK_NULLANY(StuInf.IDCard, return StuInf)
	memcpy(StuInf.IDCard, idcard, len);

	len = strlen(mail) + 1;
	StuInf.Mail = (char*)calloc(len, sizeof(char));
	CHECK_NULLANY(StuInf.Mail, return StuInf)
	memcpy(StuInf.Mail, mail, len);

	len = strlen(PhoneNumber) + 1;
	StuInf.PhoneNumber = (char*)calloc(len, sizeof(char));
	CHECK_NULLANY(StuInf.PhoneNumber, return StuInf)
	memcpy(StuInf.PhoneNumber, PhoneNumber, len);

	len = strlen(Photo) + 1;
	StuInf.Photo = (char*)calloc(len, sizeof(char));
	CHECK_NULLANY(StuInf.Photo, return StuInf)
	memcpy(StuInf.Photo, Photo, len);
	/**
	��󷵻ص���StuInf�����ص�ʱ��ᴴ��StuInf���ڴ渱����Ȼ�����ڵ�StuInf�ᱻ������
	�����µ�StuInf�ᱻ���أ����ڼ�ֻ���ַ���ָ�뱾��ת���ˣ��ַ����������ڴ��в���Ӱ��
	**/
	return StuInf;
}

void DeConstructStudentInformation(StudentInformation *StuInf)
{
	//ȫfree��������ֱ�Ӷ���StuInf����Ķ�̬�����ַ��������Զ����٣����ڴ�й©
	free(StuInf->Hometown);
	free(StuInf->IDCard);
	free(StuInf->Mail);
	free(StuInf->PhoneNumber);
	free(StuInf->Photo);
}

Student MakeStudent(StudentInformation StuInf,const char* name, const StuID NewID)
{
	//��ϸ�������ο�MakeStudentInformation
	Student Stu = { 0 };
	if (NewID < 1) {//�ж�StuID�Ϸ���
		return Stu;
	}
	//ֱ�Ӹ�ֵ
	Stu.Id = NewID;
	Stu.name = (char*)calloc(strlen(name) + 1, sizeof(char));
	CHECK_NULLANY(Stu.name,return Stu)
	strcpy(Stu.name, name);
	Stu.Inf = StuInf;//�������ֱ�Ӹ�ֵ����Ϊ�ṹ��ֱ�Ӵ�����ȥ�ˣ��൱���ǰ��ַ���ָ�봫�ݹ�ȥ��
	return Stu;
}

void DeConstructStudent(Student* student)
{
	//��DeConstructStudentInformation
	DeConstructStudentInformation(&student->Inf);
	free(student->name);
}

/**AllStus���ݿ��������**/
int GetNumOfStudents()
{
	//�ų�����removed��ѧ��
	int removed = 0;
	for (int a = 0; a < NumOfStudents; a++) {//����AllStus
		if (AllStus[a].remove == true) {//ֻҪ����remove��ʶ�Զ���remove��һ
			removed++;
		}
	}
	return NumOfStudents - removed;//�ܳ�-ɾ������Ŀ=��Ч����
}

StuID NewStudent(Student* NewStu)
{
	//�ȼ��StuID�Ϸ���
	if (NewStu->Id < 1) {
		return -1;
	}
	//��һ�бȽ�����⣬��ο�CHECK_NULLANY��һ�𿴣��������˼���������AllStus��û����ͷ����ڴ�
	CHECK_NULLANY(AllStus, //��һ�����ж�NULL������Ҳ�����ж�AllStus�Ƿ�Ϊ��
		AllStus = (Student*)calloc(MinAllocSize, sizeof(Student)); //���������жϽ��ִ�У�Ҳ�������Ϊ����ô��ʲô
	AllocNumOfStu += MinAllocSize;)//һ�η���һ��MinAllocSize��С
	else {//�������ú�չ��ֱ�ӽ��ϣ���ʾAllStus��Ϊ������

		//���Ԥ����洢�Ѿ��ľ����ͼ���������
		if (NumOfStudents >= AllocNumOfStu) {
			Student* NewStus = (Student*)realloc(AllStus, sizeof(Student) * ((long)AllocNumOfStu + MinAllocSize));
			CHECK_NULLANY(NewStus, 
				printf("Error: Failed to alloc memory.Allocing:%d * %d\n", AllocNumOfStu + MinAllocSize, (int)sizeof(Student));
			return -1;)//�ж��ڴ����ʧ�ܷ�

			//realloc�������ɹ����Ͱ�AllStus��Ϊ�·����NewStus���ɵ�AllStus�ᱻrealloc�Զ�����
			AllStus = NewStus;
			//�ѷ����С�ǵü���
			AllocNumOfStu += MinAllocSize;
		}
	}

	//��һ�����Ǹ���ѧ�����
	Student* astu = NULL;
	//�����ж�ѧ�������غ�
	for (int i = -1; (astu = IterateStudent(&i)) != NULL;) {//IterateStudent����ѧ��
		if (astu->Id == NewStu->Id) {//һ�����ֺ������غţ�ֱ��return
			return -2;
		}
	}
	//û����Ļ�������ĩβ���µ�Student���ƹ�ȥ
	memcpy(AllStus + (NumOfStudents), NewStu, sizeof(Student));
	NumOfStudents++;//ѧ��������һ
	//����ID
	return AllStus->Id;
}

StuID DeleteStudent(StuID Id)
{
	Student* TheStu = SeekStudent(Id);//��Ѱ�����ѧ��������������Student�ṹ���ַ
	CHECK_NULL(TheStu)//�ж��ҵ���
	TheStu->remove = true;//��ɾ��λ��һ
	return TheStu->Id;//����ID
}

Student* SeekStudent(StuID SeekStu)
{
	//���ж�AllStus��û�з��䣬������ʿ�ָ��
	CHECK_NULLPTR(AllStus)
	if (SeekStu < 1) {//���StuID�Ϸ���
		return NULL;
	}
	for (int a = 0; a < NumOfStudents; a++) {//����AllStus
		if (AllStus[a].Id == SeekStu && AllStus[a].remove==false) {//����ҵ���ѧ�����Ҳ�����ɾ��ѧ��
			return AllStus+a;//ֱ�ӷ����������е�ַ
		}
	}
	return NULL;//�Ҳ������ؿ�
}

inline Student* IterateStudent(int* Index)
{
	for ((*Index)++;//Index��������������ʾ����һ��ѧ��������һ��
		AllStus[*Index].remove == true && *Index<NumOfStudents; //Ȼ���ж���һ����û�б�ɾ����Index��û�г���AllStus����
		(*Index)++);//�����ɾ����ôforѭ������������Index����һ��

	//���forѭ������Ҫô�ҵ��ˣ�Ҫô������
	if (*Index >= NumOfStudents) {//�ж��ǲ���������
		return NULL;
	}
	//ֱ�ӷ����������е�ַ
	return AllStus + *Index;
}
