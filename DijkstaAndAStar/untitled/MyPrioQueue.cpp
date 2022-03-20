#include "MyPrioQueue.h"
bool comp(Cell* first, Cell* second)
{
    return first->get_mark() < second->get_mark();
}; //bad code (hard code)



