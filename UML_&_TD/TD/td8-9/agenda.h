#include "evenement.h"


#pragma once
class Agenda{
private:
	TIME::Evt1j** tab;
	int nbEvt;
public:
	Agenda();
	Agenda(Agenda& copy){};
	~Agenda(void);

	void operator=(Agenda& other){};
};

