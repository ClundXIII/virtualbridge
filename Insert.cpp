#include "allBridge.h"
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{

    int i=0, j=0;
	fstream Dat_teame;
	fstream Dat_Erg;
    string Eingabe;
    int AnzP;
    int AnzG;
    Board *tempB;

    if (argc>1) //Parameter
    {
        if (argv[1][0] == '-')
        {
            if (argv[1][1] == 'a')
            {
                if (argv[1][2] == 'p')
                {
                    cout << "Bitte teamnummer eingeben:" << endl;
                    Dat_teame.open("teame.txt", ios::out | ios::app);
                    cout << "Nr.: ";
                    cin >> i;
                    cout << "Bitte Namen eingeben:" << endl;
                    cin >> Eingabe;
                    Dat_teame << endl << i << " " << Eingabe << " ";
                    return 0;
                }
                if (argv[1][2] == 'b')
                {
                    Dat_Erg.open("Boards.txt", ios::out | ios::app);
                    cout << "Board-Nr?: ";
                    cin >> i;
                    Dat_Erg << endl << i << " ";

				    cout << "Runden-Nr? ";
				    cin >> i;
				    Dat_Erg << i << " ";

				    cout << "teamNummer N/S : ";
				    cin >> i;
				    Dat_Erg << i << " ";

                    cout << "Ergebnis N/S   : ";
				    cin >> i;
				    Dat_Erg << i << " ";

                    cout << "teamnummer O/W : ";
				    cin >> i;
				    Dat_Erg << i << " ";

                    cout << "Ergebnis O/W   : ";
				    cin >> i;
				    Dat_Erg << i << " ";

				    return 0;
                }
            }
            /*else
            {
                cout << "Unbekannter Parameter: \"" << argv[1][1] << "\"!" << endl;
            }*/
        }

        if (argv[1][1] == 'p' && argv[1][2] == 'e')
        {
            cout << endl << "Eingabe der teame! \nEigabe mit 'END' beenden!" << endl;
            cout << "Bitte Keine Leerzeichen!" << endl;
			Dat_teame.open("teame.txt", ios::out | ios::trunc);


            i++;
            cout << "Nr. " << i << ": "; cin >> Eingabe;
            if ( Eingabe != "END") Dat_teame << i << " " << Eingabe << " ";

			while ( Eingabe != "END")
			{
				i++;
				cout << "Nr. " << i << ": "; cin >> Eingabe;
				if ( Eingabe != "END") Dat_teame << endl << i << " " << Eingabe << " ";
			}


			Dat_teame.close();
			return 0;
        }
    }

    cout << "##############################\n# Bridge Analyse V 0.4 beta  #\n# (c) by Simon Michalke 3.12 #\n# C-Unterprogramm V. 0.2.1   #\n##############################\n";
    int einasdf;
    //cout << endl << "Was wollen sie tun?" << endl;
    //cout << "1: teame eingeben" << endl;
    //cout << "2: Ergebnisse eingeben" << endl;
    //cout << ">";
    //cin >> einasdf;

    einasdf = 2;

    switch (einasdf)
    {
     case 1:

		//try
		//{
			cout << endl << "Eingabe der teame! \nEigabe mit 'END' beenden!" << endl;

			Dat_teame.open("teame.txt", ios::out | ios::trunc);


            i++;
            cout << "Nr. " << i << ": "; cin >> Eingabe;
            if ( Eingabe != "END") Dat_teame << i << " " << Eingabe << " ";

			while ( Eingabe != "END")
			{
				i++;
				cout << "Nr. " << i << ": "; cin >> Eingabe;
				if ( Eingabe != "END") Dat_teame << endl << i << " " << Eingabe << " ";
			}


			Dat_teame.close();
		//}

		//catch (1)
		//{cout << "Fehler wurde festgestellt" << endl;}

		break;

     case 2:

		//try
		//{
			cout << endl << "Eingabe der Boards!" << endl;

			Dat_Erg.open("Boards.txt", ios::out | ios::trunc);

			Eingabe = "asdf";

			cout << "Wieviele teame? ";
			cin >> AnzP;
            Dat_Erg << AnzP << endl;

			cout << "Wieviele Runden?";
			cin >> i;
			cout << "Boards pro Runde? ";
			cin >> j;

			i*=j;

            Dat_Erg << i << endl;
            tempB = new Board(i);

            int Runden;
            if (AnzP%2) Runden = (AnzP-1)/2;
            else        Runden = AnzP/2;
			AnzG = Runden;
            cout << Runden << " Runden!" << endl;
			Dat_Erg << Runden;

			int Nr;
			int PNS, POW, ErgNS, ErgOW;


			while ( Nr != 0)
			{
			    cout << endl << "Geben Sie Boardnummer 0 zum Beenden ein!" << endl << endl;
				cout << "Boardnummer    : ";
				cin >> Nr;

				for (int i=1; ( i <= Runden ) && ( Nr != 0 ) ; i++)
				{
				    cout << endl << "        Runde " << i << " !" << endl;
				    cout << "teamNummer N/S : ";
                    cin >> PNS;
                    cout << "Ergebnis N/S   : ";
                    cin >> ErgNS;
                    cout << "teamnummer O/W : ";
                    cin >> POW;
                    cout << "Ergebnis O/W   : ";
                    cin >> ErgOW;
                    cout << endl << "Nr.: " << Nr << " PNS: " << PNS << " ErgNS: " << ErgNS << " POW: " << POW << " ErgOW: " << ErgOW << endl << endl ;
                    if ( ( ErgNS > 0 ) && ( ErgOW > 0) )
                    {
                        cout << "Falsche Eingabe! Nur ein team bekommt Punkte! Nochmal bitte!" << endl;
                        i--;
                    }
                    else if ( ( ErgNS <= 0 ) && ( ErgOW <= 0) )
                    {
                        cout << "....!?" << endl << "irgendwer hat doch gewonnen, oder?" << endl;
                        i--;
                    }
                    else if ( (PNS>AnzP) && (POW>AnzP) )
                    {
                        cout << "soviel teame gibt es nicht! Bitte Widerholen!" << endl;
                        i--;
                    }
                    else
                    {
                        tempB->insGame(i, PNS, POW, ErgNS, ErgOW);
                        Dat_Erg  << endl << Nr << " " << i << " " << PNS << " " << ErgNS << " " << POW << " " << ErgOW << " ";
                    }

				}

            }

			Dat_Erg.close();
		//}
		//catch () {cout << "Fehler wurde festgestellt" << endl;}
    }
}
