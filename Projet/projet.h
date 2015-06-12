#ifndef PROJET_H
#define PROJET_H
#include "duree.h"
#include <QDate>
#include <QTime>
#include <QTreeWidget>
#include "evenement.h"
#include <QString>
#include <vector>


/*! \class Projet
* \brief regroupe un ensemble de taches portant sur un certain sujet
*/
class Projet{
	friend class ProjetManager;
private:
    int currentId;   //<!id de la prochaine tache de ce projet>
    QString titre;   //<!titre du projet>
    QDate debut;     //<!date de dispo du projet>
    QDate fin;       //<!date de fin du projet>
	std::vector<Tache*> taches;      //<!taches appartenant au projet>

	Projet(const QString & t, const QDate & deb, const QDate & fin);   //<!constructeur, privé>
	/*!
	*  \brief ajoute une tache au projet
	*  \param id : id de la tache
	*/
	void ajouterTache(Tache * t);
	
	/*!
	*  \brief cherche une tache par son titre 
	*  attention : renvoit la premiere tache renseignée si plusieurs taches ont le meme titre
	*  \param t : titre de la tache
	*/
	Tache* trouverTache(const QString & t) const;
	/*!
	*  \brief cherche une tache par son id
	*  \param id : id de la tache
	*/
	Tache* trouverTache(int id) const ;
	/*!
	*  \brief sert a creer l'arbre du projet
	*  \param t : tache pour laquelle on doit renseigner les enfants
	*  \param i : widget correspondant a t dans l'arbre
	*/
    void AjouterSousTachesArbre(TacheComposite * t, QTreeWidgetItem & i) const;

public:
	/*!
	*  \brief cree une tache correspondant aux arguments passés
	*  \param type : type de la tache (TacheUnitaire/TacheComposite/TacheUnitairePreemptee)
	*  \param titre : titre de la tache a creer
	*  \param dDispo : date de disponibilite de la tache
	*  \param dEcheance : date d'echeance de la tache
	*  \param pre : prerequis de la tache
	*  \param parent : parent de la tache (tache composite de niveau superieur)
	*  \param du : duree de la tache
	*/
    Tache & creerTache(QString type, const QString & titre, const QDate & dDispo, const QDate & dEcheance, std::vector<Tache*> pre = std::vector<Tache*>(), Tache* parent = 0, Duree du = Duree(0));
	
	
	int getCurrentId() { return currentId; }    //<!renvoit l'id actuel>


	const std::vector<Tache*> getTaches() const;    //<!renvoit la liste des taches du projet>
	/*!
	*  \brief cherche une tache par son titre
	*  attention : renvoit la premiere tache renseignée si plusieurs taches ont le meme titre
	*  \param t : titre de la tache
	*/
	Tache& getTache(const QString & t);
	/*!
	*  \brief cherche une tache par son id 
	*  \param id : id de la tache
	*/
	Tache& getTache(int id);
	/*!
	*  \brief cherche une tache par son titre (const)
	*  attention : renvoit la premiere tache renseignée si plusieurs taches ont le meme titre
	*  \param t : titre de la tache
	*/
	const Tache& getTache(const QString & t)const;
	/*!
	*  \brief cherche une tache par son id (const)
	*  \param id : id de la tache
	*/
    const Tache& getTache(int id)const;
	/*!
	*  \brief supprime la tache par son id
	*  \param id : id de la tache a supprimer
	*/
    void supprimerTache(int id);
	/*!
	*  \brief supprime la tache par son titre
	*  attention : supprime la premiere tache renseignée si plusieurs taches ont le meme titre
	*  \param t : titre de la tache a supprimer
	*/
    void supprimerTache(const QString & t);

    const QString getTitre()const { return titre; }    //<!renvoit le titre du projet>
    const QDate getDebut()const { return debut; }     //<!renvoit la date de debut du projet>
    const QDate getFin()const { return fin; }         //<!renvoit la date de fin>

    QTreeWidget * creerArbre() const;    //<!permet l'affichage de toutes les taches du projet sous forme d'arbre>

    ~Projet();
};




/*! \class ProjetManager
* \brief permet la gestion de tous les projets
*/
class ProjetManager{
private:
    std::vector<Projet*> projets;    //<!liste des projets>

	static ProjetManager * instance;  //<!design pattern singleton>

    ProjetManager(){}    //<!constructeur, private>
    ~ProjetManager();    //<!destructeur, private>

	/*!
	*  \brief cherche un projet
	*  \param t : titre du projet cherché
	*/
	Projet* trouverProjet(const QString &t) const;
	
	/*!
	*  \brief permet la creation de l'arbre des projets
	*  \param t : tache pour laquelle on doit renseigner les enfants
	*  \param i : widget correspondant a t dans l'arbre
	*/
	void AjouterSousTachesArbre(TacheComposite * t, QTreeWidgetItem & i);

public:
    static ProjetManager& getInstance();      //<!design pattern singleton>
    static void libererInstance();        //<!design pattern singleton>
	
	/*!
	*  \brief crée et ajoute un projet a la liste des projets
	*  \param t : titre du projet
	*  \param dispo : date de disponibilité du projet
	*  \param echeance : date d'exheance du projet
	*/
    void ajouterProjet(const QString& t, const QDate& dispo, const QDate& echeance);

    const std::vector<Projet*> & getProjets() const;   //<!renvoit la liste des projets>
	/*!
	*  \brief cherche un projet
	*  \param t : titre du projet cherché
	*/
    Projet& getProjet(const QString & t);
	/*!
	*  \brief cherche un projet (const)
	*  \param t : titre du projet cherché
	*/
    const Projet& getProjet(const QString & t) const;
	/*!
	*  \brief cherche le projet dont fait partie une certaine tache
	*  \param tacheCherchee : tache cherchee
	*/
    const Projet& getProjet(const Tache *tacheCherchee) const;
	/*!
	*  \brief supprime un projet
	*  \param t : titre du projet a supprimer
	*/
    void supprimerProjet(const QString t);

    QTreeWidget * creerArbreProjets();     //<!permet l'affichage de tous les projets et de leurs taches>
};


#endif
