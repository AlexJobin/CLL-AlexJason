#ifndef NOTES_H
#define NOTES_H

class Notes
{
    Q_OBJECT

public:
    explicit Notes(QWidget *parent = 0);
    ~Notes();
    Notes(int x);
    int PosX;
    int PosY;
    bool Etat;
};


#endif // NOTES_H
