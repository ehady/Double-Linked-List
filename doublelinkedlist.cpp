#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>
#include <iterator>

struct Node
{
    int value;
    Node *next;
    Node *prev;

    explicit Node(int v) : value(v), next(nullptr), prev(nullptr) {}
    /* used to mark constructors to NOT implicitly convert types */
};

class DoubleLinkedList
{
    Node *head;
    Node *tail;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr) {}
    Node *begin()
    {
        return head;
    }
    Node *end()
    {
        return tail;
    }
    void push_back(int v)
    {
        Node *n = new Node(v);
        if (head == nullptr)
        {
            head = n;
            tail = n;
        }
        else
        {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
    }
    void push_front(int v)
    {
        Node *n = new Node(v);
        if (head == nullptr)
        {
            head = n;
            tail = n;
        }
        else
        {
            head->prev = n;
            n->next = head;
            head = n;
        }
    }
    void pop_back()
    {
        if (tail == nullptr)
        {
            return;
        }
        if (tail == head)
        {
            delete tail;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node *n = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete n;
    }
    void pop_front()
    {
        if (head == nullptr)
        {
            return;
        }
        if (tail == head)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node *n = head;
        head = head->next;
        head->prev = nullptr;
        delete n;
    }
    bool empty()
    {
        return head == nullptr;
    }
    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }
    ~DoubleLinkedList()
    {
        clear();
    }
    void print()
    {
        Node *n = head;
        while (n != nullptr)
        {
            std::cout << n->value << " ";
            n = n->next;
        }
        std::cout << std::endl;
    }
    void remove(Node *n)
    {
        if (n == head)
        {
            pop_front();
            return;
        }
        if (n == tail)
        {
            pop_back();
            return;
        }
        n->prev->next = n->next;
        n->next->prev = n->prev;
        delete n;
    }
    void insert_before(Node *n, int value)
    {
        if (n == nullptr)
        {
            push_back(value);
            return;
        }
        if (n == head)
        {
            push_front(value);
            return;
        }
        Node *new_node = new Node(value);
        new_node->next = n;
        new_node->prev = n->prev;
        n->prev->next = new_node;
        n->prev = new_node;
    }
    Node *find(Node *from, Node *up_to, int value)
    {
        if (from == nullptr)
        {
            from = head;
        }
        while (from != up_to)
        {
            if (from->value == value)
            {
                break;
            }
            from = from->next;
        }
        return from;
    }
    /* or just use find
             Node *find(int value)
        {
                return find(head, nullptr, value);
        }
*/
    void fill(Node *n1, Node *n2, int value)
    {
        if (n1 == nullptr)
        {
            n1 = head;
        }
        while (n1 != n2)
        {
            n1->value = value;
            n1 = n1->next;
        }
    }
    void fill_n(Node *from, int n, int v)
    {
        while (n--) // until n reaches 0
        {
            from->value = v;
            from = from->next;
        }
    }

    void iota(Node *from, Node *up_to, int start)
    {
        if (from == nullptr)
        {
            from = head;
        }
        int i = start;
        while (from != nullptr)
        {
            from->value = i++;
            from = from->next;
        }
    }
    /* void iota(int start)
    {
        iota(head, nullptr, start);
    } */
    void reverse()
    {
        Node *n = head;
        while (n != nullptr)
        {
            Node *next = n->next;
            n->next = n->prev;
            n->prev = next;
            n = next;
        }
        std::swap(head, tail);
    }
    void insert_sorted(int data)
    {
        Node *n = head;
        while (n != nullptr)
        {
            if (n->value > data)
            {
                insert_before(n, data);
                break;
            }
            n = n->next;
        }
    }
};

int main()
{
    DoubleLinkedList L;
    L.push_back(1);
    L.push_back(3);
    L.push_back(5);
    L.push_back(7);
    L.push_back(9);
    L.insert_sorted(6);
    L.insert_sorted(2);
    L.print();
    L.remove(L.find(L.begin(), L.end(), 3));
    L.print();
    L.fill()
}