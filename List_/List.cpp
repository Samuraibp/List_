#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node<T>* next;
};

template <typename T>
class Stack
{
    Node<T>* Head;
    int Count;

public:
    Stack()
    {
        Head = nullptr;
        Count = 0;
    }

    Stack(const Stack<T>& S)
    {
        Head = nullptr;
        Count = 0;

        if (S.Head == nullptr) return;

        Node<T>* temp = S.Head;
        Stack<T> tmp;

        while (temp)
        {
            tmp.push(temp->data);
            temp = temp->next;
        }

        while (!tmp.isEmpty())
        {
            push(tmp.top());
            tmp.pop();
        }
    }

    ~Stack()
    {
        clear();
    }

    bool isEmpty() const
    {
        return Head == nullptr;
    }

    int size() const
    {
        return Count;
    }

    void push(const T& value)
    {
        Node<T>* temp = new Node<T>{ value, Head };
        Head = temp;
        Count++;
    }

    void pop()
    {
        if (isEmpty()) return;

        Node<T>* temp = Head;
        Head = Head->next;
        delete temp;
        Count--;
    }

    T top() const
    {
        if (isEmpty())
            throw runtime_error("Stack is empty");

        return Head->data;
    }

    void clear()
    {
        while (!isEmpty())
            pop();
    }

    Stack<T>& operator=(const Stack<T>& S)
    {
        if (this == &S) return *this;

        clear();

        Stack<T> tmp;
        Node<T>* cur = S.Head;

        while (cur)
        {
            tmp.push(cur->data);
            cur = cur->next;
        }

        while (!tmp.isEmpty())
        {
            push(tmp.top());
            tmp.pop();
        }

        return *this;
    }

    void print() const
    {
        Node<T>* temp = Head;
        cout << "Top -> ";
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main()
{
    Stack<int> S;

    S.push(10);
    S.push(20);
    S.push(30);

    S.print();   

    S.pop();
    S.print();   

    cout << "Top element: " << S.top() << endl;

    Stack<int> S2 = S;
    S2.print();
}
