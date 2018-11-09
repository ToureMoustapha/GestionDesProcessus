#ifndef CHRONOGRAMME_H
#define CHRONOGRAMME_H
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTableView>
#include <QStandardItemModel>
#include <QCheckBox>
#include <QFile>

class Chronogramme : public QDialog {

    Q_OBJECT
    private :
//Zone centrale
       QVBoxLayout       *VBoxLayoutePrincipale;
 //Zone hausse
       QHBoxLayout       *HBoxLayouteHaut;
  //Zone hausse-gauche
       QGroupBox         *groupeBoxHaut;
       QFormLayout       *formLayouteHaut;
       QSpinBox         *nbreColonnes;
       QSpinBox         *nbreLignes;
       QHBoxLayout       *HBoxLayouteGroupBoxHaut1;
       QPushButton       *okHaut;
       QPushButton       *annulerHaut;
       QHBoxLayout       *HBoxLayouteGroupBoxHaut2;
       QPushButton       *joindreFichier;
  //Zone hausse-droite
       QGroupBox         *groupeBoxHautDroite;
       QFormLayout       *formLayouteHautDroite;
       QTableView         *tableView;
       QStandardItemModel *standardItemModel;
 //Zone basse
       QHBoxLayout       *HBoxLayouteBas;
//Zone basse-gauche de l'interface
       QGroupBox        *groupeBoxBasGauche;
       QFormLayout      *formLayouteBasGauche;
       QCheckBox        *fifo;
       QCheckBox        *tourniquet;
       QCheckBox        *pcte;
       QCheckBox        *pgp;
       QHBoxLayout      *HBoxLayouteGroupeBoxBasGauche1;
       QCheckBox        *recapitulatif;
       QHBoxLayout      *HBoxLayouteGroupeBoxBasGauche2;
       QPushButton      *okBas;
       QPushButton      *annulerBas;
//Zone basse-droite de l'interface
       QGroupBox        *groupeBoxBasDroite;
       QFormLayout      *formLayouteBasDroite;
       QCheckBox        *classement;
       QSpinBox         *nbreTestes;
       QHBoxLayout      *HBoxLayouteGroupeBoxBasDroite;
       QPushButton      *okBasDroite;
       QPushButton      *annulerBasDroite;
       QHBoxLayout      *HBoxLayouteGroupeBoxBasDroite1;
       QPushButton      *afficherMethodePlusOptimale;
//Données du programme
       int              nbreLignesFifchierDonnees;
       int              nbreColonnesFichierDonnees;
       bool             cocherFifo;
       bool             cocherTourniquet;
       bool             cocherPcte;
       bool             cocherPgp;
       int              nombreDeTestes;
       int              nombreDeTestesAdjoint;
       bool             autoriserATester;

    public :
       Chronogramme();
       void nbreColonnesLignesFichier(const QString nomFichier,int* nbreLignes,int* nbreColonnes);
       QString** creerTableau(int nbreLignes,int nbreColonnes);
       void stockDonneesFichierDansTableau(const QString nomFichier,QString*** t ,int* nbreLignes,int* nbreColonnes);
       void stockDonneesTableauDansFichier(QString** t,int nbreLignes,int nbreColonnes,const QString nomFichier);
       void croissantSuivantColonne2(QString** t,int nbreLignes,int nbreColonnes);
       void croissantSuivantColonne3(QString** t,int nbreLignes,int nbreColonnes);
       int positionProcessus(QString chaine,QString** tabGanttOrigine,int nbreColonnes);
       void reparerPositionProcessus(QString**t,QString** tPosOrigine,int nbreLignes,int nbreColonnes);
       QString** creerTabPosOrigine(QString** t,int nbreLignes);
       void croissantSuivantColonne4(QString** t,int nbreLignes,int nbreColonnes);
       void diagrammeGanttFifo(QString** t,int nbreLignes,int nbreColonnes,const QString nomFichier);
       void diagrammeGanttPcte(QString** t,int nbreLignes,int nbreColonnes,const QString nomFichier);
       void diagrammeGanttPgp(QString** t,int nbreLignes,int nbreColonnes,const QString nomFichier);
       int tempsDexecutionProcessus(QString chaine,QString** tTemps,int nbreColonnes);
       void estSonTour(QString chaine,int q,QString** tTemps,int nbreColonnes);
       QString existeSuivant(QString** tTemps,int nbreColonnes);
       void diagrammeGanttTourniquet(QString** t,int nbreLignes,int nbreColonnes,int q,const QString nomFichier);
       QString** creerTabTempsDexecution(QString** t,int nbreLignes);
       QString calculTempsDattenteSysteme(QString nomProcessus,const QString nomFichier);
       QString calculTempsDattenteQueue(QString nomProcessus,const QString nomFichier);
       void stockageTempsDattenteSystemeEtQueueSansRequisitionDansFichier(QString const nomFichier,const QString nomFichierGantt);
       void stockageTempsDattenteSystemeEtQueueAvecRequisitionDansFichier(QString const nomFichier,const QString nomFichierGantt);
       QString calculTempsDattenteMoyen(QString);
       void ordreCroissantSuivantTempsDattenteMoyen(QString**,int,int);
       void rangerSuivantNomDesMethodes(QString**,int,int);
       void votesDesMethodes();


    private slots :
       void clicOkHaut();
       void clicAnnulerHaut();
       void clicOkBas();
       void clicAnnulerBas();
       void clicJoindreFichier();
       void clicOkBasDroite();
       void clicAnnulerBasDroite();
       void clicAfficherMethodePlusOptimale();
};

#endif // CHRONOGRAMME_H
