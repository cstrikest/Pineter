#include "Pineter.h"

Pineter::Pineter(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.action_Open, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui.bh, SIGNAL(click()), this, SLOT(bhc()));
}

Pineter::~Pineter()
{}

void Pineter::openFile()
{
    //QFileDialog dlg(this, "Open a Bitmap file.", "c:\\", "Bitmap Files (*.bmp)");
    QFileDialog dlg(this, Qt::Dialog);
    if (dlg.exec())
    {
        QString fileName = dlg.selectedFiles().first();
        ip = new IP(fileName.toStdString());

        ui.label->setText(QString::number(ip->image_->getArea()));
    }
}
