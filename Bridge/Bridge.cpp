#include "../headers.h"
#include "bridge.h"

Board::Board(int AnzG){
    Spiel = new Game[AnzG];
}

Board::~Board(){
    delete[] Spiel;
}

void Board::insGame(int Nr, int pPNS, int pPOW, int pErgNS, int pErgOW){
    Spiel[Nr-1].setGame(&pPNS, &pPOW, &pErgNS, &pErgOW);
}


Teamhelper::Teamhelper(int Anz){
    teams = new team*[Anz];
	for (int i=0; i<Anz; i++)
		teams[i] = 0;
    this->Anz = Anz;
}

Teamhelper::~Teamhelper(){
    for (int i=0; i<Anz; i++)
        if (teams[i])
            delete[] teams[i];

    delete teams;
}

void Teamhelper::Setteam(int Nummer, std::string Name){
	if (Nummer > Anz){
		std::cout << "Teamnumber out of bounds!" << std::endl;
		return;
	}

    if (teams[Nummer-1])
        delete teams[Nummer-1]; //Speicherresistenz!!! --> Bug
    else
        std::cout << "Zeiger wurde neu erstellt!" << std::endl;

    std::cout << "Setze team " << Nummer << " auf " << Name << std::endl;
    teams[Nummer-1] = new team(Name, Nummer);
}


Bridge::Bridge(int PAnz, int GAnz, int BAnz){

    std::cout << "Erzeuge " << PAnz << " Spieler." << std::endl;
    bTeams = new Teamhelper(PAnz);

    std::cout << "Erzeuge " << BAnz << " Boards." << std::endl;
    Boards = new Board*[BAnz];
    for (int i=0; i<BAnz; i++) Boards[i] = new Board(GAnz);

    AnzP = PAnz;
    AnzG = GAnz;
    AnzB = BAnz;

    MAXMP = (AnzG*2)-2;
}

Bridge::~Bridge(){
    delete(bTeams);
	for (int i=0; i<AnzB; i++)
		if (Boards[i])
			delete Boards[i];
    delete Boards;
}

void Bridge::insPlayer(int Nummerts, std::string Namets){
    std::cout << "Setze team " << Nummerts << " auf " << Namets << std::endl;
    bTeams->Setteam(Nummerts, Namets);
}

void Bridge::insGame(int BNr, int SNr, int pPNS, int pPOW, int pErgNS, int pErgOW){
    Boards[BNr-1]->insGame(SNr, pPNS, pPOW, pErgNS, pErgOW);
}
