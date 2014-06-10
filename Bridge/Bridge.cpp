#include "../headers.h"
#include "Bridge.h"

Board::Board(int AnzG){
    Spiel = new Game[AnzG];
}

Board::~Board(){
    delete[] Spiel;
}

void Board::insGame(int Nr, int pPNS, int pPOW, int pErgNS, int pErgOW){
    Spiel[Nr-1].setGame(&pPNS, &pPOW, &pErgNS, &pErgOW);
}


BriPaare::BriPaare(int Anz){
    Paare = new Paar*[Anz];
    this->Anz = Anz;
}

BriPaare::~BriPaare(){
    for (int i=0; i<Anz; i++)
        if (Paare[i])
            delete[] Paare[i];

    delete[] Paare;
}

void BriPaare::SetPaar(int Nummer, std::string Name){
    if (Paare[Nummer-1])
        delete Paare[Nummer-1]; //Speicherresistenz!!!
    else
        std::cout << "Zeiger wurde neu erstellt!" << std::endl;

    std::cout << "Setze Paar " << Nummer << " auf " << Name << std::endl;
    Paare[Nummer-1] = new Paar(Name, Nummer);
    int i = (int) *Paare;
    std::cout << i << std::endl;
}


Bridge::Bridge(int PAnz, int GAnz, int BAnz){

    std::cout << "Erzeuge " << PAnz << " Spieler." << std::endl;
    Paare = new BriPaare(PAnz);

    std::cout << "Erzeuge " << BAnz << " Boards." << std::endl;
    Boards = new Board*[BAnz];
    for (int i=0; i<BAnz; i++) Boards[i] = new Board(GAnz);

    AnzP = PAnz;
    AnzG = GAnz;
    AnzB = BAnz;

    MAXMP = (AnzG*2)-2;
}

Bridge::~Bridge(){
    delete(Paare);
    delete[] (Boards);
}

void Bridge::insPlayer(int Nummerts, std::string Namets){
    std::cout << "Setze Paar " << Nummerts << " auf " << Namets << std::endl;
    Paare->SetPaar(Nummerts, Namets);
}

void Bridge::insGame(int BNr, int SNr, int pPNS, int pPOW, int pErgNS, int pErgOW){
    Boards[BNr-1]->insGame(SNr, pPNS, pPOW, pErgNS, pErgOW);
}
