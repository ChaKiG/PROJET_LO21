#include "emploidutemps.h"



ChoixSemaine::ChoixSemaine(){
	lay = new QGridLayout;
	valider = new QPushButton("valider");
	text = new QLabel("date :");
	choix = new QDateEdit;
	choix->setDate(QDate::currentDate());
	setLayout(lay);
	lay->addWidget(text, 0, 0);
	lay->addWidget(choix, 1, 0, 1, 3);
	lay->addWidget(valider, 2, 1, 1, 1);
	QObject::connect(valider, SIGNAL(clicked()), this, SLOT(accesEdT()));
}

void ChoixSemaine::accesEdT(){
	new EmploiDuTemps(choix->date());
	close();
}

ChoixSemaine::~ChoixSemaine(){
	delete lay;
	delete valider;
	delete text;
	delete choix;
}




EmploiDuTemps::EmploiDuTemps(QDate indate){
	indate = indate.addDays(1-indate.dayOfWeek());
	date= new QDate(indate);
	//permet d'avoir le lundi correspondant a n'importe quel jour d'une semaine
	
	addEvent = new QPushButton("Ajouter Evenement");
    quitter = new QPushButton("fermer");
	tab = new QTableWidget(60,7);
	lay = new QGridLayout();
	week = new QStringList();
	hours = new QStringList();
	*week << "Lundi" << "Mardi" << "Mercredi" << "Jeudi" << "Vendredi" << "Samedi" << "Dimanche";
	for (int i(0); i < 60; i++){
		if (i % 4)
			*hours << "";
		else
			*hours << (QString::number(i / 4 + 7) + "h");
	}

	creerEdT();

	setLayout(lay);
	resize(1000, 700);
	lay->addWidget(addEvent,0,0);
    lay->addWidget(tab,1,0,4,5);
	lay->addWidget(quitter,5,4);
	tab->setVerticalHeaderLabels(*hours);
	tab->setHorizontalHeaderLabels(*week);
	tab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //permet au tableau de changer de taille dynamiquement
	tab->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tab->verticalHeader()->setDefaultSectionSize(1);
		
	tab->setSelectionBehavior(QAbstractItemView::SelectItems); //limite la selection a un item
	tab->setSelectionMode(QAbstractItemView::SingleSelection);

	show();
	
	QObject::connect(tab, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(editItem(QTableWidgetItem *)));  //Rend les cases renseignees du tableau cliquables : elles ouvrent la fenetre de modification d'evenement
	QObject::connect(addEvent, SIGNAL(clicked()), this, SLOT(newProg()));
	QObject::connect(quitter, SIGNAL(clicked()), this, SLOT(close()));
}



void EmploiDuTemps::creerEdT(){

	std::vector<Programmation*> vectEdt = ProgrammationManager::getInstance().getSemaine((*date));
	std::vector<Programmation*>::iterator ite = vectEdt.begin();
	while (ite != vectEdt.end()){
		QTableWidgetItem * item = new QTableWidgetItem((*ite)->getEvent()->getTitre());
		item->setData(Qt::UserRole, (*ite)->getId());
		int column = (*ite)->getDateChoisie().dayOfWeek() - 1;
		int row = (((*ite)->getHoraireChoisi().hour() - 7) * 4 + (*ite)->getHoraireChoisi().minute()/15);
		int rowSpan = ((*ite)->getDuree().getDureeEnMinutes()/15);
		tab->setItem(row, column, item);
		if(rowSpan!=0) 
			tab->setSpan(row, column, rowSpan, 1);
		tab->item(row,column)->setBackgroundColor(QColor(qrand()%255,qrand()%255,qrand()%255));
		ite++;
	}
}



void EmploiDuTemps::editItem(QTableWidgetItem * item){
	Programmation & prog = ProgrammationManager::getInstance().getProgrammation(item->data(Qt::UserRole).toInt());
	new ProgrammationEditeur(prog);
    close();
}

void EmploiDuTemps::newProg(){
	new CreationProgrammation();
	close();
}




EmploiDuTemps::~EmploiDuTemps(){
	delete addEvent;
	delete quitter;
	delete lay;
	delete tab;
	delete week;
	delete hours;
	delete date;
}



