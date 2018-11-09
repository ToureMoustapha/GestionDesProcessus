#include "TableauRecapitulatif.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QStandardItem>

TableauRecapitulatif::TableauRecapitulatif(int nbreLignes, int nbreColonnes) : QDialog(){

    this->setWindowTitle("TABLEAU RECAPITULATIF DE L'EXECUTION DES PROCESSUS");
    this->setMinimumWidth(975);
    this->setMinimumHeight(nbreLignes*47);
    this->setFont(QFont("Comic Sans MS",10));

    VBoxLayoute = new QVBoxLayout(this);

    HBoxLayouteHaut = new QHBoxLayout();

    tableView = new QTableView();
    tableView->setSpan(0,0,2,1);
    tableView->setSpan(0,1,1,2);
    tableView->setSpan(0,3,1,2);
    tableView->setSpan(0,5,1,2);
    tableView->setSpan(0,7,1,2);
    HBoxLayouteHaut->addWidget(tableView);
    standardItemModel = new QStandardItemModel(nbreLignes,nbreColonnes);
    tableView->setModel(standardItemModel);

    //chargerTableauRecapitulatif();

    HBoxLayoute = new QHBoxLayout();
    HBoxLayoute->setAlignment(Qt::AlignRight);
    ok = new QPushButton("&Ok");
    HBoxLayoute->addWidget(ok);

    VBoxLayoute->addLayout(HBoxLayouteHaut);
    VBoxLayoute->addLayout(HBoxLayoute);

    chargerTableauRecapitulatif();

    QObject::connect(ok,SIGNAL(clicked()),this,SLOT(clicOk()));

}

void TableauRecapitulatif::nbreColonnesLignesFichier(const QString nomFichier,int* nbreLignes,int* nbreColonnes){
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

QString** TableauRecapitulatif::creerTableau(int nbreLignes,int nbreColonnes){
  QString** t = NULL;
  t = new QString*[nbreLignes];
  for(int i=0; i<nbreLignes; i++)
       t[i] = new QString[nbreColonnes];
return t;
}


void TableauRecapitulatif::stockDonneesFichierDansTableau(const QString nomFichier,QString*** t ,int* nbreLignes,int* nbreColonnes){
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

QString TableauRecapitulatif::tempsDattenteSysteme(QString chaine,QString nomFichier){
    int nbreColonnes = 0, nbreLignes = 0;
    QString **t=NULL;
    stockDonneesFichierDansTableau(nomFichier,&t ,&nbreLignes,&nbreColonnes);
    int j=0;
    while( j<nbreColonnes && t[0][j].compare(chaine,Qt::CaseInsensitive) )
          j++;
return t[1][j];
}

QString TableauRecapitulatif::tempsDattenteQueue(QString chaine,QString nomFichier){
    int nbreColonnes = 0, nbreLignes = 0;
    QString **t=NULL;
    stockDonneesFichierDansTableau(nomFichier,&t ,&nbreLignes,&nbreColonnes);
    int j=0;
    while( j<nbreColonnes && t[0][j].compare(chaine,Qt::CaseInsensitive) )
          j++;
return t[2][j];
}


void TableauRecapitulatif::chargerTableauRecapitulatif(){

   standardItemModel->setItem(0,1, new QStandardItem("                     FIFO"));
   standardItemModel->setItem(0,3, new QStandardItem("                 TOURNIQUET"));
   standardItemModel->setItem(0,5, new QStandardItem("                     PCTE"));
   standardItemModel->setItem(0,7, new QStandardItem("                     PGP"));

   for(int j=1;j<=8;j++)
       if(j%2 == 0)
           standardItemModel->setItem(1,j, new QStandardItem("   Ta.Queue"));
       else
           standardItemModel->setItem(1,j, new QStandardItem("    Ta.Sys"));

   int nbreColonnes = 0, nbreLignes = 0;
   QString **t=NULL;
   stockDonneesFichierDansTableau("données.txt",&t ,&nbreLignes,&nbreColonnes);

   standardItemModel->setItem(0,0, new QStandardItem(" "+t[0][0]));

   for(int i=1;i<nbreLignes;i++)
       standardItemModel->setItem(i+1,0, new QStandardItem("       "+t[i][0]));

   for(int i=1;i<nbreLignes;i++)
      {
       standardItemModel->setItem(i+1,1, new QStandardItem("           "+tempsDattenteSysteme(t[i][0],"tempsDattenteSystemeEtQueueFifo")));
       standardItemModel->setItem(i+1,2, new QStandardItem("           "+tempsDattenteQueue(t[i][0],"tempsDattenteSystemeEtQueueFifo")));
       standardItemModel->setItem(i+1,3, new QStandardItem("           "+tempsDattenteSysteme(t[i][0],"tempsDattenteSystemeEtQueueTourniquet")));
       standardItemModel->setItem(i+1,4, new QStandardItem("           "+tempsDattenteQueue(t[i][0],"tempsDattenteSystemeEtQueueTourniquet")));
       standardItemModel->setItem(i+1,5, new QStandardItem("           "+tempsDattenteSysteme(t[i][0],"tempsDattenteSystemeEtQueuePcte")));
       standardItemModel->setItem(i+1,6, new QStandardItem("           "+tempsDattenteQueue(t[i][0],"tempsDattenteSystemeEtQueuePcte")));
       standardItemModel->setItem(i+1,7, new QStandardItem("           "+tempsDattenteSysteme(t[i][0],"tempsDattenteSystemeEtQueuePgp")));
       standardItemModel->setItem(i+1,8, new QStandardItem("           "+tempsDattenteQueue(t[i][0],"tempsDattenteSystemeEtQueuePgp")));
      }
}

void TableauRecapitulatif::clicOk(){
    this->close();
}



