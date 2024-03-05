#pragma once

template<typename T>
class LinkedList
{
public:
    LinkedList()
    {

    }
    
    ~LinkedList()
    {
        Node* current = first;
        while(current != nullptr)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    typedef void (*Foreach)(T value);

    struct Node
    {
        T value;
        Node* next;
    };

    void Add(T value)
    {
        if (last == nullptr)
        {
            first = new Node();
            first->value = value;
            last = first;
            return;
        }

        Node* node = new Node();
        node->value = value;
        last->next = node;
        last = last->next;
    }

    T& Get(int index)
    {
        Node* current = first;
        for(int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->value;
    }

    void Loop(Foreach callback)
    {
        Node* current = first;
        while(current != nullptr)
        {
            callback(current->value);
            current = current->next;
        }
    }
private:
    Node* first = nullptr;
    Node* last = nullptr;
};