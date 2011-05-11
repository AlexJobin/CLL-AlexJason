#include "thecoute.h"

thEcoute::thEcoute()
{
    rate = false;
    etat = false;
}

void thEcoute::run()
{
    QTcpSocket sockClient;
    QByteArray NoteRecu;

    sockClient.connectToHost("10.1.1.154", 65124);
    if(sockClient.waitForConnected(1000))
        while(etat)
         {
             while (sockClient.waitForReadyRead(100))
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
    sockClient.disconnectFromHost();
    sockClient.close();

}
