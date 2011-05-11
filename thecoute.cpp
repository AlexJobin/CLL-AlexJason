#include "thecoute.h"

thEcoute::thEcoute()
{
    rate = false;
}

void thEcoute::run()
{
    QTcpSocket sockClient;
    QByteArray NoteRecu;

    sockClient.connectToHost("10.1.1.153", 0);
    if(sockClient.waitForConnected(100))
    {
        while(etat)
        {
            while (sockClient.waitForReadyRead(100))
            {
                NoteRecu.append(sockClient.read(sockClient.bytesAvailable()));
                emit (NouvelleNote(NoteRecu));
                NoteRecu.clear();
                sockClient.write("#");
                sockClient.waitForBytesWritten();
                if(rate)
                {
                    sockClient.write("V");
                    sockClient.waitForBytesWritten();
                    rate = false;
                }
            }
        }
    }
    sockClient.disconnectFromHost();
    sockClient.close();
}
