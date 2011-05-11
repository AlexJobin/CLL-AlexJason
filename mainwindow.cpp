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
#include "QSound"

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
    timer2 = new QTimer(this);
    timer2->setInterval(225);
    connect(timer2, SIGNAL(timeout()), this, SLOT(sltimerout2()));
    EcouteNote = new thEcoute();
    if(!connect(EcouteNote, SIGNAL(NouvelleNote(QByteArray)), this, SLOT(NoteRecu(QByteArray))))
        QMessageBox::information(this, "ERREUR", "CONNECT");
    timer->start();
    Local = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnChercherPartie_clicked()
{
   if(EcouteNote->etat == false)
   {
       EcouteNote->etat = true;
       EcouteNote->start();
       ui->txtEtat->setText("connexion ...");
       ui->btnChercherPartie->setVisible(false);
   }
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
            if(y+50 != 700)
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
                    QVariant v;
                    ListeNotes.removeAt(i);
                    if(VieLocal >=1)
                    {
                        VieLocal --;
                        v.setValue(VieLocal);
                        ui->txtVieLocal->setText(v.toString());
                        EcouteNote->rate = true;
                    }
                    else
                    ui->txtVieLocal->setText("0");

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
                if(y>= 550 && y<= 650)
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
                if(y>= 550 && y<= 650)
                {
                    qApp->beep();
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
                if(y>= 550 && y<= 650)
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
                if(y>= 550 && y<= 650)
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
                if(y>= 550 && y<= 650)
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

void MainWindow::NoteRecu(QByteArray n)
{
    QVariant v;
    QString s;
    int x;
    v.setValue(n);
    s = v.toString();
    if(s[0] != 'F' && s[0] != 'V')
    {
        x = v.toInt();
        if(x>=0 && x<=0)
        {
            ui->txtEtat->setText("Partie en cours");
            ListeNotes.append(new Notes(x));
        }
    }
    else
    {
        if(s[0] == 'F')
        {
           ui->txtVieLocal->setText("VICTOIRE");
           ui->txtVieExterne->setText("MORT");
           EcouteNote->etat =false;
           ui->btnChercherPartie->setVisible(false);
        }
        if(s[0] == 'V')
        {
            VieExterne --;
            v.setValue(VieExterne);
            ui->txtVieExterne->setText(v.toString());
        }
    }
}

void MainWindow::on_btnJouerLocal_clicked()
{
    ui->txtEtat->setText("non connecte");
    if(!Local)
    {
        timer2->start();
        Local = true;
        ui->btnChercherPartie->setVisible(false);
        ui->btnJouerLocal->setText("Jouer Reseau");
    }
    else
    {
        timer2->stop();
        ListeNotes.clear();
        Local = false;
        VieLocal =10;
        ui->txtVieLocal->setText("10");
        ui->btnJouerLocal->setText("Jouer Local");
        ui->btnChercherPartie->setVisible(true);
    }
}
void MainWindow::sltimerout2()
{
    ListeNotes.append(new Notes(randInt(1,5)));
}
