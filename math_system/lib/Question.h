#ifndef QUESTION_H
#define QUESTION_H
#define MAX_QUESTIONS 10 // ���������Ŀ��
#define MAX_LENGTH 50 // ��Ŀ�ַ�������
typedef struct {
    int numerator;   // ����
    int denominator; // ��ĸ
} Fraction;



void choose_question(int digits, int result, int *n);
void init_acc();

#endif // QUESTION_H