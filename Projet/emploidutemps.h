#ifndef EMPLOIDUTEMPS_H
#define EMPLOIDUTEMPS_H

#include <QWidget>
#include <QInputDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QDate>
#include <QLabel>
#include <QSpinBox>
#include <QTreeWidget>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QVector>
#include <QComboBox>
#include <QDir>
#include <QTextStream>
#include <QXmlStreamWriter>


#include "programmation.h"
#include "projet.h"
#include "fenetres_gestion_programmations.h"


/*
* \file emploidutemps.h
* \brief gere l'affichage de l'emploi du temps
* \author Thomas Pelletier, Paul Buzaud, Amélie Thery
* \version 1
* \date 07/06/2015
*/


/*! \class ChoixSemaine
* \brief Choisir la date a afficher dans l'emploi du temps
*/
class ChoixSemaine : public QWidget {
	Q_OBJECT
private:
	QGridLayout *lay;       //<!simple layout>
	QPushButton *valider;   //<!lance l'emploi du temps>
	QLabel *text;           //<!invite a choisir la date>
	QDateEdit *choix;       //<!date choisie>

public:
	ChoixSemaine();        //<!constructeur>
	~ChoixSemaine();       //<!destructeur>
public slots:
	void accesEdT();      //<!utilise par valider pour lancer EdT>
};


/*! \class ChoixSemaine
*  \brief affichage d'une semaine
*  permet de creer des programmations ou l'export de l'emploi du temps
*/
class EmploiDuTemps : public QWidget{
	Q_OBJECT
private:
    QDate * date;
    QPushButton * addEvent;
	QPushButton * quitter;
	QTableWidget * tab;
	QGridLayout * lay;
	QStringList * week;
	QStringList  * hours;

public:
	/*!
	*  \brief constructeur
	*  \param indate jour que l'on veut voir (affiche semaine correspondante)
	*/
    EmploiDuTemps(QDate indate);   //<!Constructeur>
    void creerEdT();               //<!rempli le tableau avec l'emploi du temps>
	~EmploiDuTemps();              //<!destructeur>
public slots :
/*!
*  \brief permet de modifier une programmation selectionnee
*  \param item item renvoyant sur la programmation a modifier
*/
    void editItem(QTableWidgetItem * item);
    void newProg();            //<!lance l'interface de creation de programmation>
};


#endif // EMPLOIDUTEMPS_H
