#include "TableauDeVotes.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QStandardItem>

TableauDeVotes::TableauDeVotes(int nbreLignes, int nbreColonnes) : QDialog(){

    this->setWindowTitle("TABLEAU DE VOTES DES METHODES");
    this->setMinimumWidth(975);
    this->setMinimumHeight((nbreLignes+3)*50);
    this->setFont(QFont("Comic Sans MS",10));

    VBoxLayoute = new QVBoxLayout(this);

    HBoxLayouteHaut = new QHBoxLayout;

    tableView = new QTableView();
    tableView->setSpan(0,0,2,1);
    tableView->setSpan(0,1,1,2);
    tableView->setSpan(0,3,1,2);
    tableView->setSpan(0,5,1,2);
    tableView->setSpan(0,7,1,2);
    HBoxLayouteHaut->addWidget(tableView);
    nombreDeLignesView = nbreLignes+3;
    standardItemModel = new QStandardItemModel(nombreDeLignesView,nbreColonnes);
    tableView->setModel(standardItemModel);

    standardItemModel->setItem(0,0, new QStandardItem("Testes"));
    standardItemModel->setItem(0,1, new QStandardItem("FIFO"));
    standardItemModel->setItem(0,3, new QStandardItem("TOURNIQUET"));
    standardItemModel->setItem(0,5, new QStandardItem("PCTE"));
    standardItemModel->setItem(0,7, new QStandardItem("PGP"));
    for(int j=1;j<=8;j++)
        if(j%2 == 0)
            standardItemModel->setItem(1,j, new QStandardItem("    Notes"));
        else
            standardItemModel->setItem(1,j, new QStandardItem("    Ta.Moyen"));
        for(int i=1;i<=nbreLignes;i++)
            standardItemModel->setItem(i+1,0, new QStandardItem("   Teste "+QString::number(i)));

        standardItemModel->setItem(nbreLignes+2,0, new QStandardItem("Note totale"));

    HBoxLayoute = new QHBoxLayout;
    HBoxLayoute->setAlignment(Qt::AlignRight);
    ok = new QPushButton("&Ok");
    HBoxLayoute->addWidget(ok);

    HBoxLayoute1 = new QHBoxLayout;
    HBoxLayoute1->setAlignment(Qt::AlignCenter);
    label = new QLabel;
    HBoxLayoute1->addWidget(label);

    VBoxLayoute->addLayout(HBoxLayouteHaut);
    VBoxLayoute->addLayout(HBoxLayoute1);
    VBoxLayoute->addLayout(HBoxLayoute);

    chargerTableauDeVotes();

    QObject::connect(ok,SIGNAL(clicked()),this,SLOT(clicOk()));

}


void TableauDeVotes::nbreColonnesLignesFichier(const QString nomFichier,int* nbreLignes,int* nbreColonnes){
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

QString** TableauDeVotes::creerTableau(int nbreLignes,int nbreColonnes){
  QString** t = NULL;
  t = new QString*[nbreLignes];
  for(int i=0; i<nbreLignes; i++)
       t[i] = new QString[nbreColonnes];
return t;
}


void TableauDeVotes::stockDonneesFichierDansTableau(const QString nomFichier,QString*** t ,int* nbreLignes,int* nbreColonnes){
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

void TableauDeVotes::chargerTableauDeVotes(){
   int nbreColonnes = 0, nbreLignes = 0;
   QString **t=NULL;
   stockDonneesFichierDansTableau("fichierVotes",&t ,&nbreLignes,&nbreColonnes);
   int k = 2;
   for(int i=1;i<nbreLignes;i++)
       if(i%2)
          {
           standardItemModel->setItem(k,1, new QStandardItem(t[i][0]));
           standardItemModel->setItem(k,3, new QStandardItem(t[i][1]));
           standardItemModel->setItem(k,5, new QStandardItem(t[i][2]));
           standardItemModel->setItem(k,7, new QStandardItem(t[i][3]));
           k++;
          }
    k = 2;
    for(int i=1;i<nbreLignes;i++)
           if(!(i%2))
              {
               standardItemModel->setItem(k,2, new QStandardItem(t[i][0]));
               standardItemModel->setItem(k,4, new QStandardItem(t[i][1]));
               standardItemModel->setItem(k,6, new QStandardItem(t[i][2]));
               standardItemModel->setItem(k,8, new QStandardItem(t[i][3]));
               k++;
              }
    int somme;
    k=2;
    for(int j = 0;j<nbreColonnes;j++)
        {
         somme = 0;
         for(int i = 1;i<nbreLignes;i++)
             if(!(i%2))
                 somme += t[i][j].toInt();
         standardItemModel->setItem(nombreDeLignesView - 1,k, new QStandardItem(QString::number(somme)));
         k += 2;
        }
    label->setText("La méthode la plus optimale est celle du <strong>"+methodePlusOptimale()+"</strong>");
}

QString TableauDeVotes::methodePlusOptimale(){
    int nbreColonnes = 0, nbreLignes = 0;
    QString **t=NULL;
    stockDonneesFichierDansTableau("fichierVotes",&t ,&nbreLignes,&nbreColonnes);
    int Jmax =0,max;
    for(int j=0;j<nbreColonnes;j++)
       {
        int somme = 0;
        for(int i=3;i<nbreLignes;i++)
            if(!(i%2))
                somme +=t[i][j].toInt();
        if(j==0)
            max = somme;
        else
            if(max<somme)
               {
                max = somme;
                Jmax = j;
               }
       }
return  t[0][Jmax];
}

void TableauDeVotes::clicOk(){
    this->close();
}
