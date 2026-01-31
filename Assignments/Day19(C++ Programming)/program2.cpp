//program for circular linked list

#include <iostream>
#include <cstdlib>

struct Node {
    public:
        int data;
        Node* next;

        Node(int val) : data(val), next(nullptr) {}

        ~Node() {
            std::cout << "Node with data " << data << " is being deleted." << std::endl;
        }
};

struct circularLinkedList {
    private:
        Node* head;

    public:
        circularLinkedList() : head(nullptr) {}

        Node* createNode(int data) {
            Node* newNode = new Node(data);
            return newNode;
        }

        void insertEnd(int data)
        {
            Node *newNode = createNode(data);
            if (head == NULL)
            {
                head = newNode;
                newNode->next = head;
                return;
            }
            else
           {
            Node *temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
            }
        }

        void insertBeginning(int data)
        {
            Node *newNode = createNode(data);
            if (head == NULL)
            {
                head = newNode;
                newNode->next = head;
                return;
            }
            else
            {
                Node *temp = head;
                while (temp->next != head)
                {
                    temp = temp->next;
                }
                temp->next = newNode;
                newNode->next = head;
                head = newNode;
            }
        }

        void insertAtPosition(int data, int position)
        {
            if (position == 0)
            {
                insertBeginning(data);
                return;
            }
            Node *newNode = createNode(data);
            Node *temp = head;
            for (int i = 0; i < position - 1; i++)
            {
                temp = temp->next;
                if (temp == head) {
                    std::cout << "Position out of bounds. Inserting at end." << std::endl;
                    break;
                }
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }   

        void displayList() 
        {
            if (head == NULL) {
                std::cout << "List is empty." << std::endl;
                return;
            }
            Node* temp = head;
            do {
                std::cout << temp->data << " -> ";
                temp = temp->next;
            } while (temp != head);
            std::cout << "(head: " << head->data << ")" << std::endl;
        }

        void deleteNode(int key) {
            if (head == nullptr)
            {
                std::cout<<"\nlist is empty\n"<<std::endl;
                return;
            }
            Node *current = head, *previous = nullptr;

            // If the node to be deleted is the head node
            if (current->data == key) {
                // Find the last node to update its next pointer
                while (current->next != head) {
                    current = current->next;
                }
                // If there's only one node
                if (head->next == head) {
                    delete head;
                    head = nullptr;
                } else {
                    Node* temp = head;
                    head = head->next;
                    current->next = head;
                    delete temp;
                }
                return;
            }

            // Search for the node to be deleted
            current = head;
            do {
                previous = current;
                current = current->next;
                if (current->data == key) {
                    previous->next = current->next;
                    delete current;
                    return;
                }
            } while (current != head);
        }

        ~circularLinkedList() {
            if (head == nullptr) return;

            Node* current = head;
            Node* nextNode;

            do {
                nextNode = current;;
                current = current->next;
                delete nextNode;
            } while (current != head);

            head = nullptr;
            std::cout << "Circular linked list destroyed." << std::endl;
        }
};



int main() 
{
    circularLinkedList cll;
    int value;
    bool running = true;
    int delValue;
    int choice;
    int position;
    while(running) 
    {
        std::cout << "1. Insert at End\n2. Insert at Beginning\n3. Insert at Position\n4. Display List\n5. Delete Node\n6. Exit\nChoose an option: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Enter value to insert at end: ";
                std::cin >> value;
                cll.insertEnd(value);
                break;
            case 2:
                std::cout << "Enter value to insert at beginning: ";
                std::cin >> value;
                cll.insertBeginning(value);
                break;
            case 3:
                {
                    std::cout << "Enter value to insert: ";
                    std::cin >> value;
                    std::cout << "Enter position to insert at: ";
                    std::cin >> position;
                    cll.insertAtPosition(value, position);
                }
                break;
            case 4:
                cll.displayList();
                break;
            case 5:
                {
                    std::cout << "Enter value to delete: ";
                    std::cin >> delValue;
                    cll.deleteNode(delValue);
                }
                break;
            case 6:
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
}