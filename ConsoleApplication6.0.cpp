// ConsoleApplication6.0.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS 1
#include < stdio.h >
#include < string.h >
#include<stdlib.h>
#define STUD_N 31
#define COURSE_N 7
#define NAME_N 15
struct node
{
	char name[100];
	long long xuehao;
	int menshu;
	double chengji[10];
	double zongfen;
};
typedef struct node sb;
void ReadScore(sb score[], int n, int l);
void AverforCourse(sb score[], int n, int l);
void AverforStud1(sb score[], int n, int l);
void HightoLow(sb score[], int n, int l);
void LowtoHigh(sb score[], int n, int l);
void IDsize(sb score[], int n, int l);
void Dictionary(sb score[], int n, int l);
void SeachbyID(sb score[], int n, int l);
void SeachbyNAME(sb score[], int n, int l);
void Analysis(sb score[], int n, int l);
void List(sb score[], int n, int l);
void WtoFile(sb score[],int n);
int RfromFile(sb score[]);
int cmp1(const void* a, const void* b);
int cmp2(const void* a, const void* b);
int cmp3(const void* a, const void* b);
int cmp4(const void* a, const void* b);


int main()
{
	int n, l;
	struct node score[35];
	printf("请输入学生总数(n <= 30):");
	scanf("%d", &n);
	printf("请输入课程总数(l <= 6):");
	scanf("%d", &l);
	int m;
	do {
		printf("1. Input record\n2. Caculate total and average score of every course \n3. Caculate total and average score of every student \n4. Sort in descending order by total score of every student\n5. Sort in ascending order by total score of every student\n6. Sort in ascending order by number\n7. Sort in dictionary order by name\n8. Search by number\n9. Search by name\n10. Statistic analysis for every course\n11. List record\n12. Write to file\n13.Read from file\n0.Exit\nPlease enter your choice:\n");
		scanf("%d", &m);
		switch (m) {
		case 1:ReadScore(score, n, l); break;
		case 2:AverforCourse(score, n, l); break;
		case 3:AverforStud1(score, n, l); break;
		case 4:HightoLow(score, n, l); break;
		case 5:LowtoHigh(score, n, l); break;
		case 6:IDsize(score, n, l); break;
		case 7:Dictionary(score, n, l); break;
		case 8:SeachbyID(score, n, l); break;
		case 9:SeachbyNAME(score, n, l); break;
		case 10:Analysis(score, l, n); break;
		case 11:List(score, n, l); break;
		case 12:WtoFile(score, n);
		case 13: {n = RfromFile(score); List(score, n, l); }
		case 0:return 0;
		}
	} while (1);
}
void ReadScore(sb score[], int n, int l)
{
	printf("Input student' s name, ID and score:\n");
	for (int i = 0; i < n; i++) {
		score[i].menshu = l;
		score[i].zongfen = 0;
		scanf("%s %lld", score[i].name, &score[i].xuehao);
		for (int j = 0; j < l; j++) {
			scanf("%lf", &score[i].chengji[j]);
			score[i].zongfen += score[i].chengji[j];
		}
	}
}
void AverforCourse(sb score[], int n, int l)
{
	for (int i = 0; i < l; i++) {
		double sum = 0;
		for (int j = 0; j < n; j++) {
			sum += score[j].chengji[i];
		}
		printf("第%d门 总分: %.2lf  平均分%.2lf\n", i + 1, sum, sum / n);
	}
}
void AverforStud1(sb score[], int n, int l)
{
	for (int i = 0; i < n; i++) {
		printf("第%d个学生 总分%.2lf  平均分%.2lf\n", i + 1, score[i].zongfen, score[i].zongfen / score[i].menshu);
	}
}
void HightoLow(sb score[], int n, int l)
{
	qsort(score, n, sizeof(sb), cmp1);
	double fen = -1;
	int top = -1;
	for (int i = 0; i < n; i++) {
		if (score[i].zongfen == fen)
			printf("rank:%d %s %lld %.2lf\n", top + 1, score[i].name, score[i].xuehao, score[i].zongfen);
		else {
			printf("rank:%d %s %lld %.2lf\n", i + 1, score[i].name, score[i].xuehao, score[i].zongfen);
			top = i;
			fen = score[i].zongfen;
		}
	}
}
void LowtoHigh(sb score[], int n, int l)
{
	qsort(score, n, sizeof(sb), cmp2);

	for (int i = 0; i < n; i++) {
		int mingci = 1;
		for (int j = 0; j < n; j++) {
			if (score[j].zongfen > score[i].zongfen) {
				mingci += 1;
			}
		}
		printf("rank:%d %s %lld %.2lf\n", mingci, score[i].name, score[i].xuehao, score[i].zongfen);
	}
}
void IDsize(sb score[], int n, int l)
{
	qsort(score, n, sizeof(sb), cmp3);

	for (int i = 0; i < n; i++) {
		printf("%s %lf\n", score[i].name, score[i].zongfen);
		for (int j = 0; j < l; j++) {
			printf("%lf  ", score[i].chengji[j]);
		}
		printf("\n");

	}
}
void Dictionary(sb score[], int n, int l)
{
	qsort(score, n, sizeof(sb), cmp4);
	for (int i = 0; i < n; i++) {
		printf("%s %lf\n", score[i].name, score[i].zongfen);
		for (int j = 0; j < l; j++) {
			printf("%lf  ", score[i].chengji[j]);
		}
		printf("\n");
	}
}
void SeachbyNAME(sb score[], int n, int l)
{
	char myname[100];
	scanf("%s", myname);
	for (int i = 0; i < n; i++) {
		if (strcmp(score[i].name, myname) == 0) {
			int mingci = 0;
			for (int j = 0; j < n; j++) {
				if (score[j].zongfen > score[i].zongfen) {
					mingci += 1;
				}
			}
			printf("name:%s   ID:%lld  rank:%d  total score:%lf\nscore: ", score[i].name, score[i].xuehao, mingci, score[i].zongfen);
			for (int j = 0; j < l; j++) {
				printf("%lf  ", score[i].chengji[j]);
			}
			printf("\n");
		}
	}
}
void SeachbyID(sb score[], int n, int l)
{
	long long myid;
	scanf("%lld", &myid);
	for (int i = 0; i < n; i++) {
		if (score[i].xuehao == myid) {
			int mingci = 0;
			for (int j = 0; j < n; j++) {
				if (score[j].zongfen > score[i].zongfen) {
					mingci += 1;
				}
			}
			printf("name:%s ID:%lld  rank:%d  total score:%lf\nscore: ", score[i].name, score[i].xuehao, mingci, score[i].zongfen);
			for (int j = 0; j < l; j++) {
				printf("%lf  ", score[i].chengji[j]);
			}
			printf("\n");
		}
	}
}
void Analysis(sb score[], int n, int l)
{
	for (int i = 0; i < l; i++) {
		int a = 0, b = 0, c = 0, d = 0, e = 0;
		for (int j = 0; j < n; j++) {
			if (score[j].chengji[i] >= 90)
				a++;
			else if (score[j].chengji[i] >= 80)
				b++;
			else if (score[j].chengji[i] >= 70)
				c++;
			else if (score[j].chengji[i] >= 60)
				d++;
			else
				e++;
		}
		printf("科目  %d\n", i + 1);
		printf("\t%6d%6d%6d%6d%6d\n", a, b, c, d, e);
		printf("\t%5.2f%%%5.2f%%%5.2f%%%5.2f%%%5.2f%%\n", a * 100.0 / n, b * 100.0 / n, c * 100.0 / n, d * 100.0 / n, e * 100.0 / n);

	}
}
void List(sb score[], int n, int l)
{
	for (int i = 0; i < n; i++) {
		printf("%s %lld %lf %lf\n", score[i].name, score[i].xuehao, score[i].zongfen, score[i].zongfen / n);
		for (int j = 0; j < l; j++) {
			printf("%lf ", score[i].chengji[j]);
		}
		printf("\n");
	}
}
void WtoFile(sb score[],int n)
{
	FILE* fp;
	if ((fp = fopen("text.txt", "w")) == NULL)
	{
		printf("文件打开失败\n");
		exit(0);
	}
	fwrite(score, sizeof(sb), n, fp);
	fclose(fp);
}
int RfromFile(sb score[])
{
	FILE* fp;
	int i;
	if ((fp = fopen("text.txt", "r")) == NULL)
	{
		printf("文件打开失败\n");
		exit(0);
	}
	for ( i = 0; !feof(fp); i++)
	{
		fread(&score[i], sizeof(sb), 1, fp);
	}
	fclose(fp);
	return i - 1;
}
int cmp1(const void* a, const void* b)
{
	return (*((sb*)b)).zongfen - (*((sb*)a)).zongfen;
}
int cmp2(const void* a, const void* b)
{
	return (*((sb*)a)).zongfen - (*((sb*)b)).zongfen;
}
int cmp3(const void* a, const void* b)
{
	return (*((sb*)a)).xuehao - (*((sb*)b)).xuehao;
}
int cmp4(const void* a, const void* b)
{
	return strcmp((*((sb*)a)).name, (*((sb*)b)).name);
}
