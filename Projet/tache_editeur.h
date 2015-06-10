#ifndef TACHE_EDITEUR_H
#define TACHE_EDITEUR_H

#include "projet.h"
#include "evenement.h"
#include "duree.h"
#include <QDateEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <QListWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>


class TacheEditeur : public QWidget{
	Q_OBJECT
private:
	QGridLayout* box;
	QLineEdit* titre;
	QSpinBox* heureDebut, *minDebut;
	QSpinBox* heureEffectue, *minEffectue;
	QDateEdit* dispo, *echeance;
    QLabel *label_pre, *label_sousTaches, *label_t, *label_dispo, *label_echeance, *label_duree, *labelDureeEffectue, *labelDureeInitiale, *labelPrerequis;
    QPushButton* ajoutPre, *suppPre;
	QPushButton* annuler, *saveButton;
    QListWidget *sousTaches, *prerequis;
    Tache* _tache;

public:
    TacheEditeur(Tache * tacheToEdit, QWidget *parent = 0);
public slots:
    void addPre();
    void delPre();
	void save();
};

#endif
