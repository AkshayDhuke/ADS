#include <stdio.h>
#include <stdlib.h>

int count = 0;

struct node
{
    int data;
    struct node *next;
};

struct node *insert_at_end(struct node *head, int key)
{
    struct node *newnode;
    struct node *temp;

    if (head == NULL)
    {
        newnode = malloc(sizeof(struct node));
        newnode->data = key;
        newnode->next = NULL;
        return newnode;
    }

    newnode = malloc(sizeof(struct node));
    newnode->data = key;
    newnode->next = NULL;
    temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newnode;
    return head;
}

struct node *delete_node(struct node *head, int key)
{
    struct node *prenode;
    struct node *temp;

    prenode = NULL;
    temp = head;

    if (temp->data == key)
    {
        head = temp->next;
        free(temp);
        return head;
    }

    while (temp->data != key)
    {
        prenode = temp;
        temp = temp->next;
    }

    prenode->next = temp->next;
    free(temp);
    return head;
}

struct node *cookie(struct node *head, int k)
{
    struct node *temp = head;
    int min1, min2;

    while (1)
    {
        temp = head;
        if (temp->data < temp->next->data)
        {
            min1 = temp->data;
            min2 = temp->next->data;
        }
        else
        {
            min2 = temp->data;
            min1 = temp->next->data;
        }

        while (temp->next != NULL)
        {
            temp = temp->next;
            if (min1 >= temp->data)
            {
                min2 = min1;
                min1 = temp->data;
            }
            else if (min1 < temp->data && min2 > temp->data)
            {
                min2 = temp->data;
            }
            else
            {
                continue;
            }
        }

        if (min1 >= k)
        {
            return head;
        }

        head = insert_at_end(head, min1 + 2 * min2);
        count++;
        head = delete_node(head, min1);
        head = delete_node(head, min2);
    }
    return head;
}

int main()
{
    int n, k, val;
    struct node *head = NULL;

    printf("Enter N and K: ");
    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        head = insert_at_end(head, val);
    }

    count = 0;

    head = cookie(head, k);

    struct node *temp = head;
    printf("Special cookie are : ");
    while (temp != NULL)
    {
        printf("%d  ", temp->data);
        temp = temp->next;
    }
    printf("\nNumber of operations = %d", count);

    
    return 0;
}
