#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtWidgets>
#include <QMouseEvent>
#include<QTimer>
#include <chrono>
#include <thread>
#include <QVector>
#include "builder.h"
#include "AlgorithmGraph.h"

#include <string>
#define MAP_SIZE 20 //set 11 for custom map


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void          set_button_clicked() {is_start_button_clicked = true;};
    bool          is_button_clicked() const {return is_start_button_clicked;};
    const QTimer& get_timer() const {return timer;};
    ~MainWindow();

private slots:
    void on_start_alg_button_clicked();
    void make_step();
    void on_helpButton_clicked();

    void on_aboutbutton_clicked();

private:
    Ui::MainWindow*        ui;
    QGraphicsScene*        scene;
    const int              map_size = MAP_SIZE;
    QVector<QVector<Cell>> cells;
    Builder                builder;
    QTimer                 timer;
    AlgorithmsGraph        alg;
    PointCells             start_point;
    PointCells             end_point;

    const std::string      map[MAP_SIZE] = {"****#***~**",
                                            "****#***~**",
                                            "*~***~*~***",
                                            "*****~*****",
                                            "**~*****#**",
                                            "***~****#**",
                                            "****~***#**",
                                            "*~******#**",
                                            "***######**",
                                            "*#*~*~**~*~",
                                            "*~~*#***~**"};
    bool check_input_data();
    bool is_start_button_clicked = false;
    void reset_map(const Builder& builder);
    void set_button_colours();

};
#endif // MAINWINDOW_H
