//============================================================================
// Name        : Assignment2.cpp
// Author      : Akash Kalme
// Version     : 1
// Copyright   : Your copyright notice
// Description : Dictionary using Binary Search Tree
//                          Assignment - 2
// Name: Akash Kalme                                                Roll No.: 21141
// Problem Statement:
//  A Dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords,
//  updating values of any entry. Provide facility to display whole data sorted in ascending/ Descending order.
//  Also find how many maximum comparisons may require for finding any keyword. Use Binary Search Tree for implementation.
//============================================================================

#include <iostream>
#include <string.h>
using namespace std;

class BST;
class Node
{
private:
    string word;
    string meaning;
    Node *lchild;
    Node *rchild;
public:
    friend class BST;
    Node()
    {
        word = meaning ="";
        lchild = rchild = NULL;
    }
    Node(string word, string meaning)
    {
        this->word = word;
        this->meaning = meaning;
        lchild = rchild = NULL;
    }
};

class BST
{
public:
    Node *root;
    BST()
    {
        root = NULL;
    }
    void Create();
    void Insert(Node *, string, string);
    int Search(Node *, string);
    void Update(Node *, string);
    void DisplayAscending(Node *);
    void DisplayDescending(Node *);
    Node *Delete(Node *, string);
    Node *Successor(Node *);
};

void BST :: Create()
{
    Node *temp = new Node;
    cout << "Enter Word: ";
    cin >> temp->word;
    cout << "Enter Meaning: ";
    cin >> temp->meaning;
    cout << endl;

    if (root == NULL)
    {
        root = temp;
    }
    else
    {
        Insert(root, temp->word, temp->meaning);
    }
    cout << "Insertion Successful!" << endl;
}

void BST :: Insert(Node *p, string word, string meaning)
{
    if (p == NULL)
    {
        p = new Node;
        p->word = word;
        p->meaning =meaning;
        p->lchild = p->rchild = NULL;
        p = new Node(word, meaning);
    }
    else
    {
        if (word < p->word)
        {
            if (p->lchild != NULL)
                Insert(p->lchild, word, meaning);
            else
                p->lchild = new Node (word, meaning);
        }
        else if (word > p->word)
        {
            if (p->rchild != NULL)
                Insert(p->rchild, word, meaning);
            else
                p->rchild = new Node (word, meaning);
        }
    }
}

int BST :: Search(Node *p, string word)
{
    int comparisons = 0;
    while (p != NULL)
    {
        if (word < p->word)
        {
            comparisons++;
            p = p->lchild;
        }
        else if (word > p->word)
        {
            comparisons++;
            p = p->rchild;
        }
        else if (word == p->word)
        {
            comparisons++;
            cout << "Word Found!" << endl;
            cout << "Word: " << p->word << " Meaning: " << p->meaning << endl << endl;
            cout << "Number of Comparisons: " << comparisons  << endl;
            return 1;
        }
    }
    cout << word << " is NOT Present in the Dictionary." << endl;
    return 0;
}

void BST :: DisplayAscending(Node *p)
{
    if (p != NULL)
    {
        DisplayAscending(p->lchild);
        cout << "Word: " << p->word << "    ";
        cout << "Meaning: " << p->meaning << endl;
        DisplayAscending(p->rchild);
    }
}

void BST :: DisplayDescending(Node *p)
{
    if (p != NULL)
    {
        DisplayDescending(p->rchild);
        cout << "Word: " << p->word << "    ";
        cout << "Meaning: " << p->meaning << endl;
        DisplayDescending(p->lchild);
    }
}

void BST :: Update(Node *p, string word)
{
    string new_meaning;
    while (p != NULL)
    {
        if (word < p->word)
            p = p->lchild;
        else if (word > p->word)
            p = p->rchild;
        else if (word == p->word)
        {
            cout << "Enter the New Meaning of Word " << word << ": ";
            cin >> new_meaning;
            cout << endl;
            p->meaning = new_meaning;
            cout << "Meaning of word "<< word <<" has been updated to:  " << p->meaning <<endl;
            return;
        }
    }
    cout << word << "is NOT present in Dictionary!" << endl;
}

Node* BST :: Successor (Node *q)
{
    while (q->lchild != NULL)
    {
        q = q->lchild;
    }
    return q;
}

Node* BST :: Delete(Node *p, string word)
{
    if (p == NULL)
        return p;
    Node *temp ;
    if (word < p->word)
        p->lchild = Delete(p->lchild, word);
    else if (word > p->word)
        p->rchild = Delete(p->rchild, word);
    else
    {
        // Node has 1 or 0 Child
        if (p->lchild == NULL)
        {
            temp = p->rchild;
            delete p;
            return temp;
        }
        else if (p->rchild == NULL)
        {
            temp = p->lchild;
            delete p;
            return temp;
        }
        // Node has 2 Children
        temp = Successor(p->rchild);
        p->word = temp->word;
        p->rchild = Delete(p->rchild, temp->word);
    }
    return p;
}

int main()
{
    BST dictionary;
    string find_word, update_word, delete_word;
    int choice;
    while(1)
    {
        cout << endl;
        cout << "********************MAIN MENU********************" << endl;
        cout << "1. Insert Item" << endl;
        cout << "2. Display Dictionary Items in Ascending Order" << endl;
        cout << "3. Display Dictionary Items in Descending Order" << endl;
        cout << "4. Search a Word in Dictionary" << endl;
        cout << "5. Update Meaning of a Word" << endl;
        cout << "6. Delete a Word and its Meaning" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter Your Choice: ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            dictionary.Create();
            break;

        case 2:
            if (dictionary.root == NULL)
            {
                cout << "Dictionary is Empty! Insert Item." << endl;
            }
            else
            {
                cout << "Dictionary in Ascending Order" << endl << endl;
                dictionary.DisplayAscending(dictionary.root);
            }
            break;

        case 3:
            if (dictionary.root == NULL)
            {
                cout << "Dictionary is Empty! Insert Item." << endl;
            }
            else
            {
                cout << "Dictionary in Descending Order" << endl << endl;
                dictionary.DisplayDescending(dictionary.root);
            }
            break;

        case 4:
            if (dictionary.root == NULL)
            {
                cout << "Dictionary is Empty! Insert Item." << endl;
            }
            else
            {
                cout << "Enter Word to be Found: ";
                cin >> find_word;
                dictionary.Search(dictionary.root, find_word);
            }
            break;

        case 5:
            if (dictionary.root == NULL)
            {
                cout << "Dictionary is Empty! Insert Item." << endl;
            }
            else
            {
                cout << "Enter Word whose Meaning is to be Updated: ";
                cin >> update_word;
                dictionary.Update(dictionary.root, update_word);
            }
            break;

        case 6:
            if (dictionary.root == NULL)
            {
                cout << "Dictionary is Empty! Insert Item." << endl;
            }
            else
            {
                cout << "Enter Word to be Deleted: ";
                cin >> delete_word;
                if (dictionary.Search(dictionary.root, delete_word))
                {
                    dictionary.Delete(dictionary.root, delete_word);
                    cout << "Succefully Deleted Word '" << delete_word << "' and its Meaning!" << endl;
                }
                else
                {
                    cout << delete_word << " Not Present in Dictionary." << endl;
                }
            }
            break;

        case 0:
            cout << "THANK YOU!" << endl;
            exit(0);

        default:
            cout << "INVALID CHOICE!" << endl;
            break;
        }
    }
    return 0;
}
