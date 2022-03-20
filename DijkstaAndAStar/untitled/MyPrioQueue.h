#pragma once
#ifndef MYPRIOQUEUE_H
#define MYPRIOQUEUE_H

#include <vector>
#include <iterator>
#include "Comparator.h"
#include <algorithm>
#include "Exceptions.h"


template <typename Type, typename Key>
class PriorityQueue
{
private:
    std::vector<Type> prio_queue;
    Comparator<Type>* comparator;
    bool is_exist(const Type& element) const;
public:
    PriorityQueue() = default;
    PriorityQueue(Comparator<Type>* cmp) { comparator = cmp; };
    void  push_in_queue(const Type& element);
    Type  pop_min();
    Type& get_min();
    void  update_queue();
    bool  is_empty() const { return (prio_queue.size() == 0) ? true : false; };
    void  clear_queue();
    ~PriorityQueue();
};
bool comp(Cell* first, Cell* second);


template <typename Type, typename Key>
Type& PriorityQueue<Type, Key>::get_min()
{
    if (is_empty())
    {
        throw Exception("Priority queue is empty. Get_min error.");
    }
    auto iterator = prio_queue.begin();
    return *iterator;
}


template <typename Type, typename Key>
void PriorityQueue<Type, Key>::push_in_queue(const Type& element)
{
    if (is_exist(element))
    {
        return;
    }

    auto iterator = prio_queue.begin();

    while (iterator != prio_queue.end())
    {
        if (!comparator->compare(element, *iterator))
        {
            iterator++;
        }
        else
        {
            prio_queue.insert(iterator, element);
            return;
        }
    }
    prio_queue.push_back(element);
    return;
}

template <typename Type, typename Key>
Type PriorityQueue<Type, Key>::pop_min()
{
    if (is_empty())
    {
        throw Exception("Priority queue is empty. Pop_min error.");
    }
    auto iterator = prio_queue.begin();
    Type object = *iterator;
    prio_queue.erase(prio_queue.begin());
    return object;
}

template <typename Type, typename Key>
void PriorityQueue<Type, Key>::update_queue()
{
    std::sort(prio_queue.begin(), prio_queue.end(), comp); //bad code (hard code). Didn`t think how to fix because too long.
}

template <typename Type, typename Key>
bool PriorityQueue<Type, Key>::is_exist(const Type& element) const
{
    for (auto it : prio_queue) // optymization: dichotomy search. Because sorted collection.
    {
        if (it == element)
        {
            return true;
        }
    }
    return false;
}

template<typename Type, typename Key>
void PriorityQueue<Type, Key>::clear_queue()
{
    while(!prio_queue.empty())
    {
        prio_queue.pop_back();
    }
}

template<typename Type, typename Key>
PriorityQueue<Type, Key>::~PriorityQueue()
{
    clear_queue();
}
#endif // MYPRIOQUEUE_H
