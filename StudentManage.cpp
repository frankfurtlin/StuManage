#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.cpp"

int main()
{
	while(1)
	{
		Menu();				//显示初始菜单
		char c= getchar();
		while(c!= '1' && c!= '2' && c!= '3' && c!= '4')
		{
			printf("输入错误！！请再次输入！\n");
			fflush(stdin);
			c= getchar();
		}
		MenuChoice(c);			//对初始菜单进行处理
		system("cls");
	}

	system("pause");
	return 0;
}