//system design for vehicle service queue using singly linked list
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int vehicleId;
    struct node* next; 
}NODE;


void dispList(NODE *);
NODE *createNode();
NODE *addBegin(NODE *, int);
NODE *addEnd(NODE *, int);
NODE *addAfterValue(NODE *, int, int);
NODE *deleteNode(NODE *, int);
void search(NODE *,int);
void freeNodes(NODE *);


int main()
{
    NODE *head = NULL;
    int ch=1, vehicle=0, after=0;
    while(ch)
    {
        printf("\n=============Vehicle Service===============\n");
        printf("\nPress,");
        printf("\n1. Add Vehicle for Emergency Service");
        printf("\n2. Add Vehicle for Regular Service");
        printf("\n3. Add Vehicle After a Specific Vehicle ID");
        printf("\n4. Remove Vehicle Id");
        printf("\n5. Search Vehicle Id");
        printf("\n6. Display Service Queue");
        printf("\n7. Exit");
        printf("\nChoice: ");

        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
                printf("\nEnter the Vehicle Id for Emergency Service:\n");
                scanf("%d",&vehicle);
                head = addBegin(head,vehicle);
                break;
            case 2:
                printf("\nEnter the Vehicle Id for Regular Service:\n");
                scanf("%d",&vehicle);
                head = addEnd(head,vehicle);
                break;
            case 3:
                printf("\nEnter the Vehicle Id to be added after specific vehicle id:\n");
                scanf("%d",&after);
                printf("\nEnter the vehicle id to add:\n");
                scanf("%d",&vehicle);
                head = addAfterValue(head,after, vehicle);
                break;
            case 4:
                printf("\nEnter the Vehicle ID to remove:\n");
                scanf("%d",&vehicle);
                head = deleteNode(head, vehicle);
                break;
            case 5:
                  printf("\nEnter the Vehicle ID to search:\n");
                  scanf("%d",&vehicle);
                  search(head, vehicle);
            case 6:
                dispList(head);
                break;
            case 7:
                freeNodes(head);
                exit(EXIT_SUCCESS);
            default:
                printf("\nEnter the correct choice");
            
        }


    }

    printf("\n\n");

    return (EXIT_SUCCESS);
}


NODE *createNode()
{
    return ((NODE *)malloc(sizeof(NODE)));
}

NODE *addEnd(NODE *head, int  val)
{
    NODE *nn = createNode();
    nn->vehicleId = val;
    nn->next = NULL;
    
    if(head == NULL)
    {
        //list is empty
        head = nn;
        
    }
    else
    {
        NODE *temp = head;
        while(temp->next != NULL)
            temp = temp->next;
        
        temp->next = nn;
        
    }
    return head;
}

NODE *addBegin(NODE *head, int val)
{
    NODE *nn = createNode();
    nn->vehicleId = val;
    nn->next = head;
    return nn;
}


NODE *addAfterValue(NODE *head, int after, int val)
{
    NODE *temp = head;
    while(temp != NULL && temp->vehicleId != after)
        temp = temp->next;
    
    if(temp == NULL)
    {
        printf("\nvehicle_id %d not found in the list",after);
        return head;
    }
    NODE *nn = createNode();
    nn->vehicleId = val;
    // nn->next = NULL;
    nn->next = temp->next;
    temp->next = nn;
    return head;

}


NODE *deleteNode(NODE *head, int val)
{
    NODE *temp = head;
    NODE *prev = NULL;

    if(head == NULL)
    {
        printf("\nService Queue is Empty\n");
        return head;
    }

    //first node to be deleted
    if(head->vehicleId == val)
    {
        head = head->next;
        free(temp);
        return head;
    }

    while(temp != NULL && temp->vehicleId != val)
    {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("\n%d vehicle_id  not found in the list", val);
        return head;
    }

    prev->next = temp->next;
    free(temp);

    return head;
}

void dispList(NODE *temp)
{
    printf("\nVehicle ID's\n");
    while(temp != NULL)
    {
        printf("%d->",temp->vehicleId);
        temp = temp->next;
    }
    printf("NULL\n\n");
}

void freeNodes(NODE *head)
{
    NODE *temp;
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("\nAll nodes are freed\n");
}

void search(NODE *head,int vehicle_id)
{
    NODE *temp = head;
    int found = 0;
    while(temp != NULL)
    {
        if(temp->vehicleId == vehicle_id)
        {
            found = 1;
            break;
        }
        temp = temp->next;
    }
    if(found)
        printf("\nVehicle ID %d found in the list\n", vehicle_id);
    else
        printf("\nVehicle ID %d not found in the list\n", vehicle_id);
}