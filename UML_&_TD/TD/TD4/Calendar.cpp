#include "Calendar.h"

using namespace std;
using namespace TIME;


void TacheManager::addItem(Tache *t){
    if(nb>=nbMax){
        Tache **newtab = new Tache*[nbMax+10];
        for(int i(0); i<nb;++i){
            newtab[i]=taches[i];
        }delete[] taches;
        taches = newtab;
        nbMax+=10;
        ++nb;
        taches[nb] = t;
    }else{
        ++nb;
        taches[nb] = t;
    }
}


Tache * TacheManager::existe(const string & id) const{
    for(int i(0);i<nb;++i){
        if(id==taches[i]->getId())
            return taches[i];
        else
            return 0;
    }
}


void TacheManager::ajouterTache(const string& id, const string& t, const Duree& dur, const Date& dispo, const Date& deadline){
    if(existe(id)!=0){
        throw CalendarException("tache existe deja");
        Tache * tach = new Tache(id,t,dur,dispo,deadline);
        addItem(tach);
    }
}


Tache & TacheManager::getTache(const string &id){
    Tache *t = existe(id);
    if(t==0)
        throw CalendarException("cette tache n'existe pas");
    else
        return *t;
}

const Tache & TacheManager::getTache(const string &id) const{
    Tache const *t = existe(id);
    if(t==0)
        throw CalendarException("cette tache n'existe pas");
    else
        return *t;
}




