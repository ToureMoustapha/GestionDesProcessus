#include "FenPrincipale.h"
#include <QMenuBar>
#include <QApplication>

FenPrincipale::FenPrincipale() : QMainWindow() {

    this->setWindowTitle("GESTION DES PROCESSUS");
    this->setMinimumWidth(1000);
    this->setMinimumHeight(550);

//Zone centrale de l'interface graphique
    zoneCentralSDI = new QTabWidget;
    zoneCentralSDI->setFont(QFont("Comic Sans MS",10));

    //Onglet Gauche
    chronogrammes = new Chronogramme;

    //Onglet droit
    //votes = new QWidget;

    zoneCentralSDI->addTab(chronogrammes,"SIMULATION DE CHRONOGRAMMES");
    //zoneCentralSDI->addTab(votes,"CALCUL ET DETERMINATION DE LA M2THODE OPTIMALE");
    this->setCentralWidget(zoneCentralSDI);

    //Créaation de la barre des menus
        //Ajout de menus
        menuFichier = menuBar()->addMenu("&Fichier");
        //Ajout d'actions
        actionQuitter = menuFichier->addAction("Quitter");
        actionQuitter->setStatusTip("Fermer le programme");
        actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));

    //Création de la barre d'etat
        etatBarre = statusBar();
        etatBarre->showMessage("Prêt à  être utilisé",15000);

        QObject::connect(actionQuitter,SIGNAL(triggered()),qApp,SLOT(quit()));
}
