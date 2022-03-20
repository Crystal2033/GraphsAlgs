#pragma once
#ifndef BUILDER_H
#define BUILDER_H
#include "Cell.h"
#include <time.h>
#include<iostream>
#include "Exceptions.h"

class Builder
{
private:
    int  map_size;
    bool is_user_map;
public:
    Builder() = default;

    void set_map_size(const int size) {map_size = size;};
    int  get_map_size() const {return map_size;};
    bool get_is_user_map() const {return is_user_map;};
    void build_location(QVector<QVector<Cell>>& cells, QGraphicsScene* scene, const int size_map);
    void build_existing_map(const std::string my_map[10], QVector<QVector<Cell>>& cells, QGraphicsScene* scene);
    void remove_colors_and_cells_stats(QVector<QVector<Cell>>& cells) const;
};

#endif // BUILDER_H
