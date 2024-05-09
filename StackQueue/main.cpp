/*
Program Name: Stack Queue
Date: 11/4/2022
Author: Ji Min Yoon
Module Purpose:Designed to develop implementations of a stack and a queue using templates.

*/



#include <iostream>
using namespace std;

#include "stack.tpp"
#include "queue.tpp"

int main() {

    StackListClass<int> stack01;
    stack01.Display("stack01 created");

    for (int i : { 8, 5, 10, 7 }) {
        stack01.Push(i);
        cout << "Push(" << i << ")" << endl;
    }
    stack01.Display("stack01 populated");

    StackListClass<int> stack02 = stack01;
    stack02.Display("copy constructor StackListClass<int> stack02 = stack01");

    StackListClass<int> stack03;
    stack03.Display("stack03 created");

    stack03 = stack02;
    stack03.Display("= : stack03 = stack02");

    stack01.Clear();
    stack01.Display("stack01 empty:");

    stack02.Display("stack2:");
    int d = stack02.Pop();
    cout << "d : " << d << endl;
    stack02.Display("int d = stack02.Pop();");

    stack02.Display("stack2:");
    d = stack02.Pop();
    cout << "d : " << d << endl;
    stack02.Display("int d = stack02.Pop();");

    stack02.Display("stack2:");
    d = stack02.Pop();
    cout << "d : " << d << endl;
    stack02.Display("int d = stack02.Pop();");


    QueueListClass<int> queue01;
    queue01.Display("queue01");

    for (auto item : { 5,  8,  11, 17 })
        queue01.Enqueue(item);
    queue01.Display("queue01");

    d = queue01.Peek();
    cout << "d = queue01.Peek()" << d << endl;

    queue01.Display("queue01");
    d = queue01.Dequeue();
    queue01.Display(" queue01.dequeue()");

    QueueListClass<int> queue02 = queue01;
    queue02.Display("QueueListClass<int> queue02 = queue01");

    QueueListClass<int> queue03;
    queue03 = queue01 = queue02;
    queue01.Display("queue01 - queue03 = queue01 = queue02");
    queue02.Display("queue02 - queue03 = queue01 = queue02");
    queue03.Display("queue03 - queue03 = queue01 = queue02");

    queue01.Enqueue(333);
    queue01.Display("queue01.enqueue(333)");
    queue02.Enqueue(555);
    queue02.Display("queue02.enqueue(555)");

    queue02.Clear();
    queue02.Display("queue02.clear()");

    return(0);
}