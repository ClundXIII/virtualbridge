#ifndef PAARE_H_INCLUDED
#define PAARE_H_INCLUDED

#include "../headers.h"

class Paar
{
    public:

    int GespielteBoards;
    float Prozent;
    int tempScore;

    Paar(std::string Namets, int Nummerts);
    ~Paar();

    void AddMP(float MPtoAdd);

    float GetMP();
    std::string GetName();
    int GetNummer();
    void SetName(std::string Namets);

    protected:
    private:

    int Nummer;

    float MP;

    std::string Name;
};


#endif /* PAARE_h_INCLUDED */
