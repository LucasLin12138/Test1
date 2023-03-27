#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 50
#define INT_PT_1 int*
#define INT_PT_2 int *

char *s_gets(char *st, int n);
char *(*sgets)(char*, int);

int main(void)
{
	char month[SIZE] = "123Motherfucker";
	printf("month = %d\n", atoi(month));
	printf("strcmp(\"Jan.\", \"Jan\") = %d\n", strcmp("Jan.", "Jan"));
	
	//sgets是一个指向函数的指针 
	//函数名即函数的地址 
	sgets = s_gets;
	char word[SIZE];
	sgets(word, SIZE);
	puts(word);
	
	//结构内不同部分用分号隔开 
	struct testpp {
		int title;
		float author;
	};
	
	struct testpp zzz;
	
	zzz.title = 100;
	zzz.author = 5.1;
	
	printf("zzz.title = %d, zzz.author = %.1f\n", zzz.title, zzz.author);
	
	struct name {
		char first[20];
		char last[20];
		int len;
	};
	
	struct name jk = { "Shit", "Mother", 25 };
	
	printf("jk's first name is %s, last name is %s, number is %d.\n", jk.first, jk.last, jk.len);
	
	typedef struct name a_new_type;
	
	a_new_type jl = { "MJ", "Crikit", 24 };
	
	printf("jl = %s %s and %d\n", jl.first, jl.last, jl.len);
	
	//可以在switch中把枚举变量作为标签 
	enum all_color { red, orange, yellow, green, cyan, blue, purple };
	
	typedef enum all_color color;
	
	color c_1 = red;
	
	while (c_1 <= purple) {
		printf("%d\n", c_1);
		c_1++;
	}
	
	
	/*
	用typedef代替int *或int*均可使第一个变量后的变量变为指针类型
	这里typedef替换的类型名用到变量上相当于int *x, *y,两个变量都给它上了指针标识符 
	用#define代替int *或int*都只能令第一个变量变为指针类型
	用int *和int* 定义变量都只能令第一个变量变为指针类型 
	*/
	typedef int* int_pt_1;
	typedef int * int_pt_2;
	int_pt_1 x, y; //int*
	int_pt_2 m, n; //int *
	INT_PT_1 u, v; //int*
	INT_PT_2 e, f; //int *
	int* a, b;
	int *o, p;
	printf("sizeof(int) = %zd\n", sizeof(int));
	printf("sizeof(int*) = %zd\n", sizeof(int*));
	printf("sizeof(int *) = %zd\n", sizeof(int *));
	printf("sizeof(x) = %zd, sizeof(y) = %zd\n", sizeof(x), sizeof(y));
	printf("sizeof(m) = %zd, sizeof(n) = %zd\n", sizeof(m), sizeof(n));
	printf("sizeof(u) = %zd, sizeof(v) = %zd\n", sizeof(u), sizeof(v));
	printf("sizeof(e) = %zd, sizoef(f) = %zd\n", sizeof(e), sizeof(f));
	printf("sizeof(a) = %zd, sizoef(b) = %zd\n", sizeof(a), sizeof(b));
	printf("sizeof(o) = %zd, sizoef(p) = %zd\n", sizeof(o), sizeof(p));
	
	union abc {
		char first;
		int second;
		float third;
	};
	
	union abc ttt;
	
	ttt.first = 'a';
	printf("ttt.first = %c\n", ttt.first);
	ttt.second = 100;
	printf("ttt.second = %d\n", ttt.second);
	ttt.third = 3.14;
	printf("ttt.third = %.2f\n", ttt.third);
	
	return 0;
}

char *s_gets(char *st, int n)
{
	char *ret_val;
	char *find;
	
	ret_val = fgets(st, n, stdin);
	if(ret_val)
	{
		find = strchr(st, '\n');
		if (find)
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	
	return ret_val;
}
