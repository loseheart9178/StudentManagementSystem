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
#define POS_X3 50
#define POS_X4 65
#define POS_Y1 3
#define DATA_FILE "studentInfo.txt"

// 结构体定义
typedef struct student
{
    long num;                // 学号
    char name[NAME_LEN];     // 姓名
    float score[COURSE_NUM]; // 成绩
    float sum;               // 总分
    float aver;              // 平均分
} STU;

// 链表节点结构体
typedef struct node
{
    STU data;
    struct node *next;
} NODE;

// 函数声明
int Menu();                                                       // 菜单函数
void SetPosition(int x, int y);                                   // 设置光标位置函数
void ClearInputBuffer(void);                                      // 清空输入缓冲区函数
void InputRecord(int *stuNums, int *courseNums, NODE **head);     // 输入学生信息函数
void AppendRecord(int *stuNums, int courseNums, NODE **head);     // 追加学生信息函数
void DeleteRecord(int *stuNums, int courseNums, NODE **head);     // 删除学生信息函数
void SearchByNum(int stuNums, int courseNums, NODE *head);        // 按学号查询学生信息函数
void SearchByName(int stuNums, int courseNums, NODE *head);       // 按姓名查询学生信息函数
void ModifyRecord(int stuNums, int courseNums, NODE *head);       // 修改学生信息函数
void CalculateScoreOfStudent(int stuNums, int courseNums, NODE *head); // 计算学生成绩函数
void CalculateScoreOfCourse(int stuNums, int courseNums, NODE *head);  // 计算课程成绩函数
void SortByNum(int stuNums, int courseNums, NODE **head);          // 按学号排序函数
void SortByName(int stuNums, int courseNums, NODE **head);         // 按姓名排序函数
void SortByScore(int stuNums, int courseNums, NODE **head, int (*compare)(float a, float b)); // 按总分排序函数
int Accending(float a, float b);                                  // 升序比较函数
int Decending(float a, float b);                                  // 降序比较函数
void StatisticAnalysis(int stuNums, int courseNums, NODE *head);   // 统计分析函数
void PrintRecord(int stuNums, int courseNums, NODE *head);         // 打印学生信息函数
void WriteToFile(int stuNums, int courseNums, NODE *head);         // 将学生信息写入文件函数
int ReadFromFile(int *stuNums, int *courseNums, NODE **head, int *first); // 从文件读取学生信息函数
void FreeList(NODE *head);                                         // 释放链表内存函数

// 主函数入口
int main()
{
    int stuNums = 0;
    int courseNums = 0;
    int choice;
    int first = 1;    // 标志变量，表示是否第一次运行程序
    NODE *head = NULL; // 链表头指针

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
            InputRecord(&stuNums, &courseNums, &head);
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
            AppendRecord(&stuNums, courseNums, &head);
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
            DeleteRecord(&stuNums, courseNums, &head);
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
            SearchByNum(stuNums, courseNums, head);
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
            SearchByName(stuNums, courseNums, head);
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
            ModifyRecord(stuNums, courseNums, head);
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
            CalculateScoreOfStudent(stuNums, courseNums, head);
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
            CalculateScoreOfCourse(stuNums, courseNums, head);
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
            SortByNum(stuNums, courseNums, &head);
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
            SortByName(stuNums, courseNums, &head);
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
            SortByScore(stuNums, courseNums, &head, Decending);
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
            SortByScore(stuNums, courseNums, &head, Accending);
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
            StatisticAnalysis(stuNums, courseNums, head);
            system("pause");
            break;
        case 14:
            system("cls");
            PrintRecord(stuNums, courseNums, head);
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
            WriteToFile(stuNums, courseNums, head);
            system("pause");
            break;
        case 16:
            system("cls");
            if (ReadFromFile(&stuNums, &courseNums, &head, &first))
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
            FreeList(head); // 释放链表内存
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

// 输入学生信息，创建链表
void InputRecord(int *stuNums, int *courseNums, NODE **head)
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
    // 清空原有链表
    FreeList(*head);
    *head = NULL;
    NODE *tail = NULL;

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
        NODE *newNode = (NODE *)malloc(sizeof(NODE));
        if (!newNode)
        {
            printf("内存分配失败！\n");
            exit(1);
        }
        printf("请输入第%d个学生信息:\t", i + 1);
        scanf("%ld%s", &newNode->data.num, newNode->data.name);
        for (j = 0; j < *courseNums; j++)
        {
            scanf("%f", &newNode->data.score[j]);
        }
        ClearInputBuffer();
        newNode->data.sum = 0;   // 后续计算
        newNode->data.aver = 0;  // 后续计算
        newNode->next = NULL;
        if (*head == NULL)
        {
            *head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
}

// 追加学生信息
void AppendRecord(int *stuNums, int courseNums, NODE **head)
{
    int i, j;
    int num_record;
    if (*stuNums + num_record > STU_NUM)
    {
        SetPosition(POS_X2, 12);
        printf("要增加的记录条数太多，请重新输入:");
        return;
    }
    printf("请输入要追加的学生人数:");
    scanf("%d", &num_record);
    ClearInputBuffer();
    if (num_record <= 0)
    {
        printf("追加人数输入无效！");
        return;
    }
    // 找到尾节点
    NODE *tail = *head;
    if (tail)
    {
        while (tail->next)
            tail = tail->next;
    }
    for (i = 0; i < num_record; i++)
    {
        NODE *newNode = (NODE *)malloc(sizeof(NODE));
        if (!newNode)
        {
            printf("内存分配失败！\n");
            exit(1);
        }
        SetPosition(POS_X2, 14 + i * 2);
        printf("请输入第%d个学生信息:\t", *stuNums + i + 1);
        scanf("%ld%s", &newNode->data.num, newNode->data.name);
        for (j = 0; j < courseNums; j++)
        {
            scanf("%f", &newNode->data.score[j]);
        }
        ClearInputBuffer();
        newNode->data.sum = 0;
        newNode->data.aver = 0;
        newNode->next = NULL;
        if (*head == NULL)
        {
            *head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    *stuNums += num_record;
    printf("追加成功！");
}

// 删除学生信息
void DeleteRecord(int *stuNums, int courseNums, NODE **head)
{
    long id;
    char ch;
    printf("请输入要删除的学生学号：");
    scanf("%ld", &id);
    ClearInputBuffer();
    NODE *prev = NULL, *curr = *head;
    while (curr)
    {
        if (curr->data.num == id)
        {
            printf("找到了，该学号对应的学生信息如下：\n");
            printf("%10ld%15s", curr->data.num, curr->data.name);
            for (int j = 0; j < courseNums; j++)
                printf("%10.2f", curr->data.score[j]);
            printf("%10.2f%10.2f\n", curr->data.sum, curr->data.aver);
            printf("是否确认删除该学生信息？(Y/y或N/n):");
            scanf("%c", &ch);
            ClearInputBuffer();
            if (ch == 'Y' || ch == 'y')
            {
                if (prev == NULL)
                    *head = curr->next;
                else
                    prev->next = curr->next;
                free(curr);
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
        prev = curr;
        curr = curr->next;
    }
    printf("未找到学号为%ld的学生!\n", id);
}

// 按学号查询
void SearchByNum(int stuNums, int courseNums, NODE *head)
{
    long id;
    printf("请输入要查询的学号：");
    scanf("%ld", &id);
    ClearInputBuffer();
    NODE *p = head;
    while (p)
    {
        if (p->data.num == id)
        {
            printf("找到了，该学号对应的学生信息如下：\n");
            printf("%10ld%15s", p->data.num, p->data.name);
            for (int j = 0; j < courseNums; j++)
                printf("%10.2f", p->data.score[j]);
            printf("%10.2f%10.2f\n", p->data.sum, p->data.aver);
            return;
        }
        p = p->next;
    }
    printf("未找到学号为%ld的学生!\n", id);
}

// 按姓名查询
void SearchByName(int stuNums, int courseNums, NODE *head)
{
    int flag = 1;
    int k = 0;
    char name[NAME_LEN];
    printf("请输入要查询学生的姓名：");
    scanf("%s", name);
    ClearInputBuffer();
    NODE *p = head;
    while (p)
    {
        if (strcmp(p->data.name, name) == 0)
        {
            printf("找到了，第%d个对应的学生信息如下：\n", ++k);
            printf("%10ld%15s", p->data.num, p->data.name);
            for (int j = 0; j < courseNums; j++)
                printf("%10.2f", p->data.score[j]);
            printf("%10.2f%10.2f\n", p->data.sum, p->data.aver);
            flag = 0;
        }
        p = p->next;
    }
    if (flag)
        printf("未找到姓名为%s的学生!\n", name);
}

// 修改学生信息
void ModifyRecord(int stuNums, int courseNums, NODE *head)
{
    long id;
    char ch;
    printf("请输入要修改的学生学号：");
    scanf("%ld", &id);
    ClearInputBuffer();
    NODE *p = head;
    while (p)
    {
        if (p->data.num == id)
        {
            printf("找到了，该学号对应的学生信息如下：\n");
            printf("%10ld%15s", p->data.num, p->data.name);
            for (int j = 0; j < courseNums; j++)
                printf("%10.2f", p->data.score[j]);
            printf("%10.2f%10.2f\n", p->data.sum, p->data.aver);
            printf("是否确认修改该学生信息？(Y/y或N/n):");
            scanf("%c", &ch);
            ClearInputBuffer();
            if (ch == 'Y' || ch == 'y')
            {
                printf("请输入新的学生姓名：");
                scanf("%s", p->data.name);
                for (int j = 0; j < courseNums; j++)
                {
                    printf("请输入新的课程%d成绩：", j + 1);
                    scanf("%f", &p->data.score[j]);
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
        p = p->next;
    }
    printf("未找到学号为%ld的学生!\n", id);
}

// 计算每个学生的总分和平均分
void CalculateScoreOfStudent(int stuNums, int courseNums, NODE *head)
{
    if (courseNums <= 0)
    {
        printf("课程数量无效，无法计算学生成绩！\n");
        return;
    }
    printf("每个学生的各门课程总分和平均分为：\n");
    NODE *p = head;
    int i = 1;
    while (p)
    {
        float sum = 0;
        for (int j = 0; j < courseNums; j++)
            sum += p->data.score[j];
        p->data.sum = sum;
        p->data.aver = sum / courseNums;
        printf("第%d个学生:总分 = %.2f:平均分 = %.2f\n", i++, p->data.sum, p->data.aver);
        p = p->next;
    }
}

// 计算每门课程的总分和平均分
void CalculateScoreOfCourse(int stuNums, int courseNums, NODE *head)
{
    int posy = 7;
    if (stuNums <= 0 || courseNums <= 0)
    {
        printf("当前没有可计算的学生成绩数据！\n");
        return;
    }
    float sum[COURSE_NUM] = {0};
    float aver[COURSE_NUM];
    NODE *p = head;
    while (p)
    {
        for (int j = 0; j < courseNums; j++)
            sum[j] += p->data.score[j];
        p = p->next;
    }
    SetPosition(POS_X1, posy);
    printf("各门课程总分和平均分计算结果：\n");
    for (int j = 0; j < courseNums; j++)
    {
        aver[j] = sum[j] / stuNums;
        SetPosition(POS_X1, ++posy);
        printf("第%d门课：总分 = %.2f，平均分 = %.2f\n", j + 1, sum[j], aver[j]);
    }
}

// 按学号排序（交换节点数据）
void SortByNum(int stuNums, int courseNums, NODE **head)
{
    if (!head || !*head || (*head)->next == NULL) return;
    // 获取所有节点指针
    NODE *arr[STU_NUM];
    int count = 0;
    NODE *p = *head;
    while (p)
    {
        arr[count++] = p;
        p = p->next;
    }
    // 冒泡排序（按学号升序）
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (arr[i]->data.num > arr[j]->data.num)
            {
                // 交换节点中的数据，不改变指针链接
                STU temp = arr[i]->data;
                arr[i]->data = arr[j]->data;
                arr[j]->data = temp;
            }
        }
    }
    SetPosition(POS_X2, 10);
    printf("按学号升序排序完成！");
}

// 按姓名排序
void SortByName(int stuNums, int courseNums, NODE **head)
{
    if (!head || !*head || (*head)->next == NULL) return;
    NODE *arr[STU_NUM];
    int count = 0;
    NODE *p = *head;
    while (p)
    {
        arr[count++] = p;
        p = p->next;
    }
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(arr[i]->data.name, arr[j]->data.name) > 0)
            {
                STU temp = arr[i]->data;
                arr[i]->data = arr[j]->data;
                arr[j]->data = temp;
            }
        }
    }
    SetPosition(POS_X2, 10);
    printf("按姓名升序排序完成！");
}

int Accending(float a, float b) { return a < b; }
int Decending(float a, float b) { return a > b; }

// 按总分排序（通过比较函数指定升/降序）
void SortByScore(int stuNums, int courseNums, NODE **head, int (*compare)(float a, float b))
{
    if (!head || !*head || (*head)->next == NULL) return;
    NODE *arr[STU_NUM];
    int count = 0;
    NODE *p = *head;
    while (p)
    {
        arr[count++] = p;
        p = p->next;
    }
    // 选择排序
    for (int i = 0; i < count - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < count; j++)
        {
            if (compare(arr[k]->data.sum, arr[j]->data.sum))
                k = j;
        }
        if (k != i)
        {
            STU temp = arr[i]->data;
            arr[i]->data = arr[k]->data;
            arr[k]->data = temp;
        }
    }
}

// 统计分析成绩分布
void StatisticAnalysis(int stuNums, int courseNums, NODE *head)
{
    int t[6];
    for (int j = 0; j < courseNums; j++)
    {
        printf("\n课程%d成绩统计结果：\n", j + 1);
        printf("分数段\t人数\t占比\n");
        memset(t, 0, sizeof(t));
        NODE *p = head;
        while (p)
        {
            float score = p->data.score[j];
            if (score >= 0 && score < 60) t[0]++;
            else if (score >= 60 && score < 70) t[1]++;
            else if (score >= 70 && score < 80) t[2]++;
            else if (score >= 80 && score < 90) t[3]++;
            else if (score >= 90 && score < 100) t[4]++;
            else if (score == 100) t[5]++;
            p = p->next;
        }
        for (int i = 0; i < 6; i++)
        {
            if (i == 0)
                printf("<60\t%d\t%.2f%%\n", t[i], (float)t[i] / stuNums * 100);
            else if (i == 5)
                printf("100\t%d\t%.2f%%\n", t[i], (float)t[i] / stuNums * 100);
            else
                printf("%d-%d\t%d\t%.2f%%\n", (i + 5) * 10, (i + 5) * 10 + 9, t[i], (float)t[i] / stuNums * 100);
        }
    }
}

// 打印所有学生信息
void PrintRecord(int stuNums, int courseNums, NODE *head)
{
    printf("学号\t\t姓名\t\t");
    for (int j = 0; j < courseNums; j++)
        printf("课程%d\t", j + 1);
    printf("总分\t\t平均分\n");
    NODE *p = head;
    while (p)
    {
        printf("%-16ld\t%-16s\t", p->data.num, p->data.name);
        for (int j = 0; j < courseNums; j++)
            printf("%16.1lf\t", p->data.score[j]);
        printf("%16.2lf\t%16.2lf\n", p->data.sum, p->data.aver);
        p = p->next;
    }
}

// 将学生信息写入文件
void WriteToFile(int stuNums, int courseNums, NODE *head)
{
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL)
    {
        printf("无法打开文件，写入失败！请检查当前目录是否可写。");
        return;
    }
    fprintf(fp, "%10ld%10ld\n", stuNums, courseNums);
    NODE *p = head;
    while (p)
    {
        fprintf(fp, "%10ld%10s", p->data.num, p->data.name);
        for (int j = 0; j < courseNums; j++)
            fprintf(fp, "%10.2f", p->data.score[j]);
        fprintf(fp, "%10.2f%10.2f\n", p->data.sum, p->data.aver);
        p = p->next;
    }
    fclose(fp);
    printf("学生信息已成功写入文件\n");
}

// 从文件读取学生信息
int ReadFromFile(int *stuNums, int *courseNums, NODE **head, int *first)
{
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL)
    {
        printf("无法打开文件，读取失败！请确认文件已存在。");
        return 1;
    }
    fscanf(fp, "%10ld%10ld", stuNums, courseNums);
    // 清空原有链表
    FreeList(*head);
    *head = NULL;
    NODE *tail = NULL;
    for (int i = 0; i < *stuNums; i++)
    {
        NODE *newNode = (NODE *)malloc(sizeof(NODE));
        if (!newNode)
        {
            printf("内存分配失败！\n");
            exit(1);
        }
        fscanf(fp, "%10ld%10s", &newNode->data.num, newNode->data.name);
        for (int j = 0; j < *courseNums; j++)
            fscanf(fp, "%10f", &newNode->data.score[j]);
        fscanf(fp, "%10f%10f", &newNode->data.sum, &newNode->data.aver);
        newNode->next = NULL;
        if (*head == NULL)
        {
            *head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    fclose(fp);
    *first = 0;
    printf("学生信息已成功从文件读取\n");
    return 0;
}

// 释放链表内存
void FreeList(NODE *head)
{
    NODE *p = head;
    while (p)
    {
        NODE *next = p->next;
        free(p);
        p = next;
    }
}