#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    uiSlider(*ui->horizontalSlider),
    controller(uiSlider)
{
    ui->setupUi(this);

    QSlider *slider0 = new QSlider;
    QSlider &deref0 = *slider0;
    deref0.setValue(10);
    std::cout << deref0.value() << std::endl;

    Slider *slider1 = new Slider;
    Slider &deref1 = *slider1;
    deref1.setValue(20);
    std::cout << deref1.value() << std::endl;

    // This does not break
    Slider &deref2 = *ui->horizontalSlider;
    deref2.setValue(30);
    std::cout << deref2.value() << std::endl;


    // uiSlider.setValue(20); <- This breaks
    // controller.setValues(20); <- This also breaks


    //This also does not break
    Controller<Slider> cont = Controller(*ui->horizontalSlider);
    cont.setValues(50);
    std::cout << ui->horizontalSlider->value() << std::endl;


}

MainWindow::~MainWindow()
{
    delete ui;
}
