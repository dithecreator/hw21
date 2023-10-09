//
//  main.cpp
//  hw21
//
//  Created by Дима on 09.10.23.
//



#include <stdio.h>
#include <iostream>
using namespace std;




struct Elem
{
    int data; // данные
    Elem* next, * prev;
    int Count;
};

template <class T>
class Queue{
    // Голова, хвост
    Elem* Head, * Tail;
    // Количество элементов
    int Count;

public:

    // Конструктор
    Queue <T>();
    
    Queue<T>(T sum);

    // Деструктор
    ~Queue <T>();

    // Получить количество
    int GetCount();
    // Получить элемент списка
    Elem* GetElem(int);

    // Удалить весь список
    void DelAll();
    // Удаление элемента, если параметр не указывается,
    // то функция его запрашивает
    void Del(int pos = 0);
    // Вставка элемента, если параметр не указывается,
    // то функция его запрашивает
    void Insert(int pos = 0);

    // Добавление в конец списка
    void AddTail(int n);

    // Добавление в начало списка
    void AddHead(int n);

    // Печать списка
    void Print();
    // Печать определенного элемента
    void Print(int pos);

 
};


template <class T>
Queue<T>:: Queue(T sum){
     Head = Tail = NULL;
    Count = sum;
}

template <class T>
Queue<T>::Queue()
{
    // Изначально список пуст
    Head = Tail = NULL;
    Count = 0;
}

template <class T>
Queue<T>::~Queue()
{
    // Удаляем все элементы
    DelAll();
}

template <class T>
void Queue<T>::AddHead(int n)
{
    // новый элемент
    Elem* temp = new Elem;

    // Предыдущего нет
    temp->prev = 0;
    // Заполняем данные
    temp->data = n;
    // Следующий - бывшая голова
    temp->next = Head;

    // Если элементы есть?
    if (Head != 0)
        Head->prev = temp;

    // Если элемент первый, то он одновременно и голова и хвост
    if (Count == 0)
        Head = Tail = temp;
    else
        // иначе новый элемент - головной
        Head = temp;

    Count++;
}



template <class T>
void Queue<T>::AddTail(int n)
{
    // Создаем новый элемент
    Elem* temp = new Elem;
    // Следующего нет
    temp->next = 0;
    // Заполняем данные
    temp->data = n;
    // Предыдущий - бывший хвост
    temp->prev = Tail;

    // Если элементы есть?
    if (Tail != 0)
        Tail->next = temp;

    // Если элемент первый, то он одновременно и голова и хвост
    if (Count == 0)
        Head = Tail = temp;
    else
        // иначе новый элемент - хвостовой
        Tail = temp;

    Count++;
}

template <class T>
void Queue<T>::Insert(int pos)
{
    // если параметр отсутствует или равен 0, то запрашиваем его
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }

    // Позиция от 1 до Count?


    if (pos < 1 || pos > Count + 1)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return;
    }

    // Если вставка в конец списка
    if (pos == Count + 1)
    {
        // Вставляемые данные
        int data;
        cout << "Input new number: ";
        cin >> data;
        // Добавление в конец списка
        AddTail(data);
        return;
    }
    else if (pos == 1)
    {
        // Вставляемые данные
        int data;
        cout << "Input new number: ";
        cin >> data;
        // Добавление в начало списка
        AddHead(data);
        return;
    }

    // Счетчик
    int i = 1;

    // Отсчитываем от головы n - 1 элементов
    Elem* Ins = Head;

    while (i < pos)
    {
        // Доходим до элемента,
        // перед которым вставляемся
        Ins = Ins->next;
        i++;
    }

    // Доходим до элемента,
    // который предшествует
    Elem* PrevIns = Ins->prev;

    // Создаем новый элемент
    Elem* temp = new Elem;

    // Вводим данные
    cout << "Input new number: ";
    cin >> temp->data;

    // настройка связей
    if (PrevIns != 0 && Count != 1)
        PrevIns->next = temp;

    temp->next = Ins;
    temp->prev = PrevIns;
    Ins->prev = temp;

    Count++;
}

template <class T>
void Queue<T>::Del(int pos)
{
    // если параметр отсутствует или равен 0, то запрашиваем его
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }
    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return;
    }

    // Счетчик
    int i = 1;

    Elem* Del = Head;

    while (i < pos)
    {
        // Доходим до элемента,
        // который удаляется
        Del = Del->next;
        i++;
    }

    // Доходим до элемента,
    // который предшествует удаляемому
    Elem* PrevDel = Del->prev;
    // Доходим до элемента, который следует за удаляемым
    Elem* AfterDel = Del->next;

    // Если удаляем не голову
    if (PrevDel != 0 && Count != 1)
        PrevDel->next = AfterDel;
    // Если удаляем не хвост
    if (AfterDel != 0 && Count != 1)
        AfterDel->prev = PrevDel;

    // Удаляются крайние?
    if (pos == 1)
        Head = AfterDel;
    if (pos == Count)
        Tail = PrevDel;

    // Удаление элемента
    delete Del;

    Count--;
}


template <class T>
void Queue<T>::Print(int pos)
{
    // Позиция от 1 до Count?


    if (pos < 1 || pos > Count)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return;
    }

    Elem* temp;

    // Определяем с какой стороны
    // быстрее двигаться
    if (pos <= Count / 2)
    {
        // Отсчет с головы
        temp = Head;
        int i = 1;

        while (i < pos)
        {
            // Двигаемся до нужного элемента
            temp = temp->next;
            i++;
        }
    }
    else
    {
        // Отсчет с хвоста
        temp = Tail;
        int i = 1;

        while (i <= Count - pos)
        {
            // Двигаемся до нужного элемента
            temp = temp->prev;
            i++;
        }
    }
    // Вывод элемента
    cout << pos << " element: ";
    cout << temp->data << endl;
}


template <class T>
void Queue<T>::Print()
{
    // Если в списке присутствуют элементы, то пробегаем по нему
    // и печатаем элементы, начиная с головного
    if (Count != 0)
    {
        Elem* temp = Head;
        cout << "( ";
        while (temp->next != 0)
        {
            cout << temp->data << ", ";
            temp = temp->next;
        }

        cout << temp->data << " )\n";
    }
}


template <class T>
void Queue<T>::DelAll()
{
    // Пока остаются элементы, удаляем по одному с головы
    while (Count != 0)
        Del(1);
}

template <class T>
int Queue<T>::GetCount()
{
    return Count;
}


template <class T>
Elem* Queue<T>::GetElem(int pos)
{
    Elem* temp = Head;

    // Позиция от 1 до Count?
    if (pos < 1 || pos > Count)
    {
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return 0;
    }

    int i = 1;
    // Ищем нужный нам элемент
    while (i < pos && temp != 0)
    {
        temp = temp->next;
        i++;
    }

    if (temp == 0)
        return 0;
    else
        return temp;
}

// Тестовый пример
int main()
{
    Queue<int> queue(11);
    
        for (int i = 0; i < 11; i++) {
            queue.AddHead(rand() % (11));
        }

            queue.Print();
     
}

