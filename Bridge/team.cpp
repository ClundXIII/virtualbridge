#include "team.h"
//#include <iostream>
//#include <string.h>

using namespace std;

team::team(string Namets, int Nummerts)
{
    std::cout << "Setze team " << Nummerts << " auf " << Namets << std::endl;
    if (Namets != ""){
        Name = Namets;
    }
    else{
        cout << "Error: kein Name, bzw. leerer String angegeben!" << endl;
    }
    if (Nummerts != 0){
        Nummer = Nummerts;
    }
    else{
        cout << "keine Nummer (oder 0) angegeben! return Error;" << endl;
        throw 1;
    }

    MP = 0;
    Prozent = 0;
    GespielteBoards = 0;
};

void team::AddMP(float MPtoAdd)
{
    std::cout << "team " << Name << ", Nummer " << Nummer << " bekommt " << MPtoAdd << " zu " << MP << " dazu" << endl;
    MP += MPtoAdd;
    GespielteBoards++;
};

float team::GetMP(){return MP;}
std::string team::GetName(){return Name;}
int team::GetNummer(){return Nummer;}
void team::SetName(std::string Namets){Name = Namets;}

team::~team()
{
    std::cout << "team Nummer " << Nummer << " mit Namen " << Name << "geloescht!" << endl;
};

