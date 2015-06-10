#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QListWidget>
#include <QVector>
#include "emploidutemps.h"
#include "projet.h"
#include "programmation.h"
#include "fenetres_gestion_projets.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////             simple fenetre :                                 ////////////////////////////////
//////////////     choix d'afficher l'interface d'emploi du temps,          ////////////////////////////////
//////////////        de gestion des projets, ou d'export complet           ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////


class FenetreDepart : public QWidget{
	Q_OBJECT
private:
	QVBoxLayout *layout;
	QPushButton *affichageEdt;
	QPushButton *exportEdt;
	QPushButton *importEdt;
	QPushButton *gestionProjet;
	QPushButton *exit;
	QString file;

public:
	FenetreDepart();
	~FenetreDepart();
public slots:
	void accesEdt();
	void accesProjet();
	void save();
	void load();
};








#endif
