#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Pineter.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "ip.h"

class Pineter : public QMainWindow
{
    Q_OBJECT

public:
    Pineter(QWidget *parent = nullptr);
    ~Pineter();

public slots:
    void openFile();
    void bhc();
    void bwc();

private:
    Ui::PineterClass ui;
    IP* ip;
    bool is_image_open_;
};
