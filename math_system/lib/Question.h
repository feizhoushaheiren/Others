#ifndef QUESTION_H
#define QUESTION_H
#define MAX_QUESTIONS 10 // 设置最大题目数
#define MAX_LENGTH 50 // 题目字符串长度
typedef struct {
    int numerator;   // 分子
    int denominator; // 分母
} Fraction;



void choose_question(int digits, int result, int *n);
void init_acc();

#endif // QUESTION_H