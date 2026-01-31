//program for queue using linked list   
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node
{
    int data;
    struct Node* next;
}Node;

Node* front = NULL;
Node* rear = NULL;

void enqueue(int value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if(rear == NULL)
    {
        front = rear = newNode;
        return;
    }
    rear->next = newNode;
    rear = newNode;
    printf("Enque successful\n");
}

void dequeue()
{
    if(front == NULL)
    {
        printf("Queue is empty\n");
        return;
    }
    Node* temp = front;
    front = front->next;
    if(front == NULL)
        rear = NULL;
    free(temp);
    printf("Dequeue successful\n");
}

void display()
{
    if(front == NULL)
    {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    Node* temp = front;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    bool choice = true;
    int option, value;
    printf("\t\tQueue using Linked List\n");
    while(choice)
    {
        printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);
        switch(option)
        {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                choice = false;
                break;
            default:
                printf("Invalid option\n");
        }
    }

}