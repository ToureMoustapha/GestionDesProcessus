#ifndef TABLEAUDESAISIE_H
#define TABLEAUDESAISIE_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>

class TableauDeSaisie : public QDialog {

    Q_OBJECT
    private :
       QStandardItemModel **modelRecu;
       QTableView         *vueRecu;
//Zone centrale
       QVBoxLayout        *VBoxLayoute;

  //Zone tableau
       QTableView         *tableView;
       QStandardItemModel *standardItemModel;
  //Zone boutton
       QHBoxLayout       *HBoxLayouteHaut;
       QHBoxLayout        *HBoxLayoute;
       QPushButton        *valider;
       QPushButton        *annuler;


    public :
       TableauDeSaisie(int nbreLignes, int nbreColonnes,QStandardItemModel** modelEnvoye,QTableView* vueEnvoye);
       void nbreColonnesLignesFichier(const QString nomFichier,int* nbreLignes,int* nbreColonnes);
       QString** creerTableau(int nbreLignes,int nbreColonnes);
       void stockDonneesFichierDansTableau(const QString nomFichier,QString*** t ,int* nbreLignes,int* nbreColonnes);
       void stocketDonneesSaisieDansFichier(QString nomFichier);

    private slots :
       void clicValider();


};
#endif // TABLEAUDESAISIE_H
