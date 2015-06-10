#ifndef PROJET_H
#define PROJET_H
#include "duree.h"
#include <QDate>
#include <QTime>
#include <QTreeWidget>
#include "evenement.h"
#include <QString>
#include <vector>



class Projet{
	friend class ProjetManager;
private:
    int currentId;
    QString titre;
    QDate debut;
    QDate fin;
	std::vector<Tache*> taches;

	Projet(const QString & t, const QDate & deb, const QDate & fin);
	Tache* trouverTache(const QString & t) const;
	Tache* trouverTache(int id) const ;

public:
    Tache & creerTache(QString type, const QString & titre, const QDate & dDispo, const QDate & dEcheance, std::vector<Tache*> pre = std::vector<Tache*>(), Tache* parent = 0, Duree du = Duree(0));
	int getCurrentId() { return currentId; }
	
	
	void ajouterTache(Tache * t);

	const std::vector<Tache*> getTaches() const;
	Tache& getTache(const QString & t);
	Tache& getTache(int id);
	const Tache& getTache(const QString & t)const;
    const Tache& getTache(int id)const;

    void supprimerTache(int t);
    void supprimerTache(const QString & t);

    const QString getTitre()const { return titre; }
    const QDate getDebut()const { return debut; }
    const QDate getFin()const { return fin; }

    ~Projet();
};





class ProjetManager{
private:
    std::vector<Projet*> projets;

    static ProjetManager * instance;

    ProjetManager(){}
    ~ProjetManager();
	Projet* trouverProjet(const QString &t) const;

	void AjouterSousTachesArbre(TacheComposite * t, QTreeWidgetItem & i);

public:
    static ProjetManager& getInstance();
    static void libererInstance();
    void ajouterProjet(const QString& t, const QDate& dispo, const QDate& echeance);
    Tache & getTache(int id);

    const std::vector<Projet*> & getProjets() const;
    Projet& getProjet(const QString & t);
    const Projet& getProjet(const QString & t) const;
    const Projet& getProjet(const Tache *tacheCherchee) const;
    void supprimerProjet(const QString p);

    QTreeWidget * creerArbreProjets();
};


#endif
