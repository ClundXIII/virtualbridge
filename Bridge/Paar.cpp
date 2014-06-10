#include "Paar.h"
//#include <iostream>
//#include <string.h>

using namespace std;

Paar::Paar(string Namets, int Nummerts)
{
    std::cout << "Setze Paar " << Nummerts << " auf " << Namets << std::endl;
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

void Paar::AddMP(float MPtoAdd)
{
    std::cout << "Paar " << Name << ", Nummer " << Nummer << " bekommt " << MPtoAdd << " zu " << MP << " dazu" << endl;
    MP += MPtoAdd;
    GespielteBoards++;
};

float Paar::GetMP(){return MP;}
std::string Paar::GetName(){return Name;}
int Paar::GetNummer(){return Nummer;}
void Paar::SetName(std::string Namets){Name = Namets;}

Paar::~Paar()
{
    std::cout << "Paar Nummer " << Nummer << " mit Namen " << Name << "geloescht!" << endl;
};

