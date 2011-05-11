#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>
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
#include <notes.h>
#include "thecoute.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnChercherPartie_clicked();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void sltimerout();
    void sltimerout2();
    int randInt(int low, int high);
    void NoteRecu(QByteArray);
    void on_btnJouerLocal_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *timer2;
    QList<Notes*> ListeNotes;
    int VieLocal;
    int VieExterne;
    thEcoute *EcouteNote;
    bool Local;

};


#endif // MAINWINDOW_H
