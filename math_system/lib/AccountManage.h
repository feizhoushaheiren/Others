#ifndef ACCOUNT_MANAGE_H
#define ACCOUNT_MANAGE_H

#include "Queue.h"
#define ACCOUNT_FILE_PATH "C:\\Users\\13629\\Desktop\\math1\\data\\account.txt"
typedef struct {
    char name[50];
    int grade;
    Queue scoreQueue;
} Account;

void init_account(Account *account, const char *name, int grade);
void load_accounts_from_file(const char *filename, Account accounts[], int *account_count);
void print_account(const Account *account);
void save_all_accounts_to_file(Account accounts[], int account_count, const char *filename);
void update_grade(Account *account);


#endif