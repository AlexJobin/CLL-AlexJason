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
    m_VieLocal=25;
    m_VieExterne=25;
    m_timer = new QTimer(this);
    m_timer->setInterval(10);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(sltimerout()));
    m_timer2 = new QTimer(this);
    m_timer2->setInterval(225);
    connect(m_timer2, SIGNAL(timeout()), this, SLOT(sltimerout2()));
    m_EcouteNote = new thEcoute();
    connect(m_EcouteNote, SIGNAL(Vie(int)), this, SLOT(ViePerdue(int)));
    if(!connect(m_EcouteNote, SIGNAL(NouvelleNote(QByteArray)), this, SLOT(NoteRecu(QByteArray))))
        QMessageBox::information(this, "ERREUR", "CONNECT");
    m_timer->start();
    m_Local = false;
    m_Debut = true;
    m_T1 = false;
    m_T2 = false;
    m_T3 = false;
    m_T4 = false;
    m_T5 = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnChercherPartie_clicked()
{
   if(m_EcouteNote->etat == false)
   {
       m_EcouteNote->etat = true;
       m_EcouteNote->start();
       ui->txtEtat->setText("connexion ...");
       ui->btnChercherPartie->setVisible(false);
   }
}

void MainWindow::paintEvent(QPaintEvent *)
 {

    QPainter Note(this);
    QBrush Brush(Qt::SolidPattern);
    QPen Pen(Qt::SolidLine);
    if(m_EcouteNote->isRunning() && m_ListeNotes.isEmpty() && m_VieLocal != 0 &&  !m_Debut)
                ui->txtEtat->setText("VICTOIRE");

    for(int i = 0; i< m_ListeNotes.length();i++)
    {
        Notes *n = m_ListeNotes.at(i);
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
                    m_ListeNotes.removeAt(i);
                    if(m_VieLocal >=1)
                    {
                        m_VieLocal --;
                        v.setValue(m_VieLocal);
                        ui->txtVieLocal->setText(v.toString());
                        m_EcouteNote->rate = true;
                    }
                    else
                    {
                        m_EcouteNote->etat = false;
                        ui->txtVieLocal->setText("0");
                        ui->txtEtat->setText("PERDUE");
                    }

                }
         }
         else
         {

             m_ListeNotes.removeAt(i);
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

    if(m_T1)
    {
       Pen.setColor(Qt::green);
       Cercles.setPen(Pen);
       Brush.setColor(Qt::green);
       Cercles.setBrush(Brush);
       Cercles.drawEllipse(265,577,60,60);
    }

    if(m_T2)
    {
        Pen.setColor(Qt::red);
        Cercles.setPen(Pen);
        Brush.setColor(Qt::red);
        Cercles.setBrush(Brush);
        Cercles.drawEllipse(330,577,60,60);
    }
    if(m_T3)
    {
        Pen.setColor(Qt::yellow);
        Cercles.setPen(Pen);
        Brush.setColor(Qt::yellow);
        Cercles.setBrush(Brush);
        Cercles.drawEllipse(395,577,60,60);
    }
    if(m_T4)
    {
        Pen.setColor(Qt::blue);
        Cercles.setPen(Pen);
        Brush.setColor(Qt::blue);
        Cercles.setBrush(Brush);
        Cercles.drawEllipse(460,577,60,60);
    }
    if(m_T5)
    {
        Pen.setColor(Qt::magenta);
        Cercles.setPen(Pen);
        Brush.setColor(Qt::magenta);
        Cercles.setBrush(Brush);
        Cercles.drawEllipse(525,577,60,60);
    }
 }
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_1)
    {
        m_T1 = true;
        for(int i = 0; i< m_ListeNotes.length();i++)
        {
            Notes *n = m_ListeNotes.at(i);
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
         m_T2 = true;
        for(int i = 0; i< m_ListeNotes.length();i++)
        {
            Notes *n = m_ListeNotes.at(i);
            int x = n->PosX;
            int y = n->PosY;

            if(n->Etat == false && x == 335)
             {
                if(y>= 550 && y<= 650)
                {
                    //qApp->beep();
                    n->Etat=true;

                    repaint();
                }

             }

        };
    }
    if(event->key()==Qt::Key_3)
    {
         m_T3 = true;
        for(int i = 0; i< m_ListeNotes.length();i++)
        {
            Notes *n = m_ListeNotes.at(i);
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
         m_T4 = true;
        for(int i = 0; i< m_ListeNotes.length();i++)
        {
            Notes *n = m_ListeNotes.at(i);
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
         m_T5 = true;
        for(int i = 0; i< m_ListeNotes.length();i++)
        {
            Notes *n = m_ListeNotes.at(i);
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

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_1)
      m_T1 = false;
    if(event->key()==Qt::Key_2)
      m_T2 = false;
    if(event->key()==Qt::Key_3)
      m_T3 = false;
    if(event->key()==Qt::Key_4)
      m_T4 = false;
    if(event->key()==Qt::Key_5)
      m_T5 = false;

    repaint();
}

void MainWindow::sltimerout()
{

    for(int i = 0; i< m_ListeNotes.length();i++)
    {
        Notes *n = m_ListeNotes.at(i);;
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
    m_Debut =false;
    if(s[0] != 'F' && s[0] != 'V')
    {
        x = v.toInt();
        if(x>=1 && x<=5)
        {
            ui->txtEtat->setText("Partie en cours");
            m_ListeNotes.append(new Notes(x));
        }
        if(x>5 && x<10)
        switch(x)
        {
            case 6:
                m_ListeNotes.append(new Notes(1));
                m_ListeNotes.append(new Notes(2));
                break;
            case 7:
                m_ListeNotes.append(new Notes(2));
                m_ListeNotes.append(new Notes(5));
                break;
            case 9:
                m_ListeNotes.append(new Notes(2));
                m_ListeNotes.append(new Notes(3));
                m_ListeNotes.append(new Notes(4));
                break;
        }
    }
    else
    {
        if(s[0] == 'F')
        {
           ui->txtVieLocal->setText("VICTOIRE");
           m_EcouteNote->etat =false;
           ui->btnChercherPartie->setVisible(false);
        }
        if(s[0] == 'V')
        {
            m_VieExterne --;
            v.setValue(m_VieExterne);
        }
    }
}

void MainWindow::on_btnJouerLocal_clicked()
{
    ui->txtEtat->setText("non connecte");
    if(!m_Local)
    {
        m_timer2->start();
        m_Local = true;
        ui->btnChercherPartie->setVisible(false);
        ui->btnJouerLocal->setText("Jouer Reseau");
    }
    else
    {
        m_timer2->stop();
        m_ListeNotes.clear();
        m_Local = false;
        m_VieLocal =25;
        ui->txtVieLocal->setText("25");
        ui->btnJouerLocal->setText("Jouer Local");
        ui->btnChercherPartie->setVisible(true);
    }
}
void MainWindow::sltimerout2()
{
    int x = randInt(1,12);
    if(x>=0 && x<=5)
    m_ListeNotes.append(new Notes(x));
    else
    switch(x)
    {
        case 6:
            m_ListeNotes.append(new Notes(1));
            m_ListeNotes.append(new Notes(2));
            break;
        case 7:
            m_ListeNotes.append(new Notes(2));
            m_ListeNotes.append(new Notes(5));
            break;
        case 8:
            m_ListeNotes.append(new Notes(2));
            m_ListeNotes.append(new Notes(3));
            break;
        case 9:
            m_ListeNotes.append(new Notes(2));
            m_ListeNotes.append(new Notes(3));
            m_ListeNotes.append(new Notes(4));
            break;
    }
}
void MainWindow::ViePerdue()
{
    QVariant v;
    m_VieExterne --;
    v.setValue(m_VieExterne);
}
