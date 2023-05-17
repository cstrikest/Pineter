#include "Pineter.h"
//https://subingwen.cn/qt/qt-signal-slot/
//https://www.xinbaoku.com/archive/8yc8sMF5.html
//https://www.w3cschool.cn/learnroadqt/edlr1j3y.html
//https://wizardforcel.gitbooks.io/qt-beginning/content/5.html
//https://qtguide.ustclug.org/
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
