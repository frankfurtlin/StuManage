#include <stdio.h>
#include "student.cpp"

void AdminOperate(char ch);						//管理员操作
void TeacherOperate(char ch);					//教师操作
void StudentOperate(char ch);					//学生操作

void AdminOperate(char ch)			//管理员操作
{
	switch(ch)
	{
		case '1':						//添加学生信息
		{
			AddStudent();
			break;
		}
		case '2':						//删除学生信息
		{
			
			DelStudent();
			break;
		}
		case '3':										//为指定学生添加指定的课程
		{
			AddCourse();
			break;
		}
		case '4':										//删除指定学生的指定课程
		{
			DelCourse();
			break;
		}
		case '5':										//为所有学生添加指定课程
		{
			AddAllCourse();
			break;
		}
		case '6':										//删除所有学生的指定课程
		{
			DelAllCourse();
			break;
		}
	}	
}

void TeacherOperate(char ch)			//教师操作
{
	while ((getchar()) != '\n');
	switch(ch)
	{
		case '1':					//为某个学生某门课给分
		{		
			GiveStuScore();
			break;
		}
		case '2':							//查看某门课及格率，平均分
		{
			CountScore();
			break;
		}
		case '3':									//查看某门课所有学生成绩
		{
			PrintCourse();
			break;
		}
	}
}

void StudentOperate(char ch)			//学生操作
{
	while ((getchar()) != '\n');	//查看我的信息
	if(ch == '1')
	{	
		StuMessage();	
	}
	while ((getchar()) != '\n');
}