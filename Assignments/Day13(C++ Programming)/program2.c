//program for queue implementation in c
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 20

typedef struct queue
{
    int arr[MAX];
    int front;
    int rear;
}Queue;

int count=0;

void init(Queue *q)
{
    q->front=-1;   
    q->rear=-1;    
}

void add(Queue *q,int data)
{
  if(q->rear==MAX)
  {
      printf("Queue is Full\n");
      return;
  }
  if(q->front==-1)
  {
      q->front+=1; 
      q->arr[q->front]=data; 
      q->rear=q->front;
  }
  else
  {
    q->rear+=1;
    q->arr[q->rear]=data;
  }
//   printf("front rear %d %d\n",q->front,q->rear);
  printf("Element Added To Queue Successfully\n");
}

void poll(Queue *q)
{
    if(q->front==-1)
    {
        printf("Queue is empty\n");
        return;
    }
    // printf("front %d\n",q->front);
    printf("First Element = %d\n",q->arr[q->front]);
}

void remove_element(Queue *q)
{
    if(q->front==-1)
    {
        printf("Queue is Already Empty\n");
        return;
    }
    else if(q->front>=q->rear)
    {
        printf("Removed First Element %d\n",q->arr[q->front]);
        printf("Queue has become Empty Now\n");
        q->front=-1;   
        q->rear=-1;
        return;
    }
    else
    {
    printf("Removed First Element %d\n",q->arr[q->front]);
    q->front++;
    }
}

int main()
{
    Queue q;
    init(&q);
    int n;
    int data;
    printf("-------------------------------------------------------------------\n");
    printf("\t\t\tMy Custom Queue\t\t");
    bool flag=true; 
    while(flag)
    {
        printf("\n------------------------0-add,1-poll,2-remove----------------------\n");
        printf("Choose Any Queue Operation (0-2):\n");
        scanf("%d",&n);
        printf("You have selected option %d",n);
        switch(n)
        {
            case 0:
            {
                printf("\nOption 1 To Add Element\n");
                printf("Enter The Element To Add: \n");
                scanf("%d",&data);
                add(&q,data);
                break;
            }
            case 1:
            {
                printf("\nOption 2 To Poll Element\n");
                poll(&q);
                break;
            }
            case 2:
            {
                printf("\nOption 3 To Remove Element\n");
                remove_element(&q);
                break;
            }
            default:
            {
                printf("You Have Selected Wrong Choice\n");
                flag=false;
                break;
            }
        }
    }
    return 0;
}