#include "Comparator.h"

bool ComparatorCells::compare(Cell* const& left, Cell* const& right) const
{
        return left->get_mark() < right->get_mark();
}
