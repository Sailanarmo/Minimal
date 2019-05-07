#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <QObject>
#include <QWidget>
#include <QSlider>
#include <iostream>

class Slider : public QSlider
{
    Q_OBJECT
public:
    Slider(QWidget *parent = nullptr);


    void updateValue(int value) { this->setValue(value);}
    int get() const { return this->value(); }

};

#endif // SLIDER_HPP
