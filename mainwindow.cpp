#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notes.h"
#include <QVariant>
#include <notes.h>
#include <QDir>
#include <QTimer>
#include <QtGui>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <string>
#include <QVariant>
#include <QPainter>
#include <QRegion>
#include <QPaintEvent>
#include <QPen>
#include <QBrush>
#include "QKeyEvent"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(sltimerout()));
    timer->setInterval(10);
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnChercherPartie_clicked()
{
   ListeNotes.append(new Notes(1));
}

void MainWindow::paintEvent(QPaintEvent *)
 {
    for(int i = 0; i< ListeNotes.length();i++)
    {
        Notes *n = ListeNotes.at(i);
        QPainter Note(this);
        QBrush Brush(Qt::SolidPattern);
        int x = n->PosX;
        int y = n->PosY;
        Brush.setColor(Qt::white);
        Note.drawEllipse(x,y-5,x+50,y+45);
        if(n->Etat == false)
         {
            if(y+50 != 550)
            {
                switch(x)
                {
                    case 270: Brush.setColor(Qt::green); break;
                    case 335: Brush.setColor(Qt::red);break;
                    case 400: Brush.setColor(Qt::yellow);break;
                    case 465: Brush.setColor(Qt::blue);break;
                    case 530: Brush.setColor(Qt::darkYellow);break;
                };
                    Note.setBrush(Brush);
                    Note.drawEllipse(x,y,x+50,y+50);
            }
            else
                {
                    ListeNotes.removeAt(i);
                    //envoi raté
                }
         }
         else
         {
             ListeNotes.removeAt(i);
         }

    };
 }
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_1)
    {
        qApp->quit();
    }

}

void MainWindow::sltimerout()
{
    for(int i = 0; i< ListeNotes.length();i++)
    {
        Notes *n = ListeNotes.at(i);;
        n->PosY+=5;
    };
}
