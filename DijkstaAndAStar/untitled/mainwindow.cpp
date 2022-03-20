#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QMessageBox>
#include <QtWidgets>
#include "MyPrioQueue.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    this->setFixedSize(950, 660);
    this->setGeometry(this->pos().x() + 100, this->pos().y() + 30, 950, 660);
    for(int i = 0; i < map_size; i++)
    {
        cells.push_back(QVector<Cell>(map_size));
    }
    set_button_colours();
    this->setWindowTitle("Graph algorithms");
    this->setWindowIcon(QIcon(":/images/Pictures/graph.png"));

    //SET USER MAP OR GENERATE MAP BY PROGRAMM:
    try
    {
    builder.build_location(cells, scene, map_size); // you have to change MAP_SIZE in mainwindow.h also size_width in cell.h
    //builder.build_existing_map(map, cells, scene); //you can change it for self map.
    }
    catch(BuilderException& err)
    {
        QMessageBox::critical(this, "Bulder error.", QString(err.builder_what().c_str()));
        exit(-1);
    }

    //SET USER MAP OR GENERATE MAP BY PROGRAMM:

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_alg_button_clicked()
{

    if(is_button_clicked())
    {
        builder.set_map_size(map_size);
        reset_map(builder);
    }
    else
    {
        set_button_clicked();
    }

    if (check_input_data() == true)
    {
        if(ui->dijkstra_radio->isChecked())
        {
            alg.set_alg_type(DIJKSTRA);
        }
        else if(ui->a_star_radio->isChecked())
        {
            alg.set_print_status((builder.get_is_user_map()));
            alg.set_alg_type(ASTAR);
            alg.set_scene(scene);
        }

        connect(&timer, SIGNAL(timeout()), this, SLOT(make_step()));
        alg.set_map_size(map_size);
        alg.set_begin(start_point, end_point, cells);
        timer.start(7);

    }
}

void MainWindow::make_step()
{
    switch(alg.get_status())
    {
        case DONE:
        {
            disconnect(&timer, SIGNAL(timeout()), this, SLOT(make_step()));
            alg.show_the_way();
            ui->start_alg_button->setEnabled(true);
            timer.stop();
            return;
        }
        case WAY_ERROR:
        {
            QMessageBox::warning(this, "Impossible to make a way.", "Can`t create a way to your end point.");
            disconnect(&timer, SIGNAL(timeout()), this, SLOT(make_step()));
            timer.stop();
            ui->start_alg_button->setEnabled(true);
            return;
        }
        case RUN:
        {
            if(alg.get_alg_type() == DIJKSTRA)
            {
                alg.Dijkstra_step();
            }
            else if(alg.get_alg_type() == ASTAR)
            {
                alg.AStar_step();
            }

        }
    }



}

bool MainWindow::check_input_data()
{

    QString check_tmp;
    std::string str(std::to_string(map_size - 1));
    QString qstring(str.c_str());
    if(ui->x_start->text().length() == 0)
    {
        QMessageBox::critical(this, "X start value error.", "You have to input X start position (row number from 0 to " + qstring + ").");
        return false;
    }
    else if(ui->y_start->text().length() == 0)
    {
        QMessageBox::critical(this, "Y start value error.", "You have to input Y start position (column number from 0 to " + qstring + ").");
        return false;
    }
    else if(ui->x_end->text().length() == 0)
    {
        QMessageBox::critical(this, "X end value error.", "You have to input X end position (row number from 0 to " + qstring + ").");
        return false;
    }
    else if(ui->y_end->text().length() == 0)
    {
        QMessageBox::critical(this, "Y end value error.", "You have to input Y end position (column number from 0 to " + qstring + ").");
        return false;
    }

    check_tmp = ui->x_start->text();
    try
    {
        start_point.set_row(std::stoi(check_tmp.toStdString()));
        if(start_point.get_row() < 0 || start_point.get_row() > (map_size - 1))
        {
            QMessageBox::warning(this, "X start value out of range.", "Your value has to be in range from 0 to " + qstring + " (row number).");
            return false;
        }
    }  catch (std::invalid_argument e)
    {

        QMessageBox::warning(this, "X start value error.", "You have to input X start position (row number from 0 to " + qstring + ").");
        return false;
    }

    check_tmp = ui->y_start->text();
    try
    {
        start_point.set_col(std::stoi(check_tmp.toStdString()));
        if(start_point.get_col() < 0 || start_point.get_col() > (map_size - 1))
        {
            QMessageBox::warning(this, "Y start value out of range.", "Your value has to be in range from 0 to " + qstring + " (column number).");
            return false;
        }
    }  catch (std::invalid_argument e)
    {
        QMessageBox::warning(this, "Y start value error.", "You have to input Y start position (column number from 0 to " + qstring + ").");
        return false;
    }

    check_tmp = ui->x_end->text();
    try
    {
        end_point.set_row(std::stoi(check_tmp.toStdString()));
        if(end_point.get_row() < 0 || end_point.get_row() > (map_size - 1))
        {
            QMessageBox::warning(this, "X end value out of range.", "Your value has to be in range from 0 to " + qstring + " (row number).");
            return false;
        }
    }  catch (std::invalid_argument e)
    {
        QMessageBox::warning(this, "X end value error.", "You have to input X end position (row number from 0 to " + qstring + ").");
        return false;
    }

    check_tmp = ui->y_end->text();
    try
    {
        end_point.set_col(std::stoi(check_tmp.toStdString()));
        if(end_point.get_col() < 0 || end_point.get_col() > (map_size - 1))
        {
            QMessageBox::warning(this, "Y end value out of range.", "Your value has to be in range from 0 to " + qstring + " (column number).");
            return false;
        }
    }  catch (std::invalid_argument e)
    {
        QMessageBox::warning(this, "Y end value error.", "You have to input Y end position (column number from 0 to " + qstring + ").");
        return false;
    }

    if((start_point.get_col() == end_point.get_col()) && (start_point.get_row() == end_point.get_row()))//
    {
        QMessageBox::warning(this, "Start and end collision.", "Your start and end points are the same.");
        return false;
    }

    if(cells[start_point.get_row()][start_point.get_col()].is_wall())
    {
        QMessageBox::warning(this, "Start point is wall.", "You can`t start from wall.");
        return false;
    }
    if(cells[end_point.get_row()][end_point.get_col()].is_wall())
    {
        QMessageBox::warning(this, "End point is wall.", "You can`t end on wall.");
        return false;
    }
    if(!ui->dijkstra_radio->isChecked() && !ui->a_star_radio->isChecked())
    {
        QMessageBox::warning(this, "Choose alg error.", "You have to choose: Dijkstra alg or A* alg.");
        return false;
    }
    else if(ui->dijkstra_radio->isChecked())
    {
        ui->start_alg_button->setEnabled(false);

    }
    else if(ui->a_star_radio->isChecked())
    {
        ui->start_alg_button->setEnabled(false);
    }
    return true;
}

void MainWindow::set_button_colours()
{
    ui->helpButton->setStyleSheet("background-color: DarkCyan");
    ui->start_alg_button->setStyleSheet("background-color: DarkCyan");
    ui->aboutbutton->setStyleSheet("background-color: DarkCyan");
}

void MainWindow::reset_map(const Builder &builder)
{
    builder.remove_colors_and_cells_stats(cells);
}

void MainWindow::on_helpButton_clicked()
{
    QMessageBox::about(this, "Program rules.",
"<H2> <U>The object of the program</U>: </H2>"
"<H3> The object of the program is to show how \"find shortest way algorithms\" work."
" </H3> "
"<H2> <U>How to start:</U> </H2>"
"<H3><UL>"
"<LI>You have to choose start position cell and end position cell on the map and input their coordinates.</LI>"
"<LI>You have to chosen one algorithm: <U>Dijkstra</U> or <U>A*</U>.</LI>"
"<LI>After that you have to input the \"Start algorithm\" button."
"</LI></UL></H3>"
"<H2> <U>How to change map:</U> </H2>"
"<H3> 1. You can set your unique map using map double dimentional array in mainwindow.h (private zone). Also you have to uncomment builder method ( builder.build_existing_map(map, cells, scene);) in constructor of window in mainwindow.cpp. </H3>"
"<H3> 2. You can use generated by programm map. You just have to uncomment builder method (builder.build_location(cells, scene, map_size);) and comment previous method (in first point). After that you have to change MAP_SIZE in mainwindow.h and choose new cell size (size_width) in cell.h (for beautiful picture)."
"<H2> <U>MAP MENU:</U> </H2>"
"<H3><font color=\"green\"> Green</font> -- is grass. The easiest way to move. * on map.</H3>"
"<H3><font color=\"blue\"> Blue</font> -- is water. In water movement is slower. ~ on map.</H3>"
"<H3><font color=\"black\"> Black</font> -- is wall. You can`t move throw the wall. # on map.</H3>");
}

void MainWindow::on_aboutbutton_clicked()
{
    QMessageBox::information(this, " Student info.", "<H1><font face=\"times new roman\", size=\"6\"> The algorithm vizualization was done by Kulikov Paul, FIIT, MAI, 2022. </font> </H1>");
}
