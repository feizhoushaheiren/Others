#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_SIZE 5

typedef struct {
    float scores[QUEUE_SIZE];
    int front;
    int rear;
    int count;
} Queue;

void init_queue(Queue *q);
int is_full(Queue *q);
int is_empty(Queue *q);
void enqueue(Queue *q, float score);
float dequeue(Queue *q);

#endif