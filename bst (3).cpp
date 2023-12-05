#include<bits/stdc++.h>
using namespace std;

struct node
{
    int data;
    struct node* left;
    struct node* right;
};

struct node* insert(struct node* node,int key)
{
    if(node==NULL)
    {
        node=(struct node*)malloc(sizeof(struct node));
        node->data=key;
        node->left=NULL;
        node->right=NULL;
        return node; 
    }
    else if(key < node->data)
    {
        node->left=insert(node->left,key);
    }
    else if(key > node->data)
    {
        node->right=insert(node->right,key);
    }
    else
    cout<<"key is already present in BST.";
    return node;
}

struct node* deletenode(struct node* node,int key)
{
    if(node==NULL)
    {
        cout<<"ELEMENT NOT FOUND"<<endl;
        return node;
    }
    else if(key < node->data)
    {
        node->left =deletenode(node->left,key);
        return node;
    }
    else if(key > node->data)
    {
        node->right=deletenode(node->right,key);
        return node;
    }
  // deleted node is found
     if (node->left == NULL) {
        struct node* temp = node->right;
        delete node;
        return temp;
    }
    else if (node->right == NULL) {
        struct node* temp = node->left;
        delete node;
        return temp;
    }
    else
    {
        struct node* succParent = node;

        struct node* succ = node->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        if (succParent != node)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;
 

        node->data = succ->data;
        delete succ;
        return node;
    }
    
   
}

void search(struct node* node,int key)
{
    if(node==NULL)
    {
        cout<<"element not found"<<endl;
    }
    else if(key==node->data)
    {
        cout<<"element found"<<endl;
    }
    else if(key<node->data)
    {
        search(node->left,key);
    }
    else
    {
        search(node->right,key);
    }
}

void display(struct node* node)
{
    if(node==NULL)
    return;

    display(node->left);
    cout<<node->data<<" ";
    display(node->right);
}

int main()
{
    struct node* root;
    root=(struct node*)malloc(sizeof(struct node));
    root=NULL;
    int ch,key;
    
    do
    {
        cout<<"\n1.insert\n2.delete\n3.display\n4.search\n5.exit\nenter your choise:";
        cin>>ch;

        switch(ch)
        {
            case 1:
                    cout<<"enter the key to insert:";
                    cin>>key;
                    root=insert(root,key);
                    break;
            case 2:
                    cout<<"enter the key to delete:";
                    cin>>key;
                    deletenode(root,key);
                    cout<<"deleted node is :"<<key<<endl;
                    break;
            case 3:
                    cout<<"Inorder traversal is:";
                    display(root);
                    cout<<endl;
                    break;
            case 4:
                   cout<<"enter the number to search:";
                   cin>>key;
                   search(root,key);
                   break;
            case 5:
                    cout<<"END"<<endl;
                    break;
            default:
            cout<<"invalid choise"<<endl;
                    
        }

    }while(ch!=5);
    return 0;
}