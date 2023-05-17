#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Pineter.h"

class Pineter : public QMainWindow
{
    Q_OBJECT

public:
    Pineter(QWidget *parent = nullptr);
    ~Pineter();

private:
    Ui::PineterClass ui;
};
