#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 200

typedef struct stack 
{
    int arr[MAX];
    int top;
}Stack;

void init(Stack *s)
{
    s->top=-1; 
}

void push(Stack *s,int data)
{
  if(s->top==20)
  {
      printf("stack overflow\n");
      return;
  }
  s->top+=1;
  s->arr[s->top]=data;
  printf("element pushed successfully\n");
}

void peek(Stack *s)
{
    if(s->top==-1)
    {
        printf("stack is empty\n");
        return;
    }
    // printf("%d\n",s->top);
    printf("peek element = %d\n",s->arr[s->top]);
}

void pop(Stack *s)
{
    if(s->top==-1)
    {
        printf("stack underflow\n");
        return;
    }
    printf("popped data %d\n",s->arr[s->top]);
    s->top-=1;  
}

int main()
{
    Stack s;
    init(&s);
    int n;
    int data;
    printf("---------------------------------------------------------\n");
    printf("\t\tMy Custom Stack\t\n");
    bool flag=true; 
    while(flag)
    {
        printf("---------------0-push,1-pop,2-peek-----------------------\n");
        printf("choose any stack operation (0-2)\n");
        scanf("%d",&n);
        printf("You have selected option %d\n",n);
        switch(n)
        {
            case 0:
            {
                printf("enter the element to push\n");
                scanf("%d",&data);
                push(&s,data);
                break;
            }
            case 1:
            {
                pop(&s);
                break;
            }
            case 2:
            {
                peek(&s);
                break;
            }
            default:
            {
                flag=false;
                break;
            }
        }
    }
    return 0;
}