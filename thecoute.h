#ifndef THECOUTE_H
#define THECOUTE_H
#include <QThread>
#include <QTcpSocket>

class thEcoute : public QThread
{
    Q_OBJECT

public:
    thEcoute();
    bool etat;
    bool rate;
protected:
    void run();
signals:
    void NouvelleNote(QByteArray);
    void Vie();
};

#endif // THECOUTE_H
