#ifndef BRIDGE_H_INCLUDED
#define BRIDGE_H_INCLUDED

#include "Game.h"
#include "Paar.h"

class Board
{
    public:

    Board(int AnzG);
    ~Board();

    void insGame(int Nr, int pPNS, int pPOW, int pErgNS, int pErgOW);

    Game *Spiel;

    protected:
    private:

};

class BriPaare
{
    public:

    BriPaare(int Anz);
    ~BriPaare();

    void SetPaar(int Nummer, std::string Name);

    int Anz;

    Paar **Paare;

    protected:
    private:

};

class Bridge
{
    public:

    Bridge(int PAnz, int GAnz, int BAnz);
    ~Bridge();

    void insPlayer(int Nummerts, std::string Namets);
    void insGame(int BNr, int SNr, int pPNS, int pPOW, int pErgNS, int pErgOW);

    void Auswertung();

    protected:
    private:

    Board   **Boards;

    BriPaare *Paare;

    int AnzP;
    int AnzG;
    int AnzB;

    int MAXMP;
};


#endif /* BRIDGE_h_INCLUDED */
