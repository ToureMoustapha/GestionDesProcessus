#ifndef TABLEAURECAPITULATIF_H
#define TABLEAURECAPITULATIF_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>

class TableauRecapitulatif : public QDialog {

    Q_OBJECT
    private :
       QStandardItemModel *modelRecu;
//Zone centrale
       QVBoxLayout        *VBoxLayoute;

  //Zone tableau
       QTableView         *tableView;
       QStandardItemModel *standardItemModel;
  //Zone boutton
       QHBoxLayout       *HBoxLayouteHaut;
       QHBoxLayout        *HBoxLayoute;
       QPushButton        *ok;


    public :
       TableauRecapitulatif(int nbreLignes, int nbreColonnes);
       void nbreColonnesLignesFichier(const QString nomFichier,int* nbreLignes,int* nbreColonnes);
       QString** creerTableau(int nbreLignes,int nbreColonnes);
       void stockDonneesFichierDansTableau(const QString nomFichier,QString*** t ,int* nbreLignes,int* nbreColonnes);
       QString tempsDattenteSysteme(QString chaine,QString nomFchier);
       QString tempsDattenteQueue(QString chaine,QString nomFchier);
       void chargerTableauRecapitulatif();

    private slots :
       void clicOk();

};

#endif // TABLEAURECAPITULATIF_H
