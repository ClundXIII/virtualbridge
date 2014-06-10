#include "../headers.h"
#include "bridge.h"
#include "team.h"
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
    team **tempteamArrayNS;
    team **tempteamArrayOW;
    bool fertig=false;
    team *tempteam;
    DynDurchSchnitt Durch;
    //int tempMPtoadd;

    tempteamArrayNS = new team*[AnzG];
    tempteamArrayOW = new team*[AnzG];
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
            cout << "    team " << tempPNS << " bekommt " << (tempErgNS - tempErgOW) << endl;
            cout << "    team " << tempPOW << " bekommt " << (tempErgOW - tempErgNS) << endl;
            bTeams->teams[tempPNS-1]->tempScore = (tempErgNS - tempErgOW);
            bTeams->teams[tempPOW-1]->tempScore = (tempErgOW - tempErgNS);
            tempteamArrayNS[tempArrayIndex] = bTeams->teams[tempPNS-1];
            tempteamArrayOW[tempArrayIndex] = bTeams->teams[tempPOW-1];
            tempArrayIndex++;
        }

        //Sortiere die teame


        fertig = false;

        while (!fertig){ //Bubblesort nach Score
            fertig = true;
            for (int i=0; i < (AnzG-1); i++)
            {
                if (tempteamArrayNS[i]->tempScore < tempteamArrayNS[i+1]->tempScore)
                {
                    cout << "team " << tempteamArrayNS[i]->GetName() << ", Nummer " << tempteamArrayNS[i]->GetNummer() << " hat weniger Score wie " << tempteamArrayNS[i+1]->GetName() << ", Nummer " << tempteamArrayNS[i+1]->GetNummer() << endl;
                    tempteam             = tempteamArrayNS[i];
                    tempteamArrayNS[i]   = tempteamArrayNS[i+1];
                    tempteamArrayNS[i+1] = tempteam;

                    tempteam             = tempteamArrayOW[i];
                    tempteamArrayOW[i]   = tempteamArrayOW[i+1];
                    tempteamArrayOW[i+1] = tempteam;
                    fertig = false;
                }
            }
        }

        for (int i=0; i<AnzG; i++) cout << tempteamArrayNS[i]->GetNummer() << ": " << tempteamArrayNS[i]->GetName() << ": " << tempteamArrayNS[i]->tempScore << endl;
        cout << "OW:" << endl;
        for (int i=0; i<AnzG; i++) cout << tempteamArrayOW[i]->GetNummer() << ": " << tempteamArrayOW[i]->GetName() << ": " << tempteamArrayOW[i]->tempScore << endl;
        //temporaerer Score ermittelt, ermittle PM:

        cout << "   scanne fuer MP ..." << endl;

        tempActMP = MAXMP;

        Durch.reset();

        for (int i=0; i<(AnzG-1); i++)
        {
            cout << "MP: " << tempActMP << ", team: " << tempteamArrayNS[i]->GetName() << endl;
            Durch.add(tempActMP);

            if (tempteamArrayNS[i]->tempScore != tempteamArrayNS[i+1]->tempScore)
            {
                for (int j=i; j > (i-Durch.GetGrad()); j--)
                {
                    tempteamArrayNS[j]->AddMP(Durch.GetDurchschnitt());
                    tempteamArrayOW[j]->AddMP(MAXMP-Durch.GetDurchschnitt());
                }
                Durch.reset();
            }

            tempActMP -= 2;
        }

        cout << "MP: " << tempActMP << ", team: " << tempteamArrayNS[AnzG-1]->GetName() << endl;
        Durch.add(tempActMP);

        for (int j=(AnzG-1); j > ((AnzG-1)-Durch.GetGrad()); j--)
            {
                tempteamArrayNS[j]->AddMP(Durch.GetDurchschnitt());
                tempteamArrayOW[j]->AddMP(MAXMP-Durch.GetDurchschnitt());
            }


    }

    //Berechne tatsächliche MP
    cout << "Werte nicht gespielte Boards aus ..." << endl;

    for (int i=0; i<AnzP; i++){//Berechne Prozente
        bTeams->teams[i]->Prozent = 100* (bTeams->teams[i]->GetMP() / (MAXMP*bTeams->teams[i]->GespielteBoards));}

    for (int i=0; i<AnzP; i++) cout << bTeams->teams[i]->GespielteBoards << " ";
    cout << endl;

    for (int i=0; i<AnzP; i++){
        cout << "team " << bTeams->teams[i]->GetName() \
        << " bekommt fuer " << (AnzB - (bTeams->teams[i]->GespielteBoards)) \
        << " ungespielte Boards den Durchschnitt " \
        << (AnzB - (bTeams->teams[i]->GespielteBoards)) * (bTeams->teams[i]->Prozent*MAXMP/100) \
        << " dazu!" << endl;

        bTeams->teams[i]->AddMP( (AnzB - (bTeams->teams[i]->GespielteBoards)) * (bTeams->teams[i]->Prozent*MAXMP/100) );
    }

    cout << endl << "Beginne mit Bubblesort ..." << endl << endl;

    fertig=false;
    //Beginne Mit Bubblesort

    while (!fertig){ //Bubblesort
        fertig = true;
        for (int i=0; i<(AnzP-1); i++)
        {
            if (bTeams->teams[i]->GetMP() < bTeams->teams[i+1]->GetMP())
            {
                tempteam           = bTeams->teams[i];
                bTeams->teams[i]   = bTeams->teams[i+1];
                bTeams->teams[i+1] = tempteam;
                fertig = false;
            }
        }
    }

    for (int i=0; i<AnzP; i++){ //Anzeigen der teame
        //Prozent berechnen
        //teame->teame[i]->Prozent = 100* (teame->teame[i]->GetMP() / (MAXMP*AnzB));

        cout << bTeams->teams[i]->GetNummer() << ": " << bTeams->teams[i]->GetName() << ": " << bTeams->teams[i]->GetMP() << " Prozent: " << bTeams->teams[i]->Prozent << endl;
    }

    cout << endl << endl << "Schoenere Ausgabe:" << endl;

    cout << "Plz  |Pnr|Name                |    MP |Prozent" << endl;
    cout << "----------------------------------------------" << endl;

    for (int i=0; i<AnzP; i++){
        cout << setw(5) << i+1 << "|" << setw(3) << bTeams->teams[i]->GetNummer() << "|" << setw(20) << bTeams->teams[i]->GetName() << "|" << setw(7) << bTeams->teams[i]->GetMP() << "|" << bTeams->teams[i]->Prozent << endl;
    }
    
    cout << endl << endl << "erzeuge HTML-Ausgabe ..." << endl;
    
    fstream html;
    
    html.open("Ergebnis.html", ios::out | ios::trunc);
    
    //Der Header
    html << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"><html><head><title>Bridge-Ergenbis</title></head><body>" << endl;    
    //die Tabelle (Anfang)
    html << "<table border=\"1\"><tr><th>Place</th><th>Teamnumber</th><th>Names</th><th>MP</th><th>Win-Percent</th></tr>" << endl;
        
    for (int i=0; i<AnzP; i++){
        html << "<tr>";
		//std::cout.precision(2);
        html << "<th>"<<i+1<<"</th><th>"<<bTeams->teams[i]->GetNummer()<<"</th><th>"<<bTeams->teams[i]->GetName()<<"</th><th>"<<bTeams->teams[i]->GetMP()<<"</th><th>"<<bTeams->teams[i]->Prozent<<"</th>"<<endl;
        html << "</tr>";
    }
    
    //die Tabelle (Schluss)
    html << "</table>";    
    //Abschluss
    html << "<P>VirtualBridge, (c) by Simon Michalke, 2012</P></body></html>" << endl;
    html.close();
    
}
