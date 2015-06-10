#ifndef CALENDAR_h
#define CALENDAR_h


#include <string>
#include <iostream>
#include "timing.h"


using namespace std;
using namespace TIME;


class CalendarException{
public:
    CalendarException(const string& message):info(message){}
    string getInfo() const { return info; }
private:
    string info;
};

class Tache{
public:
    Tache(const string & id_, const string & ti, const Duree & duree_, const Date & date_Dispo_, const Date & deadline_): id(id_), titre(ti), duree(duree_),date_dispo(date_Dispo_),deadline(deadline_){};
    string getId() const {return id;};
    string getTitre() const {return titre;};
    Duree getDuree() const {return duree;};
    Date getDate() const {return date_dispo;};
    Date getDeadline() const {return deadline;};
    ~Tache();
private:
    string id;
    string titre;
    Duree duree;
    Date date_dispo,deadline;
};

class TacheManager {
private:
    Tache** taches;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(Tache* t);
public:
    TacheManager();
    void ajouterTache(const string& id, const string& t, const Duree& dur, const Date& dispo, const Date& deadline);
    Tache& getTache(const string& id);
    const Tache& getTache(const string& id) const;
    Tache * existe(const string & id) const;
    const Tache * existe(const string & id) const;
};


#endif
