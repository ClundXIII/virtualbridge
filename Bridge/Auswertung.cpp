#include "../headers.h"
#include "Bridge.h"
#include "Paar.h"
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

class DynDurchSchnitt
{
    public:

    DynDurchSchnitt(){reset();}

    void reset(){
        Grad = 0;
        Durchschnitt = 0;
    }

    void add(double NextZahl){
        Grad++;
        if (Grad == 0) Durchschnitt = NextZahl;
        else{
            cout << Durchschnitt << " + " << NextZahl << " -> ";
            Durchschnitt = (Durchschnitt*(Grad-1)+NextZahl)/Grad;
            cout << Durchschnitt << endl;
        }
    }

    float GetDurchschnitt(){return Durchschnitt;}

    int GetGrad(){return Grad;}

    protected:
    private:

    double Durchschnitt;

    int Grad;

};

void Bridge::Auswertung()
{
    cout << "Beginne mit der Auswertung ..." << endl;
    //temporäre Vars
    int tempPNS, tempPOW;
    int tempErgNS, tempErgOW;
    float tempActMP;
    Paar **tempPaarArrayNS;
    Paar **tempPaarArrayOW;
    bool fertig=false;
    Paar *tempPaar;
    DynDurchSchnitt Durch;
    //int tempMPtoadd;

    tempPaarArrayNS = new Paar*[AnzG];
    tempPaarArrayOW = new Paar*[AnzG];
    int tempScore[AnzG];
    int tempArrayIndex=0;

    for (int aktBNr=1; aktBNr <= AnzB; aktBNr++)
    {
        tempArrayIndex = 0;
        cout << "Board Numer " << aktBNr << endl;
        for (int i=0; i<AnzP; i++) tempScore[i]=0;
        cout << "   tempScore resettet!" << endl;
        cout << "   analysiere Spiele ..." << endl;
        for (int GNr=1; GNr<=AnzG; GNr++)
        {
            cout << "    analysiere Spiel " << GNr << " ..." << endl;
            Boards[aktBNr-1]->Spiel[GNr-1].getGame(&tempPNS, &tempPOW, &tempErgNS, &tempErgOW);
            cout << "    Paar " << tempPNS << " bekommt " << (tempErgNS - tempErgOW) << endl;
            cout << "    Paar " << tempPOW << " bekommt " << (tempErgOW - tempErgNS) << endl;
            Paare->Paare[tempPNS-1]->tempScore = (tempErgNS - tempErgOW);
            Paare->Paare[tempPOW-1]->tempScore = (tempErgOW - tempErgNS);
            tempPaarArrayNS[tempArrayIndex] = Paare->Paare[tempPNS-1];
            tempPaarArrayOW[tempArrayIndex] = Paare->Paare[tempPOW-1];
            tempArrayIndex++;
        }

        //Sortiere die Paare


        fertig = false;

        while (!fertig){ //Bubblesort nach Score
            fertig = true;
            for (int i=0; i < (AnzG-1); i++)
            {
                if (tempPaarArrayNS[i]->tempScore < tempPaarArrayNS[i+1]->tempScore)
                {
                    cout << "Paar " << tempPaarArrayNS[i]->GetName() << ", Nummer " << tempPaarArrayNS[i]->GetNummer() << " hat weniger Score wie " << tempPaarArrayNS[i+1]->GetName() << ", Nummer " << tempPaarArrayNS[i+1]->GetNummer() << endl;
                    tempPaar             = tempPaarArrayNS[i];
                    tempPaarArrayNS[i]   = tempPaarArrayNS[i+1];
                    tempPaarArrayNS[i+1] = tempPaar;

                    tempPaar             = tempPaarArrayOW[i];
                    tempPaarArrayOW[i]   = tempPaarArrayOW[i+1];
                    tempPaarArrayOW[i+1] = tempPaar;
                    fertig = false;
                }
            }
        }

        for (int i=0; i<AnzG; i++) cout << tempPaarArrayNS[i]->GetNummer() << ": " << tempPaarArrayNS[i]->GetName() << ": " << tempPaarArrayNS[i]->tempScore << endl;
        cout << "OW:" << endl;
        for (int i=0; i<AnzG; i++) cout << tempPaarArrayOW[i]->GetNummer() << ": " << tempPaarArrayOW[i]->GetName() << ": " << tempPaarArrayOW[i]->tempScore << endl;
        //temporaerer Score ermittelt, ermittle PM:

        cout << "   scanne fuer MP ..." << endl;

        tempActMP = MAXMP;

        Durch.reset();

        for (int i=0; i<(AnzG-1); i++)
        {
            cout << "MP: " << tempActMP << ", Paar: " << tempPaarArrayNS[i]->GetName() << endl;
            Durch.add(tempActMP);

            if (tempPaarArrayNS[i]->tempScore != tempPaarArrayNS[i+1]->tempScore)
            {
                for (int j=i; j > (i-Durch.GetGrad()); j--)
                {
                    tempPaarArrayNS[j]->AddMP(Durch.GetDurchschnitt());
                    tempPaarArrayOW[j]->AddMP(MAXMP-Durch.GetDurchschnitt());
                }
                Durch.reset();
            }

            tempActMP -= 2;
        }

        cout << "MP: " << tempActMP << ", Paar: " << tempPaarArrayNS[AnzG-1]->GetName() << endl;
        Durch.add(tempActMP);

        for (int j=(AnzG-1); j > ((AnzG-1)-Durch.GetGrad()); j--)
            {
                tempPaarArrayNS[j]->AddMP(Durch.GetDurchschnitt());
                tempPaarArrayOW[j]->AddMP(MAXMP-Durch.GetDurchschnitt());
            }


    }

    //Berechne tatsächliche MP
    cout << "Werte nicht gespielte Boards aus ..." << endl;

    for (int i=0; i<AnzP; i++){//Berechne Prozente
        Paare->Paare[i]->Prozent = 100* (Paare->Paare[i]->GetMP() / (MAXMP*Paare->Paare[i]->GespielteBoards));}

    for (int i=0; i<AnzP; i++) cout << Paare->Paare[i]->GespielteBoards << " ";
    cout << endl;

    for (int i=0; i<AnzP; i++){
        cout << "Paar " << Paare->Paare[i]->GetName() \
        << " bekommt fuer " << (AnzB - (Paare->Paare[i]->GespielteBoards)) \
        << " ungespielte Boards den Durchschnitt " \
        << (AnzB - (Paare->Paare[i]->GespielteBoards)) * (Paare->Paare[i]->Prozent*MAXMP/100) \
        << " dazu!" << endl;

        Paare->Paare[i]->AddMP( (AnzB - (Paare->Paare[i]->GespielteBoards)) * (Paare->Paare[i]->Prozent*MAXMP/100) );
    }

    cout << endl << "Beginne mit Bubblesort ..." << endl << endl;

    fertig=false;
    //Beginne Mit Bubblesort

    while (!fertig){ //Bubblesort
        fertig = true;
        for (int i=0; i<(AnzP-1); i++)
        {
            if (Paare->Paare[i]->GetMP() < Paare->Paare[i+1]->GetMP())
            {
                tempPaar          = Paare->Paare[i];
                Paare->Paare[i]   = Paare->Paare[i+1];
                Paare->Paare[i+1] = tempPaar;
                fertig = false;
            }
        }
    }

    for (int i=0; i<AnzP; i++){ //Anzeigen der Paare
        //Prozent berechnen
        //Paare->Paare[i]->Prozent = 100* (Paare->Paare[i]->GetMP() / (MAXMP*AnzB));

        cout << Paare->Paare[i]->GetNummer() << ": " << Paare->Paare[i]->GetName() << ": " << Paare->Paare[i]->GetMP() << " Prozent: " << Paare->Paare[i]->Prozent << endl;
    }

    cout << endl << endl << "Schoenere Ausgabe:" << endl;

    cout << "Plz  |Pnr|Name                |    MP |Prozent" << endl;
    cout << "----------------------------------------------" << endl;

    for (int i=0; i<AnzP; i++){
        cout << setw(5) << i+1 << "|" << setw(3) << Paare->Paare[i]->GetNummer() << "|" << setw(20) << Paare->Paare[i]->GetName() << "|" << setw(7) << Paare->Paare[i]->GetMP() << "|" << Paare->Paare[i]->Prozent << endl;
    }
    
    cout << endl << endl << "erzeuge HTML-Ausgabe ..." << endl;
    
    fstream html;
    
    html.open("Ergebnis.html", ios::out | ios::trunc);
    
    //Der Header
    html << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"><html><head><title>Bridge-Ergenbis</title></head><body>" << endl;    
    //die Tabelle (Anfang)
    html << "<table border=\"1\"><tr><th>Platzierung</th><th>Paarnummer</th><th>Name</th><th>MP</th><th>Prozent</th></tr>" << endl;
        
    for (int i=0; i<AnzP; i++){
        html << "<tr>";
        html << "<th>"<<i+1<<"</th><th>"<<Paare->Paare[i]->GetNummer()<<"</th><th>"<<Paare->Paare[i]->GetName()<<"</th><th>"<<Paare->Paare[i]->GetMP()<<"</th><th>"<<Paare->Paare[i]->Prozent<<"</th>"<<endl;
        html << "</tr>";
    }
    
    //die Tabelle (Schluss)
    html << "</table>";    
    //Abschluss
    html << "<P>VirtualBridge, (c) by Simon Michalke, 2012</P></body></html>" << endl;
    html.close();
    
}
