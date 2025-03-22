#ifndef MATH_OPERATION_H
#define MATH_OPERATION_H

#include "AccountManage.h"
#include "Question.h"
#include "Queue.h"
#include <stdio.h>
#include <string.h>

// ��Ϸģ��
void game(Account *current_account, Account accounts[], int account_count);

// ����ƽ��׼ȷ��
float calculate_average_accuracy(const Account *account);

// ����͹���ģ��
int compare_accounts(const void *a, const void *b);
void sort_accounts(Account accounts[], int account_count);
int filter_accounts_by_grade(Account accounts[], int account_count, Account filtered_accounts[], int grade);
void display_ranking_by_grade(Account accounts[], int account_count, int grade);

// ������ģ��
void start();

#endif // MATH_OPERATION_H