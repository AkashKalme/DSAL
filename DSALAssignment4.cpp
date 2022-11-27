//============================================================================
// Name        : Assignment4.cpp
// Author      : Akash Kalme
// Version     : 1
// Copyright   : Your copyright notice
// Description : Telephone Book Database using Hashing
//                          Assignment - 4
// Name: Akash Kalme                                                Roll No.: 21141
// Problem Statement:
//  Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client‘s telephone number. 
//  Make use of two collision handling techniques and compare them using number of comparisons required to find a set of telephone numbers 
//  (use linear probing with replacement and without replacement).
//============================================================================

#include <iostream>
#include <iomanip>

#define SIZE 117
#define ll long long int

using namespace std;

class HashEntry
{
    ll tele_No;
    string name;

    HashEntry()
    {
        this->name = "";
        this->tele_No = 0;
    }
    friend class HashTable;
};

class HashTable
{
    HashEntry Arr[SIZE];
    int count;

public:
    HashTable()
    {
        this->count = 0;
    }
    
    int HashFunction(ll key)
    {
        return key % SIZE;
    }

    void insert_without_replacement(ll key, string value)
    {
        if(count == SIZE)
        {
            cout << "Table is Full!" << endl;
            return;
        }
        int HashIndex = HashFunction(key);
        int HashIndex_Copy = HashIndex;
        do
        {
            if(Arr[HashIndex].tele_No == 0)
            {
                Arr[HashIndex].tele_No = key;
                Arr[HashIndex].name = value;
                count++;
                break;
            }
            HashIndex = (HashIndex+1)%SIZE;
        } while (HashIndex != HashIndex_Copy);
    }

    void insert_with_replacement(ll key, string value)
    {
        if(count == SIZE)
        {
            cout << "Table is Full!" << endl;
            return;
        }
        int HashIndex = HashFunction(key);
        int HashIndex_Copy = HashIndex;
        do
        {
            if(Arr[HashIndex].tele_No == 0)
            {
                Arr[HashIndex].tele_No = key;
                Arr[HashIndex].name = value;
                count++;
                break;
            }
            else
            {
                int HashIndex_Collision = HashFunction(Arr[HashIndex].tele_No);
                if(HashIndex != HashIndex_Collision && HashIndex == HashIndex_Copy)
                {
                    ll KeyCollision = Arr[HashIndex].tele_No;
                    string ValueCollision = Arr[HashIndex].name;
                    Arr[HashIndex].tele_No = key;
                    Arr[HashIndex].name = value;
                    insert_with_replacement(KeyCollision, ValueCollision);
                    break;
                }
                else
                {
                    HashIndex = (HashIndex+1) % SIZE;
                }
            }
        } while (HashIndex != HashIndex_Copy);
    }
    
    void Display()
    {
        for(int i=0; i<SIZE; i++)
        {
            if(Arr[i].tele_No != 0)
            {
                cout << setw(10)<< i << setw(20) << Arr[i].tele_No << setw(20) << Arr[i].name << endl; 
            }
        }
    }

    void Search(ll key)
    {
        int comparisons = 0;
        int HashIndex = HashFunction(key);
        int HashIndex_Copy = HashIndex;
        do
        {
            if(Arr[HashIndex].tele_No == key)
            {
                cout << "Telephone Number Found!" << endl;
                cout << left << setw(10) << "Index" << setw(20) << "Telephone Number" << setw(20) << "Name" << setw(12) << "Comparisons" << endl;
                cout << left << setw(10) << HashIndex << setw(20) << Arr[HashIndex].tele_No << setw(20) << Arr[HashIndex].name << setw(12) << comparisons << endl;
                return;
            }
            HashIndex = (HashIndex+1) % SIZE;
            comparisons++;
        } while (HashIndex != HashIndex_Copy);
        cout << "Telephone Number NOT Found!" << endl;
    }
};

int main()
{
    HashTable with_replacement;
    HashTable without_replacement;
    int choice;
    while(1)
    {
        cout << endl;
        cout << "MAIN MENU" << endl;
        cout << "1. Add Entry to Telephone Book" << endl;
        cout << "2. Display Telephone Book" << endl;
        cout << "3. Search Telephone Number" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter Your Choice: ";
        cin >> choice;

        cout << endl;

        switch(choice)
        {
        case 1:
        {
            ll key;
            string value;
            cout << "Enter Telephone Number: ";
            cin >> key;
            cout << "Enter Name of Client: ";
            cin >> value;
            without_replacement.insert_without_replacement(key, value);
            with_replacement.insert_with_replacement(key, value);
            break;
        }

        case 2:
        {
            cout << "Table Without Replacement" << endl;
            cout << left << setw(10) << "Index" << setw(20) << "Telephone Number" << setw(20) << "Name" << endl;
            without_replacement.Display();
            cout << endl << endl;

            cout << "Table with Replacement" << endl;
            cout << setw(10) << "Index" << setw(20) << "Telephone Number" << setw(20) << "Name" << endl;
            with_replacement.Display();
            cout << endl << endl;
            break;
        }

        case 3:
        {
            ll key;
            cout << "Enter Telephone Number to be Searched: ";
            cin >> key;
            cout << endl;
            cout << "Search for Table without Replacement" << endl;
            without_replacement.Search(key);
            cout << endl;
            cout << "Search for Table with Replacement" << endl;
            with_replacement.Search(key);
            cout << endl;
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
    return 0;
}