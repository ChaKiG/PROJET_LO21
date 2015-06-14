#ifndef FEN_GESTION_PROJ_H
#define FEN_GESTION_PROJ_H


#include <QInputDialog>
#include <QXmlStreamWriter>
#include <QWidget>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <iterator>
#include <QLayout>
#include <QComboBox>
#include <QDateEdit>
#include <QListWidget>
#include <QDir>
#include <QCheckBox>
#include <QDebug>

#include "projet.h"
#include "programmation.h"
#include "tache_editeur.h"
#include "gestiontache.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////               affiche et modifie les informations d'une tache       /////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////         fenetre principale pour la gestion des projets        /////////////////////////////
///////////////         tous les ajouts/suppressions/modifications            /////////////////////////////
///////////////         des taches ET/OU projets se font a partir d'ici       /////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
class GestionProj : public QWidget{
	Q_OBJECT
private:
	QPushButton * nTache, *nTacheRacine;
	QTreeWidget * arbre;
	QGridLayout * lay;
	TacheEditeur * editeur;
	QPushButton * addprojet;
	QPushButton * supprprojet;
	QPushButton * exportprojet;
	QPushButton * importerprojet;

public:
	GestionProj();
	~GestionProj();
public slots:
	void majEdit(QTreeWidgetItem * item);   //slot pour mettre a jour l'editeur
	void ajoutprojet();
	void suppr();
	void exportp();
	void importp();
    void ajoutTacheRacine();
    void ajoutTache();
};


class suppressionProjet : public QWidget{
	Q_OBJECT
private:
	QLabel * text;
	QComboBox* box;
	QPushButton *valider;
	QPushButton * annuler;
	QGridLayout *lay;

public:
	suppressionProjet();
	~suppressionProjet();
	public slots:
	void deleteprojet();
	void retour();
};




class exportProjet : public QWidget{
	Q_OBJECT
private:
	QLabel * text;
	QComboBox* box;
	QPushButton *valider;
	QPushButton * annuler;
	QGridLayout *lay;
	QString file;

public:
	exportProjet();
	~exportProjet();
	public slots:
	void expprojet();
	void retour();
};

class importProjet : public QWidget{
	Q_OBJECT
private:
	QLabel * text;
	QLineEdit* textedit;
	QPushButton *valider;
	QPushButton * annuler;
	QGridLayout *lay;
	QString file;

public:
	importProjet();
	~importProjet();
	public slots:
	void load();
	void retour();
};


class ajouterProjet :public QWidget{
	Q_OBJECT
private:
	QPushButton *valider;
	QPushButton * annuler;
	QLabel * choixtitre;
	QLineEdit * titre;
	QLabel * choixdatedispo;
	QDateEdit * datedispo;
	QLabel * choixdateeche;
	QDateEdit * dateeche;
	QGridLayout *lay;

public:
	ajouterProjet();
	~ajouterProjet();
	public slots:
	void ajoutProjet();
	void retour();
	void setmindateechee(QDate);
};




#endif
