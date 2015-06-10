#include <iostream>
#include "Calendar.h"
#include "timing.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}


/* Question 3 :
    on ne peut pas allouer un tableau de taches car new ne permet pas l'appel de constructeur avec arguments
    -> on peut cependant allour un tableau de pointeurs de taches initialisés par une boucle (Tache **)
*/
