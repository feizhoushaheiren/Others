#include <stdio.h>
#include <string.h>
#include "Queue.h"
#include "AccountManage.h"

void init_account(Account *account, const char *name, int grade) {
    /* 初始化账户 */
    strncpy(account->name, name, sizeof(account->name) - 1);
    account->name[sizeof(account->name) - 1] = '\0';
    account->grade = grade;
    init_queue(&account->scoreQueue);
}

void load_accounts_from_file(const char *filename, Account accounts[], int *account_count) {
    /* 从文件读取账户信息 */
    FILE *file = fopen(ACCOUNT_FILE_PATH, "r");
    if (file == NULL) {
        perror("打开文件错误");
        return;
    }

    char name[50];
    int grade;
    float score;
    int count = 0;

    while (fscanf(file, "%s %d", name, &grade) != EOF) {
        // 读取年级
        init_account(&accounts[count], name, grade);
        for (int i = 0; i < QUEUE_SIZE; i++) {
            if (fscanf(file, "%f", &score) == 1) {
                enqueue(&accounts[count].scoreQueue, score);
            } else {
                break;
            }
        }
        count++;
    }
    // 更新账户数量
    *account_count = count;
    fclose(file);
}

void print_account(const Account *account) {
    /* 打印账户信息 */
    printf("用户名: %s, 年级: %d, 成绩:", account->name, account->grade);
    for (int i = 0; i < account->scoreQueue.count; i++) {
        printf(" %.2f", account->scoreQueue.scores[(account->scoreQueue.front + i) % QUEUE_SIZE]);
    }
    printf("\n");
}

void print_accounts_from_file(const char *filename) {
    /* 打印文件中的账户信息 */
    FILE *file = fopen(ACCOUNT_FILE_PATH, "r");
    if (file == NULL) {
        perror("打开文件错误");
        return;
    }

    char name[50];
    int grade;
    float score;
    while (fscanf(file, "%s %d", name, &grade) != EOF) {
        printf("用户名: %s, 年级: %d, 成绩:", name, grade);
        for (int i = 0; i < QUEUE_SIZE; i++) {
            if (fscanf(file, "%f", &score) == 1) {
                printf(" %.2f", score);
            } else {
                break;
            }
        }
        printf("\n");
    }

    fclose(file);
}

void save_all_accounts_to_file(Account accounts[], int account_count, const char *filename) {
    /* 保存账户信息到文件 */
    FILE *file = fopen(ACCOUNT_FILE_PATH, "w");
    if (file == NULL) {
        perror("打开文件错误");
        return;
    }

    for (int i = 0; i < account_count; i++) {
        fprintf(file, "%s %d", accounts[i].name, accounts[i].grade);
        for (int j = 0; j < accounts[i].scoreQueue.count; j++) {
            fprintf(file, " %.2f", accounts[i].scoreQueue.scores[(accounts[i].scoreQueue.front + j) % QUEUE_SIZE]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void update_grade(Account *account) {
    /* 更新账户等级 */
    if (account->scoreQueue.count >= 5) {
        float sum = 0;
        for (int i = 0; i < 5; i++) {
            sum += account->scoreQueue.scores[(account->scoreQueue.front + i) % QUEUE_SIZE];
        }
        float average = sum / 5;
        if (average > 80 && account->grade < 6) {
            account->grade++;
            printf("恭喜 %s 晋级到 %d 年级\n", account->name, account->grade);
            init_queue(&account->scoreQueue); // 升级后清空成绩
        }
    }
}


