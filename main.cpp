#include <iostream>
#include "fonctionsSyntaxique.h"
using namespace std;
char c =lireCar();
int main()
{
    remplirTableMotsClesHachee();
    motCourant=uniteSuivanteSansCommentaire(c);
    programme();
    afficherTS();
    for(int i=0;i<tableDeSymboles.size();i++)
    {
        delete tableDeSymboles[i];
    }
    return 0;
}
