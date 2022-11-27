//============================================================================
// Name        : Assignment8.cpp
// Author      : Akash Kalme
// Version     : 1
// Copyright   : Your copyright notice
// Description : Topological Sorting
//                          Assignment - 8
// Name: Akash Kalme                                                Roll No.: 21141
// Problem Statement:
//  Write a C++/Java program to implement topological sorting on graph using object oriented 
//  programming features Design necessary class. ( Use of graph)
//============================================================================

#include <bits/stdc++.h>
#include <iostream>
#define MAX 50
typedef long long ll;
using namespace std;
class Queue
{ // Queue Class For Topoloagiacal Sort!
    int Q[MAX];
    int front;
    int rear;

public:
    Queue()
    {
        front = -1;
        rear = -1;
    }
    int top() // Return the top Eleement of the queue
    {
        return Q[front];
    }
    
    void Enqueue(int v)
    {
        if (front == -1 && rear == -1)
        {
            front++;
            rear++;
        }
        else
        {
            rear++;
        }
        Q[rear] = v;
    }
    int Dequeue()
    {
        int x;
        x = Q[front];
        front++;
        return x;
    }
    int Empty()
    {
        if (front == rear || front == -1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    
};

class Graph
{
    ll G[100][100];
    ll TS[100];
    ll B[100];
    ll size;

public:
    Graph(int m)
    {
        size = m;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                G[i][j] = 0;
            }
        }
    }
    void Insert(int x, int y)
    {
        if (G[y][x] == 0)
        {
            G[x][y] = 1;
        }
        else
        {
            cout << "\nGraph must be Acyclic!" << endl;
        }
    }
    int Indegree(int x)
    {
        int indeg_count = 0;
        for (int i = 0; i < size; i++)
        {
            if (G[i][x] == 1)
            {
                indeg_count++;
            }
        }
        return indeg_count;
    }
    void Display()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << G[i][j] << "  ";
            }
            cout << endl;
        }
    }

    void Topological()
    {
        Queue q;
        int j = 0;
        for (int i = 0; i < size; i++)
        {
            TS[i] = Indegree(i);
            if (TS[i] == 0)
            {
                q.Enqueue(i);
            }
        }
        while (!q.Empty())
        {
            int k = q.top();
            q.Dequeue();
            B[j++] = k;

            for (int i = 0; i < size; i++)
            {
                if (G[k][i] == 1)
                {
                    G[k][i] = 0;
                    TS[i] = TS[i] - 1;
                    if (TS[i] == 0)
                    {
                        q.Enqueue(i);
                    }
                }
            }
        }
        for (int i = 0; i < size; i++)
        {
            cout << B[i] << "  ";
        }
        cout << endl;
    }
    friend class Queue;
};

int main()
{
    int ch, v;
    cout << "\nEnter theTotal Number Of Vertex - ";
    cin >> v;
    Graph g(v);
    do
    {
        cout << "\n1.Create Graph - " << endl;
        cout << "2.To Display - " << endl;
        cout << "3.Display Topological Sort" << endl;
        cout << "\nEnter the Choice  - ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            int e;
            cout << "\nEnter the Total Number of Edges - ";
            cin >> e;
            for (int i = 0; i < e; i++)
            {
                int x, y;
                cout << "\nEnter the source and Destination - ";
                cin >> x >> y;
                g.Insert(x, y);
            }
            break;
        case 2:
            g.Display();
            break;
        case 3:
            g.Topological();
            break;
        default:
            break;
        }
    } while (ch != 0);

    return 0;
}
