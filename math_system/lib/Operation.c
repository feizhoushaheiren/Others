#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Operation.h"
#include "AccountManage.h"
#include "Question.h"
#include "Queue.h"

void game(Account *current_account, Account accounts[], int account_count)
{
    int acc=0;
    int continue_game = 1;

    srand(time(NULL)); // 初始化随机数种子
    int grade;

    while (continue_game==1) {
    init_acc();
    grade=current_account->grade;
    clock_t start_time = clock();  // 记录开始时间
    printf("\n测试开始\n");
    int digits = grade; // 根据年级设置数字位数
    int result;
    // 进行算术运算测试
    for (int i = 0; i < 10; i++) { // 进行10次测试
        printf("第%d题: ", i + 1);
        choose_question(digits, result, &acc);
    }
    clock_t end_time = clock();
    printf("正确率: %d%% \n", acc*10);
    double time_taken = (double)(end_time - start_time) / 1000;
    printf("用时:%d 分 %.1f 秒\n", (int)time_taken / 60 , time_taken - (int)time_taken / 60 * 60);
    enqueue(&current_account->scoreQueue, acc * 10);
    update_grade(current_account);
    printf("\n是否继续练习？(1:是 0:否): ");
    scanf("%d", &continue_game);
    }
    save_all_accounts_to_file(accounts, account_count, ACCOUNT_FILE_PATH); // 保存账户信息

}

float calculate_average_accuracy(const Account *account) {
    /* 计算平均准确率 */
    float sum = 0;
    int count = account->scoreQueue.count;
    for (int i = 0; i < count; i++) {
    sum += account->scoreQueue.scores[i];
    }
    return count > 0 ? sum / count : 0;
}

int compare_accounts(const void *a, const void *b) {
    /* 比较两个账户 */
    Account *accountA = (Account *)a;
    Account *accountB = (Account *)b;

    float avgA = calculate_average_accuracy(accountA);
    float avgB = calculate_average_accuracy(accountB);
    if (avgA < avgB) return 1;
    if (avgA > avgB) return -1;
    return 0;

}

void sort_accounts(Account accounts[], int account_count) {
    /* 排序账户 */
    qsort(accounts, account_count, sizeof(Account), compare_accounts);
}

int filter_accounts_by_grade(Account accounts[], int account_count, Account filtered_accounts[], int grade) {
    /* 过滤账户 */
    int count = 0;
    for (int i = 0; i < account_count; i++) {
        if (accounts[i].grade == grade) {
            filtered_accounts[count++] = accounts[i];
        }
    }
    return count;
}

void display_ranking_by_grade(Account accounts[], int account_count, int grade) {
    /* 显示指定年级的排行榜 */
    Account filtered_accounts[100];
    int filtered_count = filter_accounts_by_grade(accounts, account_count, filtered_accounts, grade);  // 选择相应年级的账户

    if (filtered_count == 0) {
        printf("没有找到年级为 %d 的账户\n", grade);
        return;
    }

    sort_accounts(filtered_accounts, filtered_count);   // 排序

    printf("年级 %d 的排行榜:\n", grade);
    printf("%-7s\t%10s\t%-4s\t%-10s\n", "排名", "用户名", "年级", "平均准确率");

    int rank = 1;
    for (int i = 0; i < filtered_count; i++) {
        float avg_accuracy = calculate_average_accuracy(&filtered_accounts[i]);
        if (i > 0 && avg_accuracy < calculate_average_accuracy(&filtered_accounts[i - 1])) {
            rank = rank + 1;
        }
        printf("%-6d\t%12s\t%7d\t%12.2f%%\n", rank, filtered_accounts[i].name, filtered_accounts[i].grade, avg_accuracy);
    }
}

void start() {
    int choice;
    char account_name[50];
    Account accounts[100];
    int account_count = 0;
    Account *current_account = NULL;

    while (choice != 6) {
        printf("欢迎使用小学生数学练习系统\n");
        printf("1.登录账号\n");
        printf("2.注册账号\n");
        printf("3.删除账号\n");
        printf("4.显示排行榜\n");
        printf("5.查看历史成绩\n");
        printf("6.退出\n");
        printf("请选择: ");
        scanf("%d", &choice);

        load_accounts_from_file(ACCOUNT_FILE_PATH, accounts, &account_count);

        switch (choice) {
            case 1:
                printf("请输入用户名: ");
                scanf("%s", account_name);
                // 查找用户
                for (int i = 0; i < account_count; i++) {
                    if (strcmp(accounts[i].name, account_name) == 0) {
                        current_account = &accounts[i];
                        printf("欢迎回来，%s\n", current_account->name);
                        printf("您现在的年级为%d年级\n",current_account->grade);
                        printf("是否开始练习(1:是 0:否): ");
                        int start_game;
                        scanf("%d", &start_game);
                        if (start_game) {
                            game(current_account, accounts, account_count);
                        }
                        save_all_accounts_to_file(accounts, account_count, ACCOUNT_FILE_PATH);
                        break;
                    }
                }
                if (current_account == NULL) {
                    printf("用户名不存在，请注册\n");
                    break;
                }
                break;
            case 2:
                printf("请输入用户名: ");
                scanf("%s", account_name);
                // 检查用户名是否已存在
                for (int i = 0; i < account_count; i++) {
                    if (strcmp(accounts[i].name, account_name) == 0) {
                        printf("用户名已存在\n");
                        break;
                    }
                }

                int grade;
                printf("请输入年级(1-6): ");
                scanf("%d", &grade);
                if (grade < 1 || grade > 6) {
                    printf("年级无效\n");
                    return;
                }

                init_account(&accounts[account_count], account_name, grade);
                current_account = &accounts[account_count];
                account_count++;
                save_all_accounts_to_file(accounts, account_count, ACCOUNT_FILE_PATH);
                printf("注册成功\n");
                printf("是否开始练习(1:是 0:否): ");

                int start_game;
                scanf("%d", &start_game);
                if (start_game) {
                    game(current_account, accounts, account_count);
                }
                save_all_accounts_to_file(accounts, account_count, ACCOUNT_FILE_PATH);
                break;
            case 3:
                printf("请输入用户名: ");
                scanf("%s", account_name);
                // 查找用户
                for (int i = 0; i < account_count; i++) {
                    if (strcmp(accounts[i].name, account_name) == 0) {
                        for (int j = i; j < account_count - 1; j++) {
                            accounts[j] = accounts[j + 1];
                        }
                        account_count--;
                        save_all_accounts_to_file(accounts, account_count, ACCOUNT_FILE_PATH);
                        printf("删除成功\n");
                        break;
                    }
                }
                break;
            case 4:
                printf("请输入要查看的年级(1-6): ");
                int grade1;
                scanf("%d", &grade1);
                if (grade1 < 1 || grade1 > 6) {
                    printf("年级无效\n");
                } else {
                    display_ranking_by_grade(accounts, account_count, grade1);
                }
                break;
            case 5:
                printf("请输入查看的用户名: ");
                scanf("%s", account_name);
                // 查找用户
                for (int i = 0; i < account_count; i++) {
                    if (strcmp(accounts[i].name, account_name) == 0) {
                        current_account = &accounts[i];
                        printf("您的历史成绩如下:\n");
                        print_account(current_account);
                        break;
                        } else {
                            printf("用户名不存在\n");
                        break;
                        }
                    }
                break;
            case 6:
                printf("感谢使用，再见\n");
                return;
            default:
                printf("输入无效\n");
                break;
        }
    }
}
