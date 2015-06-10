#ifndef CALENDAR_h
#define CALENDAR_h
#include<string>
#include<iostream>
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

class Tache {
    friend class TacheManager; //TacheManager a accès au constructeur/destructeur

private:
	string identificateur;
	string titre;
	Duree duree;
	Date disponibilite;
	Date echeance;
	Tache(const string& id, const string& t, const Duree& dur, const Date& dispo, const Date& deadline):
			identificateur(id),titre(t),duree(dur),disponibilite(dispo),echeance(deadline){}
    Tache(const Tache& copy):
        identificateur(copy.identificateur),titre(copy.titre),duree(copy.duree),disponibilite(copy.disponibilite),echeance(copy.echeance) {}               //pas obligatoire
    Tache& operator=(const Tache& autre);   //pas obligatoire
    ~Tache() {};

public:
	string getId() const { return identificateur; }
	string getTitre() const { return titre; }
	Duree getDuree() const { return duree; }
	Date getDateDisponibilite() const {  return disponibilite; }
	Date getDateEcheance() const {  return echeance; }
};


class TacheManager {
private:
	Tache** taches;
	unsigned int nb;
	unsigned int nbMax;
	string file;
	static TacheManager *instance;

	TacheManager();
	~TacheManager();
	TacheManager(const TacheManager& um);
	TacheManager& operator=(const TacheManager& um);
	void addItem(Tache* t);
	Tache* trouverTache(const string& id) const;

public:
    static TacheManager& getInstance();
	static void libererInstance();
	Tache& ajouterTache(const string& id, const string& t, const Duree& dur, const Date& dispo, const Date& deadline);
	Tache& getTache(const string& id);
	const Tache& getTache(const string& code) const;
	void load(const string& f);
	void save(const string& f);


	class Iterator{
        friend class TacheManager;
    private:
        Tache **pt;
        /*unsigned int nbRestant;
        Iterator(): pt(0), nbRestant(0) {}
        Iterator(Tache **pt, unsigned int nbRestant): pt(pt), nbRestant(nbRestant) {}  inutile */
        Iterator(): pt(0) {}
        Iterator(Tache **pt): pt(pt) {}
    public:
        Tache& current() const;
        bool operator!=(const Iterator &other) const {return pt!=other.pt;}
        void operator++() {++pt;}
        Tache& operator*() const {return **pt;}
        //void next(); inutile
	};
	//Iterator getIterator() const {return Iterator(taches,nb);} //Attention : si on ajoute une tache il faut recréer l'iterateur (nb aura varié)
};


class Programmation {
	const Tache* tache;
	Date date;
	Horaire horaire;

public:
	Programmation(const Tache& t, const Date& d, const Horaire& h):tache(&t), date(d), horaire(h){}
	const Tache& getTache() const { return *tache; }
	Date getDate() const { return date; }
	Horaire getHoraire() const { return horaire; }
};


class ProgrammationManager {
private:
	Programmation** programmations;
	unsigned int nb;
	unsigned int nbMax;
	void addItem(Programmation* t);
	Programmation* trouverProgrammation(const Tache& t) const;

public:
	ProgrammationManager();
	~ProgrammationManager();
	ProgrammationManager(const ProgrammationManager& um);
	ProgrammationManager& operator=(const ProgrammationManager& um);
	void ajouterProgrammation(const Tache& t, const Date& d, const Horaire& h);
};

ostream& operator<<(ostream& f, const Tache& t);
ostream& operator<<(ostream& f, const Programmation& p);

#endif
