#ifndef TABLEAUDEVOTES_H
#define TABLEAUDEVOTES_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QLabel>

class TableauDeVotes : public QDialog {

    Q_OBJECT
    private :
//Zone centrale
       QVBoxLayout        *VBoxLayoute;

  //Zone tableau
       QTableView         *tableView;
       QStandardItemModel *standardItemModel;
  //Zone boutton
       QHBoxLayout        *HBoxLayouteHaut;
       QHBoxLayout        *HBoxLayoute;
       QHBoxLayout        *HBoxLayoute1;
       QPushButton        *ok;
       QLabel             *label;

       int                nombreDeLignesView;

    public :
       TableauDeVotes(int nbreLignes, int nbreColonnes);
       void nbreColonnesLignesFichier(const QString nomFichier,int* nbreLignes,int* nbreColonnes);
       QString** creerTableau(int nbreLignes,int nbreColonnes);
       void stockDonneesFichierDansTableau(const QString nomFichier,QString*** t ,int* nbreLignes,int* nbreColonnes);
       void chargerTableauDeVotes();
       QString methodePlusOptimale();

    private slots :
       void clicOk();
};

#endif // TABLEAUDEVOTES_H
