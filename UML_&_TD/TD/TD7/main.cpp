/*#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include <QFileDialog>
#include "Calendar.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QWidget *fen = new QWidget();
    fen->show();
    QPushButton *button = new QPushButton("Wesh Ma gueule", &titre);
    button->show();
    QObject::connect(button,SIGNAL(clicked()),&app,SLOT(quit()));
    QPushButton *button2 = new QPushButton("coucou", &titre);
    button2->show();


    fen->setFixedSize(200,200);
    QLineEdit *identificateur = new QLineEdit(fen);
    identificateur->setFixedWidth(180);
    identificateur->move(10,10);
    identificateur->show();
    QTextEdit *titre = new QTextEdit(fen);
    titre->setGeometry(10,45,180,110);
    titre->show();
    QPushButton *save = new QPushButton(fen);
    save->setFixedWidth(80);
    save->move(10,170);
    save->show();


    QWidget *fen = new QWidget();
    TacheManager &man = TacheManager::getInstance();
    QString chemin = QFileDialog::getOpenFileName();
    man.load(chemin);
    Tache &t1 = man.getTache("T1");
    QTextEdit *titre = new QTextEdit(t1.getTitre(),fen);
    QLineEdit*identificateur = new QLineEdit(t1.getId(),fen);
    QPushButton *save = new QPushButton("save",fen);
    QVBoxLayout *box = new QVBoxLayout(fen);
    box->addWidget(identificateur);
    box->addWidget(titre);
    box->addWidget(save);

    titre->show();
    identificateur->show();
    save->show();
    fen->show();

    QObject::connect(save,SIGNAL(clicked()),fen,SLOT(close()));


    return app.exec();
}
*/

#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QComboBox>
#include "Calendar.h"
#include "tacheediteur.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    TacheManager& m=TacheManager::getInstance();
    QString chemin = "";
    chemin = QFileDialog::getOpenFileName();
    m.load(chemin);
    Tache& t=m.getTache("T2");
    TacheEditeur fenetre(t);
    fenetre.show();

    return app.exec();
}

