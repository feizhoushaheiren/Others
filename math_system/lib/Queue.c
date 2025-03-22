#include <stdio.h>
#include "Queue.h"
#define QUEUE_SIZE 5

void init_queue(Queue *q) {
    /* 初始化队列 */
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int is_full(Queue *q) {
    /* 判断队列是否已经满了 */
    return q->count == QUEUE_SIZE;
}

int is_empty(Queue *q) {
    /* 判断队列是否为空 */
    return q->count == 0;
}

void enqueue(Queue *q, float score) {
    /* 入队 */
    if (is_full(q)) {
        // 移除最旧的数据
        q->front = (q->front + 1) % QUEUE_SIZE;
        q->count--;
    }
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    q->scores[q->rear] = score;
    q->count++;
}

float dequeue(Queue *q) {
    /* 出队 */
    if (!is_empty(q)) {
        float score = q->scores[q->front];
        q->front = (q->front + 1) % QUEUE_SIZE;
        q->count--;
        return score;
    } else {
        printf("队列为空\n");
        return -1;
    }
}