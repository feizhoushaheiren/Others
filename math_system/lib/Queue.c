#include <stdio.h>
#include "Queue.h"
#define QUEUE_SIZE 5

void init_queue(Queue *q) {
    /* ��ʼ������ */
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int is_full(Queue *q) {
    /* �ж϶����Ƿ��Ѿ����� */
    return q->count == QUEUE_SIZE;
}

int is_empty(Queue *q) {
    /* �ж϶����Ƿ�Ϊ�� */
    return q->count == 0;
}

void enqueue(Queue *q, float score) {
    /* ��� */
    if (is_full(q)) {
        // �Ƴ���ɵ�����
        q->front = (q->front + 1) % QUEUE_SIZE;
        q->count--;
    }
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    q->scores[q->rear] = score;
    q->count++;
}

float dequeue(Queue *q) {
    /* ���� */
    if (!is_empty(q)) {
        float score = q->scores[q->front];
        q->front = (q->front + 1) % QUEUE_SIZE;
        q->count--;
        return score;
    } else {
        printf("����Ϊ��\n");
        return -1;
    }
}