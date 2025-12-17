#include <iostream>
using namespace std;

template <typename T>
struct Elem
{
    T data;
    Elem<T>* next;
    Elem<T>* prev;
};

template <typename T>
class List
{
    Elem<T>* Head;
    Elem<T>* Tail;
    int Count;

public:
    // Конструктор
    List()
    {
        Head = Tail = nullptr;
        Count = 0;
    }

    // Конструктор копирования
    List(const List<T>& L)
    {
        Head = Tail = nullptr;
        Count = 0;

        Elem<T>* temp = L.Head;
        while (temp)
        {
            AddTail(temp->data);
            temp = temp->next;
        }
    }

    // Деструктор
    ~List()
    {
        DelAll();
    }

    int GetCount() const
    {
        return Count;
    }

    // Удалить весь список
    void DelAll()
    {
        while (Count)
            Del(1);
    }

    void Del(int pos)
    {
        if (pos < 1 || pos > Count) return;

        Elem<T>* cur = Head;
        for (int i = 1; i < pos; i++)
            cur = cur->next;

        if (cur->prev) cur->prev->next = cur->next;
        if (cur->next) cur->next->prev = cur->prev;

        if (cur == Head) Head = cur->next;
        if (cur == Tail) Tail = cur->prev;

        delete cur;
        Count--;
    }

    void AddTail(T value)
    {
        Elem<T>* temp = new Elem<T>{ value, nullptr, Tail };

        if (Tail) Tail->next = temp;
        else Head = temp;

        Tail = temp;
        Count++;
    }

    void AddHead(T value)
    {
        Elem<T>* temp = new Elem<T>{ value, Head, nullptr };

        if (Head) Head->prev = temp;
        else Tail = temp;

        Head = temp;
        Count++;
    }

    void Print() const
    {
        Elem<T>* temp = Head;
        cout << "( ";
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << ")\n";
    }

    // оператор присваивания
    List<T>& operator=(const List<T>& L)
    {
        if (this == &L) return *this;

        DelAll();
        Elem<T>* temp = L.Head;

        while (temp)
        {
            AddTail(temp->data);
            temp = temp->next;
        }

        return *this;
    }

    // сложение списков
    List<T> operator+(const List<T>& L) const
    {
        List<T> res(*this);
        Elem<T>* temp = L.Head;

        while (temp)
        {
            res.AddTail(temp->data);
            temp = temp->next;
        }

        return res;
    }

    // переворот списка
    List<T> operator-() const
    {
        List<T> res;
        Elem<T>* temp = Head;

        while (temp)
        {
            res.AddHead(temp->data);
            temp = temp->next;
        }

        return res;
    }
};

int main()
{
    List<int> L;

    for (int i = 0; i < 10; i++)
        (i % 2 == 0) ? L.AddHead(i) : L.AddTail(i);

    L.Print();

    List<int> T = L;
    List<int> Sum = -L + T;

    Sum.Print();
}
