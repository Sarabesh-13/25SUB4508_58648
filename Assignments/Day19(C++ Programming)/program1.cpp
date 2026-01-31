//program for creating and displaying a double linked list in C++
#include <iostream>
#include <iomanip>

struct Node
{
    public:
        int data;
        Node* prev;
        Node* next;

        Node(int val): data(val),prev(nullptr),next(nullptr){}

        ~Node()
        {
            std::cout << "Node with value " << data << " deleted.\n";
        }
};


struct DLL
{
  private:
    Node* tail;
    Node* head;
  
  public:
    DLL(): head(nullptr), tail(nullptr) {}

    Node *createNode(int data)
    {
        Node* node = new Node(data);
        return node;
    }

    void insertAtBeginning(int data)
    {
        Node* newNode = createNode(data);
        if(head == nullptr)
        {
            newNode->next = newNode;
            newNode->prev = newNode;
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
    }

   void insertAtEnd(int data)
    {
        Node* newNode = createNode(data);
        if(head == nullptr)
        {
            newNode->next = newNode;
            newNode->prev = newNode;
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
        }
        return;
    }

   void insertAtMiddle(int afterVal, int newVal)
    {
        if(head == nullptr)
        {
            std::cout << "\nList is empty. Cannot add after value " << afterVal << ".\n";
            return;
        }   

        Node *current = head;
        Node *nn = createNode(newVal);

        // Searching for the node after which to insert
        do {
            if(current->data == afterVal)
            {
                nn->next = current->next;
                nn->prev = current;
                current->next->prev = nn;
                current->next = nn;
                return;
            }
            current = current->next;
        } while(current != head);

        std::cout << "\nValue " << afterVal << " not found in the list. Cannot insert " << newVal << ".\n";
        delete nn; // Free the allocated memory since insertion didn't happen
        return;
    }

    void deleteNode(int val)
    {
        if(head == nullptr)
        {
            std::cout << "\nList is empty. Cannot delete.\n";
            return;
        }

        Node *current = head;
        Node *toDelete = nullptr;

        // Searching for the node to delete
        do {
            if(current->data == val)
            {
                toDelete = current;
                break;
            }
            current = current->next;
        } while(current != head);

        if(toDelete == nullptr)
        {
            std::cout << "\nValue " << val << " not found in the list.\n";
            return;
        }

        // If the list has only one node
        if(toDelete->next == toDelete && toDelete->prev == toDelete)
        {
            delete toDelete;
            head = nullptr;
            tail = nullptr;
            return;
        }

        // Adjusting the pointers to remove the node
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;

        // Update head or tail if necessary
        if(toDelete == head)
            head = toDelete->next;
        if(toDelete == tail)
            tail = toDelete->prev;

        delete toDelete;
        return;
    }

    void displayList()
    {
        if(head == nullptr)
        {
            std::cout << "List is empty.\n";
            return;
        }

        Node *temp = head;
        std::cout << "Forward order:\n";
        do {
            std::cout << temp->data << " <-> ";
            temp = temp->next;
        } while(temp != head);
        std::cout << "(back to head " << head->data << ")\n";

        // Backward display
        std::cout << "Reverse order:\n";
        temp = head->prev; 
        do {
            std::cout << temp->data << " <-> ";
            temp = temp->prev;
        } while(temp != head->prev);
        std::cout << "(back to tail " << head->prev->data << ")\n";
    }

    ~DLL()
    {
        Node* current = head;
        if(current != nullptr)
        {
            do {
                Node* temp = current;
                current = current->next;
                delete temp;
            } while(current != head);
        }
        std::cout << "All nodes deleted and memory freed.\n";
    }
};

int main()
{
    int value;
    bool running = true;
    DLL list;
    int choice;
    while(running)
    {
        std::cout << "\nMenu:\n";
        std::cout << "1. Insert at Beginning\n";
        std::cout << "2. Insert at End\n";
        std::cout << "3. Insert at Middle\n";
        std::cout << "4. Delete Node\n";
        std::cout << "5. Display List\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch(choice)
        {
            case 1:
                std::cout << "Enter value to insert at beginning: ";
                std::cin >> value;
                list.insertAtBeginning(value);
                break;
            case 2:
                std::cout << "Enter value to insert at end: ";
                std::cin >> value;
                list.insertAtEnd(value);
                break;
            case 3:
            {
                int afterVal, newVal;
                std::cout << "Enter value after which to insert: ";
                std::cin >> afterVal;
                std::cout << "Enter new value to insert: ";
                std::cin >> newVal;
                list.insertAtMiddle(afterVal, newVal);
                break;
            }
            case 4:
                std::cout << "Enter value to delete: ";
                std::cin >> value;
                list.deleteNode(value);
                break;
            case 5:
                list.displayList();
                break;
            case 6:
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}