#include <iostream>
#include <string.h>
#include <fstream>
#include "allBridge.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "##############################\n# Bridge Analyse V 0.4 beta  #\n# (c) by Simon Michalke 3.12 #\n# C-Unterprogramm V. 0.2.1   #\n##############################\n";

    char cstring[30];
    fstream Dat_Boards, Dat_Paare;
    int Anz_B, Anz_G, Anz_P;

    Bridge *DAS_SPIEL;

    cout << "Oeffne Dateien ..." << endl;

    Dat_Boards.open("Boards.txt", ios::in);
    if (!Dat_Boards.good()) cout << "Fehler beim Oeffnen von Boards.txt!" << endl;
    else cout << "Boards.txt erfolgreich geoeffnet!" << endl;

    Dat_Paare.open("Paare.txt", ios::in);
    if (!Dat_Paare.good()) cout << "Fehler beim Oeffnen von Paare.txt!" << endl;
    else cout << "Paare.txt erfolgreich geoeffnet!" << endl;

    cout << "lese Spiel ein ..." << endl;

    Dat_Boards >> Anz_P;
    cout << Anz_P << " Spieler ..." << endl;

    Dat_Boards >> Anz_B;
    cout << Anz_B << " Boards ..." << endl;

    Dat_Boards >> Anz_G;
    cout << Anz_G << " Spiele pro Board ..." << endl;

    cout << "Erzeuge das Spiel ..." << endl;
    DAS_SPIEL = new Bridge(Anz_P, Anz_G, Anz_B);
    cout << endl << " ... fertig!" << endl;

    cout << "fange mit Einlesen an ..." << endl;

    cout << "Lese Paare ein:" << endl;

    char *z;
    int i;
    string tempString;
    
    for (int j=1; j<=Anz_P; j++)
        DAS_SPIEL->insPlayer(j, "Unbenannt");

    while (!Dat_Paare.eof())
    {
        Dat_Paare.getline(cstring, sizeof(cstring));
        z = cstring;
        cout << cstring << endl << "-> ";
        i = getintfc(&z);

        tempString.clear();
        tempString.append(z);

        cout << "Paar \"" << tempString << "\", Nr.: " << i << endl;

        DAS_SPIEL->insPlayer(i, tempString);
    }

    Dat_Paare.close();

    int BNr, SNr, pPNS, pPOW, pErgNS, pErgOW;

    Dat_Boards.getline(cstring, sizeof(cstring)); //HUHU? warum???

    while (!Dat_Boards.eof())
    {
        Dat_Boards.getline(cstring, sizeof(cstring));
        z = cstring;
        cout << cstring << endl << "-> ";

        BNr = getintfc(&z);
        SNr = getintfc(&z);
        pPNS = getintfc(&z);
        pErgNS = getintfc(&z);
        pPOW = getintfc(&z);
        pErgOW = getintfc(&z);

        cout << "BNr: " << BNr << " SNr: " << SNr << " PNS: " << pPNS << " ErgNS: " << pErgNS << " POW: " << pPOW << " ErgOW: " << pErgOW << endl;

        if ((pPNS<=Anz_P) && (pPOW<=Anz_P)){
            DAS_SPIEL->insGame(BNr, SNr, pPNS, pPOW, pErgNS, pErgOW);
        }
        else
        {
            cout << "Ergebnis ausgelassen! Paarnummer out of Range!" << endl;
        }
    }

    DAS_SPIEL->Auswertung(); ///yay

    cin.getline(cstring, sizeof(cstring));
    cout << "temporaere Daten werden freigegeben ..." << endl;
    delete(DAS_SPIEL);
    cout << endl << " ... fertig!" << endl;

    return 0;
}
