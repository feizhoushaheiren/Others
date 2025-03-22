#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Question.h"

int acc=0;

// 用于存储已出现的题目
char questions_history[MAX_QUESTIONS][MAX_LENGTH];
int question_count = 0;

// 判断题目是否已经出现过
int is_question_repeated(const char* question) {
    for (int i = 0; i < question_count; i++) {
        if (strcmp(questions_history[i], question) == 0) {
            return 1; // 题目已出现
        }
    }
    return 0; // 题目未出现
}

// 将题目记录到历史题库
void record_question(const char* question) {
    if (question_count < MAX_QUESTIONS) {
        strcpy(questions_history[question_count], question);
        question_count++;
    }
}
// 随机生成指定范围内的整数,用于加减法
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
    max = max * 10 - 1; // 生成的最大值
    return rand() % (max - min + 1) + min;//存疑？？？？？？
}

// 随机生成指定范围内的整数,用于乘法
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
    max = max * 10 - 1; // 生成的最大值
    return rand() % (max - min + 1) + min;//存疑？？？？？？
}

// 随机生成指定范围内的整数,用于除法
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
    max = max * 10 - 1; // 生成的最大值
    return rand() % (max - min + 1) + min;//存疑？？？？？？
}

// 随机生成指定范围内的整数,用于分式计算
int random_number_d(int digits) {
    int min;
    int max;
    if (digits>5)
    {
        max=1.2;
        min=1;
    }
    max = max * 10 - 1; // 生成的最大值
    return rand() % (max - min + 1) + min;
}

// 加法函数
int addition(int digits) {
    int a = random_number_a(digits);
    int b = random_number_a(digits);
    char question[MAX_LENGTH];

    // 生成题目字符串
    sprintf(question, "%d + %d", a, b);

    // 检查题目是否已经出现过
    if (is_question_repeated(question)) {
        return addition(digits); // 如果重复，重新生成题目
    }

    // 记录题目
    record_question(question);

    printf(" %d + %d = ?\n", a, b);
    return a + b;
}

// 减法函数
int subtraction(int digits) {
    int a = random_number_a(digits);
    int b = random_number_a(digits);
    char question[MAX_LENGTH];

    // 生成题目字符串
    if (a < b) {
        sprintf(question, "%d - %d", b, a);
    } else {
        sprintf(question, "%d - %d", a, b);
    }

    // 检查题目是否已经出现过
    if (is_question_repeated(question)) {
        return subtraction(digits); // 如果重复，重新生成题目
    }

    // 记录题目
    record_question(question);

    if (a < b) {
        printf(" %d - %d = ?\n", b, a);
        return b - a;
    } else {
        printf(" %d - %d = ?\n", a, b);
        return a - b;
    }
}

// 乘法函数
int multiplication(int digits) {
    int a = random_number_b(digits);
    int b = random_number_b(digits);
    char question[MAX_LENGTH];

    // 生成题目字符串
    sprintf(question, "%d * %d", a, b);

    // 检查题目是否已经出现过
    if (is_question_repeated(question)) {
        return addition(digits); // 如果重复，重新生成题目
    }

    // 记录题目
    record_question(question);

    printf(" %d * %d = ?\n", a, b);
    return a * b;

}

// 整除函数
int division(int digits) {
    int a = random_number_c(digits);
    int b;
    do {
        b = random_number_c(digits);
    } while (b == 0); // 确保除数不为0
    a = a * b; // 确保整除
    char question[MAX_LENGTH];

    // 生成题目字符串
    sprintf(question, "%d / %d", a, b);

    // 检查题目是否已经出现过
    if (is_question_repeated(question)) {
        return addition(digits); // 如果重复，重新生成题目
    }

    // 记录题目
    record_question(question);

    printf(" %d / %d = ?\n", a, b);
    return a / b;
}

//分式计算——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


// 计算最大公约数
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// 约分分式
Fraction simplify(Fraction frac) {
    int divisor = gcd(frac.numerator, frac.denominator);
    frac.numerator /= divisor;
    frac.denominator /= divisor;
    return frac;
}

// 分式加法
Fraction add(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    result.denominator = a.denominator * b.denominator;
    return simplify(result);
}

// 分式减法
Fraction subtract(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
    result.denominator = a.denominator * b.denominator;
    return simplify(result);
}

// 分式乘法
Fraction multiply(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.numerator;
    result.denominator = a.denominator * b.denominator;
    return simplify(result);
}

// 分式除法
Fraction divide(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator;
    result.denominator = a.denominator * b.numerator;
    return simplify(result);
}

// 分式加法运算函数
void fraction_operations_addition(int digits) {
    Fraction frac1 = {random_number_d(digits), random_number_d(digits)};;
    Fraction frac2 = {random_number_d(digits), random_number_d(digits)};;
    Fraction result;
    result = add(frac1, frac2);
    printf(" %d/%d + %d/%d = ?\n", frac1.numerator, frac1.denominator, frac2.numerator, frac2.denominator);

    // 提示用户输入答案
    int user_numerator, user_denominator;
    printf("请输入你的答案的分子和分母（例如 3 -4 表示 3/-4）: ");
    scanf("%d %d", &user_numerator, &user_denominator);

    // 检查用户答案
    if (user_numerator == result.numerator && user_denominator == result.denominator) {
        printf("回答正确！\n\n");
        acc++;
    } else {
        printf("回答错误，正确答案是: %d/%d\n\n", result.numerator, result.denominator);
    }
}

// 分式减法运算函数
void fraction_operations_subtraction(int digits) {
    Fraction frac1 = {random_number_d(digits), random_number_d(digits)};;
    Fraction frac2 = {random_number_d(digits), random_number_d(digits)};;
    Fraction result;
    result = subtract(frac1, frac2);
    printf(" %d/%d - %d/%d = ?\n", frac1.numerator, frac1.denominator, frac2.numerator, frac2.denominator);

    // 提示用户输入答案
    int user_numerator, user_denominator;
    printf("请输入你的答案的分子和分母（例如 3 -4 表示 3/-4）: ");
    scanf("%d %d", &user_numerator, &user_denominator);

    // 检查用户答案
    if (user_numerator == result.numerator && user_denominator == result.denominator) {
        printf("回答正确！\n\n");
        acc++;
    } else {
        printf("回答错误，正确答案是: %d/%d\n\n", result.numerator, result.denominator);
    }
}

// 分式乘法运算函数
void fraction_operations_multiplication(int digits) {
    Fraction frac1 = {random_number_d(digits), random_number_d(digits)};;
    Fraction frac2 = {random_number_d(digits), random_number_d(digits)};;
    Fraction result;
    result = multiply(frac1, frac2);
    printf(" %d/%d * %d/%d = ?\n", frac1.numerator, frac1.denominator, frac2.numerator, frac2.denominator);

    // 提示用户输入答案
    int user_numerator, user_denominator;
    printf("请输入你的答案的分子和分母（例如 3 -4 表示 3/-4）: ");
    scanf("%d %d", &user_numerator, &user_denominator);

    // 检查用户答案
    if (user_numerator == result.numerator && user_denominator == result.denominator) {
        printf("回答正确！\n\n");
        acc++;
    } else {
        printf("回答错误，正确答案是: %d/%d\n\n", result.numerator, result.denominator);
    }
}

// 分数除法运算函数
void fraction_operations_division(int digits) {
    Fraction frac1 = {random_number_d(digits), random_number_d(digits)};;
    Fraction frac2 = {random_number_d(digits), random_number_d(digits)};;
    Fraction result;
    result = divide(frac1, frac2);
    printf(" %d/%d + %d/%d = ?\n", frac1.numerator, frac1.denominator, frac2.numerator, frac2.denominator);

    // 提示用户输入答案
    int user_numerator, user_denominator;
    printf("请输入你的答案的分子和分母（例如 3 -4 表示 3/-4）: ");
    scanf("%d %d", &user_numerator, &user_denominator);

    // 检查用户答案
    if (user_numerator == result.numerator && user_denominator == result.denominator) {
        printf("回答正确！\n\n");
        acc++;
    } else {
        printf("回答错误，正确答案是: %d/%d\n\n", result.numerator, result.denominator);
    }
}

// 随机选择分数运算函数
void fraction_choose_question(int digits) {
    int operation = rand() % 4; // 随机选择运算，增加分式运算
    int result;
    int user_answer;

    switch (operation) {
        case 0:
            fraction_operations_addition(digits);
            return; // 直接返回，不需要再检查答案
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

// 执行运算————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

// 随机选择运算函数
void choose_question(int digits, int result, int *n) {
    int operation ; // 随机选择运算
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
        // 提示用户输入答案
        printf("请输入你的答案: ");
        scanf("%d", &user_answer);

        // 检查用户答案
        if (user_answer == result) {
            printf("回答正确！\n\n");
            acc++;
        } else {
            printf("回答错误，正确答案是: %d\n\n", result);
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
        // 提示用户输入答案
        printf("请输入你的答案: ");
        scanf("%d", &user_answer);

        // 检查用户答案
        if (user_answer == result) {
            printf("回答正确！\n\n");
            acc++;
        } else {
            printf("回答错误，正确答案是: %d\n\n", result);
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
        // 提示用户输入答案
        printf("请输入你的答案: ");
        scanf("%d", &user_answer);

        // 检查用户答案
        if (user_answer == result) {
            printf("回答正确！\n\n");
            acc++;
        } else {
            printf("回答错误，正确答案是: %d\n\n", result);
        }

    }
    *n=acc;
}

void init_acc(){
    acc=0;
}


