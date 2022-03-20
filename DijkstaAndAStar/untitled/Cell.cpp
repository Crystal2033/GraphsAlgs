#include "Cell.h"

void Cell::reset_weight()
{
    switch (type)
    {
        case GRASS:
        {
            weight = 10;
            break;
        }
        case WATER:
        {
            weight = 20;
            break;
        }
        case WALL:
        {
            break;
        }
    }
}

void Cell::get_back_type_color()
{
    switch (type)
    {
        case GRASS:
        {
            rect->setBrush(QColor(100, 110, 47));
            break;
        }
        case WATER:
        {
            rect->setBrush(QColor(0, 150, 190));
            break;
        }
        case WALL:
        {
            rect->setBrush(QColor(20, 20, 20));
            break;
        }
    }
}

void Cell::show_text_nums(QGraphicsScene* scene)
{
    if(weight_text == nullptr)
    {
        weight_text   = new QGraphicsTextItem;
        eurystic_text = new QGraphicsTextItem;
        mark_text     = new QGraphicsTextItem;

        mark_text->setDefaultTextColor(QColor(DARK_RED));
        weight_text->setDefaultTextColor(QColor(FOREST_GREEN));
        eurystic_text->setDefaultTextColor(QColor(TURQUOISE));

        // y in function where y because x is a row (vertical move). Y - column (horizontal move)
        weight_text->setPos(  (size_width * 0.2) + (position.y() * size_width), (position.x() * size_width) + (size_width * 0.66) );
        eurystic_text->setPos((size_width * 0.7) + (position.y() * size_width), (position.x() * size_width) + (size_width * 0.66) );
        mark_text->setPos(    (size_width * 0.7) + (position.y() * size_width), (position.x() * size_width) + (size_width * 0.10) );

        scene->addItem(weight_text);
        scene->addItem(eurystic_text);
        scene->addItem(mark_text);
    }

    if(!weight_text->isVisible())
    {
        weight_text->show();
        eurystic_text->show();
        mark_text->show();
    }
    weight_text->setPlainText(QString(std::to_string(weight).c_str()));
    eurystic_text->setPlainText(QString(std::to_string(eurystic_num).c_str()));
    mark_text->setPlainText(QString(std::to_string(mark_num).c_str()));


    weight_text->update();
    eurystic_text->update();
    mark_text->update();

}

void Cell::hide_text()
{
    if(weight_text != nullptr)
    {
        weight_text->hide();
        mark_text->hide();
        eurystic_text->hide();
    }
}

Cell::Cell()
{
    weight_text   = nullptr;
    eurystic_text = nullptr;
    mark_text     = nullptr;
    pixmap_item   = nullptr;
    picture.load(":/images/Pictures/arrow.png");
}

void Cell::hide_picture()
{
    if(pixmap_item != nullptr)
    {
        pixmap_item->hide();
    }
}

void Cell::show_arrow_and_rotate(const int angle, QGraphicsScene *scene)
{
    if(pixmap_item == nullptr)
    {
        pixmap_item = scene->addPixmap(picture);
        pixmap_item->setScale(0.01);
        pixmap_item->setPos(size_width * position.y() + size_width / 2 + 10,  size_width * position.x() + size_width / 2 + 10);
    }
    else
    {
        pixmap_item->show();
    }
    pixmap_item->setRotation(angle);
}

void Cell::set_new_min_cell_ptr(Cell* const &prev_cell)
{
    min_cell_from = prev_cell;
}

void Cell::set_type(TYPES new_type)
{
    type = new_type;
    pen.setColor(Qt::black);
    pen.setWidth(1);

    switch (type)
    {
        case GRASS:
        {
            weight = 10;
            brush  = QBrush(QColor(100, 110, 47));
            break;
        }
        case WATER:
        {
            weight = 20;
            brush  = QBrush(QColor(0, 150, 190));
            break;
        }
        case WALL:
        {
            brush = QBrush(QColor(20, 20, 20));
            break;
        }
    }
}

void Cell::paint_cell(QGraphicsScene *scene, const QRectF& position)
{
    rect = scene->addRect(position.x(), position.y(), size_width, size_width, pen, brush);
}

void Cell::repaint_cell(const QColor& color)
{
    if((color == QColor(YELLOW) || color == QColor(INDIGO)) && rect->brush().color() == QColor(PINK))
    {
        return;
    }
    rect->setBrush(color);
    rect->update();
}

Cell::~Cell()
{
    if(weight_text != nullptr) //костыль, но у меня не создается объект QGraphicsTextItem без указателя
    {
        delete  weight_text;
        delete  eurystic_text;
        delete  mark_text;
    }
}

bool operator==(const Cell& left, const Cell& right)
{
    return left.get_mark() == right.get_mark();
}


