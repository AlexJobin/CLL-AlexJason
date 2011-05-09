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
    VieLocal=10;
    VieExterne=10;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(sltimerout()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnChercherPartie_clicked()
{
   ListeNotes.append(new Notes(randInt(1,5)));
}

void MainWindow::paintEvent(QPaintEvent *)
 {

    QPainter Note(this);
    QBrush Brush(Qt::SolidPattern);
    QPen Pen(Qt::SolidLine);


    for(int i = 0; i< ListeNotes.length();i++)
    {
        Notes *n = ListeNotes.at(i);
        int x = n->PosX;
        int y = n->PosY;
        Brush.setColor(Qt::black);
        Note.setBrush(Brush);
        Note.drawEllipse(x-5,y-5,60,60);

        if(n->Etat == false)
         {
            if(y+50 != 660)
            {
                switch(x)
                {
                    case 270: Brush.setColor(Qt::green); break;
                    case 335: Brush.setColor(Qt::red);break;
                    case 400: Brush.setColor(Qt::yellow);break;
                    case 465: Brush.setColor(Qt::blue);break;
                    case 530: Brush.setColor(Qt::darkMagenta);break;
                }
                    Note.setBrush(Brush);
                    Note.drawEllipse(x,y,50,50);
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

    QPainter Cercles(this);
    Pen.setWidth(4);
    Pen.setColor(Qt::green);
    Cercles.setPen(Pen);
    Cercles.drawEllipse(265,577,60,60);
    Pen.setColor(Qt::red);
    Cercles.setPen(Pen);
    Cercles.drawEllipse(330,577,60,60);
    Pen.setColor(Qt::yellow);
    Cercles.setPen(Pen);
    Cercles.drawEllipse(395,577,60,60);
    Pen.setColor(Qt::blue);
    Cercles.setPen(Pen);
    Cercles.drawEllipse(460,577,60,60);
    Pen.setColor(Qt::magenta);
    Cercles.setPen(Pen);
    Cercles.drawEllipse(525,577,60,60);

 }
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_1)
    {
        for(int i = 0; i< ListeNotes.length();i++)
        {
            Notes *n = ListeNotes.at(i);
            int x = n->PosX;
            int y = n->PosY;

            if(n->Etat == false && x == 270)
             {
                if(y>= 550)
                {
                    n->Etat=true;
                    repaint();
                }

             }

        };

    }
    if(event->key()==Qt::Key_2)
    {
        for(int i = 0; i< ListeNotes.length();i++)
        {
            Notes *n = ListeNotes.at(i);
            int x = n->PosX;
            int y = n->PosY;

            if(n->Etat == false && x == 335)
             {
                if(y>= 550)
                {
                    n->Etat=true;
                    repaint();
                }

             }

        };
    }
    if(event->key()==Qt::Key_3)
    {
        for(int i = 0; i< ListeNotes.length();i++)
        {
            Notes *n = ListeNotes.at(i);
            int x = n->PosX;
            int y = n->PosY;

            if(n->Etat == false && x == 400)
             {
                if(y>= 550)
                {
                    n->Etat=true;
                    repaint();
                }

             }

        };
    }
    if(event->key()==Qt::Key_4)
    {
        for(int i = 0; i< ListeNotes.length();i++)
        {
            Notes *n = ListeNotes.at(i);
            int x = n->PosX;
            int y = n->PosY;

            if(n->Etat == false && x == 465)
             {
                if(y>= 550)
                {
                    n->Etat=true;
                    repaint();
                }

             }

        };
    }
    if(event->key()==Qt::Key_5)
    {
        for(int i = 0; i< ListeNotes.length();i++)
        {
            Notes *n = ListeNotes.at(i);
            int x = n->PosX;
            int y = n->PosY;

            if(n->Etat == false && x == 530)
             {
                if(y>= 550)
                {
                    n->Etat=true;
                    repaint();
                }

             }

        };
    }

}

void MainWindow::sltimerout()
{


    for(int i = 0; i< ListeNotes.length();i++)
    {
        Notes *n = ListeNotes.at(i);;
        n->PosY+=5;
    };

    repaint();

}

int MainWindow::randInt(int low, int high)
    {
        return qrand() % ((high + 1) - low) + low;
    }
