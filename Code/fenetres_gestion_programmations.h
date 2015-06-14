#ifndef FEN_PROG
#define FEN_PROG

#include <QLabel>
#include <QGridLayout>
#include <QTreeWidget>
#include <QPushButton>
#include <QDateEdit>
#include <QSpinBox>
#include <QLineEdit>
#include <QMessageBox>

#include "emploidutemps.h"
#include "projet.h"
#include "programmation.h"



////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////        sert a choisir quelle tache on va programmer        /////////////////////////////
///////////////////              ou si on veut creer une activite              /////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CreationProgrammation : public QWidget {
	Q_OBJECT
private:
	QLabel *l, *l_debut;
	QGridLayout * lay;
	QTreeWidget *arbre;
	QPushButton  *choisir, *newActi;
	QDateEdit * d_j;
	QSpinBox *d_h, *d_m;

public:
	CreationProgrammation(QWidget * parent = 0);
	~CreationProgrammation();
	public slots:
	void creerProg();
	void creerActi();
};



class CreationActivite : public QWidget {
	Q_OBJECT
private:
	QGridLayout *lay;
	QPushButton *valider;
	QLabel *text, *text1, *text2, *text3, *text4;
	QSpinBox *typeActi;
	QSpinBox *heure;
	QSpinBox * minute;
	QDateTimeEdit * debut;
	QLabel * textacti;
	QLineEdit * titre, *participant, *lieu;
	QList<QLineEdit*> List;

public:
	CreationActivite(QWidget * parent = 0);
	~CreationActivite();
	public slots :
	void save();
	void change(int);
};


class ProgrammationEditeur : QWidget{
	Q_OBJECT
private:
	QLabel *l_date, *l_debut, *l_duree, *l_titre;
	QGridLayout *lay;
	QDateEdit *debut_j;
	QSpinBox *debut_h_h, *debut_h_m, *dur_h, *dur_m;
	QLineEdit * titre;
	QPushButton *val, *ann, *supp;
	Programmation & _prog;

public:
	ProgrammationEditeur(Programmation & prog, QWidget * parent = 0);
	~ProgrammationEditeur();
	public slots:
	void save();
	void delprog();
};

#endif
