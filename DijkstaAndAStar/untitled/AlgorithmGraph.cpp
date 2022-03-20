#include "AlgorithmGraph.h"


AlgorithmsGraph::AlgorithmsGraph()
{
    comparator = new ComparatorCells;
    queue      = new PriorityQueue<Cell*, int>(comparator);
}

AlgorithmsGraph::AlgorithmsGraph(const STATUS &status)
{
    this->status = status;
    comparator   = new ComparatorCells;
    queue        = new PriorityQueue<Cell*, int>(comparator);
}

QList<Cell*> AlgorithmsGraph::get_neighbours(int row, int col, PriorityQueue<Cell *, int> &queue)
{
    QList<Cell*> cell_list;
    for(int i = -1; i < 2; i++)
    {
        int x = row + i;
        if(x < 0 || (x > map_size - 1))
        {
            continue;
        }
        for(int j = -1; j < 2; j++)
        {

            int y = col + j;
            if(y < 0 || (y > map_size - 1) || (i == 0 && j == 0))
            {
                continue;
            }
            if ((*cells)[x][y].is_visited() || (*cells)[x][y].is_wall())
            {
                continue;
            }
            cell_list.append(&(*cells)[x][y]);
            queue.push_in_queue(&(*cells)[x][y]);
            if((*cells)[x][y].get_color_brush() == QColor(YELLOW))
            {
                continue;
            }
            (*cells)[x][y].repaint_cell(QColor(YELLOW));
        }
    }
    return cell_list;
}

void AlgorithmsGraph::show_the_way_from_vertex(Cell &curr_cell)
{
    int vert_end_row = curr_cell.get_position().x();
    int vert_end_col = curr_cell.get_position().y();

    Cell* cur_pos_way = &(*cells)[vert_end_row][vert_end_col];
    while(cur_pos_way != &(*cells)[start_row][start_col])
    {
        if(cur_pos_way == nullptr)
        {

            status = WAY_ERROR;
            break;
        }
        cur_pos_way->repaint_cell(QColor(INDIGO));
        cur_pos_way = cur_pos_way->get_vertex_min_ptr();
    }
    last_shown_vertex = &curr_cell;
}

void AlgorithmsGraph::clear_drawn_way()
{
    if(last_shown_vertex == nullptr)
    {
        return;
    }

    int vert_end_row = last_shown_vertex->get_position().x();
    int vert_end_col = last_shown_vertex->get_position().y();

    Cell* cur_pos_way = &(*cells)[vert_end_row][vert_end_col];
    while(cur_pos_way != &(*cells)[start_row][start_col])
    {
        if(cur_pos_way == nullptr)
        {

            status = WAY_ERROR;
            break;
        }
        cur_pos_way->repaint_cell(QColor(YELLOW));
        cur_pos_way = cur_pos_way->get_vertex_min_ptr();
    }
}

double AlgorithmsGraph::get_rotate_angle(const QPoint &curr_cell, const QPoint &neighbour_cell) const
{
    double angle = 0.0;
    angle = qRadiansToDegrees(qAtan2((double)(curr_cell.x() - neighbour_cell.x()), double(curr_cell.y() - neighbour_cell.y())));
    if(angle < 0)
    {
        angle += 360;
    }
    return angle;
}

void AlgorithmsGraph::Dijkstra_step()
{
    clear_drawn_way();
    try
    {
    //qDebug() << "Before. Visited value = " << value_of_visited;
    Cell* min_queue = queue->pop_min();
    //value_of_visited++;
    qDebug() << "Here is good";
    if (min_queue == &(*cells)[end_row][end_col])
    {
         status = DONE;
    }
//    if(min_queue == &(*cells)[end_row][end_col])
//    {
//        status = DONE;
//        queue->clear_queue();
//    }

    QList<Cell*> neigh_cells = get_neighbours(min_queue->get_position().x(), min_queue->get_position().y(), *queue);
    for (auto iterator : neigh_cells)
    {
        if(iterator->is_visited())
        {
            continue;
        }


        int new_mark = min_queue->get_mark() + iterator->get_weight();
        if(new_mark < iterator->get_mark())
        {
            iterator->set_mark(new_mark);
            iterator->set_new_min_cell_ptr(min_queue);
            queue->update_queue();
        }


        show_the_way_from_vertex(*min_queue);

    }
    min_queue->set_visited_status(true);
    //value_of_visited++;
    }
    catch(Exception& err)
    {
        qDebug() << err.what();
        status = WAY_ERROR;
    }
}

void AlgorithmsGraph::AStar_step()
{
    clear_drawn_way();
    try
    {

    Cell* min_queue = queue->pop_min();
    if(min_queue == &(*cells)[end_row][end_col])
    {
        status = DONE;
        queue->clear_queue();
    }

    QList<Cell*> neigh_cells = get_neighbours(min_queue->get_position().x(), min_queue->get_position().y(), *queue);
    for (auto iterator : neigh_cells)
    {
        if(iterator->is_visited())
        {
            continue;
        }
        iterator->set_eurystic_num(chebyshev_distance(iterator->get_position()) * 10);

        int evrystic_number = iterator->get_eurystic_num();
        int cell_weight     = iterator->get_weight();
        int new_mark        = cell_weight + evrystic_number;
        if(new_mark < iterator->get_mark())
        {
            iterator->set_weight(cell_weight + min_queue->get_weight());
            new_mark = iterator->get_weight() + evrystic_number;
            iterator->set_mark(new_mark);
            iterator->set_new_min_cell_ptr(min_queue);
            queue->update_queue();
        }
        if(need_print_nums)
        {
            iterator->show_text_nums(alg_scene);
            int angle = (int)get_rotate_angle(min_queue->get_position(), iterator->get_position());
            iterator->show_arrow_and_rotate(angle, alg_scene);
        }
        show_the_way_from_vertex(*min_queue);

    }
    min_queue->set_visited_status(true);
    //value_of_visited++;
    }
    catch(Exception& err)
    {
        qDebug() << err.what();
        status = WAY_ERROR;
    }

}

void AlgorithmsGraph::show_the_way()
{
    Cell* cur_pos_way = &(*cells)[end_row][end_col];
    while(cur_pos_way != &(*cells)[start_row][start_col])
    {
        if(cur_pos_way == nullptr)
        {

            status = WAY_ERROR;
            break;
        }
        cur_pos_way->repaint_cell(QColor(INDIGO));
        cur_pos_way = cur_pos_way->get_vertex_min_ptr();
    }
}

int AlgorithmsGraph::chebyshev_distance(const QPoint &curr_position)
{
    return std::max(abs(curr_position.x() - end_row), abs(curr_position.y() - end_col));
}

void AlgorithmsGraph::set_begin(const PointCells &start_point, const PointCells &end_point, QVector<QVector<Cell>>& main_cells)
{
    last_shown_vertex = nullptr;
    start_row = start_point.get_row();
    start_col = start_point.get_col();

    end_row = end_point.get_row();
    end_col = end_point.get_col();
    status = RUN;
    this->cells = &main_cells;
    (*cells)[start_row][start_col].set_visited_status(true);
    (*cells)[start_row][start_col].repaint_cell(QColor(PINK));
    (*cells)[end_row][end_col].repaint_cell(QColor(PINK));

    (*cells)[start_row][start_col].set_mark(0);
    queue->push_in_queue(&(*cells)[start_row][start_col]);


}

AlgorithmsGraph::~AlgorithmsGraph()
{
    delete this->comparator;
    delete this->queue;
}
