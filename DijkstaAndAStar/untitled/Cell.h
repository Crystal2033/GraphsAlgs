#pragma once
#ifndef CELL_H
#define CELL_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QColor>
#include <QtGui>
#include <QtCore>
#include <QBrush>
#define YELLOW 255, 215, 0
#define GOLD 255, 215, 0
#define PINK 219, 112, 147
#define INDIGO 75, 0, 130
#define DARK_RED 200, 0, 0
#define FOREST_GREEN 34, 139, 34
#define TURQUOISE 0, 206, 209


class PointCells
{
private:
    int row;
    int col;
public:
    PointCells() = default;
    int get_row() const {return row;};
    int get_col() const {return col;};

    void set_row(const int new_row){row = new_row;};
    void set_col(const int new_col){col = new_col;};

};


enum TYPES{GRASS, WATER, WALL}; //50%, 30%, 20%
class Cell
{
private:
    QGraphicsRectItem*   rect;
    QGraphicsPixmapItem* pixmap_item;
    QPixmap              picture;

    QPoint               position;
    int                  weight = 0;
    int                  mark_num = 100000;
    int                  eurystic_num;
    QGraphicsTextItem*   weight_text;
    QGraphicsTextItem*   mark_text;
    QGraphicsTextItem*   eurystic_text;
    bool                 visited = false;
    int                  size_width = 30; //mapsize-cellsize: 10-60, 100-6, 50-12, 11-54
    TYPES                type;
    QBrush               brush;
    QPen                 pen;

    Cell*                min_cell_from = nullptr; //from which cell got the shortest way.

public:
    Cell();
    void reset_weight();
    void set_mark(const int new_mark){mark_num = new_mark;};
    int  get_mark() const {return mark_num;};
    void set_weight(const int new_weight) {weight = new_weight;};
    void set_eurystic_num(const int new_num) {eurystic_num = new_num;};
    void get_back_type_color();
    int  get_eurystic_num() const {return eurystic_num;};
    void show_text_nums(QGraphicsScene* scene);
    void hide_text();


    void hide_picture();
    void show_arrow_and_rotate(const int angle, QGraphicsScene* scene);


    void         set_visited_status(const bool status){visited = status;};
    void         set_new_min_cell_ptr(Cell* const& prev_cell);
    Cell* const& get_vertex_min_ptr() {return min_cell_from;};
    int          get_cell_size() const {return size_width;};
    void         set_type(TYPES new_type);
    void         set_position(const QPoint pos){position = pos;};
    void         paint_cell(QGraphicsScene* scene, const QRectF& position);
    void         repaint_cell(const QColor& color);
    int          get_weight() {return weight;}
    bool         is_visited () {return visited;}
    bool         is_wall(){return (type == WALL) ? true : false;}
    QColor       get_color_brush() const {return brush.color();};
    QPoint       get_position() const {return position;};
   friend bool   operator==(const Cell& left, const Cell& right);

    ~Cell();
};


#endif // CELL_H
