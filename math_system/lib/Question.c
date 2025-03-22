#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Question.h"

int acc=0;

// ���ڴ洢�ѳ��ֵ���Ŀ
char questions_history[MAX_QUESTIONS][MAX_LENGTH];
int question_count = 0;

// �ж���Ŀ�Ƿ��Ѿ����ֹ�
int is_question_repeated(const char* question) {
    for (int i = 0; i < question_count; i++) {
        if (strcmp(questions_history[i], question) == 0) {
            return 1; // ��Ŀ�ѳ���
        }
    }
    return 0; // ��Ŀδ����
}

// ����Ŀ��¼����ʷ���
void record_question(const char* question) {
    if (question_count < MAX_QUESTIONS) {
        strcpy(questions_history[question_count], question);
        question_count++;
    }
}
// �������ָ����Χ�ڵ�����,���ڼӼ���
int random_number_a(int digits) {
    int min;
    int max;
    if (digits==1)
    {
        max=1;
        min=1;
    }
    if (digits==2)
    {
        max=5;
        min=1;
    }
    if (digits>2)
    {
        max=100;
        min=1;
    }
    max = max * 10 - 1; // ���ɵ����ֵ
    return rand() % (max - min + 1) + min;//���ɣ�����������
}

// �������ָ����Χ�ڵ�����,���ڳ˷�
int random_number_b(int digits) {
    int min;
    int max;
    if (digits==2)
    {
        max=1;
        min=1;
    }
    if (digits==3)
    {
        max=5;
        min=1;
    }
    if (digits>3 && digits<6)
    {
        max=10;
        min=1;
    }
    if (digits==6)
    {
        max=20;
        min=1;
    }
    max = max * 10 - 1; // ���ɵ����ֵ
    return rand() % (max - min + 1) + min;//���ɣ�����������
}

// �������ָ����Χ�ڵ�����,���ڳ���
int random_number_c(int digits) {
    int min;
    int max;
    if (digits==2)
    {
        max=1;
        min=1;
    }
    if (digits==3)
    {
        max=5;
        min=1;
    }
    if (digits>3)
    {
        max=10;
        min=1;
    }
    max = max * 10 - 1; // ���ɵ����ֵ
    return rand() % (max - min + 1) + min;//���ɣ�����������
}

// �������ָ����Χ�ڵ�����,���ڷ�ʽ����
int random_number_d(int digits) {
    int min;
    int max;
    if (digits>5)
    {
        max=1.2;
        min=1;
    }
    max = max * 10 - 1; // ���ɵ����ֵ
    return rand() % (max - min + 1) + min;
}

// �ӷ�����
int addition(int digits) {
    int a = random_number_a(digits);
    int b = random_number_a(digits);
    char question[MAX_LENGTH];

    // ������Ŀ�ַ���
    sprintf(question, "%d + %d", a, b);

    // �����Ŀ�Ƿ��Ѿ����ֹ�
    if (is_question_repeated(question)) {
        return addition(digits); // ����ظ�������������Ŀ
    }

    // ��¼��Ŀ
    record_question(question);

    printf(" %d + %d = ?\n", a, b);
    return a + b;
}

// ��������
int subtraction(int digits) {
    int a = random_number_a(digits);
    int b = random_number_a(digits);
    char question[MAX_LENGTH];

    // ������Ŀ�ַ���
    if (a < b) {
        sprintf(question, "%d - %d", b, a);
    } else {
        sprintf(question, "%d - %d", a, b);
    }

    // �����Ŀ�Ƿ��Ѿ����ֹ�
    if (is_question_repeated(question)) {
        return subtraction(digits); // ����ظ�������������Ŀ
    }

    // ��¼��Ŀ
    record_question(question);

    if (a < b) {
        printf(" %d - %d = ?\n", b, a);
        return b - a;
    } else {
        printf(" %d - %d = ?\n", a, b);
        return a - b;
    }
}

// �˷�����
int multiplication(int digits) {
    int a = random_number_b(digits);
    int b = random_number_b(digits);
    char question[MAX_LENGTH];

    // ������Ŀ�ַ���
    sprintf(question, "%d * %d", a, b);

    // �����Ŀ�Ƿ��Ѿ����ֹ�
    if (is_question_repeated(question)) {
        return addition(digits); // ����ظ�������������Ŀ
    }

    // ��¼��Ŀ
    record_question(question);

    printf(" %d * %d = ?\n", a, b);
    return a * b;

}

// ��������
int division(int digits) {
    int a = random_number_c(digits);
    int b;
    do {
        b = random_number_c(digits);
    } while (b == 0); // ȷ��������Ϊ0
    a = a * b; // ȷ������
    char question[MAX_LENGTH];

    // ������Ŀ�ַ���
    sprintf(question, "%d / %d", a, b);

    // �����Ŀ�Ƿ��Ѿ����ֹ�
    if (is_question_repeated(question)) {
        return addition(digits); // ����ظ�������������Ŀ
    }

    // ��¼��Ŀ
    record_question(question);

    printf(" %d / %d = ?\n", a, b);
    return a / b;
}

//��ʽ���㡪��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������


// �������Լ��
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Լ�ַ�ʽ
Fraction simplify(Fraction frac) {
    int divisor = gcd(frac.numerator, frac.denominator);
    frac.numerator /= divisor;
    frac.denominator /= divisor;
    return frac;
}

// ��ʽ�ӷ�
Fraction add(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    result.denominator = a.denominator * b.denominator;
    return simplify(result);
}

// ��ʽ����
Fraction subtract(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
    result.denominator = a.denominator * b.denominator;
    return simplify(result);
}

// ��ʽ�˷�
Fraction multiply(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.numerator;
    result.denominator = a.denominator * b.denominator;
    return simplify(result);
}

// ��ʽ����
Fraction divide(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator;
    result.denominator = a.denominator * b.numerator;
    return simplify(result);
}

// ��ʽ�ӷ����㺯��
void fraction_operations_addition(int digits) {
    Fraction frac1 = {random_number_d(digits), random_number_d(digits)};;
    Fraction frac2 = {random_number_d(digits), random_number_d(digits)};;
    Fraction result;
    result = add(frac1, frac2);
    printf(" %d/%d + %d/%d = ?\n", frac1.numerator, frac1.denominator, frac2.numerator, frac2.denominator);

    // ��ʾ�û������
    int user_numerator, user_denominator;
    printf("��������Ĵ𰸵ķ��Ӻͷ�ĸ������ 3 -4 ��ʾ 3/-4��: ");
    scanf("%d %d", &user_numerator, &user_denominator);

    // ����û���
    if (user_numerator == result.numerator && user_denominator == result.denominator) {
        printf("�ش���ȷ��\n\n");
        acc++;
    } else {
        printf("�ش������ȷ����: %d/%d\n\n", result.numerator, result.denominator);
    }
}

// ��ʽ�������㺯��
void fraction_operations_subtraction(int digits) {
    Fraction frac1 = {random_number_d(digits), random_number_d(digits)};;
    Fraction frac2 = {random_number_d(digits), random_number_d(digits)};;
    Fraction result;
    result = subtract(frac1, frac2);
    printf(" %d/%d - %d/%d = ?\n", frac1.numerator, frac1.denominator, frac2.numerator, frac2.denominator);

    // ��ʾ�û������
    int user_numerator, user_denominator;
    printf("��������Ĵ𰸵ķ��Ӻͷ�ĸ������ 3 -4 ��ʾ 3/-4��: ");
    scanf("%d %d", &user_numerator, &user_denominator);

    // ����û���
    if (user_numerator == result.numerator && user_denominator == result.denominator) {
        printf("�ش���ȷ��\n\n");
        acc++;
    } else {
        printf("�ش������ȷ����: %d/%d\n\n", result.numerator, result.denominator);
    }
}

// ��ʽ�˷����㺯��
void fraction_operations_multiplication(int digits) {
    Fraction frac1 = {random_number_d(digits), random_number_d(digits)};;
    Fraction frac2 = {random_number_d(digits), random_number_d(digits)};;
    Fraction result;
    result = multiply(frac1, frac2);
    printf(" %d/%d * %d/%d = ?\n", frac1.numerator, frac1.denominator, frac2.numerator, frac2.denominator);

    // ��ʾ�û������
    int user_numerator, user_denominator;
    printf("��������Ĵ𰸵ķ��Ӻͷ�ĸ������ 3 -4 ��ʾ 3/-4��: ");
    scanf("%d %d", &user_numerator, &user_denominator);

    // ����û���
    if (user_numerator == result.numerator && user_denominator == result.denominator) {
        printf("�ش���ȷ��\n\n");
        acc++;
    } else {
        printf("�ش������ȷ����: %d/%d\n\n", result.numerator, result.denominator);
    }
}

// �����������㺯��
void fraction_operations_division(int digits) {
    Fraction frac1 = {random_number_d(digits), random_number_d(digits)};;
    Fraction frac2 = {random_number_d(digits), random_number_d(digits)};;
    Fraction result;
    result = divide(frac1, frac2);
    printf(" %d/%d + %d/%d = ?\n", frac1.numerator, frac1.denominator, frac2.numerator, frac2.denominator);

    // ��ʾ�û������
    int user_numerator, user_denominator;
    printf("��������Ĵ𰸵ķ��Ӻͷ�ĸ������ 3 -4 ��ʾ 3/-4��: ");
    scanf("%d %d", &user_numerator, &user_denominator);

    // ����û���
    if (user_numerator == result.numerator && user_denominator == result.denominator) {
        printf("�ش���ȷ��\n\n");
        acc++;
    } else {
        printf("�ش������ȷ����: %d/%d\n\n", result.numerator, result.denominator);
    }
}

// ���ѡ��������㺯��
void fraction_choose_question(int digits) {
    int operation = rand() % 4; // ���ѡ�����㣬���ӷ�ʽ����
    int result;
    int user_answer;

    switch (operation) {
        case 0:
            fraction_operations_addition(digits);
            return; // ֱ�ӷ��أ�����Ҫ�ټ���
        case 1:
            fraction_operations_subtraction(digits);
            return;
        case 2:
            fraction_operations_multiplication(digits);
            return;
        case 3:
            fraction_operations_division(digits);
            return;
    }
}

// ִ�����㡪������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������

// ���ѡ�����㺯��
void choose_question(int digits, int result, int *n) {
    int operation ; // ���ѡ������
    int user_answer;
    if (digits<2)
    {
        operation = rand() % 2;
        switch (operation) {
            case 0:
                result = addition(digits);
                break;
            case 1:
                result = subtraction(digits);
                break;
        }
        // ��ʾ�û������
        printf("��������Ĵ�: ");
        scanf("%d", &user_answer);

        // ����û���
        if (user_answer == result) {
            printf("�ش���ȷ��\n\n");
            acc++;
        } else {
            printf("�ش������ȷ����: %d\n\n", result);
        }
    }
    if (digits>=2 && digits<6)
    {
        operation = rand() % 4;
        switch (operation) {
            case 0:
                result = addition(digits);
                break;
            case 1:
                result = subtraction(digits);
                break;
            case 2:
                result = multiplication(digits);
                break;
            case 3:
                result = division(digits);
                break;
        }
        // ��ʾ�û������
        printf("��������Ĵ�: ");
        scanf("%d", &user_answer);

        // ����û���
        if (user_answer == result) {
            printf("�ش���ȷ��\n\n");
            acc++;
        } else {
            printf("�ش������ȷ����: %d\n\n", result);
        }
    }
    if (digits==6)
    {
        operation = rand() % 5;
        switch (operation) {
            case 0:
                result = addition(digits);
                break;
            case 1:
                result = subtraction(digits);
                break;
            case 2:
                result = multiplication(digits);
                break;
            case 3:
                result = division(digits);
                break;
            case 4:
                fraction_choose_question(digits);
                return;
        }
        // ��ʾ�û������
        printf("��������Ĵ�: ");
        scanf("%d", &user_answer);

        // ����û���
        if (user_answer == result) {
            printf("�ش���ȷ��\n\n");
            acc++;
        } else {
            printf("�ش������ȷ����: %d\n\n", result);
        }

    }
    *n=acc;
}

void init_acc(){
    acc=0;
}


