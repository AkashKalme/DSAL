//============================================================================
// Name        : Assignment1.cpp
// Author      : Akash Kalme
// Version     : Final Version
// Copyright   : Your copyright notice
// Description : Operations on Binary Tree
//                          Assignment - 1
// Name: Akash Kalme                                                Roll No.: 21141
// Problem Statement:
//  Beginning with an empty binary BT, Construct binary BT by inserting the values in the order given.
//  After constructing a binary BT perform following operations on it-
//  1.Perform inorder /preorder and post order traversal <-
//  2.Change a BT so that the roles of the left and right pointers are swapped at every node
//  3.Find the height of BT <-
//  4.Copy this BT to another [operator=]
//  5.Count number of leaves, number of internal nodes.
//  6.Erase all nodes in a binary BT.
//  (implement both recursive and non-recursive methods)
//============================================================================

#include <iostream>

using namespace std;

class TreeNode
{
public:
    TreeNode *lchild;
    int data;
    TreeNode *rchild;
} * root, *tree2;

class stack
{
public:
    int top;
    int size;
    TreeNode **s;
    stack(int n)
    {
        size = n;
        top = -1;
        s = new TreeNode *[size];
    }
    bool isFull();
    bool isEmpty();
    void push(TreeNode *);
    TreeNode *pop();
};

bool stack::isEmpty()
{
    if (top == -1)
        return true;
    else
        return false;
}

bool stack::isFull()
{
    return (top == size - 1);
}

void stack::push(TreeNode *x)
{
    if (!this->isFull())
    {
        top++;
        s[top] = x;
    }
    else
    {
        cout << "Stack is FULL !!! " << endl;
    }
}

TreeNode *stack::pop()
{
    TreeNode *p = NULL;
    if (!isEmpty())
    {
        p = s[top];
        top--;
    }
    else
    {
        cout << "Stack is EMPTY !!! " << endl;
    }
    return p;
}

class queue
{
public:
    int front;
    int rear;
    int size;
    TreeNode **q;
    queue(int n)
    {
        front = rear = -1;
        size = n;
        q = new TreeNode *[size];
    }
    void enqueue(TreeNode *);
    TreeNode *dequeue(void);
    bool isEmpty();
    bool isFULL();
};

bool queue::isFULL()
{
    return (rear == size - 1);
}

bool queue::isEmpty()
{
    return front == rear;
}

void queue::enqueue(TreeNode *x)
{
    if (!isFULL())
    {
        rear++;
        q[rear] = x;
    }
    else
    {
        cout << "Queue is Full! " << endl;
    }
}

TreeNode *queue::dequeue()
{
    TreeNode *x = NULL;
    if (!isEmpty())
    {
        front++;
        x = q[front];
    }
    return x;
}

// Tree Creation
void createtree()
{
    queue q(100);
    TreeNode *p, *t;
    int x;
    cout << "Enter the Data for Root Node: ";
    cin >> x;
    root = new TreeNode;
    root->data = x;
    root->lchild = NULL;
    root->rchild = NULL;
    q.enqueue(root);
    while (!q.isEmpty())
    {
        p = q.dequeue();
        cout << "Enter the Data for L-Child (-1 for Empty Data): ";
        cin >> x;
        if (x != -1)
        {
            t = new TreeNode;
            t->data = x;
            t->lchild = t->rchild = NULL;
            p->lchild = t;
            q.enqueue(t);
        }
        cout << "Enter the Data for R-Child (-1 for Empty Data): ";
        cin >> x;
        if (x != -1)
        {
            t = new TreeNode;
            t->data = x;
            t->lchild = t->rchild = NULL;
            p->rchild = t;
            q.enqueue(t);
        }
    }
}

// Recursive Traversals
void r_preorder(TreeNode *t)
{
    if (t)
    {
        cout << t->data << " ";
        r_preorder(t->lchild);
        r_preorder(t->rchild);
    }
}

void r_inorder(TreeNode *t)
{
    if (t)
    {
        r_inorder(t->lchild);
        cout << t->data << " ";
        r_inorder(t->rchild);
    }
}

void r_postorder(TreeNode *t)
{
    if (t)
    {
        r_postorder(t->lchild);
        r_postorder(t->rchild);
        cout << t->data << " ";
    }
}

// Iterative Traversals
void i_preorder(TreeNode *t)
{
    stack st(50);
    while (t || !st.isEmpty())
    {
        if (t)
        {
            cout << t->data << " ";
            st.push(t);
            t = t->lchild;
        }
        else
        {
            t = st.pop();
            t = t->rchild;
        }
    }
}

void i_inorder(TreeNode *t)
{
    stack st(50);
    while (true)
    {
        while (t != NULL)
        {
            st.push(t);
            t = t->lchild;
        }
        if (st.isEmpty())
        {
            return;
        }
        t = st.pop();
        cout << t->data << " ";
        t = t->rchild;
    }
}

void i_postorder(TreeNode *t)
{
    stack s1(50);
    stack s2(50);
    s1.push(root);
    TreeNode *node;

    while (!s1.isEmpty())
    {
        node = s1.pop();
        s2.push(node);
        if (node->lchild)
            s1.push(node->lchild);
        if (node->rchild)
            s1.push(node->rchild);
    }
    while (!s2.isEmpty())
    {
        node = s2.pop();
        cout << node->data << " ";
    }
}

// Count the Number of Internal Nodes
int internal(TreeNode *t)
{
    int x, y;
    if (t)
    {
        x = internal(t->lchild);
        y = internal(t->rchild);
        if (t->lchild || t->rchild)
        {
            return x + y + 1;
        }
        else
            return x + y;
    }
    return 0;
}

// Count the Number of External Nodes
int external(TreeNode *t)
{
    int x, y;
    if (t)
    {
        x = external(t->lchild);
        y = external(t->rchild);
        if (!t->lchild && !t->rchild)
        {
            return x + y + 1;
        }
        else
            return x + y;
    }
    return 0;
}

// Height of Tree
int height(TreeNode *t)
{
    int x, y;
    if (t)
    {
        x = height(t->lchild);
        y = height(t->rchild);
        if (x > y)
        {
            return x + 1;
        }
        else
            return y + 1;
    }
    return 0;
}

// Copy Binary Tree
TreeNode *copy_Btree(TreeNode *t, TreeNode *t2)
{
    if (t == NULL)
    {
        t2 == NULL;
    }
    else
    {
        t2 = new TreeNode;
        t2->data = t->data;
        copy_Btree(t->lchild, t2->lchild);
        copy_Btree(t->rchild, t2->rchild);
        return t2;
    }
    return NULL;
}

// Swap Binary Nodes
void swap(TreeNode *t)
{
    if (t == NULL)
        return;
    else
    {
        TreeNode *temp;
        swap(t->lchild);
        swap(t->rchild);
        temp = t->lchild;
        t->lchild = t->rchild;
        t->rchild = temp;
    }
}

// Delete the Complete Binary Tree
void deleteALL(TreeNode *t)
{
    if (!t)
        return;
    else
    {
        deleteALL(t->lchild);
        deleteALL(t->rchild);
        delete t;
        t = NULL;
        root = NULL;
    }
}

int main()
{
    while (1)
    {
        cout << endl;
        cout << "***** MENU ***** " << endl;
        cout << "1. Create a Binary Tree" << endl;
        cout << "2. Tree Traversal" << endl;
        cout << "3. Change a BT so that the roles of the left and right pointers are swapped at every node." << endl;
        cout << "4. Find Height of BT" << endl;
        cout << "5. Copy this BT to another" << endl;
        cout << "6. Count Number of Internal and External Nodes" << endl;
        cout << "7. Erase all nodes in a BT " << endl;
        cout << "0. Exit" << endl;
        cout << endl;
        cout << "Enter the choice : ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            createtree();
            break;
        }
        case 2:
        {
            if (root == NULL)
            {
                cout << "Tree is Empty!" << endl;
                break;
            }
            else
            {
                cout << "1. Recursive traversal" << endl;
                cout << "2. Iterative traversal" << endl;
                cout << "Enter your Choice: ";
                int c;
                cin >> c;
                switch (c)
                {
                case 1:
                {
                    cout << "Recursive Preorder: ";
                    r_preorder(root);
                    cout << endl;
                    cout << "Recursive Inorder: ";
                    r_inorder(root);
                    cout << endl;
                    cout << "Recursive Postorder: ";
                    r_postorder(root);
                    cout << endl;
                    break;
                }
                case 2:
                {
                    cout << "Iterative Preorder: ";
                    i_preorder(root);
                    cout << endl;
                    cout << "Iterative Inorder: ";
                    i_inorder(root);
                    cout << endl;
                    cout << "Iterative Postorder: ";
                    i_postorder(root);
                    cout << endl;
                    break;
                }
                }
            }
            break;
        }
        case 3:
        {
            if (root == NULL)
            {
                cout << "Tree is Empty!" << endl;
                break;
            }
            swap(root);
            cout << "Successfully swapped the nodes!" << endl;
            cout << "Inorder Travesal: ";
            r_inorder(root);
            cout << endl
                 << endl;
            break;
        }
        case 4:
        {
            if (root == NULL)
            {
                cout << "Tree is Empty!" << endl;
                break;
            }
            cout << "Height of the Binary Tree is: " << height(root) << endl;
            break;
        }
        case 5:
        {
            if (root == NULL)
            {
                cout << "Tree is Empty!" << endl;
                break;
            }
            tree2 = copy_Btree(root, tree2);
            cout << "Tree Copied Successfully!" << endl;
            cout << "Inorder Traversal: ";
            r_inorder(tree2);
            cout << endl
                 << endl;
            break;
        }
        case 6:
        {
            if (root == NULL)
            {
                cout << "Tree is Empty!" << endl;
                break;
            }
            cout << "Number of Internal Nodes: " << internal(root) << endl;
            cout << "Number of External Nodes (Leaves): " << external(root) << endl;
            break;
        }
        case 7:
        {
            if (root == NULL)
            {
                cout << "Tree is Empty!" << endl;
                break;
            }
            deleteALL(root);
            cout << "All Nodes in the Tree are Erased Succesfully! Ending!" << endl;
            break;
        }
        default:
            cout << "THANK YOU!!!" << endl;
            exit(0);
        }
    }
    return 0;
}
