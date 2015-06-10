#include "fonction.h"



void MATH::fonction::setfonction(int n, int d){
    if(d==0){
        throw FractionException("d nul");
    }numerateur=n;
    denominateur=d;
    simplification();
}
