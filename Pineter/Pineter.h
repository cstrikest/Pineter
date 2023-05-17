#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Pineter.h"
#include <qfiledialog.h>

#include "ip.h"

class Pineter : public QMainWindow
{
    Q_OBJECT

public:
    Pineter(QWidget *parent = nullptr);
    ~Pineter();

public slots:
    void openFile();

private:
    Ui::PineterClass ui;
    IP* ip;
};
