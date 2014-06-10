#ifndef teamE_H_INCLUDED
#define teamE_H_INCLUDED

#include "../headers.h"

class team
{
    public:

    int GespielteBoards;
    float Prozent;
    int tempScore;

    team(std::string Namets, int Nummerts);
    ~team();

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


#endif /* teamE_h_INCLUDED */
