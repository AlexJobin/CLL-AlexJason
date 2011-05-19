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
    void keyReleaseEvent(QKeyEvent *);
    void sltimerout();
    void sltimerout2();
    int randInt(int low, int high);
    void NoteRecu(QByteArray);
    void ViePerdue();
    void on_btnJouerLocal_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *m_timer;
    QTimer *m_timer2;
    QList<Notes*> m_ListeNotes;
    int m_VieLocal;
    int m_VieExterne;
    bool m_Debut;
    thEcoute *m_EcouteNote;
    bool m_Local;
    bool m_T1;
    bool m_T2;
    bool m_T3;
    bool m_T4;
    bool m_T5;



};


#endif // MAINWINDOW_H
