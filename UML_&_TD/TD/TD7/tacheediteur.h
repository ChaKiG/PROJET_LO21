#ifndef TACHEEDITEUR_H
#define TACHEEDITEUR_H

#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QString>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include "Calendar.h"

class TacheEditeur : public QWidget
{
    Q_OBJECT
protected:
    QHBoxLayout* l1,*l2,*l3,*l4;
    QVBoxLayout* box;
    QLineEdit* id;
    QTextEdit* titre;
    QSpinBox* heure,*min;
    QDateEdit* dispo,*echeance;
    QLabel* label_d,*label_pre,*label_t,*label_dispo,*label_echeance,*label_duree;
    QCheckBox* pre;
    QPushButton* annuler,*saveButton;
    Tache* tache;
public:
    explicit TacheEditeur(Tache& tacheToEdit, QWidget *parent = 0);
public slots:
    void save();
};

#endif // TACHEEDITEUR_H
