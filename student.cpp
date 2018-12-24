#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <io.h>			//该头文件包含用于存储文件信息的结构体和读取文件的各种操作。

typedef struct Course
{
	char course[10];		//课程名称
	int score;				//课程分数
}Course;

typedef struct stu
{
	int stu_id;				//学生的学号
	char name[10];			//学生姓名
	int classnum;			//班级
	int grade;				//年级
	int num;				//课程数目
	Course cour[10];		//修的课程
	struct stu *next;
}STU;

void AddStudent();				    		//添加学生信息
void DelStudent();							//删除学生信息
void AddCourse();							//为指定学生添加指定的课程
void AddCoursePro(char *path, char *course);//对指定的文件加入新课程
void DelCourse();							//删除指定学生的指定课程
void DelCoursePro(char *path, char *course);//对指定的文件删除新课程
void AddAllCourse();						//为所有学生添加指定课程
void DelAllCourse();						//删除所有学生的指定课程

void GiveStuScore();						//给某学生某门课的成绩
void CountScore();							//查询某课程及格率和平均分数											
void PrintCourse();							//查看所有学生某门课的成绩

void StuMessage();							//学生信息查询

void dirhandle(STU *head);					//对data文件夹下文件进行读取，并将数据串入链表


//------------------------------------------以管理员权限运行-----------------------------------

void AddStudent()				//添加学生信息
{
	STU stu;
	int i;

	//提示输入操作
	printf("\n\t请输入学号：");
	scanf_s("%d", &stu.stu_id);
	//更新学生登陆账号密码
	FILE *fpstu;
	fopen_s(&fpstu, "password/students.data", "a");
	fprintf(fpstu, "\n%d\n", stu.stu_id);
	fprintf(fpstu, "%d\n", stu.stu_id);
	fclose(fpstu);

	printf("\t请输入姓名：");
	scanf_s("%s", stu.name, 10);
	printf("\t请输入班级：");
	scanf_s("%d", &stu.classnum);
	printf("\t请输入年级：");
	scanf_s("%d", &stu.grade);
	printf("\t请输入课程数目：");
	scanf_s("%d", &stu.num);
	for (i = 1; i <= stu.num; i++)
	{
		printf("\t请输入该学生的第%d个课程名：", i);
		scanf_s("%s", stu.cour[i].course, 10);
		printf("\t请输入该学生第%d个课程成绩：", i);
		scanf_s("%d", &stu.cour[i].score);
	}

	//创建文件名称
	char path[20] = "data/";
	char filename[20];
	//将数字转化成字符
	snprintf(filename, sizeof(filename), "%d", stu.stu_id);
	//设置文件路径
	strcat_s(filename, ".data");
	strcat_s(path, filename);

	//文件打开
	FILE *fp;
	fopen_s(&fp, path, "w");
	if (!fp)
	{
		printf("Cannot open this file\n");
		exit(1);
	}
	//将数据读入文件
	fprintf(fp, "%d\n", stu.stu_id);
	fprintf(fp, "%s\n", stu.name);
	fprintf(fp, "%d\n", stu.classnum);
	fprintf(fp, "%d\n", stu.grade);
	fprintf(fp, "%d\n", stu.num);
	for (i = 1; i <= stu.num; i++)
	{
		fprintf(fp, "%s\n", stu.cour[i].course);
		fprintf(fp, "%d\n", stu.cour[i].score);
	}
	//关闭文件
	fclose(fp);
	printf("\n    该学生已经添加完毕！！！,两秒钟后自动跳转！！");
	Sleep(2000);
	while ((getchar()) != '\n');

	return;
}

void DelStudent()			//删除学生信息
{
	STU stu;

	printf("\n\t请输入学号：");
	scanf_s("%d", &stu.stu_id);

	//创建文件名称
	char path[20] = "data/";
	char filename[20];
	//将数字转化成字符
	snprintf(filename, sizeof(filename), "%d", stu.stu_id);
	//设置文件路径
	strcat_s(filename, ".data");
	strcat_s(path, filename);

	if(remove(path) == 0)
		printf("\n    已经删除该学生的信息，");
	else
		printf("Removed Error\n");

	printf("两秒钟后自动跳转！！\n");
	Sleep(2000);
	while ((getchar()) != '\n');
	return;
}

void AddCourse()					//为指定学生添加指定的课程
{
	int num, id;
	printf("\n\t请输入学号：");
	scanf_s("%d", &id);

	//创建文件名称
	char path[20] = "data/";
	char filename[20];
	//将数字转化成字符
	snprintf(filename, sizeof(filename), "%d", id);
	//设置文件路径
	strcat_s(filename, ".data");
	strcat_s(path, filename);

	char course[10][10];
	printf("\n\t请输入你要添加的课程数目：");
	scanf_s("%d", &num);
	for (int i = 0; i < num; i++)
	{
		printf("\n\t请输入要添加的课程%d：", i+1);
		scanf_s("%s", course[i], 10);
		AddCoursePro(path, course[i]);
	}
	printf("\n\t    课程添加成功，两秒钟后自动跳转！！\n");
	Sleep(2000);
	while ((getchar()) != '\n');
	return;
}

void AddCoursePro(char *path, char *course)				//对指定的文件加入新课程
{
	STU stu;
	int i;

	//文件打开
	FILE *fp;
	fopen_s(&fp, path, "r");
	if (!fp)
	{
		printf("Cannot open this file\n");
		exit(1);
	}
	//创建新文件，打开新文件
	FILE *fpnew;
	fopen_s(&fpnew, "data/tmp.data", "w");
	if (!fp)
	{
		printf("Cannot open this file\n");
		exit(1);
	}

	//将原来的数据读入到内存
	fscanf_s(fp, "%d\n", &stu.stu_id);
	fscanf_s(fp, "%s\n", stu.name, 10);
	fscanf_s(fp, "%d\n", &stu.classnum);
	fscanf_s(fp, "%d\n", &stu.grade);
	fscanf_s(fp, "%d\n", &stu.num);
	for (i = 1; i <= stu.num; i++)
	{
		fgets(stu.cour[i].course, 10, fp);
		stu.cour[i].course[strlen(stu.cour[i].course) - 1] = '\n';
		fscanf_s(fp, "%d\n", &stu.cour[i].score);
	}
	//将原来的数据从内存传入新文件
	fprintf(fpnew, "%d\n", stu.stu_id);
	fprintf(fpnew, "%s\n", stu.name);
	fprintf(fpnew, "%d\n", stu.classnum);
	fprintf(fpnew, "%d\n", stu.grade);
	fprintf(fpnew, "%d\n", stu.num + 1);
	for (i = 1; i <= stu.num; i++)
	{
		fprintf(fpnew, "%s", stu.cour[i].course);
		fprintf(fpnew, "%d\n", stu.cour[i].score);
	}
	fprintf(fpnew, "%s\n", course);
	fprintf(fpnew, "%d\n", 0);

	//关闭文件
	fclose(fp);
	fclose(fpnew);

	//删除原文件，将新文件命名为filename
	if (remove(path))
		printf("Removed Error\n");
	rename("data/tmp.data", path);

	printf("\n\t    课程添加成功，一秒钟后自动跳转！！\n");
	Sleep(1000);
}

void DelCourse()					//删除指定学生的指定课程
{
	int i, num, id;
	printf("\n\t请输入学号：");
	scanf_s("%d", &id);

	//创建文件名称
	char path[20] = "data/";
	char filename[20];
	//将数字转化成字符
	snprintf(filename, sizeof(filename), "%d", id);
	//设置文件路径
	strcat_s(filename, ".data");
	strcat_s(path, filename);

	char course[10][10];
	printf("\n\t请输入你要删除的课程数目：");
	scanf_s("%d", &num);
	for (i = 0; i < num; i++)
	{
		printf("\n\t请输入要删除的课程%d：", i + 1);
		scanf_s("%s", course[i], 10);
		DelCoursePro(path, course[i]);
	}
	printf("\n\t    课程添加成功，两秒钟后自动跳转！！\n");
	Sleep(2000);
	while ((getchar()) != '\n');
	return;
}

void DelCoursePro(char *path, char *course)
{
	STU stu;
	int i;

	//文件打开
	FILE *fp;
	fopen_s(&fp, path, "r");
	if (!fp)
	{
		printf("Cannot open this file\n");
		exit(1);
	}
	//创建新文件，打开新文件
	FILE *fpnew;
	fopen_s(&fpnew, "data/tmp.data", "w");
	if (!fpnew)
	{
		printf("Cannot open this file\n");
		exit(1);
	}

	//将原来的数据读入到内存
	fscanf_s(fp, "%d\n", &stu.stu_id);
	fscanf_s(fp, "%s\n", stu.name, 10);
	fscanf_s(fp, "%d\n", &stu.classnum);
	fscanf_s(fp, "%d\n", &stu.grade);
	fscanf_s(fp, "%d\n", &stu.num);
	for (i = 1; i <= stu.num; i++)
	{
		//fgets(stu.cour[i].course, 10, fp);
		//以fgets读取的会将空格，换行符读入
		fscanf_s(fp, "%s\n", stu.cour[i].course, 10);
		fscanf_s(fp, "%d\n", &stu.cour[i].score);
	}
	//将原来的数据从内存传入新文件
	fprintf(fpnew, "%d\n", stu.stu_id);
	fprintf(fpnew, "%s\n", stu.name);
	fprintf(fpnew, "%d\n", stu.classnum);
	fprintf(fpnew, "%d\n", stu.grade);
	//对课程数目进行处理
	for (i = 1; i <= stu.num; i++)
	{
		if (strcmp(stu.cour[i].course, course) == 0)
		{
			fprintf(fpnew, "%d\n", stu.num - 1);
			break;
		}
	}
	if(i == stu.num + 1)
		fprintf(fpnew, "%d\n", stu.num);
	//将删除后的课程名以及对应分数写入新文件
	for (i = 1; i <= stu.num; i++)
	{
		if (strcmp(stu.cour[i].course, course) == 0)
			continue;			
		fprintf(fpnew, "%s\n", stu.cour[i].course);
		fprintf(fpnew, "%d\n", stu.cour[i].score);
	}

	//关闭文件
	fclose(fp);
	fclose(fpnew);

	//删除原文件，将新文件命名为filename
	if (remove(path))
		printf("Removed Error\n");
	else
		rename("data/tmp.data", path);

	printf("\n\t    课程删除成功，一秒钟后自动跳转！！\n");
	Sleep(1000);
}

void AddAllCourse()					//为所有学生添加指定课程
{
	STU *p, *head;
	head = (STU *)malloc(sizeof(STU));
	dirhandle(head);
	p = head->next;

	//得到输入
	char course[10];
	printf("\n\t请输入你想为所有人添加的课程：");
	scanf_s("%s", course, 10);

	char path[25] = "data/";
	char filename[20];

	while (p != NULL)
	{
		//设置文件路径
		snprintf(filename, sizeof(filename), "%d", p->stu_id);//将数字转化成字符
		strcat_s(filename, ".data");
		strcat_s(path, filename);

		AddCoursePro(path, course);

		strcpy_s(path, "data/");
		p = p->next;
	}

	printf("\n\t所有人的课程全部添加成功，两秒钟后自动跳转！！\n");
	Sleep(2000);
	while ((getchar()) != '\n');

	return ;
}

void DelAllCourse()					//删除所有学生的指定课程
{
	STU *p, *head;
	head = (STU *)malloc(sizeof(STU));
	dirhandle(head);
	p = head->next;

	//得到输入
	char course[10];
	printf("\n\t请输入你想为所有人删除的课程：");
	scanf_s("%s", course, 10);

	char path[25] = "data/";
	char filename[20];

	while (p != NULL)
	{
		//设置文件路径
		snprintf(filename, sizeof(filename), "%d", p->stu_id);//将数字转化成字符
		strcat_s(filename, ".data");
		strcat_s(path, filename);

		DelCoursePro(path, course);

		strcpy_s(path, "data/");
		p = p->next;
	}

	printf("\n\t所有人的课程全部删除成功，两秒钟后自动跳转！！\n");
	Sleep(2000);
	while ((getchar()) != '\n');

	return;
}

//--------------------------------------------------------------------------------------

//-------------------------------------以教师权限运行------------------------------------

void GiveStuScore()			//给某学生某门课的成绩
{
	int i, id, score;
	char course[10];
	printf("\n\t请输入该学生的学号：");
	scanf_s("%d", &id);
	printf("\n\t请输入要赋分的课程：");
	scanf_s("%s", course, 10);
	printf("\n\t请输入该课程的分数：");
	scanf_s("%d", &score);

	//创建文件名称
	char path[20] = "data/";
	char filename[20];
	//将数字转化成字符
	snprintf(filename, sizeof(filename), "%d", id);
	//设置文件路径
	strcat_s(filename, ".data");
	strcat_s(path, filename);

	//文件打开
	FILE *fp;
	fopen_s(&fp, path, "r");
	if (!fp)
	{
		printf("Cannot open this file\n");
		exit(1);
	}
	//创建新文件，打开新文件
	FILE *fpnew;
	fopen_s(&fpnew, "data/tmp.data", "w");
	if (!fp)
	{
		printf("Cannot open this file\n");
		exit(1);
	}

	STU stu;
	//将原来的数据读入到内存
	fscanf_s(fp, "%d\n", &stu.stu_id);
	fscanf_s(fp, "%s\n", stu.name, 10);
	fscanf_s(fp, "%d\n", &stu.classnum);
	fscanf_s(fp, "%d\n", &stu.grade);
	fscanf_s(fp, "%d\n", &stu.num);
	for (i = 1; i <= stu.num; i++)
	{
		fscanf_s(fp, "%s\n", stu.cour[i].course, 10);
		fscanf_s(fp, "%d\n", &stu.cour[i].score);
	}
	//将原来的数据从内存传入新文件
	fprintf(fpnew, "%d\n", stu.stu_id);
	fprintf(fpnew, "%s\n", stu.name);
	fprintf(fpnew, "%d\n", stu.classnum);
	fprintf(fpnew, "%d\n", stu.grade);
	fprintf(fpnew, "%d\n", stu.num);
	for (i = 1; i <= stu.num; i++)
	{
		if (strcmp(stu.cour[i].course, course))
		{
			fprintf(fpnew, "%s\n", stu.cour[i].course);
			fprintf(fpnew, "%d\n", stu.cour[i].score);
		}
		else
		{
			fprintf(fpnew, "%s\n", stu.cour[i].course);
			fprintf(fpnew, "%d\n", score);
		}	
	}

	//关闭文件
	fclose(fp);
	fclose(fpnew);

	//删除原文件，将新文件命名为filename
	if (remove(path))
		printf("Removed Error\n");
	rename("data/tmp.data", path);

	printf("\n\t为该学生给分成功，两秒钟后自动跳转！！\n");
	Sleep(2000);
	while ((getchar()) != '\n');
	return;
}

void CountScore()				//查询某课程及格率和平均分数
{
	int num = 0, score = 0, high_num = 0;
	double pass_rate, average_score;	//及格率，平均分数

	char course[10];
	printf("\n\t请输入要统计的课程：");
	scanf_s("%s", course, 10);

	STU *p, *head;
	head = (STU *)malloc(sizeof(STU));
	dirhandle(head);
	p = head->next;

	//遍历链表
	while (p != NULL)
	{
		for (int i = 1; i <= p->num; i++)
		{
			if (!strcmp(p->cour[i].course, course))
			{
				num ++;
				score += p->cour[i].score;
				if (p->cour[i].score >= 60)
					high_num ++;
			}
		}
		p = p->next;
	}
	//处理数据
	pass_rate = (double)high_num / num;
	average_score = (double)score / num;
	printf("\n\t%s课程及格率是：%.2lf", course, pass_rate);
	printf("\n\t%s课程平均分是：%.2lf", course, average_score);

	printf("\n\n\t");
	system("pause");
	while ((getchar()) != '\n');		
	return;
}

void PrintCourse()				//查看所有学生某门课的成绩
{
	char course[10];
	printf("\n\t请输入要统计的课程：");
	scanf_s("%s", course, 10);

	STU *p, *head;
	head = (STU *)malloc(sizeof(STU));
	dirhandle(head);
	p = head->next;

	printf("\n\t  学号      姓名       分数\n");
	//遍历链表
	while (p != NULL)
	{
		for (int i = 1; i <= p->num; i++)
		{
			if (!strcmp(p->cour[i].course, course))
			{
				printf("\n\t%8d   %-10s   %d\n", p->stu_id, p->name, p->cour[i].score);
			}
		}
		p = p->next;
	}

	printf("\n\n\t");
	system("pause");
	while ((getchar()) != '\n');
	return;
}

//---------------------------------------------------------------------------------------

//--------------------------------------以学生权限运行------------------------------------

void StuMessage()						//学生信息查询
{
	STU stu;
	int i;

	//输入学号
	printf("\n\t请输入您的学号：");
	scanf_s("%d", &stu.stu_id);
	//创建文件路径及名称
	char path[20] = "data/";
	char filename[15];
	snprintf(filename, sizeof(filename), "%d", stu.stu_id);//将数字转化成字符
	strcat_s(filename, ".data");
	strcat_s(path, filename);

	//打开文件
	FILE *fp;
	fopen_s(&fp, path, "r");
	if (!fp)
	{
		printf("Cannot open this file\n");
		exit(1);
	}
	//读取文件中内容到内存
	fscanf_s(fp, "%d\n", &stu.stu_id);
	fscanf_s(fp, "%s\n", stu.name, 10);
	fscanf_s(fp, "%d\n", &stu.classnum);
	fscanf_s(fp, "%d\n", &stu.grade);
	fscanf_s(fp, "%d\n", &stu.num);
	for (i = 1; i <= stu.num; i++)
	{
		fgets(stu.cour[i].course, 10, fp);
		fscanf_s(fp, "%d\n", &stu.cour[i].score);
	}
	//关闭文件
	fclose(fp);

	printf("\n\t\t您的信息如下：\n\n");
	printf("\t学号：%d\n", stu.stu_id);
	printf("\t姓名：%s\n", stu.name);
	printf("\t班级：%d班\n", stu.classnum);
	printf("\t年级：%d级\n", stu.grade);
	printf("\t您一共学了%d门课\n", stu.num);
	for (i = 1; i <= stu.num; i++)
	{
		printf("\t   第%d门课是：%s", i, stu.cour[i].course);
		printf("\t   该课的分数是：%d\n\n", stu.cour[i].score);
	}

	printf("\n\t按任意键继续！！");
	while ((getchar()) != '\n');
	_kbhit();
	return;
}

//---------------------------------------------------------------------------------------

void dirhandle(STU *head)
{
	//初始化链表的尾节点
	STU *rear, *s;
	rear = head;

	char filename[50][15];

	//文件存储信息结构体 
	struct _finddata_t fileinfo;
	//保存文件句柄 
	long fHandle;
	//文件数记录器
	int filenum = 0;
	//读取文件夹下文件
	if ((fHandle = _findfirst("data/*.data", &fileinfo)) == -1L)
	{
		printf("\n\tdata目录下没有学生数据文件\n");
	}
	//存储读取到的文件名
	do {
		strcpy_s(filename[filenum], fileinfo.name);
		filenum++;
	} while (_findnext(fHandle, &fileinfo) == 0);

	//对文件进行操作
	FILE *fp;
	char path[25] = "data/";
	for (int i = 0; i<filenum; i++)
	{
		//打开文件
		strcat_s(path, filename[i]);
		fopen_s(&fp, path, "r");
		strcpy_s(path, "data/");
		if (!fp)
		{
			printf("Cannot open %s file\n", filename[i]);
			exit(1);
		}
		//将文件中内容存入链表
		s = (STU *)malloc(sizeof(STU));
		rear->next = s;
		rear = s;
		//将数据读入链表
		fscanf_s(fp, "%d\n", &s->stu_id);
		fscanf_s(fp, "%s\n", s->name, 10);
		fscanf_s(fp, "%d\n", &s->classnum);
		fscanf_s(fp, "%d\n", &s->grade);
		fscanf_s(fp, "%d\n", &s->num);
		for (int j = 1; j <= s->num; j++)
		{
			//fgets(s->cour[j].course, 10, fp);
			fscanf_s(fp, "%s\n", &s->cour[j].course, 10);
			fscanf_s(fp, "%d\n", &s->cour[j].score);
		}
		fclose(fp);
	}
	rear->next = NULL;

	//关闭文件句柄
	_findclose(fHandle);
}