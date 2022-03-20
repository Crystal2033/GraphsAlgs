#pragma once
#ifndef COMPARATOR_H
#define COMPARATOR_H
#include <iostream>
#include "Cell.h"

template <typename Type>
class Comparator
{
public:
        virtual bool compare(Type const& left, Type const& right) const = 0;
        virtual      ~Comparator() {}
};


class ComparatorCells final : public Comparator<Cell*> //на всякий случай.
{
public:
        ComparatorCells() = default;
        bool compare(Cell* const& left, Cell* const& right) const override;
        ~ComparatorCells() = default;
};

#endif // COMPARATOR_H
