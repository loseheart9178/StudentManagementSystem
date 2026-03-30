#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
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

// 结构体定义

// 学生结构体
typedef struct student
{
    long num;                // 学号
    char name[NAME_LEN];     // 姓名
    float score[COURSE_NUM]; // 成绩
    float sum;               // 总分
    float aver;               // 平均分
} STU;

//函数声明
int Menu(); // 菜单函数
void SetPosition(int x, int y); // 设置光标位置函数
void InputRecord(int*stuNums,int*courseNums,STU stu[]); // 输入学生信息函数
void AppendRecord(int*stuNums,int*courseNums,STU stu[]); // 追加学生信息函数
void DeleteRecord(int*stuNums,int*courseNums,STU stu[]); // 删除学生信息函数
void SearchByNum(int stuNums,int courseNums,STU stu[]); // 按学号查询学生信息函数
void SearchByName(int stuNums,int courseNums,STU stu[]); // 按姓名查询学生信息函数
void ModifyRecord(int stuNums,int courseNums,STU stu[]); // 修改学生信息函数
void CalculateScoreOfStudent(int stuNums,int courseNums,STU stu[]); // 计算学生成绩函数
void CalculateScoreOfCourse(int stuNums,int courseNums,STU stu[]); // 计算课程成绩函数
void SortByNum(int stuNums,int courseNums,STU stu[]); // 按学号排序函数
void SortByName(int stuNums,int courseNums,STU stu[]); // 按姓名排序函数
void SortByScore(int stuNums,int courseNums,STU stu[],int (*compare)(float a,float b)); // 按总分排序函数
int Accending(float a,float b); // 升序比较函数
int Decending(float a,float b); // 降序比较函数
void StatisticAnalysis(int stuNums,int courseNums,STU stu[]); // 统计分析函数
void PrintRecord(int stuNums,int courseNums,STU stu[]); // 打印学生信息函数
void WriteToFile(int stuNums,int courseNums,STU stu[]); // 将学生信息写入文件函数
void ReadFromFile(int*stuNums,int*courseNums,STU stu[],int*first); // 从文件读取学生信息函数


// 主函数入口
int main(){
    int stuNums=0;
    int courseNums=0;
    int i,j;
    int choice;
    int first=1; // 标志变量，表示是否第一次运行程序
    STU stu[STU_NUM]; // 学生数组

    system("mode con: cols=130 lines=60"); // 设置控制台窗口大小
    system("color 0E"); // 设置控制台颜色
    while (1)
    {
        system("cls"); // 清屏
        choice=Menu(); // 显示菜单并获取用户选择
        switch (choice)
        {
            case 1:
            system("cls");
            InputRecord(&stuNums, &courseNums, stu);
            system("pause");
            break;
            case 2:
            system("cls");
            AppendRecord(&stuNums, &courseNums, stu);
            system("pause");
            break;
            case 3:
            system("cls");
            DeleteRecord(&stuNums, &courseNums, stu);
            system("pause");
            break;
            case 4:
            system("cls");
            SearchByNum(stuNums, courseNums, stu);
            system("pause");
            break;
            case 5:
            system("cls");
            SearchByName(stuNums, courseNums, stu);
            system("pause");
            break;
            case 6:
            system("cls");
            ModifyRecord(stuNums, courseNums, stu);
            system("pause");
            break;
            case 7:
            system("cls");
            CalculateScoreOfStudent(stuNums, courseNums, stu);
            system("pause");
            break;
            case 8:
            system("cls");
            CalculateScoreOfCourse(stuNums, courseNums, stu);
            system("pause");
            break;
            case 9:
            system("cls");
            SortByNum(stuNums, courseNums, stu);
            system("pause");
            break;
            case 10:
            system("cls");
            SortByName(stuNums, courseNums, stu);
            system("pause");
            break;
            case 11:
            system("cls");
            SortByScore(stuNums, courseNums, stu, Decending);
            PrintRecord(stuNums, courseNums, stu);
            system("pause");
            break;
            case 12:
            system("cls");
            SortByScore(stuNums, courseNums, stu, Accending);
            PrintRecord(stuNums, courseNums, stu);
            system("pause");
            break;
            case 13:
            system("cls");
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
            WriteToFile(stuNums, courseNums, stu);
            system("pause");
            break;
            case 16:
            system("cls");
            ReadFromFile(&stuNums, &courseNums, stu, &first);
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

int Menu(){
    int posy=5;
    int choice;
    int i,j;
    SetPosition(POS_X3,posy);
    printf("学生成绩管理系统");
    for (int i = 0; i <2; i++){
        SetPosition(POS_X1,++posy);
        for(int j=0;j<55;j++){
            printf("-");
        }
    }
    SetPosition(POS_X1,++posy);
    printf("1.输入学生信息");
    SetPosition(POS_X4,posy);
    printf("2.增加学生成绩");
    SetPosition(POS_X1,posy+=2);
    printf("3.删除学生信息");
    SetPosition(POS_X4,posy);
    printf("4.按学号查询学生信息");
    SetPosition(POS_X1,posy+=2);
    printf("5.按姓名查询学生信息");
    SetPosition(POS_X4,posy);
    printf("6.修改学生信息");
    SetPosition(POS_X1,posy+=2);
    printf("7.计算学生成绩");
    SetPosition(POS_X4,posy);
    printf("8.计算课程成绩");
    SetPosition(POS_X1,posy+=2);
    printf("9.按学号排序");
    SetPosition(POS_X4,posy);
    printf("10.按姓名排序");
    SetPosition(POS_X1,posy+=2);
    printf("11.按总分降序排序");
    SetPosition(POS_X4,posy);
    printf("12.按总分升序排序");
    SetPosition(POS_X1,posy+=2);
    printf("13.学生成绩统计");
    SetPosition(POS_X4,posy);
    printf("14.打印学生信息");
    SetPosition(POS_X1,posy+=2);
    printf("15.学生记录存盘");
    SetPosition(POS_X4,posy);
    printf("16.从磁盘读取学生记录");
    SetPosition(POS_X1,posy+=2);
    printf("0.退出系统");

    //输出功能与输入提示之间的分隔线
    for(int i=0;i<2;i++){
        SetPosition(POS_X1,++posy);
        for(int j=0;j<55;j++){
            printf("-");
        }
    }
    // 提示用户输入功能编号
    SetPosition(POS_X1,++posy);
    printf("请输入功能编号[0-16]:[]\b\b\b");
    scanf("%d",&choice);
    return choice;
}

void SetPosition(int x, int y){

    HANDLE hOut;
    COORD pos;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void InputRecord(int*stuNums,int*courseNums,STU stu[]){
    int i,j;
    int posy=6;
    SetPosition(POS_X2,posy);
    printf("请输入学生人数(stuNums<%d):", STU_NUM);
    scanf("%d",stuNums);
    SetPosition(POS_X2,posy+=2);
    printf("请输入课程数量(courseNums<%d):", COURSE_NUM);
    scanf("%d",courseNums);
    for(int i=0;i<2;i++){
        SetPosition(POS_X1,++posy);
        for(int j=0;j<55;j++){
            printf("-");
        }
    }
    SetPosition(POS_X1,++posy);
    printf("请依次输入学生的学号、姓名和%d门课程的成绩:",*courseNums);
    for (i = 0; i < *stuNums; i++){
        printf("请输入第%d个学生信息:\t",i+1);
        scanf("%ld%s", &stu[i].num, stu[i].name);
        for (j = 0; j < *courseNums; j++){
            scanf("%f", &stu[i].score[j]);
        }
    }
}

// 追加学生信息
void AppendRecord(int*stuNums,int*courseNums,STU stu[]){
    int i;
    int newStuNum = *stuNums + 1;
    if(newStuNum > STU_NUM){
        SetPosition(POS_X2, 10);
        printf("学生人数已达上限，无法追加！");
        return;
    }
    SetPosition(POS_X2, 10);
    printf("请输入新学生的信息：\n");
    SetPosition(POS_X2, 12);
    printf("学号：");
    scanf("%ld", &stu[*stuNums].num);
    SetPosition(POS_X2, 14);
    printf("姓名：");
    scanf("%s", stu[*stuNums].name);
    for(i = 0; i < *courseNums; i++){
        SetPosition(POS_X2, 16 + i);
        printf("第%d门课程成绩：", i+1);
        scanf("%f", &stu[*stuNums].score[i]);
    }
    (*stuNums)++;
    SetPosition(POS_X2, 20);
    printf("追加成功！");
}

// 删除学生信息
void DeleteRecord(int*stuNums,int*courseNums,STU stu[]){
    long delNum;
    int i, j, found = 0;
    SetPosition(POS_X2, 10);
    printf("请输入要删除的学生学号：");
    scanf("%ld", &delNum);

    for(i = 0; i < *stuNums; i++){
        if(stu[i].num == delNum){
            found = 1;
            for(j = i; j < *stuNums - 1; j++){
                stu[j] = stu[j+1];
            }
            (*stuNums)--;
            SetPosition(POS_X2, 12);
            printf("学号为%ld的学生已删除！", delNum);
            break;
        }
    }
    if(!found){
        SetPosition(POS_X2, 12);
        printf("未找到学号为%ld的学生！", delNum);
    }
}

// 按学号查询学生信息
void SearchByNum(int stuNums,int courseNums,STU stu[]){
    long searchNum;
    int i, j, found = 0;
    SetPosition(POS_X2, 10);
    printf("请输入要查询的学号：");
    scanf("%ld", &searchNum);

    for(i = 0; i < stuNums; i++){
        if(stu[i].num == searchNum){
            found = 1;
            SetPosition(POS_X2, 12);
            printf("找到学生信息：\n");
            SetPosition(POS_X2, 14);
            printf("学号：%ld\n", stu[i].num);
            SetPosition(POS_X2, 16);
            printf("姓名：%s\n", stu[i].name);
            for(j = 0; j < courseNums; j++){
                SetPosition(POS_X2, 18 + j);
                printf("第%d门课程成绩：%.2f\n", j+1, stu[i].score[j]);
            }
            if(stu[i].sum > 0){
                SetPosition(POS_X2, 18 + courseNums);
                printf("总分：%.2f   平均分：%.2f\n", stu[i].sum, stu[i].aver);
            }
            break;
        }
    }
    if(!found){
        SetPosition(POS_X2, 12);
        printf("未找到学号为%ld的学生！", searchNum);
    }
}

// 按姓名查询学生信息
void SearchByName(int stuNums,int courseNums,STU stu[]){
    char searchName[NAME_LEN];
    int i, j, found = 0;
    SetPosition(POS_X2, 10);
    printf("请输入要查询的姓名：");
    scanf("%s", searchName);

    for(i = 0; i < stuNums; i++){
        if(strcmp(stu[i].name, searchName) == 0){
            found++;
            SetPosition(POS_X2, 12 + found*2);
            printf("找到学生信息 - 序号%d：\n", found);
            SetPosition(POS_X2, 14 + found*2);
            printf("学号：%ld\n", stu[i].num);
            SetPosition(POS_X2, 16 + found*2);
            printf("姓名：%s\n", stu[i].name);
            for(j = 0; j < courseNums; j++){
                SetPosition(POS_X2, 18 + found*2 + j);
                printf("第%d门课程成绩：%.2f\n", j+1, stu[i].score[j]);
            }
            if(stu[i].sum > 0){
                SetPosition(POS_X2, 18 + found*2 + courseNums);
                printf("总分：%.2f   平均分：%.2f\n", stu[i].sum, stu[i].aver);
            }
        }
    }
    if(found == 0){
        SetPosition(POS_X2, 12);
        printf("未找到姓名为%s的学生！", searchName);
    }
    if(found > 0){
        SetPosition(POS_X2, 18 + found*2 + courseNums + 2);
        printf("共找到%d个匹配的学生", found);
    }
}

// 修改学生信息
void ModifyRecord(int stuNums,int courseNums,STU stu[]){
    long modifyNum;
    int i, j, found = 0;
    SetPosition(POS_X2, 10);
    printf("请输入要修改的学生学号：");
    scanf("%ld", &modifyNum);

    for(i = 0; i < stuNums; i++){
        if(stu[i].num == modifyNum){
            found = 1;
            SetPosition(POS_X2, 12);
            printf("请输入新的信息：\n");
            SetPosition(POS_X2, 14);
            printf("新学号：");
            scanf("%ld", &stu[i].num);
            SetPosition(POS_X2, 16);
            printf("新姓名：");
            scanf("%s", stu[i].name);
            for(j = 0; j < courseNums; j++){
                SetPosition(POS_X2, 18 + j);
                printf("第%d门课程新成绩：", j+1);
                scanf("%f", &stu[i].score[j]);
            }
            stu[i].sum = 0;
            stu[i].aver = 0;
            SetPosition(POS_X2, 20 + courseNums);
            printf("修改成功！");
            break;
        }
    }
    if(!found){
        SetPosition(POS_X2, 12);
        printf("未找到学号为%ld的学生！", modifyNum);
    }
}

// 计算每个学生的总分和平均分
void CalculateScoreOfStudent(int stuNums,int courseNums,STU stu[]){
    int i, j;
    float sum;
    for(i = 0; i < stuNums; i++){
        sum = 0;
        for(j = 0; j < courseNums; j++){
            sum += stu[i].score[j];
        }
        stu[i].sum = sum;
        stu[i].aver = sum / courseNums;
    }
    SetPosition(POS_X2, 10);
    printf("已计算完成所有%d个学生的总分和平均分！", stuNums);
}

// 计算每门课程的总分和平均分
void CalculateScoreOfCourse(int stuNums,int courseNums,STU stu[]){
    int i, j;
    float sum, aver;
    SetPosition(POS_X2, 10);
    printf("各门课程统计结果：\n");
    for(j = 0; j < courseNums; j++){
        sum = 0;
        for(i = 0; i < stuNums; i++){
            sum += stu[i].score[j];
        }
        aver = sum / stuNums;
        SetPosition(POS_X2, 12 + j);
        printf("第%d门课：总分 = %.2f，平均分 = %.2f\n", j+1, sum, aver);
    }
}

// 按学号排序
void SortByNum(int stuNums,int courseNums,STU stu[]){
    int i, j;
    STU temp;
    // 升序排序
    for(i = 0; i < stuNums - 1; i++){
        for(j = i + 1; j < stuNums; j++){
            if(stu[i].num > stu[j].num){
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
void SortByName(int stuNums,int courseNums,STU stu[]){
    int i, j;
    STU temp;
    for(i = 0; i < stuNums - 1; i++){
        for(j = i + 1; j < stuNums; j++){
            if(strcmp(stu[i].name, stu[j].name) > 0){
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
int Accending(float a,float b){
    return a < b;
}

// 降序比较函数
int Decending(float a,float b){
    return a > b;
}

// 按总分排序
void SortByScore(int stuNums,int courseNums,STU stu[],int (*compare)(float a,float b)){
    int i, j;
    STU temp;
    for(i = 0; i < stuNums - 1; i++){
        for(j = i + 1; j < stuNums; j++){
            if(!compare(stu[i].sum, stu[j].sum)){
                temp = stu[i];
                stu[i] = stu[j];
                stu[j] = temp;
            }
        }
    }
}

// 统计分析成绩分布
void StatisticAnalysis(int stuNums,int courseNums,STU stu[]){
    int excellent = 0, good = 0, medium = 0, pass = 0, fail = 0;
    int i, j;
    float score;

    if(stuNums == 0){
        SetPosition(POS_X2, 10);
        printf("没有学生信息！");
        return;
    }

    // 统计所有学生平均分的等级分布
    for(i = 0; i < stuNums; i++){
        score = stu[i].aver;

        if(score >= 90) excellent++;
        else if(score >= 80) good++;
        else if(score >= 70) medium++;
        else if(score >= 60) pass++;
        else fail++;
    }

    SetPosition(POS_X2, 10);
    printf("成绩统计分析（按平均分）：\n");
    SetPosition(POS_X2, 12);
    printf("优秀(90-100)：%d人 (%.1f%%)\n", excellent, (float)excellent/stuNums*100);
    SetPosition(POS_X2, 14);
    printf("良好(80-89)：%d人 (%.1f%%)\n", good, (float)good/stuNums*100);
    SetPosition(POS_X2, 16);
    printf("中等(70-79)：%d人 (%.1f%%)\n", medium, (float)medium/stuNums*100);
    SetPosition(POS_X2, 18);
    printf("及格(60-69)：%d人 (%.1f%%)\n", pass, (float)pass/stuNums*100);
    SetPosition(POS_X2, 20);
    printf("不及格(<60)：%d人 (%.1f%%)\n", fail, (float)fail/stuNums*100);
}

// 打印所有学生信息
void PrintRecord(int stuNums,int courseNums,STU stu[]){
    int i, j;
    if(stuNums == 0){
        SetPosition(POS_X2, 10);
        printf("没有学生信息！");
        return;
    }

    SetPosition(0, 5);
    printf("====================================================================================================\n");
    printf("序号\t学号\t\t姓名\t\t");
    for(j = 0; j < courseNums; j++){
        printf("课程%d\t", j+1);
    }
    printf("总分\t平均分\n");
    printf("----------------------------------------------------------------------------------------------------\n");

    for(i = 0; i < stuNums; i++){
        printf("%d\t%ld\t\t%s\t\t", i+1, stu[i].num, stu[i].name);
        for(j = 0; j < courseNums; j++){
            printf("%.1f\t", stu[i].score[j]);
        }
        printf("%.1f\t%.2f\n", stu[i].sum, stu[i].aver);
    }
    printf("====================================================================================================\n");
    printf("共计：%d个学生\n", stuNums);
}

// 将学生信息写入文件
void WriteToFile(int stuNums,int courseNums,STU stu[]){
    FILE *fp;
    int i, j;
    char filename[50];
    SetPosition(POS_X2, 10);
    printf("请输入要保存的文件名：");
    scanf("%s", filename);

    fp = fopen(filename, "w");
    if(fp == NULL){
        SetPosition(POS_X2, 12);
        printf("无法打开文件写入！");
        return;
    }

    fprintf(fp, "%d %d\n", stuNums, courseNums);
    for(i = 0; i < stuNums; i++){
        fprintf(fp, "%ld %s ", stu[i].num, stu[i].name);
        for(j = 0; j < courseNums; j++){
            fprintf(fp, "%.2f ", stu[i].score[j]);
        }
        fprintf(fp, "%.2f %.2f\n", stu[i].sum, stu[i].aver);
    }
    fclose(fp);
    SetPosition(POS_X2, 14);
    printf("数据已成功写入文件 %s！", filename);
}

// 从文件读取学生信息
void ReadFromFile(int*stuNums,int*courseNums,STU stu[],int*first){
    FILE *fp;
    int i, j;
    char filename[50];
    SetPosition(POS_X2, 10);
    printf("请输入要读取的文件名：");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if(fp == NULL){
        SetPosition(POS_X2, 12);
        printf("文件不存在，无法读取！");
        return;
    }

    // 如果不是第一次读取，清空原有数据
    if(!(*first)){
        *stuNums = 0;
        *courseNums = 0;
    }

    fscanf(fp, "%d %d", stuNums, courseNums);
    for(i = 0; i < *stuNums; i++){
        fscanf(fp, "%ld %s", &stu[i].num, stu[i].name);
        for(j = 0; j < *courseNums; j++){
            fscanf(fp, "%f", &stu[i].score[j]);
        }
        fscanf(fp, "%f %f", &stu[i].sum, &stu[i].aver);
    }
    fclose(fp);
    *first = 0;
    SetPosition(POS_X2, 14);
    printf("已从文件 %s 中读取了%d个学生信息！", filename, *stuNums);
}
