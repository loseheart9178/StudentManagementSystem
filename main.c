#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

// 常量定义
#define STU_NUM 50    // 教学班人数上限
#define COURSE_NUM 10 // 课程数量上限
#define NAME_LEN 50   // 姓名长度上限
#define POS_X1 35
#define POS_X2 40
#define POS_X3 5011
#define POS_X4 65
#define POS_Y1 3
#define DATA_FILE "studentInfo.txt"

// 结构体定义

// 学生结构体
typedef struct student
{
    long num;                // 学号
    char name[NAME_LEN];     // 姓名
    float score[COURSE_NUM]; // 成绩
    float sum;               // 总分
    float aver;              // 平均分
} STU;

// 函数声明
int Menu();                                                                                 // 菜单函数
void SetPosition(int x, int y);                                                             // 设置光标位置函数
void ClearInputBuffer(void);                                                                 // 清空输入缓冲区函数
void InputRecord(int *stuNums, int *courseNums, STU stu[]);                                 // 输入学生信息函数
void AppendRecord(int *stuNums, int courseNums, STU stu[]);                                 // 追加学生信息函数
void DeleteRecord(int *stuNums, int courseNums, STU stu[]);                                 // 删除学生信息函数
void SearchByNum(int stuNums, int courseNums, STU stu[]);                                   // 按学号查询学生信息函数
void SearchByName(int stuNums, int courseNums, STU stu[]);                                  // 按姓名查询学生信息函数
void ModifyRecord(int stuNums, int courseNums, STU stu[]);                                  // 修改学生信息函数
void CalculateScoreOfStudent(int stuNums, int courseNums, STU stu[]);                       // 计算学生成绩函数
void CalculateScoreOfCourse(int stuNums, int courseNums, STU stu[]);                        // 计算课程成绩函数
void SortByNum(int stuNums, int courseNums, STU stu[]);                                     // 按学号排序函数
void SortByName(int stuNums, int courseNums, STU stu[]);                                    // 按姓名排序函数
void SortByScore(int stuNums, int courseNums, STU stu[], int (*compare)(float a, float b)); // 按总分排序函数
int Accending(float a, float b);                                                            // 升序比较函数
int Decending(float a, float b);                                                            // 降序比较函数
void StatisticAnalysis(int stuNums, int courseNums, STU stu[]);                             // 统计分析函数
void PrintRecord(int stuNums, int courseNums, STU stu[]);                                   // 打印学生信息函数
void WriteToFile(int stuNums, int courseNums, STU stu[]);                                   // 将学生信息写入文件函数
int ReadFromFile(int *stuNums, int *courseNums, STU stu[], int *first);                     // 从文件读取学生信息函数

// 主函数入口
int main()
{
    int stuNums = 0;
    int courseNums = 0;
    int i, j;
    int choice;
    int first = 1;    // 标志变量，表示是否第一次运行程序
    STU stu[STU_NUM]; // 学生数组

    system("chcp 65001 > nul");            // 设置控制台编码为 UTF-8，解决中文乱码问题
    system("mode con: cols=130 lines=60"); // 设置控制台窗口大小
    system("color 0E");                    // 设置控制台颜色
    while (1)
    {
        system("cls");   // 清屏
        choice = Menu(); // 显示菜单并获取用户选择
        switch (choice)
        {
        case 1:
            system("cls");
            InputRecord(&stuNums, &courseNums, stu);
            first = 0; // 已经输入过学生信息，设置标志变量为0
            system("pause");
            break;
        case 2:
            system("cls");
            if (first)
            {
                printf("请先输入学生信息！");
                system("pause");
                break;
            }
            AppendRecord(&stuNums, courseNums, stu);
            system("pause");
            break;
        case 3:
            system("cls");
            if (first)
            {
                printf("请先输入学生信息！");
                system("pause");
                break;
            }

            DeleteRecord(&stuNums, courseNums, stu);
            system("pause");
            break;
        case 4:
            system("cls");
            if (first)
            {
                printf("请先输入学生信息！");
                system("pause");
                break;
            }

            SearchByNum(stuNums, courseNums, stu);
            system("pause");
            break;
        case 5:
            system("cls");
            if (first)
            {
                printf("请先输入学生信息！");
                system("pause");
                break;
            }
            SearchByName(stuNums, courseNums, stu);
            system("pause");
            break;
        case 6:
            system("cls");
            if (first)
            {
                printf("请先输入学生信息！");
                system("pause");
                break;
            }

            ModifyRecord(stuNums, courseNums, stu);
            system("pause");
            break;
        case 7:
            system("cls");
            if (first)
            {
                printf("请先输入学生信息！");
                system("pause");
                break;
            }
            CalculateScoreOfStudent(stuNums, courseNums, stu);
            system("pause");
            break;
        case 8:
            system("cls");
            if (first)
            {
                printf("请先输入学生信息！");
                system("pause");
                break;
            }
            CalculateScoreOfCourse(stuNums, courseNums, stu);
            system("pause");
            break;
        case 9:
            system("cls");
            if ((first))
            {
                SetPosition(POS_X3, POS_Y1);
                printf("请先输入学生信息！");
                ClearInputBuffer();
                getch();
                break;
            }

            SortByNum(stuNums, courseNums, stu);
            ClearInputBuffer();
            getch();
            break;
        case 10:
            system("cls");
            if (first)
            {
                SetPosition(POS_X3, POS_Y1);
                printf("请先输入学生信息！");
                ClearInputBuffer();
                getch();
                break;
            }
            SortByName(stuNums, courseNums, stu);
            system("pause");
            break;
        case 11:
            system("cls");
            if(first)
            {
                SetPosition(POS_X3, POS_Y1);
                printf("请先输入学生信息！");
                ClearInputBuffer();
                getch();
                break;
            }
            SortByScore(stuNums, courseNums, stu, Decending);
            ClearInputBuffer();
            getch();
            break;
        case 12:
            system("cls");
            if(first)
            {
                SetPosition(POS_X3, POS_Y1);
                printf("请先输入学生信息！");
                ClearInputBuffer();
                getch();
                break;
            }

            SortByScore(stuNums, courseNums, stu, Accending);
            ClearInputBuffer();
            getch();
            break;
        case 13:
            system("cls");
                if (first)
                {
                    SetPosition(POS_X3, POS_Y1);
                    printf("请先输入学生信息！");
                    system("pause");
                    break;
                }
            StatisticAnalysis(stuNums, courseNums, stu);
            system("pause");
            break;
        case 14:
            system("cls");
            PrintRecord(stuNums, courseNums, stu);
            system("pause");
            break;
        case 15:
            system("cls");
            if (first)
            {
                SetPosition(POS_X3, POS_Y1);
                printf("请先输入学生信息！");
                system("pause");
                break;
            }
            WriteToFile(stuNums, courseNums, stu);
            system("pause");
            break;
        case 16:
            system("cls");
            if (ReadFromFile(&stuNums, &courseNums, stu, &first))
            {
                SetPosition(POS_X1, 10);
                printf("请先输入学生信息！");
                system("pause");
                break;
            }
            system("pause");
            break;
        case 0:
            system("cls");
            SetPosition(POS_X3, 10);
            printf("感谢使用学生成绩管理系统，再见！");
            printf("\n");
            exit(0);
            break;
        default:
            SetPosition(POS_X1, 30);
            printf("输入错误,请输入0-16之间的功能编号!");
            system("pause");
        }
    }
    return 0;
}

int Menu()
{
    int posy = 5;
    int choice;
    int i, j;
    SetPosition(POS_X3, posy);
    printf("学生成绩管理系统");
    for (int i = 0; i < 2; i++)
    {
        SetPosition(POS_X1, ++posy);
        for (int j = 0; j < 55; j++)
        {
            printf("-");
        }
    }
    SetPosition(POS_X1, ++posy);
    printf("1.输入学生信息");
    SetPosition(POS_X4, posy);
    printf("2.增加学生成绩");
    SetPosition(POS_X1, posy += 2);
    printf("3.删除学生信息");
    SetPosition(POS_X4, posy);
    printf("4.按学号查询学生信息");
    SetPosition(POS_X1, posy += 2);
    printf("5.按姓名查询学生信息");
    SetPosition(POS_X4, posy);
    printf("6.修改学生信息");
    SetPosition(POS_X1, posy += 2);
    printf("7.计算学生成绩");
    SetPosition(POS_X4, posy);
    printf("8.计算课程成绩");
    SetPosition(POS_X1, posy += 2);
    printf("9.按学号排序");
    SetPosition(POS_X4, posy);
    printf("10.按姓名排序");
    SetPosition(POS_X1, posy += 2);
    printf("11.按总分降序排序");
    SetPosition(POS_X4, posy);
    printf("12.按总分升序排序");
    SetPosition(POS_X1, posy += 2);
    printf("13.学生成绩统计");
    SetPosition(POS_X4, posy);
    printf("14.打印学生信息");
    SetPosition(POS_X1, posy += 2);
    printf("15.学生记录存盘");
    SetPosition(POS_X4, posy);
    printf("16.从磁盘读取学生记录");
    SetPosition(POS_X1, posy += 2);
    printf("0.退出系统");

    // 输出功能与输入提示之间的分隔线
    for (int i = 0; i < 2; i++)
    {
        SetPosition(POS_X1, ++posy);
        for (int j = 0; j < 55; j++)
        {
            printf("-");
        }
    }
    // 提示用户输入功能编号
    SetPosition(POS_X1, ++posy);
    printf("请输入功能编号[0-16]: ");
    fflush(stdout);
    scanf("%d", &choice);
    ClearInputBuffer();
    return choice;
}

void SetPosition(int x, int y)
{

    HANDLE hOut;
    COORD pos;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ClearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void InputRecord(int *stuNums, int *courseNums, STU stu[])
{
    int i, j;
    int posy = 6;
    SetPosition(POS_X2, posy);
    printf("请输入学生人数(stuNums<%d):", STU_NUM);
    scanf("%d", stuNums);
    ClearInputBuffer();
    SetPosition(POS_X2, posy += 2);
    printf("请输入课程数量(courseNums<%d):", COURSE_NUM);
    scanf("%d", courseNums);
    ClearInputBuffer();
    if (*stuNums <= 0 || *stuNums > STU_NUM)
    {
        printf("\n学生人数输入无效！");
        *stuNums = 0;
        *courseNums = 0;
        return;
    }
    if (*courseNums <= 0 || *courseNums > COURSE_NUM)
    {
        printf("\n课程数量输入无效！");
        *stuNums = 0;
        *courseNums = 0;
        return;
    }
    for (int i = 0; i < 2; i++)
    {
        SetPosition(POS_X1, ++posy);
        for (int j = 0; j < 55; j++)
        {
            printf("-");
        }
    }
    SetPosition(POS_X1, ++posy);
    printf("请依次输入学生的学号、姓名和%d门课程的成绩:", *courseNums);
    for (i = 0; i < *stuNums; i++)
    {
        printf("请输入第%d个学生信息:\t", i + 1);
        scanf("%ld%s", &stu[i].num, stu[i].name);
        for (j = 0; j < *courseNums; j++)
        {
            scanf("%f", &stu[i].score[j]);
        }
        ClearInputBuffer();
    }
}

// 追加学生信息
void AppendRecord(int *stuNums, int courseNums, STU stu[])
{
    int i, j;
    int num_record;
    int start_index;
    printf("请输入要追加的学生人数:");
    scanf("%d", &num_record);
    ClearInputBuffer();
    if (num_record <= 0)
    {
        printf("追加人数输入无效！");
        return;
    }
    if (*stuNums + num_record > STU_NUM)
    {
        SetPosition(POS_X2, 12);
        printf("要增加的记录条数太多，请重新输入:");
        return;
    }
    start_index = *stuNums;
    for (i = start_index; i < start_index + num_record; i++)
    {
        SetPosition(POS_X2, 14 + i * 2);
        printf("请输入第%d个学生信息:\t", i + 1);
        scanf("%ld%s", &stu[i].num, stu[i].name);
        for (j = 0; j < courseNums; j++)
        {
            scanf("%f", &stu[i].score[j]);
        }
        ClearInputBuffer();
    }
    *stuNums += num_record;
    printf("追加成功！");
}

// 删除学生信息
void DeleteRecord(int *stuNums, int courseNums, STU stu[])
{
    int i, j;
    long id;
    char ch;
    printf("请输入要删除的学生学号：");
    scanf("%ld", &id);
    ClearInputBuffer();
    for (i = 0; i < *stuNums; i++)
    {
        if (stu[i].num == id)
        {
            printf("找到了，该学号对应的学生信息如下：\n");
            printf("%10ld%15s", stu[i].num, stu[i].name);
            for (j = 0; j < courseNums; j++)
            {
                printf("%10.2f", stu[i].score[j]);
            }
            printf("%10.2f%10.2f\n", stu[i].sum, stu[i].aver);
            printf("是否确认删除该学生信息？(Y/y或N/n):");
            ClearInputBuffer(); // 吸收多余输入
            scanf("%c", &ch);
            ClearInputBuffer();
            if (ch == 'Y' || ch == 'y')
            {
                for (j = i; j < *stuNums - 1; j++)
                {
                    stu[j] = stu[j + 1];
                }
                (*stuNums)--;
                printf("学号为%ld的学生已删除!\n", id);
            }
            else if (ch == 'N' || ch == 'n')
            {
                printf("找到该学生记录，但不删除该学生信息!\n");
            }
            else
            {
                printf("输入错误，未删除该学生信息!\n");
            }
            return;
        }
    }
    printf("未找到学号为%ld的学生!\n", id);
}

// 按学号查询学生信息
void SearchByNum(int stuNums, int courseNums, STU stu[])
{
    long id;
    int i, j;
    printf("请输入要查询的学号：");
    scanf("%ld", &id);
    ClearInputBuffer();
    for (i = 0; i < stuNums; i++)
    {
        if (stu[i].num == id)
        {
            printf("找到了，该学号对应的学生信息如下：\n");
            printf("%10ld%15s", stu[i].num, stu[i].name);
            for (j = 0; j < courseNums; j++)
            {
                printf("%10.2f", stu[i].score[j]);
            }
            printf("%10.2f%10.2f\n", stu[i].sum, stu[i].aver);
            return;
        }
    }
    printf("未找到学号为%ld的学生!\n", id);
}
// 按姓名查询学生信息
void SearchByName(int stuNums, int courseNums, STU stu[])
{
    int flag = 1;
    int i, j;
    int k = 0;
    char name[NAME_LEN];
    printf("请输入要查询学生的姓名：");
    scanf("%s", name);
    ClearInputBuffer();
    for (i = 0; i < stuNums; i++)
    {
        if (strcmp(stu[i].name, name) == 0)
        {
            printf("找到了，第%d个对应的学生信息如下：\n", ++k);
            printf("%10ld%15s", stu[i].num, stu[i].name);
            for (j = 0; j < courseNums; j++)
            {
                printf("%10.2f", stu[i].score[j]);
            }
            printf("%10.2f%10.2f\n", stu[i].sum, stu[i].aver);
            flag = 0;
        }
    }
    if (flag)
    {
        printf("未找到姓名为%s的学生!\n", name);
    }
}

// 修改学生信息
void ModifyRecord(int stuNums, int courseNums, STU stu[])
{
    int i, j;
    long id;
    char ch;
    printf("请输入要修改的学生学号：");
    scanf("%ld", &id);
    ClearInputBuffer();
    for (i = 0; i < stuNums; i++)
    {
        if (stu[i].num == id)
        {
            printf("找到了，该学号对应的学生信息如下：\n");
            printf("%10ld%15s", stu[i].num, stu[i].name);
            for (j = 0; j < courseNums; j++)
            {
                printf("%10.2f", stu[i].score[j]);
            }
            printf("%10.2f%10.2f\n", stu[i].sum, stu[i].aver);
            printf("是否确认修改该学生信息？(Y/y或N/n):");
            ClearInputBuffer(); // 吸收多余输入
            scanf("%c", &ch);
            ClearInputBuffer();
            if (ch == 'Y' || ch == 'y')
            {
                printf("请输入新的学生姓名：");
                scanf("%s", stu[i].name);
                for (j = 0; j < courseNums; j++)
                {
                    printf("请输入新的课程%d成绩：", j + 1);
                    scanf("%f", &stu[i].score[j]);
                }
                printf("学号为%ld的学生信息已修改!\n", id);
            }
            else if (ch == 'N' || ch == 'n')
            {
                printf("找到该学生记录，但不修改该学生信息!\n");
            }
            else
            {
                printf("输入错误，未修改该学生信息!\n");
            }
            return;
        }
    }
    printf("未找到学号为%ld的学生!\n", id);
}

// 计算每个学生的总分和平均分
void CalculateScoreOfStudent(int stuNums, int courseNums, STU stu[])
{
    int i, j;
    float sum;
    if (courseNums <= 0)
    {
        printf("课程数量无效，无法计算学生成绩！\n");
        return;
    }
    printf("每个学生的各门课程总分和平均分为：\n");
    for (i = 0; i < stuNums; i++)
    {
        sum = 0;
        for (j = 0; j < courseNums; j++)
        {
            sum += stu[i].score[j];
        }
        stu[i].sum = sum;
        stu[i].aver = sum / courseNums;
        printf("第%d个学生:总分 = %.2f:平均分 = %.2f\n", i + 1, stu[i].sum, stu[i].aver);
    }
}

// 计算每门课程的总分和平均分
void CalculateScoreOfCourse(int stuNums, int courseNums, STU stu[])
{
    int i, j;
    float sum[COURSE_NUM], aver[COURSE_NUM];
    int posy = 7;
    if (stuNums <= 0 || courseNums <= 0)
    {
        printf("当前没有可计算的学生成绩数据！\n");
        return;
    }
    SetPosition(POS_X1, posy);
    printf("各门课程总分和平均分计算结果：\n");
    for (j = 0; j < courseNums; j++)
    {
        sum[j] = 0;
        for (i = 0; i < stuNums; i++)
        {
            sum[j] += stu[i].score[j];
        }
        aver[j] = sum[j] / stuNums;
        SetPosition(POS_X1, ++posy);
        printf("第%d门课：总分 = %.2f，平均分 = %.2f\n", j + 1, sum[j], aver[j]);
    }
}

// 按学号排序
void SortByNum(int stuNums, int courseNums, STU stu[])
{
    int i, j;
    STU temp;
    // 升序排序
    for (i = 0; i < stuNums - 1; i++)
    {
        for (j = i + 1; j < stuNums; j++)
        {
            if (stu[i].num > stu[j].num)
            {
                temp = stu[i];
                stu[i] = stu[j];
                stu[j] = temp;
            }
        }
    }
    SetPosition(POS_X2, 10);
    printf("按学号升序排序完成！");
}

// 按姓名排序
void SortByName(int stuNums, int courseNums, STU stu[])
{
    int i, j;
    STU temp;
    for (i = 0; i < stuNums - 1; i++)
    {
        for (j = i + 1; j < stuNums; j++)
        {
            if (strcmp(stu[i].name, stu[j].name) > 0)
            {
                temp = stu[i];
                stu[i] = stu[j];
                stu[j] = temp;
            }
        }
    }
    SetPosition(POS_X2, 10);
    printf("按姓名升序排序完成！");
}

// 升序比较函数
int Accending(float a, float b)
{
    return a < b;
}

// 降序比较函数
int Decending(float a, float b)
{
    return a > b;
}

// 按总分排序
void SortByScore(int stuNums, int courseNums, STU stu[], int (*compare)(float a, float b))
{
    int i, j;
    STU temp;
    int k;
    for (i = 0; i < stuNums - 1; i++)
    {
        k = i;
        for (j = i + 1; j < stuNums; j++)
        {
            if ((*compare)(stu[k].sum, stu[j].sum))
                k = j;
        }
        if (k != i)
        {
            temp = stu[i];
            stu[i] = stu[k];
            stu[k] = temp;
        }
    }
}

// 统计分析成绩分布
void StatisticAnalysis(int stuNums, int courseNums, STU stu[])
{
    int i,j;
    int t[6];
    for(j=0;j<courseNums;j++)
    {
        printf("\n课程%d成绩统计结果：\n",j+1);
        printf("分数段\t人数\t占比\n");
        memset(t,0,sizeof(t));
        for(i=0;i<stuNums;i++)
        {
            if(stu[i].score[j]>=0&&stu[i].score[j]<60)
            t[0]++;
            else if(stu[i].score[j]>=60&&stu[i].score[j]<70)
            t[1]++;
            else if(stu[i].score[j]>=70&&stu[i].score[j]<80)
            t[2]++;
            else if(stu[i].score[j]>=80&&stu[i].score[j]<90)
            t[3]++;
            else if(stu[i].score[j]>=90&&stu[i].score[j]<100)  
            t[4]++;
            else if (stu[i].score[j] == 100)
            t[5]++;
        }
        for(int i=0;i<6;i++){
            if(i==0)
            printf("<60\t%d\t%.2f%%\n",t[i],(float)t[i]/stuNums*100);
            else if(i==5)
            printf("100\t%d\t%.2f%%\n",t[i],(float)t[i]/stuNums*100);
            else
            printf("%d-%d\t%d\t%.2f%%\n",(i+5)*10,(i+5)*10+9,t[i],(float)t[i]/stuNums*100);
        }
    }
}

// 打印所有学生信息
void PrintRecord(int stuNums, int courseNums, STU stu[])
{  
    int i, j;
    printf("学号\t\t姓名\t\t");
    for (j = 0; j < courseNums; j++)
    {
        printf("课程%d\t", j + 1);
    }
    printf("总分\t\t平均分\n");
    for (i = 0; i < stuNums; i++)
    {
        printf("%-16ld\t%-16s\t", stu[i].num, stu[i].name);
        for (j = 0; j < courseNums; j++)
        {
            printf("%16.1lf\t", stu[i].score[j]);
        }
        printf("%16.2lf\t%16.2lf\n", stu[i].sum, stu[i].aver);
    }
}

// 将学生信息写入文件
void WriteToFile(int stuNums, int courseNums, STU stu[])
{
    int i, j;
    FILE *fp;
    fp = fopen(DATA_FILE, "w");
    if (fp == NULL)
    {
        printf("无法打开文件，写入失败！请检查当前目录是否可写。");
        return;
    }

    fprintf(fp, "%10ld%10ld\n", stuNums, courseNums);
    for (i = 0; i < stuNums; i++)
    {
        fprintf(fp, "%10ld%10s", stu[i].num, stu[i].name);
        for (j = 0; j < courseNums; j++)
        {
            fprintf(fp, "%10.2f", stu[i].score[j]);
        }
        fprintf(fp, "%10.2f%10.2f\n", stu[i].sum, stu[i].aver);
    }
    fclose(fp);
    printf("学生信息已成功写入文件\n");
}

// 从文件读取学生信息
int ReadFromFile(int *stuNums, int *courseNums, STU stu[], int *first)
{
    FILE *fp;
    int i, j;
    int posy = 8;
    SetPosition(POS_X1, posy);
    if ((fp = fopen(DATA_FILE, "r")) == NULL)
    {
        printf("无法打开文件，读取失败！请确认文件已存在。");
        return 1;
    }
    fscanf(fp, "%10ld%10ld", stuNums, courseNums);
    for (i = 0; i < *stuNums; i++)
    {
        fscanf(fp, "%10ld%10s", &stu[i].num, stu[i].name);
        for (j = 0; j < *courseNums; j++)
        {
            fscanf(fp, "%10f", &stu[i].score[j]);
        }
        fscanf(fp, "%10f%10f", &stu[i].sum, &stu[i].aver);
    }
    fclose(fp);
    *first = 0; // 已经成功读取学生信息，设置标志变量为0
    printf("学生信息已成功从文件读取\n");
    return 0;
}
