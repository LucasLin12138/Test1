#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "s_gets.h"
#include "clean.h" 

#define FLIGHT 4
#define PASSENGER 12
#define LEN 20
#define STARBAR_1 "*********************************************"
#define STARBAR_2 "............................................."

struct airline {
	int seat_num;
	bool reserved;
	char lname[LEN];
	char fname[LEN];
} info[FLIGHT][PASSENGER];
typedef struct airline areo;

char seat_alpha[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L' };

void menu_1(void);
void menu_2(int flight);
void inv_input(void);

void num_of_emp(areo info[]);
void list_of_emp(areo info[]);
void alpha_list_of_seat(areo info[]);
void assign(areo info[]);
void _delete(areo info[]);
void (*pfun)(areo info[]);
//void info_init(areo info[][12]);

int main(void)
{
	char choice_1, choice_2;
	int flight[FLIGHT] = { 102, 311, 444, 519 };
	
	menu_1();
	
	choose_1:
	puts("Enter your choice:");
	while ((choice_1 = getchar()) != 'f')
	{
		clean();
		
		switch(tolower(choice_1))
		{
			case 'a':
				choice_1 = 0;
				break;
			case 'b':
				choice_1 = 1;
				break;
			case 'c':
				choice_1 = 2;
				break;
			case 'd':
				choice_1 = 3;
				break;
			default:
				inv_input(); 
				goto choose_1;
		}
		
		menu_2(flight[choice_1]);
		
		choose_2:
		puts("Enter your choice:");
		while ((choice_2 = getchar()) != 'f')
		{
			clean();
			
			switch(tolower(choice_2))
			{
				case 'a':
					pfun = num_of_emp;
					break;
				case 'b':
					pfun = list_of_emp;
					break;
				case 'c':
					pfun = alpha_list_of_seat;
					break;
				case 'd':
					pfun = assign;
					break;
				case 'e':
					pfun = _delete;
					break;
				default:
					inv_input();
					goto choose_2;
			}
			pfun(info[choice_1]);
			
			menu_2(flight[choice_1]);
			puts("Enter your choice again.");
		}
		clean();
		
		menu_1();
		puts("Enter your choice again.");
	}
	clean();
	
	puts("Bye!");
	
	return 0;
}

//一级菜单 
void menu_1(void)
{
	puts(STARBAR_1);
	puts("* To choose a flight, enter its letter label:");
	puts("* a)102");
	puts("* b)311");
	puts("* c)444");
	puts("* d)519");
	puts("* f)quit");
	puts(STARBAR_1);
	
	return;
}

//二级菜单 
void menu_2(int flight)
{
	puts(STARBAR_1);
	printf("* Flight code: %d\n", flight);
	puts("* To choose a function, enter its letter label:");
	puts("* a)Show number of empty seats");
	puts("* b)Show list of empty seats");
	puts("* c)Show alphabetical list of seats");
	puts("* d)Assign a customer to a seat assignment");
	puts("* e)Delete a seat assignment");
	puts("* f)Quit");
	puts(STARBAR_1);
	
	return;
}

//输入报错
void inv_input(void)
{
	puts("Invalid input, please try again.");
} 

//打印空位的数量 
void num_of_emp(areo info[])
{
	int index, count;
	
	for (index = 0, count = 0; index < 12; index++)
	{
		if (info[index].reserved == false)
		{
			count++;
		}
	}
	printf("%d empty seats scanned.\n", count);
	
	return;
}

//以数字排列的座位列表 
void list_of_emp(areo info[])
{
	int index;
	
	putchar('\n');
	for (index = 0; index < 12; index++)
	{
		if (info[index].reserved == false)
		{
			printf("Seat %d is empty.\n", index + 1);
		}
		else
		{
			printf("Seat %d is reserved for %s %s.\n", index + 1, info[index].fname, info[index].lname);
		}
	}
	putchar('\n');
	
	return;
}

//以字母排列的空位列表 
void alpha_list_of_seat(areo info[])
{
	int index;
	
	putchar('\n');
	for (index = 0; index < 12; index++)
	{
		if (info[index].reserved == false)
		{
			printf("Seat %c is empty.\n", seat_alpha[index]);
		}
		else
		{
			printf("Seat %c is reserved for %s %s.\n", seat_alpha[index], info[index].fname, info[index].lname);
		}
	}
	putchar('\n');
	
	return;
}

//为乘客预订一个座位 
void assign(areo info[])
{
	int count, temp;
	char choice[LEN];

	//座位输入 
	choose_1:
	puts(STARBAR_2);
	puts("Which seat do you want? (enter EOF to quit)");
	while (scanf("%s", choice) == 1 && choice[0] != EOF)
	{
		clean();
		temp = atoi(choice);
		count = temp - 1;

		if (temp == 0)//输入为字符	
		{
			choice[0] = toupper(choice[0]);//将输入的字符转换为大写字母 
			
			if (choice[0] <= 'L' && choice[0] >= 'A')//输入的字符合法	
			{
				for (count = 0; seat_alpha[count] != choice[0]; count++);//确定输入的字符为哪个
				
				if (info[count].reserved != true)//预订成功
				{
					info[count].reserved = true;
					printf("Seat %c reserved for you successfully!\n", seat_alpha[count]);
					goto choose_2;
				}
				
				else//预订失败
				{
					printf("Seat %c has been reserved, please try again.\n", seat_alpha[count]);
					goto choose_1;
				}
			}
			
			else//输入的字符非法
			{
				inv_input();
				goto choose_1;
			}
		}

		else//输入为数字
		{
			if (count >= 0 && count <= 11)//输入的数字合法
			{
				if (info[count].reserved != true)//预订成功 
				{
					info[count].reserved = true;
					printf("Seat %d reserved for you successfully!\n", temp);
					goto choose_2;
				}
				
				else//预订失败
				{
					printf("Seat %d has been reserved, please try again.\n", temp);
					goto choose_1;	
				}
			}
			
			else//输入的数字非法
			{
				inv_input();
				goto choose_1;	
			}
		}
	}
	return;
	
	//姓名输入 
	choose_2:
	puts(STARBAR_2);
	puts("What's your name? (enter EOF to quit)");
	if (scanf("%s", info[count].fname) == 1 && info[count].fname[0] != EOF)
	{
		scanf("%s", info[count].lname);
		clean();
		printf("%s %s, Seat %d/%c now is successfully reserved for you.\n",info[count].fname, info[count].lname, count + 1, seat_alpha[count]);
		return;
	}
	
	else
	{
		info[count].reserved = false;
		return;
	}
	
	return;
}

//删除一个座位预订 
void _delete(areo info[])
{
	int temp, count;
	char choice[LEN];
	
	choose:
	puts(STARBAR_2);
	puts("Which seat reservation do you want to delete? (enter EOF to quit)");
	while (scanf("%s", choice) == 1 && choice[0] != EOF)
	{
		clean();
		temp = atoi(choice);
		count = temp - 1;
		
		//字符输入 
		if (temp == 0)
		{
			choice[0] = toupper(choice[0]);
			
			if (choice[0] >= 'A' && choice[0] <= 'L')
			{
				for (count = 0; choice[0] != seat_alpha[count]; count++);
				
				if (info[count].reserved != false)
				{
					info[count].reserved = false;
					printf("Seat %c reserved for %s %s has been delete.\n", seat_alpha[count], info[count].fname, info[count].lname);
					return;
				}
				
				else
				{
					printf("Seat %c is empty, please try again.\n", seat_alpha[count]);
					goto choose;
				}
			}
			
			else
			{
				inv_input();
				goto choose;
			}
		}
		
		else
		{
			if (count >= 0 && count <= 11)
			{
				if (info[count].reserved != false)
				{
					info[count].reserved = false;
					printf("Seat %d reserved for %s %s has been delete.\n", count + 1, info[count].fname, info[count].lname);
					return;
				}
				
				else
				{
					printf("Seat %d is empty, please try again.\n", temp);
					goto choose;
				}
			}
			
			else
			{
				inv_input();
				goto choose;
			}
		}
	}

	return;
}
