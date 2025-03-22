#include <stdio.h>
#include <string.h>
#include "Queue.h"
#include "AccountManage.h"

void init_account(Account *account, const char *name, int grade) {
    /* ��ʼ���˻� */
    strncpy(account->name, name, sizeof(account->name) - 1);
    account->name[sizeof(account->name) - 1] = '\0';
    account->grade = grade;
    init_queue(&account->scoreQueue);
}

void load_accounts_from_file(const char *filename, Account accounts[], int *account_count) {
    /* ���ļ���ȡ�˻���Ϣ */
    FILE *file = fopen(ACCOUNT_FILE_PATH, "r");
    if (file == NULL) {
        perror("���ļ�����");
        return;
    }

    char name[50];
    int grade;
    float score;
    int count = 0;

    while (fscanf(file, "%s %d", name, &grade) != EOF) {
        // ��ȡ�꼶
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
    // �����˻�����
    *account_count = count;
    fclose(file);
}

void print_account(const Account *account) {
    /* ��ӡ�˻���Ϣ */
    printf("�û���: %s, �꼶: %d, �ɼ�:", account->name, account->grade);
    for (int i = 0; i < account->scoreQueue.count; i++) {
        printf(" %.2f", account->scoreQueue.scores[(account->scoreQueue.front + i) % QUEUE_SIZE]);
    }
    printf("\n");
}

void print_accounts_from_file(const char *filename) {
    /* ��ӡ�ļ��е��˻���Ϣ */
    FILE *file = fopen(ACCOUNT_FILE_PATH, "r");
    if (file == NULL) {
        perror("���ļ�����");
        return;
    }

    char name[50];
    int grade;
    float score;
    while (fscanf(file, "%s %d", name, &grade) != EOF) {
        printf("�û���: %s, �꼶: %d, �ɼ�:", name, grade);
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
    /* �����˻���Ϣ���ļ� */
    FILE *file = fopen(ACCOUNT_FILE_PATH, "w");
    if (file == NULL) {
        perror("���ļ�����");
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
    /* �����˻��ȼ� */
    if (account->scoreQueue.count >= 5) {
        float sum = 0;
        for (int i = 0; i < 5; i++) {
            sum += account->scoreQueue.scores[(account->scoreQueue.front + i) % QUEUE_SIZE];
        }
        float average = sum / 5;
        if (average > 80 && account->grade < 6) {
            account->grade++;
            printf("��ϲ %s ������ %d �꼶\n", account->name, account->grade);
            init_queue(&account->scoreQueue); // ��������ճɼ�
        }
    }
}


