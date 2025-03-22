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

    srand(time(NULL)); // ��ʼ�����������
    int grade;

    while (continue_game==1) {
    init_acc();
    grade=current_account->grade;
    clock_t start_time = clock();  // ��¼��ʼʱ��
    printf("\n���Կ�ʼ\n");
    int digits = grade; // �����꼶��������λ��
    int result;
    // ���������������
    for (int i = 0; i < 10; i++) { // ����10�β���
        printf("��%d��: ", i + 1);
        choose_question(digits, result, &acc);
    }
    clock_t end_time = clock();
    printf("��ȷ��: %d%% \n", acc*10);
    double time_taken = (double)(end_time - start_time) / 1000;
    printf("��ʱ:%d �� %.1f ��\n", (int)time_taken / 60 , time_taken - (int)time_taken / 60 * 60);
    enqueue(&current_account->scoreQueue, acc * 10);
    update_grade(current_account);
    printf("\n�Ƿ������ϰ��(1:�� 0:��): ");
    scanf("%d", &continue_game);
    }
    save_all_accounts_to_file(accounts, account_count, ACCOUNT_FILE_PATH); // �����˻���Ϣ

}

float calculate_average_accuracy(const Account *account) {
    /* ����ƽ��׼ȷ�� */
    float sum = 0;
    int count = account->scoreQueue.count;
    for (int i = 0; i < count; i++) {
    sum += account->scoreQueue.scores[i];
    }
    return count > 0 ? sum / count : 0;
}

int compare_accounts(const void *a, const void *b) {
    /* �Ƚ������˻� */
    Account *accountA = (Account *)a;
    Account *accountB = (Account *)b;

    float avgA = calculate_average_accuracy(accountA);
    float avgB = calculate_average_accuracy(accountB);
    if (avgA < avgB) return 1;
    if (avgA > avgB) return -1;
    return 0;

}

void sort_accounts(Account accounts[], int account_count) {
    /* �����˻� */
    qsort(accounts, account_count, sizeof(Account), compare_accounts);
}

int filter_accounts_by_grade(Account accounts[], int account_count, Account filtered_accounts[], int grade) {
    /* �����˻� */
    int count = 0;
    for (int i = 0; i < account_count; i++) {
        if (accounts[i].grade == grade) {
            filtered_accounts[count++] = accounts[i];
        }
    }
    return count;
}

void display_ranking_by_grade(Account accounts[], int account_count, int grade) {
    /* ��ʾָ���꼶�����а� */
    Account filtered_accounts[100];
    int filtered_count = filter_accounts_by_grade(accounts, account_count, filtered_accounts, grade);  // ѡ����Ӧ�꼶���˻�

    if (filtered_count == 0) {
        printf("û���ҵ��꼶Ϊ %d ���˻�\n", grade);
        return;
    }

    sort_accounts(filtered_accounts, filtered_count);   // ����

    printf("�꼶 %d �����а�:\n", grade);
    printf("%-7s\t%10s\t%-4s\t%-10s\n", "����", "�û���", "�꼶", "ƽ��׼ȷ��");

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
        printf("��ӭʹ��Сѧ����ѧ��ϰϵͳ\n");
        printf("1.��¼�˺�\n");
        printf("2.ע���˺�\n");
        printf("3.ɾ���˺�\n");
        printf("4.��ʾ���а�\n");
        printf("5.�鿴��ʷ�ɼ�\n");
        printf("6.�˳�\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);

        load_accounts_from_file(ACCOUNT_FILE_PATH, accounts, &account_count);

        switch (choice) {
            case 1:
                printf("�������û���: ");
                scanf("%s", account_name);
                // �����û�
                for (int i = 0; i < account_count; i++) {
                    if (strcmp(accounts[i].name, account_name) == 0) {
                        current_account = &accounts[i];
                        printf("��ӭ������%s\n", current_account->name);
                        printf("�����ڵ��꼶Ϊ%d�꼶\n",current_account->grade);
                        printf("�Ƿ�ʼ��ϰ(1:�� 0:��): ");
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
                    printf("�û��������ڣ���ע��\n");
                    break;
                }
                break;
            case 2:
                printf("�������û���: ");
                scanf("%s", account_name);
                // ����û����Ƿ��Ѵ���
                for (int i = 0; i < account_count; i++) {
                    if (strcmp(accounts[i].name, account_name) == 0) {
                        printf("�û����Ѵ���\n");
                        break;
                    }
                }

                int grade;
                printf("�������꼶(1-6): ");
                scanf("%d", &grade);
                if (grade < 1 || grade > 6) {
                    printf("�꼶��Ч\n");
                    return;
                }

                init_account(&accounts[account_count], account_name, grade);
                current_account = &accounts[account_count];
                account_count++;
                save_all_accounts_to_file(accounts, account_count, ACCOUNT_FILE_PATH);
                printf("ע��ɹ�\n");
                printf("�Ƿ�ʼ��ϰ(1:�� 0:��): ");

                int start_game;
                scanf("%d", &start_game);
                if (start_game) {
                    game(current_account, accounts, account_count);
                }
                save_all_accounts_to_file(accounts, account_count, ACCOUNT_FILE_PATH);
                break;
            case 3:
                printf("�������û���: ");
                scanf("%s", account_name);
                // �����û�
                for (int i = 0; i < account_count; i++) {
                    if (strcmp(accounts[i].name, account_name) == 0) {
                        for (int j = i; j < account_count - 1; j++) {
                            accounts[j] = accounts[j + 1];
                        }
                        account_count--;
                        save_all_accounts_to_file(accounts, account_count, ACCOUNT_FILE_PATH);
                        printf("ɾ���ɹ�\n");
                        break;
                    }
                }
                break;
            case 4:
                printf("������Ҫ�鿴���꼶(1-6): ");
                int grade1;
                scanf("%d", &grade1);
                if (grade1 < 1 || grade1 > 6) {
                    printf("�꼶��Ч\n");
                } else {
                    display_ranking_by_grade(accounts, account_count, grade1);
                }
                break;
            case 5:
                printf("������鿴���û���: ");
                scanf("%s", account_name);
                // �����û�
                for (int i = 0; i < account_count; i++) {
                    if (strcmp(accounts[i].name, account_name) == 0) {
                        current_account = &accounts[i];
                        printf("������ʷ�ɼ�����:\n");
                        print_account(current_account);
                        break;
                        } else {
                            printf("�û���������\n");
                        break;
                        }
                    }
                break;
            case 6:
                printf("��лʹ�ã��ټ�\n");
                return;
            default:
                printf("������Ч\n");
                break;
        }
    }
}
