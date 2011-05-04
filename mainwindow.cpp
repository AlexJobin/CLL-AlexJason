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
    Notes un = new Notes(1);
    ListeNotes.append(un);

}

void MainWindow::paintEvent(QPaintEvent *)
 {
    foreach (Notes, ListeNotes)
    {
    QPainter Note(this);
    QBrush Brush(Qt::SolidPattern);
    Brush.setColor(Qt::green);
    Note.setBrush(Brush);
    Note.drawEllipse(255,80,50,50);
    };
 }

void MainWindow::sltimerout()
{

}
