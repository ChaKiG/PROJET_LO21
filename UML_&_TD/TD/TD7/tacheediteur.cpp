#include "tacheediteur.h"
#include "Calendar.h"
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include <QFileDialog>
#include <QSpinBox>
#include <QDateEdit>
#include <QLabel>
#include <QCheckBox>

TacheEditeur::TacheEditeur(Tache& tacheToEdit, QWidget* parent){
    box = new QVBoxLayout(parent);
    l1 = new QHBoxLayout();
    l2 = new QHBoxLayout();
    l3 = new QHBoxLayout();
    l4 = new QHBoxLayout();
    this->setLayout(box);
    box->addStretch(1);
    box->addLayout(l1);
    box->addStretch(1);
    box->addLayout(l2);
    box->addStretch(1);
    box->addLayout(l3);
    box->addStretch(1);
    box->addLayout(l4);

    label_d = new QLabel("identificateur");
    id = new QLineEdit(tacheToEdit.getId());
    pre = new QCheckBox();
    pre->setChecked(tacheToEdit.isPreemptive());
    label_pre = new QLabel("preemptive");
    l1->addWidget(label_d);
    l1->addWidget(id);
    l1->addWidget(pre);
    l1->addWidget(label_pre);

    label_t = new QLabel("titre");
    titre = new QTextEdit(tacheToEdit.getTitre());
    l2->addWidget(label_t);
    l2->addWidget(titre);

    label_dispo = new QLabel("disponibilité");
    dispo = new QDateEdit(tacheToEdit.getDateDisponibilite());
    label_echeance = new QLabel("échéance");
    echeance = new QDateEdit(tacheToEdit.getDateEcheance());
    label_duree = new QLabel("durée");
    heure = new QSpinBox(this);
    min = new QSpinBox(this);
    heure->setValue(tacheToEdit.getDuree().getHeure());
    heure->setSuffix(" heure(s)");
    min->setValue(tacheToEdit.getDuree().getMinute());
    min->setSuffix(" minute(s)");
    l3->addWidget(label_dispo);
    l3->addWidget(dispo);
    l3->addWidget(label_echeance);
    l3->addWidget(echeance);
    l3->addWidget(label_duree);
    l3->addWidget(heure);
    l3->addWidget(min);

    annuler = new QPushButton("annuler");
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));
    saveButton = new QPushButton("sauvegarder",this);
    QObject::connect(saveButton,SIGNAL(clicked()),this,SLOT(save()));
    l4->addWidget(annuler);
    l4->addWidget(saveButton);

    tache = &tacheToEdit;
}


void TacheEditeur::save(){
    Duree d(heure->value(),min->value());
    if(id->text()==tache->getId()){
        tache->setTitre(titre->toPlainText());
        tache->setDatesDisponibiliteEcheance(dispo->date(),echeance->date());
        tache->setDuree(d);
        if(pre->isChecked())
            tache->setPreemptive();
        else
            tache->setNonPreemptive();
    }
}
