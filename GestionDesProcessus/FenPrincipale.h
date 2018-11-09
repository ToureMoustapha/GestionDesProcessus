#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QDialog>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include "Chronogramme.h"

class FenPrincipale : public QMainWindow {

    Q_OBJECT

    private :
//Zone centrale de l'interface graphique
       QTabWidget           *zoneCentralSDI;
    //Onglet Gauche
       Chronogramme              *chronogrammes; //il peut pointer un QDialog
    //Onglet droit
       //QWidget              *votes;

//Création de la barre des menus
       QMenu             *menuFichier;
       QAction           *actionQuitter;
    //Création de la barre d'etat
       QStatusBar        *etatBarre;

    public :
       FenPrincipale();
};

#endif // FENPRINCIPALE_H
