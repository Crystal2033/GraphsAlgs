#ifndef ALGORITHMGRAPH_H
#define ALGORITHMGRAPH_H
#include "Comparator.h"
#include "MyPrioQueue.h"
#include <QtMath>

enum STATUS{DONE, RUN, WAY_ERROR};
enum ALG   {DIJKSTRA, ASTAR};

class AlgorithmsGraph
{
private:
    Comparator<Cell*>*         comparator;// = new ComparatorCells;
    PriorityQueue<Cell*, int>* queue;
    STATUS                     status;
    ALG                        alg_type;
    QGraphicsScene*            alg_scene; //for getting this scene to cell for text values (mark, weight, eurystic)
    int                        start_row, end_row, start_col, end_col;
    int                        map_size;
    bool                       need_print_nums;
    Cell*                      last_shown_vertex = nullptr;
    QVector<QVector<Cell>>*    cells;
    unsigned long              value_of_visited = 0;
    unsigned long              max_value_of_visited;

    QList<Cell*> get_neighbours(int row, int col, PriorityQueue<Cell*, int>& queue);
    void         show_the_way_from_vertex(Cell& curr_cell);
    void         clear_drawn_way();
    double       get_rotate_angle(const QPoint& curr_cell, const QPoint& neighbour_cell) const;

public:

    AlgorithmsGraph();
    AlgorithmsGraph(const STATUS& status);

    void   set_print_status(const bool decision) {need_print_nums = decision;};
    void   set_scene(QGraphicsScene* scene) {alg_scene = scene;};
    void   set_map_size(const int map_size) {this->map_size = map_size; max_value_of_visited = map_size*map_size;};
    void   set_alg_type(const ALG &alg_type) {this->alg_type = alg_type;};
    void   Dijkstra_step();
    void   AStar_step();
    void   show_the_way();
    void   set_begin(const PointCells& start_point, const PointCells& end_point, QVector<QVector<Cell>>& cells);

    int    chebyshev_distance(const QPoint& curr_position);
    int    get_map_size() const {return map_size;};
    STATUS get_status() const {return status;};
    ALG    get_alg_type() const {return alg_type;};

    ~AlgorithmsGraph();
};

#endif // ALGORITHMGRAPH_H
