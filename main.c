#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50
#define COURSE_NUM_MAX 10
#define FILENAME_LEN 64

typedef enum { ROLE_ADMIN, ROLE_TEACHER, ROLE_STUDENT, ROLE_UNKNOWN } UserRole;

typedef struct Student {
    long num;
    char name[NAME_LEN];
    int courseCount;
    float score[COURSE_NUM_MAX];
    float sum;
    float aver;
    struct Student *next;
} Student;

typedef struct {
    char username[NAME_LEN];
    char password[NAME_LEN];
    UserRole role;
    long studentNum;
} UserAccount;

static UserAccount accounts[] = {
    {"admin", "admin123", ROLE_ADMIN, 0},
    {"teacher", "teach123", ROLE_TEACHER, 0},
    {"stu001", "pass001", ROLE_STUDENT, 1001},
    {"stu002", "pass002", ROLE_STUDENT, 1002}
};
static const int accountNum = sizeof(accounts) / sizeof(accounts[0]);

static Student *head = NULL;
static int courseCount = 0;
static long currentStudentNum = 0;

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pauseMessage() {
    printf("按回车继续...");
    while (getchar() != '\n');
}

Student* findStudentByNum(long num) {
    Student *p = head;
    while (p) {
        if (p->num == num) return p;
        p = p->next;
    }
    return NULL;
}

void updateComputedFields() {
    Student *p = head;
    while (p) {
        p->sum = 0;
        for (int i = 0; i < p->courseCount; i++) p->sum += p->score[i];
        p->aver = p->courseCount > 0 ? p->sum / p->courseCount : 0;
        p = p->next;
    }
}

void adjustCourseCount() {
    int max = 0;
    Student *p = head;
    while (p) {
        if (p->courseCount > max) max = p->courseCount;
        p = p->next;
    }
    courseCount = max;
}

void addStudent() {
    if (courseCount == 0) {
        printf("请先在管理员权限下设置课程数量。\n");
        return;
    }
    Student *node = malloc(sizeof(Student));
    if (!node) {
        printf("内存分配失败。\n");
        return;
    }

    printf("输入学号: ");
    if (scanf("%ld", &node->num) != 1) { clearInput(); free(node); printf("无效学号。\n"); return; }
    clearInput();
    if (findStudentByNum(node->num)) {
        free(node);
        printf("学号已存在。\n");
        return;
    }

    printf("输入姓名: ");
    fgets(node->name, NAME_LEN, stdin);
    node->name[strcspn(node->name, "\n")] = '\0';

    printf("输入课程数量(1-%d, 默认为 %d): ", COURSE_NUM_MAX, courseCount);
    int c;
    if (scanf("%d", &c) != 1) {
        clearInput(); c = courseCount;
    }
    clearInput();
    if (c <= 0 || c > COURSE_NUM_MAX) c = courseCount;
    node->courseCount = c;

    for (int i = 0; i < node->courseCount; i++) {
        printf("第%d门成绩: ", i + 1);
        if (scanf("%f", &node->score[i]) != 1) {
            clearInput(); node->score[i] = 0;
        }
    }
    clearInput();

    node->next = NULL;
    if (!head) {
        head = node;
    } else {
        Student *p = head;
        while (p->next) p = p->next;
        p->next = node;
    }

    adjustCourseCount();
    updateComputedFields();
    printf("添加成功。\n");
}

void deleteStudentByNum() {
    printf("输入要删除的学号: ");
    long num;
    if (scanf("%ld", &num) != 1) { clearInput(); printf("无效输入。\n"); return; }
    clearInput();

    Student *p = head, *prev = NULL;
    while (p) {
        if (p->num == num) {
            if (prev) prev->next = p->next;
            else head = p->next;
            free(p);
            printf("删除成功。\n");
            adjustCourseCount();
            updateComputedFields();
            return;
        }
        prev = p;
        p = p->next;
    }
    printf("未找到学号 %ld。\n", num);
}

void modifyStudent() {
    printf("输入要修改的学号: ");
    long num;
    if (scanf("%ld", &num) != 1) { clearInput(); printf("无效输入。\n"); return; }
    clearInput();

    Student *p = findStudentByNum(num);
    if (!p) { printf("未找到学号 %ld。\n", num); return; }

    printf("新姓名(回车保留): ");
    char buf[NAME_LEN];
    fgets(buf, NAME_LEN, stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf)) strncpy(p->name, buf, NAME_LEN);

    for (int i = 0; i < p->courseCount; i++) {
        printf("第%d门成绩(%.2f)-> 输入新值：", i + 1, p->score[i]);
        float v;
        if (scanf("%f", &v) == 1) p->score[i] = v;
        clearInput();
    }

    updateComputedFields();
    printf("修改成功。\n");
}

void searchByNum() {
    printf("输入学号: ");
    long num;
    if (scanf("%ld", &num) != 1) { clearInput(); printf("无效输入。\n"); return; }
    clearInput();
    Student *p = findStudentByNum(num);
    if (!p) { printf("未找到学号 %ld。\n", num); return; }

    printf("学号:%ld 姓名:%s 总分:%.2f 平均:%.2f\n", p->num, p->name, p->sum, p->aver);
    for (int i = 0; i < courseCount; i++) {
        if (i < p->courseCount) printf("课%d:%.2f ", i + 1, p->score[i]);
        else printf("课%d:-- ", i + 1);
    }
    printf("\n");
}

void searchByNameDo() {
    printf("输入姓名: ");
    char name[NAME_LEN];
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';

    int count = 0;
    Student *p = head;
    while (p) {
        if (strcmp(p->name, name) == 0) {
            printf("学号:%ld 姓名:%s 总分:%.2f 平均:%.2f\n", p->num, p->name, p->sum, p->aver);
            count++;
        }
        p = p->next;
    }
    if (!count) printf("未找到姓名 %s。\n", name);
}

void printAllStudents() {
    if (!head) { printf("没有学生信息。\n"); return; }
    printf("学号\t姓名\t");
    for (int i = 0; i < courseCount; i++) printf("课%d\t", i + 1);
    printf("总分\t平均\n");

    Student *p = head;
    while (p) {
        printf("%ld\t%s\t", p->num, p->name);
        for (int i = 0; i < courseCount; i++) {
            if (i < p->courseCount) printf("%.2f\t", p->score[i]);
            else printf("--\t");
        }
        printf("%.2f\t%.2f\n", p->sum, p->aver);
        p = p->next;
    }
}

void sortStudentsByNum() {
    if (!head || !head->next) return;
    int swapped;
    do {
        swapped = 0;
        Student *cur = head;
        while (cur->next) {
            if (cur->num > cur->next->num) {
                long num = cur->num;
                char name[NAME_LEN]; strcpy(name, cur->name);
                int cc = cur->courseCount;
                float score[COURSE_NUM_MAX]; memcpy(score, cur->score, sizeof(cur->score));
                float sum = cur->sum, aver = cur->aver;

                cur->num = cur->next->num;
                strcpy(cur->name, cur->next->name);
                cur->courseCount = cur->next->courseCount;
                memcpy(cur->score, cur->next->score, sizeof(cur->score));
                cur->sum = cur->next->sum;
                cur->aver = cur->next->aver;

                cur->next->num = num;
                strcpy(cur->next->name, name);
                cur->next->courseCount = cc;
                memcpy(cur->next->score, score, sizeof(cur->next->score));
                cur->next->sum = sum;
                cur->next->aver = aver;

                swapped = 1;
            }
            cur = cur->next;
        }
    } while (swapped);
    updateComputedFields();
}

void sortStudentsByName() {
    if (!head || !head->next) return;
    int swapped;
    do {
        swapped = 0;
        Student *cur = head;
        while (cur->next) {
            if (strcmp(cur->name, cur->next->name) > 0) {
                long num = cur->num;
                char name[NAME_LEN]; strcpy(name, cur->name);
                int cc = cur->courseCount;
                float score[COURSE_NUM_MAX]; memcpy(score, cur->score, sizeof(cur->score));
                float sum = cur->sum, aver = cur->aver;

                cur->num = cur->next->num;
                strcpy(cur->name, cur->next->name);
                cur->courseCount = cur->next->courseCount;
                memcpy(cur->score, cur->next->score, sizeof(cur->score));
                cur->sum = cur->next->sum;
                cur->aver = cur->next->aver;

                cur->next->num = num;
                strcpy(cur->next->name, name);
                cur->next->courseCount = cc;
                memcpy(cur->next->score, score, sizeof(cur->next->score));
                cur->next->sum = sum;
                cur->next->aver = aver;

                swapped = 1;
            }
            cur = cur->next;
        }
    } while (swapped);
}

void sortStudentsByTotal(int desc) {
    if (!head || !head->next) return;
    int swapped;
    do {
        swapped = 0;
        Student *cur = head;
        while (cur->next) {
            if ((desc && cur->sum < cur->next->sum) || (!desc && cur->sum > cur->next->sum)) {
                long num = cur->num;
                char name[NAME_LEN]; strcpy(name, cur->name);
                int cc = cur->courseCount;
                float score[COURSE_NUM_MAX]; memcpy(score, cur->score, sizeof(cur->score));
                float sum = cur->sum, aver = cur->aver;

                cur->num = cur->next->num;
                strcpy(cur->name, cur->next->name);
                cur->courseCount = cur->next->courseCount;
                memcpy(cur->score, cur->next->score, sizeof(cur->score));
                cur->sum = cur->next->sum;
                cur->aver = cur->next->aver;

                cur->next->num = num;
                strcpy(cur->next->name, name);
                cur->next->courseCount = cc;
                memcpy(cur->next->score, score, sizeof(cur->next->score));
                cur->next->sum = sum;
                cur->next->aver = aver;

                swapped = 1;
            }
            cur = cur->next;
        }
    } while (swapped);
}

void gradeStatistics() {
    if (!head) { printf("无学生数据。\n"); return; }
    int a=0,b=0,c=0,d=0,f=0;
    Student *p = head;
    while (p) {
        if (p->aver >= 90) a++;
        else if (p->aver >= 80) b++;
        else if (p->aver >= 70) c++;
        else if (p->aver >= 60) d++;
        else f++;
        p = p->next;
    }
    int total = a+b+c+d+f;
    printf("优秀:%d, 良好:%d, 中等:%d, 及格:%d, 不及格:%d, 总计:%d\n", a,b,c,d,f,total);
}

void courseStatistics() {
    if (!head || courseCount == 0) { printf("无课程或学生数据。\n"); return; }
    for (int i = 0; i < courseCount; i++) {
        float sum = 0;
        int cnt = 0;
        Student *p = head;
        while (p) {
            if (i < p->courseCount) { sum += p->score[i]; cnt++; }
            p = p->next;
        }
        if (cnt > 0) printf("课程%d 总分 %.2f 平均 %.2f\n", i+1, sum, sum / cnt);
        else printf("课程%d 无有效成绩\n", i+1);
    }
}

void saveToFile() {
    char fname[FILENAME_LEN];
    printf("输入保存文件名: ");
    if (scanf("%63s", fname) != 1) { clearInput(); printf("无效文件名。\n"); return; }
    clearInput();
    FILE *fp = fopen(fname, "w");
    if (!fp) { printf("无法创建文件。\n"); return; }
    fprintf(fp, "%d\n", courseCount);
    Student *p = head;
    while (p) {
        fprintf(fp, "%ld %s %d", p->num, p->name, p->courseCount);
        for (int i = 0; i < p->courseCount; i++) fprintf(fp, " %.2f", p->score[i]);
        fprintf(fp, " %.2f %.2f\n", p->sum, p->aver);
        p = p->next;
    }
    fclose(fp);
    printf("保存完成。\n");
}

void loadFromFile() {
    char fname[FILENAME_LEN];
    printf("输入读取文件名: ");
    if (scanf("%63s", fname) != 1) { clearInput(); printf("无效文件名。\n"); return; }
    clearInput();
    FILE *fp = fopen(fname, "r");
    if (!fp) { printf("无法打开文件。\n"); return; }

    while (head) {
        Student *tmp = head;
        head = head->next;
        free(tmp);
    }

    if (fscanf(fp, "%d", &courseCount) != 1) { printf("文件格式错误。\n"); fclose(fp); return; }

    while (!feof(fp)) {
        Student *p = malloc(sizeof(Student));
        if (!p) break;
        if (fscanf(fp, "%ld %49s %d", &p->num, p->name, &p->courseCount) != 3) { free(p); break; }
        if (p->courseCount > COURSE_NUM_MAX) p->courseCount = COURSE_NUM_MAX;
        for (int i = 0; i < p->courseCount; i++) fscanf(fp, "%f", &p->score[i]);
        fscanf(fp, "%f %f", &p->sum, &p->aver);
        p->next = head;
        head = p;
    }
    fclose(fp);
    updateComputedFields();
    printf("加载完成。\n");
}

UserRole login() {
    char u[NAME_LEN], p[NAME_LEN];
    printf("用户名: ");
    if (scanf("%49s", u) != 1) { clearInput(); return ROLE_UNKNOWN; }
    printf("密码: ");
    if (scanf("%49s", p) != 1) { clearInput(); return ROLE_UNKNOWN; }
    clearInput();

    for (int i = 0; i < accountNum; i++) {
        if (strcmp(accounts[i].username, u) == 0 && strcmp(accounts[i].password, p) == 0) {
            currentStudentNum = accounts[i].studentNum;
            return accounts[i].role;
        }
    }
    printf("用户名或密码错误。\n");
    return ROLE_UNKNOWN;
}

void studentMenu() {
    while (1) {
        printf("\n--- 学生菜单 ---\n");
        printf("1. 查看本人成绩\n");
        printf("2. 按姓名查询（允许查看其他学生）\n");
        printf("0. 退出登录\n");
        printf("选择: ");
        int c;
        if (scanf("%d", &c) != 1) { clearInput(); continue; }
        clearInput();
        if (c == 0) break;
        else if (c == 1) {
            Student *p = findStudentByNum(currentStudentNum);
            if (!p) printf("未找到本人信息。\n");
            else {
                printf("学号:%ld 姓名:%s 总分:%.2f 平均:%.2f\n", p->num, p->name, p->sum, p->aver);
                for (int i = 0; i < courseCount; i++) {
                    if (i < p->courseCount)
                        printf("课%d:%.2f ", i+1, p->score[i]);
                    else
                        printf("课%d:-- ", i+1);
                }
                printf("\n");
            }
        } else if (c == 2) {
            searchByNameDo();
        } else {
            printf("无效选项。\n");
        }
        pauseMessage();
    }
}

void teacherAndAdminMenu(UserRole role) {
    while (1) {
        printf("\n--- %s 菜单 ---\n", role==ROLE_ADMIN?"管理员":"教师");
        printf("1. 添加学生\n");
        printf("2. 删除学生\n");
        printf("3. 修改学生\n");
        printf("4. 学号查询\n");
        printf("5. 姓名查询\n");
        printf("6. 计算成绩\n");
        printf("7. 课程统计\n");
        printf("8. 按学号排序\n");
        printf("9. 按姓名排序\n");
        printf("10. 总分降序\n");
        printf("11. 总分升序\n");
        printf("12. 打印所有\n");
        printf("13. 成绩分析\n");
        printf("14. 保存文件\n");
        printf("15. 读文件\n");
        if (role == ROLE_ADMIN) printf("16. 设置课程数\n");
        printf("0. 退出登录\n");

        printf("选择: ");
        int c;
        if (scanf("%d", &c) != 1) { clearInput(); continue; }
        clearInput();
        if (c == 0) break;
        switch (c) {
            case 1: addStudent(); break;
            case 2: deleteStudentByNum(); break;
            case 3: modifyStudent(); break;
            case 4: searchByNum(); break;
            case 5: searchByNameDo(); break;
            case 6: updateComputedFields(); printf("计算完成。\n"); break;
            case 7: courseStatistics(); break;
            case 8: sortStudentsByNum(); printf("排序完成。\n"); break;
            case 9: sortStudentsByName(); printf("排序完成。\n"); break;
            case 10: sortStudentsByTotal(1); printf("排序完成。\n"); break;
            case 11: sortStudentsByTotal(0); printf("排序完成。\n"); break;
            case 12: printAllStudents(); break;
            case 13: gradeStatistics(); break;
            case 14: saveToFile(); break;
            case 15: loadFromFile(); break;
            case 16:
                if (role == ROLE_ADMIN) {
                    printf("请输入课程数量(1-%d): ", COURSE_NUM_MAX);
                    int v;
                    if (scanf("%d", &v) == 1 && v > 0 && v <= COURSE_NUM_MAX) courseCount = v;
                    else printf("输入无效。");
                    clearInput();
                } else {
                    printf("权限不足。\n");
                }
                break;
            default: printf("无效选项。\n"); break;
        }
        pauseMessage();
    }
}

int main() {
    printf("欢迎使用学生信息管理系统（链表+权限）。\n");

    while (1) {
        printf("\n请先登录。\n");
        UserRole role = login();
        if (role == ROLE_UNKNOWN) continue;

        if (role == ROLE_STUDENT) {
            printf("学生登录成功，学号=%ld。\n", currentStudentNum);
            studentMenu();
        } else {
            teacherAndAdminMenu(role);
        }

        printf("已退出登录。\n");
    }
    return 0;
}
