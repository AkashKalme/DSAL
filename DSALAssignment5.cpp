//============================================================================
// Name        : Assignment5.cpp
// Author      : Akash Kalme
// Version     : 1
// Copyright   : Your copyright notice
// Description : Dictionary using Hashing
//                          Assignment - 5
// Name: Akash Kalme                                                Roll No.: 21141
// Problem Statement:
//  Implement all the functions of a dictionary (ADT) using hashing and handle collisions using separate chaining using linked list.
//  Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable, Keys must be unique.
//  Standard Operations: Insert (key, value), Find(key), Delete(key)
//============================================================================

#include <iostream>
#include <iomanip>

#define SIZE 100

using namespace std;

class HashEntry
{
    string word;
    string meaning;
    HashEntry *next;
    int node_count;

    friend class HashTable;

    HashEntry()
    {
        word = meaning = "";
        next = NULL;
        node_count = 0;
    }

    HashEntry(string key, string value)
    {
        this->word = key;
        this->meaning = value;
        this->next = NULL;
        node_count = 0;
    }
};

class HashTable
{
    HashEntry *Arr[SIZE];

public:
    HashTable()
    {
        for (int i = 0; i < SIZE; i++)
        {
            Arr[i] = new HashEntry();
        }
    }

    int HashFunction(string key)
    {
        int sum = 0;
        int len = key.length();
        for (int i = 0; i < len; i++)
        {
            sum += key[i];
        }
        return sum % SIZE;
    }

    void Insert(string key, string value)
    {
        int HashIndex = HashFunction(key);
        HashEntry *temp = Arr[HashIndex];
        temp->node_count++;
        while (temp->next != NULL)
        {
            if (temp != NULL)
                temp = temp->next;
        }
        temp->next = new HashEntry(key, value);
        cout << "Word Added Successfully!" << endl;
    }

    void Display()
    {
        HashEntry *temp = NULL;
        cout << left << setw(10) << "Bucket" << setw(15) << "Node Count" << setw(20) << "Word" << setw(20) << "Meaning" << endl;
        for (int i = 0; i < SIZE; i++)
        {
            temp = Arr[i];
            if (temp->next != NULL)
            {
                cout << left << setw(10) << i << setw(15) << temp->node_count << endl;
                temp = temp->next;
                while (temp != NULL)
                {
                    if (temp != NULL)
                    {
                        cout << left << setw(25) << " " << setw(20) << temp->word << setw(20) << temp->meaning << endl;
                        temp = temp->next;
                    }
                }
            }
        }
    }

    void Find_Word(string key)
    {
        int comparisons = 0;
        int HashIndex = HashFunction(key);
        HashEntry *temp = Arr[HashIndex];
        while (temp != NULL)
        {
            if (temp != NULL)
            {
                comparisons++;
                if (temp->word == key)
                {
                    cout << "Word Found in Dictionary!" << endl;
                    cout << "Word: " << key << endl;
                    cout << "Meaning: " << temp->meaning << endl;
                    cout << "Number of Comparisons: " << comparisons - 1 << endl;
                    return;
                }
                temp = temp->next;
            }
        }
        cout << "Word " << key << " not Present in Dictionary!" << endl;
    }

    void Delete_Key(string key)
    {
        HashEntry *temp = NULL;
        HashEntry *temp2 = NULL;
        int HashIndex = HashFunction(key);

        temp = Arr[HashIndex];

        if (temp->next == NULL)
        {
            cout << "Word NOT present in Dictionary!" << endl;
            return;
        }
        while (temp != NULL)
        {
            temp2 = temp;
            if (temp != NULL)
                temp = temp->next;
            if (temp == NULL)
            {
                cout << "Word NOT present in Dictionary!" << endl;
                return;
            }
            if (temp->word == key)
            {
                if (temp != NULL)
                    temp2->next = temp->next;
                else
                    temp2->next = NULL;
                delete temp;
                temp = NULL;
                return;
            }
        }
    }
};

int main()
{
    HashTable HT;
    int choice;
    string key, value;
    while (1)
    {
        cout << endl;
        cout << "MAIN MENU" << endl;
        cout << "1. Insert a Word and Meaning" << endl;
        cout << "2. Display Dictionary" << endl;
        cout << "3. Search a Word" << endl;
        cout << "4. Delete a Word" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter Your Choice: ";
        cin >> choice;

        cout << endl;

        switch (choice)
        {
        case 1:
        {
            cout << endl;
            cout << "Enter Word: ";
            cin >> key;
            cout << "Enter Meaning: ";
            cin >> value;
            HT.Insert(key, value);
            break;
        }

        case 2:
        {
            HT.Display();
            break;
        }

        case 3:
        {
            cout << endl;
            cout << "Enter Word to be Searched: ";
            cin >> key;
            HT.Find_Word(key);
            break;
        }

        case 4:
        {
            cout << endl;
            cout << "Enter Word to be Deleted: ";
            cin >> key;
            HT.Delete_Key(key);
            break;
        }

        case 0:
        {
            cout << "THANK YOU!" << endl;
            exit(0);
        }

        default:
        {
            cout << "INVALID CHOICE! Enter Again." << endl;
            break;
        }
        }
    }
}