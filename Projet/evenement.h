#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <vector>
#include <iostream>
#include <QString>
#include <QDate>
#include <QTime>
#include "duree.h"
#include "exception.h"



/*
* \file evenement.h
* \brief Contient Classe permettant la gestion d'une duree
* \author Thomas Pelletier, Paul Buzaud, Amélie Thery
* \version 1
* \date 07/06/2015
*/


/*! \class Evenement
* \brief Abstrait
* toutes les taches et activités programmées en héritent
*/
class Evenement{
private:
	QString titre;     //<!titre de l'evenement>
    int id;            //<!id, généré automatiquement a la creation>
	bool prog;         //<!permet de savoir si l'event est programme>

protected:
    Evenement(int id, const QString & t);          //<!constructeur>

public:
    int getId() const;                      //<!renvoit l'id de l'evenement (! l'id depend du projet si c'est une tache)>
    const QString& getTitre() const;        //<!renvoit le titre>
	/*!
	*  \brief permet de modifier le titre de l'event
	*  \param t nouveau titre
	*/
    void setTitre(const QString & t);
	/*!
	*  \brief renvoit la durée de l'evenement
	*  la classe evenement ne contient pas d'attribut Durée, mais toutes ses sous classes
	*  (sauf tache Composite) en possèdent, on décide donc de la créer virtuelle pure
	*/
    virtual Duree getDuree() const = 0;       

	/*!
	*  \brief change l'etat (programme/non programme)
	*  \param effectue : dis si l'activite est programmée ou non
	*/
	virtual void setProgramme(bool effectue) { prog = effectue; }
	bool isProgramme() { return prog; }     //<!renvoit l'etat (programme/non programme)>
	virtual ~Evenement();          //<!destructeur>
};

/*! \class Tache
* \brief Abstrait, herite Evenement
* toutes les taches en héritent, unité de base d'un projet
*/
class Tache : public Evenement{
private:
	QDate dateDispo;                   //<!Date de Disponibilité de la tache>
    QDate dateEcheance;                //<!Date d'echeance de la tache>
    Tache* parent;                     //<!Parent de la tache (tachecomposite du niveau supérieur, sinon NULL)>
    std::vector<Tache*> prerequis;          //<!Liste de tous les prérequis de la tache>

protected:
	Tache(int id, const QString & titre, const QDate & dDispo, const QDate & dEcheance, std::vector<Tache*> prerequis = std::vector<Tache*>(), Tache* parent = 0);     //<!constructeur>

public:
	/*!
	*  \brief reimplementation, permet de mettre a jour le statut de la Tache parente
	*  \param effectue : dis si l'activite est programmée ou non
	*/
	virtual void setProgramme(bool effectue);

	const QDate& getDateDisponibilite() const{ return dateDispo; }          //<!renvoit la date de disponibilite>
	const QDate& getDateEcheance() const{ return dateEcheance; }             //<!renvoit la date d'echeance>
	Tache* getParent() { return parent; }                                   //<!renvoit le parent>
	const Tache* getParent() const { return parent; }                        //<!renvoit le parent, constant>
	const std::vector<Tache*> & getPrerequis() const{ return prerequis; }       //<!renvoit la liste des prerequis>

	/*!
	*  \brief modifie le parent
	*  \param n_parent : nouveau parent de la tache
	*/
    void setParent(Tache* n_parent);
    
	/*!
	*  \brief ajoute un prérequis, renvoit exception si probleme>
	*  \param pre : prerequis a ajouter
	*/
	void ajoutPrerequi(Tache * pre);
    void delPrerequi(Tache * pre);
	/*!
	*  \brief ajoute une liste prérequis, renvoit exception si probleme>
	*  \param vec : prerequis a ajouter
	*/
	void ajoutPrerequis(std::vector<Tache*> vec);   

    void setPrerequis(std::vector<Tache*> vec);


	/*!
	*  \brief modifie la date de disponibilite
	*  \param dDispo : nouvelle date de disponibilite
	*/
    void setDateDisponibilite(const QDate &dDispo); 

	/*!
	*  \brief modifie la date d'echeance
	*  \param dEcheance : nouvelle date d'echeance
	*/
    void setDateEcheance(const QDate & dEcheance);

	void setDatesDisponibiliteEcheance(const QDate &dDispo, const QDate & dEcheance);

	virtual ~Tache();                                          //<!destructeur>
};



/*! \class ActiviteTraditionnelle
* \brief Abstrait, herite Evenement
* toutes les activites autres que les Taches en héritent
*/
class ActiviteTraditionnelle : public Evenement{
private:
    QString lieu;       //<!lieu de l'activite>
	Duree duree;        //<!duree de l'activite>
	static int currentId;      //<!permet de donner un ID unique a chaque activite>

protected:
	ActiviteTraditionnelle(const QString& titre, const QString& lieu, const Duree& duree) : Evenement(currentId++, titre), lieu(lieu), duree(duree){}
public:
    const QString& getLieu() const { return lieu; }    //<!renvoit le lieu de l'activite>
    virtual Duree getDuree() const{ return duree; }     //<!renvoit la duree de l'activite>
	
	/*!
	*  \brief modifie le lieu de l'activite
	*  \param nouveaulieu : nouveau lieu de l'activite
	*/
    void setLieu(QString nouveauLieu) { lieu = nouveauLieu; }

	/*!
	*  \brief modifie la duree de l'activite
	*  \param nouvelleDuree : nouvlle Duree de l'activite
	*/
    void setDuree(Duree nouvelleDuree) { duree = nouvelleDuree; }
};




///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////         Tache Unitaire      /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


/*! \class TacheUnitaire
* \brief Tache simple
* tache simple, d'une certaine durée, a effectuer en une fois
*/
class TacheUnitaire : public Tache{
	friend class Projet;
private:
    Duree duree;      //<!duree de la tache>
protected:
    TacheUnitaire(int id, const QString& titre, const QDate& dDispo, const QDate& dEcheance, Duree duree, const std::vector<Tache*> pre, Tache* parent) : Tache(id, titre, dDispo, dEcheance, pre, parent), duree(duree){}
public:
	 virtual Duree getDuree() const { return duree;} //<!renvoit la duree de la tache>

	 /*!
	 *  \brief modifie la duree de la tache
	 *  \param nouvelleDuree : nouvelle duree de l'activite
	 */
	 void setDuree(Duree & nouvelleDuree){duree = nouvelleDuree;}
};


/*! \class TacheUnitairePreemptee
* \brief Tache Preemptee
* tache simple, mais faisable en plusieurs fois
*/
class TacheUnitairePreemptee : public TacheUnitaire{
	friend class Projet;
private:
	Duree dureeEffectuee;         //<!duree effectuee>
	void checkPossible(std::string op, Duree d);   //<!verifie si la duree après opération est possible, renvoit exception si non>

protected:
    TacheUnitairePreemptee(int id, const QString& titre, const QDate& dDispo, const QDate& dEcheance, Duree duree, const std::vector<Tache*> pre, Tache* parent) : TacheUnitaire(id, titre, dDispo, dEcheance, duree, pre, parent), dureeEffectuee(0){} 

public:
	/*!
	*  \brief remets a zero la duree effectuee et rajoute celle en argument
	*  \param nouvelleDuree : nouvelle duree de l'activite
	*/
	void setDureeEffectuee(const Duree& dEffectuee);   
	/*!
	*  \brief  rajoute la duree effectuee
	*  \param dEffectuee :  duree a additionner
	*/
	void addDureeEffectuee(const Duree& dEffectuee);
	/*!
	*  \brief enleve la duree non effectuee
	*  \param dSupprimmee : duree a soustraire
	*/
	void subDureeEffectuee(const Duree& dSupprimmee);

    const Duree& getDureeEffectuee() const { return dureeEffectuee; }   //<!renvoit la duree effectuee>
	Duree getDureeRestante() const { return getDuree() - dureeEffectuee; }    //<!renvoit la duree restante>
};



///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////         Tache Composite      /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


/*! \class TacheComposite
* \brief regroupement de taches
* Tache complexe, divisée en plusieurs sous Taches, agis comme un projet miniature
*/
class TacheComposite : public Tache{
	friend class Projet;
private:
    std::vector<Tache*> sousTaches;       //<!tableau des sous tachess>
	/*!
	*  \brief renvoit lun pointeur sur la sous tache en fonction de son titre
	*  \param titreSousTache : titre recherché
	*/
    Tache* trouverSousTache(const QString & titreSousTache) const;
	/*!
	*  \brief renvoit un pointeur sur la sous tache en fonction de son id
	*  \param idSousTache : id recherché
	*/
    Tache* trouverSousTache(int idSousTache) const;

protected:
	/*!
	*  \brief constructeur, accessible par sous classes et Projet
	*  \param other : tache Composite a recopier
	*/
	TacheComposite(int id, const QString & titre, const QDate & dDispo, const QDate & dEcheance, std::vector<Tache*> pre, Tache* parent) :Tache(id, titre, dDispo, dEcheance, pre, parent), sousTaches(std::vector<Tache*>()){}
	/*!
	*  \brief constructeur par recopie, accessible par sous classes et Projet
	*  \param other : tache Composite a recopier
	*/
	TacheComposite(TacheComposite& other);
	/*!
	*  \brief operateur d'affectation, accessible par sous classes et Projet
	*  \param other : tache Composite a recopier
	*/
    TacheComposite& operator=(TacheComposite& other);

public:
	
	void updateProg();                                     //<!mets a jour le statut de la tache en fonction du statut de ses sous taches>

	/*!
	*  \brief ajoute une sous tache deja créée
	*  \param sousTache : sous tache a ajouter
	*/
	void ajouterSousTache(Tache* sousTache);
	/*!
	*  \brief ajoute un vecteur de sous tachse deja créées
	*  \param ssTaches : sous taches a ajouter
	*/
	void ajouterSousTaches(std::vector<Tache*> ssTaches);
    const std::vector<Tache*> & getSousTaches() const;                 //<! renvoit toutes les sous taches>  
	/*!
	*  \brief renvoit une reference sur la sous tache en fonction de son titre
	*  \param titreSousTache : titre recherche
	*/
    const Tache& getSousTache(const QString & titreSousTache);
	/*!
	*  \brief renvoit une reference sur la sous tache en fonction de son id
	*  \param idSousTache : id recherché
	*/
    const Tache& getSousTache(int idSousTache);
	/*!
	*  \brief supprimme(seulement du vecteur) une sous tache en fonction de son titre
	*  \param idSousTache : id recherché
	*/
    void supprimerSousTache(int idSousTache);
	/*!
	*  \brief supprimme(seulement du vecteur) une sous tache en fonction de son id
	*  \param titreSousTache : titre recherché
	*/
    void supprimerSousTache(const QString & titreSousTache);
    virtual ~TacheComposite();                   //<!destructeur>
	virtual Duree getDuree() const;             //<!renvoit la somme de la duree de ses sous taches>
};



////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////       Reunions       ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////



/*! \class Reunion
* \brief classe servant pour les activites avec plusieurss participants
*/
class Reunion : public ActiviteTraditionnelle {
private:
	std::vector<QString> participants;    //<!liste des participants>

public:
    Reunion(QString titre, Duree duree, QString lieu, std::vector<QString> participants) : ActiviteTraditionnelle(titre, lieu, duree), participants(participants){}
	int getNbParticipants() { return static_cast<int>(participants.size()); }  //<!renvoit le nombre de participants>
	const std::vector<QString>& getParticipants() const { return participants; }     //<!renvoit la liste des participants>

	/*!
	*  \brief rajoute le participant a la reunion
	*  \param parti : participanta ajouter
	*/
    void ajouterParticipant(const QString & parti){ participants.push_back(parti); }
	/*!
	*  \brief remplace tous les participants
	*  \param parti : nouveaux participants
	*/
	void setParticipants(const std::vector<QString> & parti);
	/*!
	*  \brief supprimme le participant désigné
	*  \param parti : participants a supprimmer
	*/
	void supprimmerParticipant(const QString & parti);
};



//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////         Rendez-vous           ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


/*! \class Rdv
* \brief sert pour un rendez-vous (un seul interlocuteur)
*/
class Rdv : public ActiviteTraditionnelle{
private:
	QString interlocuteur;
	 
public:
    Rdv(QString titre, Duree duree, QString lieu, QString interlocuteur):
        ActiviteTraditionnelle(titre,lieu,duree), interlocuteur(interlocuteur){}
    const QString& getInterlocuteur() const { return interlocuteur; }                //<!renvoit l'interlocuteur>
	/*!
	*  \brief modifie l'interlocuteur
	*  \param interl : nouvelle interlocuteur
	*/
	void setInterlocuteur(const QString& interl) { interlocuteur = interl; }
};


#endif
