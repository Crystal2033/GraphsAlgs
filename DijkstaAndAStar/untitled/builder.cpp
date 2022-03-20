#include "builder.h"
#include <iostream>


void Builder::build_location(QVector<QVector<Cell>>& cells, QGraphicsScene* scene, const int map_size)
{
    is_user_map = false;
    this->map_size = map_size;
    srand(time(NULL));
    const int cell_size = cells[0][0].get_cell_size();
    QRectF position(10, 10, cell_size, cell_size);
    for (int i = 0; i < map_size; i++)
    {
        for (int j = 0; j < map_size; j++)
        {
            int random_counter = rand() % 100 + 1;
            if (random_counter <= 50)
            {
                cells[i][j].set_type(GRASS);
            }
            else if(random_counter > 50 && random_counter <= 80)
            {
                cells[i][j].set_type(WATER);
            }
            else if(random_counter > 80 && random_counter <= 100)
            {
                cells[i][j].set_type(WALL);
            }
            cells[i][j].set_position(QPoint(i, j));

            cells[i][j].paint_cell(scene, position);
            position.setRect(position.x() + cell_size, position.y(), cell_size, cell_size);
        }
        position.setRect(position.x() - cell_size * map_size, position.y() + cell_size, cell_size, cell_size);
    }
}

void Builder::build_existing_map(const std::string my_map[], QVector<QVector<Cell>>& cells, QGraphicsScene *scene)
{
    map_size = my_map->length();
    is_user_map = true;
    const int cell_size = cells[0][0].get_cell_size();
    QRectF position(10, 10, cell_size, cell_size);
    for (int i = 0; i < map_size; i++)
    {
        for (int j = 0; j < map_size; j++)
        {
            switch (my_map[i][j])
            {
                case '*':
                {
                    cells[i][j].set_type(GRASS);
                    break;
                }
                case '~':
                {
                    cells[i][j].set_type(WATER);
                    break;
                }
                case '#':
                {
                    cells[i][j].set_type(WALL);
                    break;
                }
                default:
                {
                    throw BuilderException("Map symbol error. Was found unpredictable symbol.", my_map[i][j]);
                }

            }
            cells[i][j].set_position(QPoint(i, j));

            cells[i][j].paint_cell(scene, position);
            position.setRect(position.x() + cell_size, position.y(), cell_size, cell_size);
        }
        position.setRect(position.x() - cell_size * map_size, position.y() + cell_size, cell_size, cell_size);
    }
}

void Builder::remove_colors_and_cells_stats(QVector<QVector<Cell>>& cells) const
{
    for (int i = 0; i < map_size; i++)
    {
        for (int j = 0; j < map_size; j++)
        {
            cells[i][j].get_back_type_color();
            cells[i][j].set_mark(100000);
            cells[i][j].set_visited_status(false);
            cells[i][j].set_new_min_cell_ptr(nullptr);
            cells[i][j].hide_text();
            cells[i][j].hide_picture();
            cells[i][j].reset_weight();
        }
    }
}

