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
    QVariant v;

    sockClient.connectToHost("10.1.1.154", 65124);
    if(sockClient.waitForConnected(1000))
        while(etat)
         {
             while (sockClient.waitForReadyRead(100))
             NoteRecu.append(sockClient.read(sockClient.bytesAvailable()));
                if(NoteRecu.length() >1)
                    NoteRecu.remove(0,1);
                v.setValue(NoteRecu);
                if(v.toInt() >=1 && v.toInt() <=5)
                {
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
                if(v.toString() == "V")
                {
                    emit (Vie());
                }
            }
    sockClient.disconnectFromHost();
    sockClient.close();

}
