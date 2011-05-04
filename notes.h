#ifndef NOTES_H
#define NOTES_H

class Notes
{
    Q_OBJECT

public:
    Notes(int x);
    int PosX;
    int PosY;
    bool Etat;

};

Notes::Notes(int x)
{
    switch(x)
    {
    case 1: PosX = 270;break;
    case 2: PosX = 335;break;
    case 3: PosX = 400;break;
    case 4: PosX = 465;break;
    case 5: PosX = 530;break;
    };
    PosY = 80;
    Etat = false;
}

#endif // NOTES_H
