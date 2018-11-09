#include "TableauDeSaisie.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QStandardItemModel>

TableauDeSaisie::TableauDeSaisie(int nbreLignes, int nbreColonnes,QStandardItemModel **ModelEnvoye,QTableView* vueEnvoye) : QDialog(){

    this->setWindowTitle("TABLEAU DE SAISIE DES DONNEES DES PROCESSUS");
    modelRecu = ModelEnvoye;
    vueRecu = vueEnvoye;

    this->setMinimumWidth(450);
    //this->setMinimumHeight(height());
    this->setFont(QFont("Comic Sans MS",10));

    VBoxLayoute = new QVBoxLayout(this);

    HBoxLayouteHaut = new QHBoxLayout();
    tableView = new QTableView();
    HBoxLayouteHaut->addWidget(tableView);
    standardItemModel = new QStandardItemModel(nbreLignes,nbreColonnes);
    tableView->setModel(standardItemModel);

    HBoxLayoute = new QHBoxLayout();
    HBoxLayoute->setAlignment(Qt::AlignRight);
    valider = new QPushButton("&Valider");
    annuler = new QPushButton("&Annuler");
    HBoxLayoute->addWidget(valider);
    HBoxLayoute->addWidget(annuler);

    VBoxLayoute->addLayout(HBoxLayouteHaut);
    VBoxLayoute->addLayout(HBoxLayoute);

    QObject::connect(valider,SIGNAL(clicked()),this,SLOT(clicValider()));

}

void TableauDeSaisie::stocketDonneesSaisieDansFichier(QString nomFichier){
    QFile fichier(nomFichier);
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
       QMessageBox::critical(NULL,"ERREUR","Erreur d'ouverture du fichier <<"+ nomFichier +">>");
    else{
         QTextStream flux(&fichier);
         int nbreLignes=standardItemModel->rowCount(),nbreColonnes=standardItemModel->columnCount();
         for(int i=0; i<nbreLignes ;i++)
              for(int j=0;j<nbreColonnes;j++)
                  if(j != nbreColonnes - 1 )
                     flux <<  standardItemModel->data(standardItemModel->index(i,j)).toString() + " ";
                  else
                      flux <<  standardItemModel->data(standardItemModel->index(i,j)).toString() << endl;
        }
        fichier.close();
}

void TableauDeSaisie::nbreColonnesLignesFichier(const QString nomFichier,int* nbreLignes,int* nbreColonnes){
     QFile fichier(nomFichier);
    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
       QMessageBox::critical(NULL,"ERREUR","Erreur d'ouverture du fichier <<"+ nomFichier +">>");
    else{
         int nbEspaces = 0;
         *nbreColonnes = 0, *nbreLignes = 0;
         QTextStream  flux(&fichier);
         QString uneLigne;
         while( ! (uneLigne = flux.readLine()).isEmpty() )
              {
               (*nbreLignes)++;
               if((*nbreLignes) == 1){
                                      int longueurLigne=uneLigne.length();
                                      for(int i=0; i<longueurLigne; i++)
                                      if(uneLigne.at(i) == QChar(' '))
                                          nbEspaces++;
                                      *nbreColonnes = nbEspaces+1;
                                     }
              }
         fichier.close();
         }
 }

QString** TableauDeSaisie::creerTableau(int nbreLignes,int nbreColonnes){
  QString** t = NULL;
  t = new QString*[nbreLignes];
  for(int i=0; i<nbreLignes; i++)
       t[i] = new QString[nbreColonnes];
return t;
}

void TableauDeSaisie::stockDonneesFichierDansTableau(const QString nomFichier,QString*** t ,int* nbreLignes,int* nbreColonnes){
   QFile fichier(nomFichier);
   if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
      QMessageBox::critical(NULL,"ERREUR","Erreur d'ouverture du fichier <<"+ nomFichier +">>");

   else{
        nbreColonnesLignesFichier(nomFichier,nbreLignes,nbreColonnes);
        *t = creerTableau(*nbreLignes,*nbreColonnes);
      //Saisie des éléments du fichier dans le tableau
        QTextStream  flux(&fichier);
        for(int i=0; i<*nbreLignes; i++)
            for(int j=0; j<*nbreColonnes; j++)
                flux >> (*t)[i][j];
        fichier.close();
       }
}

void TableauDeSaisie::clicValider(){

    stocketDonneesSaisieDansFichier("données.txt");

    int nbreColonnes = 0, nbreLignes = 0;
    QString **t=NULL;
    stockDonneesFichierDansTableau("données.txt",&t ,&nbreLignes,&nbreColonnes);
    *modelRecu = new QStandardItemModel(nbreLignes,nbreColonnes);
    vueRecu->setModel(*modelRecu);
    for(int i=0;i<nbreLignes;i++)
        for(int j=0;j<nbreColonnes;j++)
            (*modelRecu)->setItem(i,j, new QStandardItem("     "+t[i][j]));
    this->close();
}

