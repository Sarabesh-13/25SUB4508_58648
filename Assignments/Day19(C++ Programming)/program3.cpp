//program for queue using linked list   
#include<iostream>
#include<cstdlib>

struct Node {
    public:
        int data;
        Node* next;

        Node(int val) : data(val), next(nullptr) {}

        ~Node() {
            std::cout << "Node with data " << data << " is being deleted." << std::endl;
        }
};

struct Queue
{
    private:
        Node* front;
        Node* rear;
    
    public:
        Queue(): front(nullptr),rear(nullptr) {}

        void enqueue(int value)
        {
            Node* newNode = new Node(value);
            if (rear == nullptr)
            {
                front = rear = newNode;
                return;
            }
            rear->next = newNode;
            rear = newNode;
            std::cout<<"\nEnque successful\n"<<std::endl;
        }

        void dequeue()
        {
            if (front == nullptr)
            {
                 std::cout<<"\nQueue is Empty\n"<<std::endl;
                return;
            }
            Node *temp = front;
            front = front->next;
            if (front ==nullptr)
                rear = nullptr;
            free(temp);
             std::cout<<"\nDequeue successful\n"<<std::endl;
        }

        void display()
        {
            if (front == nullptr)
            {
                 std::cout<<"\nQueue is empty\n"<<std::endl;
                return;
            }
            printf("Queue elements: ");
            Node *temp = front;
            while (temp != nullptr)
            {
                printf("%d ", temp->data);
                temp = temp->next;
            }
            printf("\n");
        }

        ~Queue() {
            if (front == rear)
            {
                delete front;
                delete rear;
            }
            else
            {
                Node *current = front;
                do
                {
                    Node *temp = current;
                    current = current->next;
                    delete temp;
                } while (current != nullptr);
                delete rear;
                std::cout << "Queue is destroyed." << std::endl;

            }
        }
};

int main()
{
    bool choice = true;
    int option, value;
    Queue queue;
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
                queue.enqueue(value);
                break;
            case 2:
                queue.dequeue();
                break;
            case 3:
                queue.display();
                break;
            case 4:
                choice = false;
                break;
            default:
                printf("Invalid option\n");
        }
    }

}