#include "Chronogramme.h"
#include "TableauDeSaisie.h"
#include "TableauRecapitulatif.h"
#include "PlanDeDessin.h"
#include "TableauDeVotes.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QInputDialog>

Chronogramme::Chronogramme() : QDialog() {

    this->setMinimumWidth(width());
    this->setMinimumHeight(height());

//Zone centrale
    VBoxLayoutePrincipale = new QVBoxLayout(this);

  //Zone hausse
     HBoxLayouteHaut = new QHBoxLayout;

   //Zone hausse-gauche
     groupeBoxHaut = new QGroupBox("SAISIE DES DONNEES DES PROCESSUS");
     formLayouteHaut = new QFormLayout(groupeBoxHaut);
     nbreColonnes = new QSpinBox;
     nbreColonnes->setMinimum(1);
     nbreLignes = new QSpinBox;
     nbreLignes->setMinimum(1);
     HBoxLayouteGroupBoxHaut1 = new QHBoxLayout;
     HBoxLayouteGroupBoxHaut1->setAlignment(Qt::AlignRight);
     okHaut = new QPushButton("&Ok");
     annulerHaut = new QPushButton("&Annuler");
     HBoxLayouteGroupBoxHaut1->addWidget(okHaut);
     HBoxLayouteGroupBoxHaut1->addWidget(annulerHaut);
     HBoxLayouteGroupBoxHaut2 = new QHBoxLayout;
     HBoxLayouteGroupBoxHaut2->setAlignment(Qt::AlignLeft);
     joindreFichier = new QPushButton("Joindre Fichier");
     joindreFichier->setIcon(QIcon("fleche2.png"));;
     HBoxLayouteGroupBoxHaut2->addWidget(joindreFichier);
     formLayouteHaut->addRow("&Nombre de colonnes : ",nbreColonnes);
     formLayouteHaut->addRow("&Nombre de lignes : ",nbreLignes);
     formLayouteHaut->addRow(HBoxLayouteGroupBoxHaut1);
     formLayouteHaut->addRow(HBoxLayouteGroupBoxHaut2);

    //Zone hausse-droite
     groupeBoxHautDroite = new QGroupBox("DONNEES SAISIES");
     formLayouteHautDroite = new QFormLayout(groupeBoxHautDroite);
     tableView = new QTableView();
     formLayouteHautDroite->addRow(tableView);


     HBoxLayouteHaut->addWidget(groupeBoxHaut);
     HBoxLayouteHaut->addWidget(groupeBoxHautDroite);

    //Zone basse de l'interface
        HBoxLayouteBas = new QHBoxLayout;

        //Zone basse-gauche
        groupeBoxBasGauche = new QGroupBox("SIMULATION DE CHRONOGRAMME");
        groupeBoxBasGauche->setEnabled(false);
        formLayouteBasGauche = new QFormLayout(groupeBoxBasGauche);
        fifo = new QCheckBox("Fifo");
        tourniquet = new QCheckBox("Tourniquet");
        pcte = new QCheckBox("Pcte");
        pgp = new QCheckBox("Pgp");
        HBoxLayouteGroupeBoxBasGauche1 = new QHBoxLayout;
        recapitulatif = new QCheckBox("TABLEAU RECAPITULATIF");
        recapitulatif->setEnabled(false);
        HBoxLayouteGroupeBoxBasGauche1->addWidget(recapitulatif);
        HBoxLayouteGroupeBoxBasGauche2 = new QHBoxLayout;
        HBoxLayouteGroupeBoxBasGauche2->setAlignment(Qt::AlignRight);
        okBas = new QPushButton("Ok");
        annulerBas = new QPushButton("Annuler");
        HBoxLayouteGroupeBoxBasGauche2->addWidget(okBas);
        HBoxLayouteGroupeBoxBasGauche2->addWidget(annulerBas);
        formLayouteBasGauche->addRow(fifo);
        formLayouteBasGauche->addRow(tourniquet);
        formLayouteBasGauche->addRow(pcte);
        formLayouteBasGauche->addRow(pgp);
        formLayouteBasGauche->addRow(HBoxLayouteGroupeBoxBasGauche1);
        formLayouteBasGauche->addRow(HBoxLayouteGroupeBoxBasGauche2);

        //Zone basse-droite
        groupeBoxBasDroite = new QGroupBox("CLASSEMENT DES METHODES D'EXECUTION DES PRECESSUS");
        formLayouteBasDroite = new QFormLayout(groupeBoxBasDroite);
        classement = new QCheckBox("Faire classement des méthodes");
        nbreTestes = new QSpinBox;
        nbreTestes->setMinimum(1);
        HBoxLayouteGroupeBoxBasDroite = new QHBoxLayout;
        HBoxLayouteGroupeBoxBasDroite->setAlignment(Qt::AlignRight);
        okBasDroite = new QPushButton("Ok");
        annulerBasDroite = new QPushButton("Annuler");
        HBoxLayouteGroupeBoxBasDroite->addWidget(okBasDroite);
        HBoxLayouteGroupeBoxBasDroite->addWidget(annulerBasDroite);
        HBoxLayouteGroupeBoxBasDroite1 = new QHBoxLayout;
        HBoxLayouteGroupeBoxBasDroite1->setAlignment(Qt::AlignCenter);
        afficherMethodePlusOptimale = new QPushButton("Afficher méthode plus optimale");
        afficherMethodePlusOptimale->setEnabled(false);
        HBoxLayouteGroupeBoxBasDroite1->addWidget(afficherMethodePlusOptimale);

        formLayouteBasDroite->addRow(classement);
        formLayouteBasDroite->addRow("Nombre de testes",nbreTestes);
        formLayouteBasDroite->addRow(HBoxLayouteGroupeBoxBasDroite);
        formLayouteBasDroite->addRow(HBoxLayouteGroupeBoxBasDroite1);

   HBoxLayouteBas->addWidget(groupeBoxBasGauche);
   HBoxLayouteBas->addWidget(groupeBoxBasDroite);

 VBoxLayoutePrincipale->addLayout(HBoxLayouteHaut);
 VBoxLayoutePrincipale->addLayout(HBoxLayouteBas);

 cocherFifo       = false;
 cocherTourniquet = false;
 cocherPcte       = false;
 cocherPgp        = false;

 autoriserATester = false;

 QObject::connect(okHaut,SIGNAL(clicked()),this,SLOT(clicOkHaut()));
 QObject::connect(annulerHaut,SIGNAL(clicked()),this,SLOT(clicAnnulerHaut()));
 QObject::connect(joindreFichier,SIGNAL(clicked()),this,SLOT(clicJoindreFichier()));
 QObject::connect(okBas,SIGNAL(clicked()),this,SLOT(clicOkBas()));
 QObject::connect(annulerBas,SIGNAL(clicked()),this,SLOT(clicAnnulerBas()));
 QObject::connect(okBasDroite,SIGNAL(clicked()),this,SLOT(clicOkBasDroite()));
 QObject::connect(annulerBasDroite,SIGNAL(clicked()),this,SLOT(clicAnnulerBasDroite()));
 QObject::connect(afficherMethodePlusOptimale,SIGNAL(clicked()),this,SLOT(clicAfficherMethodePlusOptimale()));

}

void Chronogramme::nbreColonnesLignesFichier(const QString nomFichier,int* nbreLignes,int* nbreColonnes){
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

QString** Chronogramme::creerTableau(int nbreLignes,int nbreColonnes){
  QString** t = NULL;
  t = new QString*[nbreLignes];
  for(int i=0; i<nbreLignes; i++)
       t[i] = new QString[nbreColonnes];
return t;
}

void Chronogramme::stockDonneesFichierDansTableau(const QString nomFichier,QString*** t ,int* nbreLignes,int* nbreColonnes){
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

void Chronogramme::stockDonneesTableauDansFichier(QString** t,int nbreLignes,int nbreColonnes,const QString nomFichier){
    QFile fichier(nomFichier);
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
       QMessageBox::critical(NULL,"ERREUR","Erreur d'ouverture du fichier <<"+ nomFichier +">>");
    else{
         QTextStream flux(&fichier);
         for(int i=0; i<nbreLignes; i++){
                                     QString ligne = "";
                                     for(int j=0; j<nbreColonnes; j++)
                                         if(j != nbreColonnes - 1)
                                             ligne += t[i][j] + " ";
                                         else
                                             ligne += t[i][j];
                                     flux << ligne << endl;
                                    }
         fichier.close();
       }
}

void Chronogramme::croissantSuivantColonne2(QString** t,int nbreLignes,int nbreColonnes){
    for(int i=1;i<nbreLignes;i++)
        for(int k=i+1;k<nbreLignes;k++)
            if( t[k][1].toInt() < t[i][1].toInt() ){
                                                    int compteur = 0;
                                                    QString temp = "";
                                                    while(compteur < nbreColonnes){
                                                                                   temp = t[i][compteur];
                                                                                   t[i][compteur] = t[k][compteur];
                                                                                   t[k][compteur] = temp;
                                                                                   compteur++;
                                                                                  }
                                                   }
}

void Chronogramme::croissantSuivantColonne3(QString** t,int nbreLignes,int nbreColonnes){
    croissantSuivantColonne2(t,nbreLignes,nbreColonnes);
    for(int i=1;i<nbreLignes;i++)
        for(int k=i+1;k<nbreLignes;k++)
            if( t[k][1].toInt() == t[i][1].toInt() && t[k][2].toInt() < t[i][2].toInt() )
               {
                int compteur = 0;
                QString temp = "";
                while(compteur < nbreColonnes){
                                               temp = t[i][compteur];
                                               t[i][compteur] = t[k][compteur];
                                               t[k][compteur] = temp;
                                               compteur++;
                                              }
               }
}

int Chronogramme::positionProcessus(QString chaine,QString** tPosOrigine,int nbreColonnes){
    int j=0;
    while( j<nbreColonnes && tPosOrigine[0][j].compare(chaine,Qt::CaseInsensitive) )
          j++;
return j+1;
}

void Chronogramme::reparerPositionProcessus(QString**t,QString** tPosOrigine,int nbreLignes,int nbreColonnes){
    for(int i=0;i<nbreColonnes;i++)
        for(int k=i+1;k<nbreColonnes;k++)
            if( t[k][3].toInt() == t[i][3].toInt() && positionProcessus(t[k][0],tPosOrigine,nbreColonnes - 1) < positionProcessus(t[i][0],tPosOrigine,nbreColonnes - 1))
            {
             int compteur = 0;
             QString temp = "";
             while(compteur < nbreColonnes){
                                            temp = t[i][compteur];
                                            t[i][compteur] = t[k][compteur];
                                            t[k][compteur] = temp;
                                            compteur++;
                                           }
            }
}

QString** Chronogramme::creerTabPosOrigine(QString** t,int nbreLignes){
    QString** tPosOrigine = creerTableau(2,nbreLignes-1);
    for(int i=1;i<nbreLignes;i++)
        {
         tPosOrigine[0][i-1] = t[i][0];
         tPosOrigine[1][i-1] =QString::number(i);
        }
 return tPosOrigine;
}

void Chronogramme::croissantSuivantColonne4(QString** t,int nbreLignes,int nbreColonnes){
    croissantSuivantColonne2(t,nbreLignes,nbreColonnes);
    for(int i=1;i<nbreLignes;i++)
        for(int k=i+1;k<nbreLignes;k++)
            if( t[k][1].toInt() == t[i][1].toInt() && t[k][3].toInt() >= t[i][3].toInt() )
               {
                int compteur = 0;
                QString temp ;
                while( compteur < nbreColonnes ){
                                                 temp = t[i][compteur];
                                                 t[i][compteur] = t[k][compteur];
                                                 t[k][compteur] = temp;
                                                 compteur++;
                                                }
               }
}

void Chronogramme::diagrammeGanttFifo(QString** t,int nbreLignes,int nbreColonnes,const QString nomFichier){
   croissantSuivantColonne2(t,nbreLignes,nbreColonnes);
   QString** tabGantt = creerTableau(2,nbreLignes-1);
   for(int i=1;i<nbreLignes;i++)
       if(i==1){
                tabGantt[0][0] = t[1][0];
                tabGantt[1][0] =QString::number( t[1][1].toInt()+t[1][2].toInt() );
               }
       else{
            tabGantt[0][i-1] = t[i][0];
            int n;
            /*if(t[i][1].toInt()>tabGantt[1][i-2].toInt())
                n = t[i][1].toInt() + t[i][2].toInt();
            else */
                n = tabGantt[1][i-2].toInt() + t[i][2].toInt();
            tabGantt[1][i-1] = QString::number(n);
           }
      stockDonneesTableauDansFichier(tabGantt,2,nbreLignes-1,nomFichier);
}

void Chronogramme::diagrammeGanttPcte(QString** t,int nbreLignes,int nbreColonnes,const QString nomFichier){
   croissantSuivantColonne3(t,nbreLignes,nbreColonnes);
   QString ** tabGantt = creerTableau(2,nbreLignes-1);
   for(int i=1;i<nbreLignes;i++)
       if(i==1){
                tabGantt[0][0] = t[1][0];
                tabGantt[1][0] = t[1][2];QString::number( t[1][1].toInt()+t[1][2].toInt() );
               }
       else{
            tabGantt[0][i-1] = t[i][0];
            int n = tabGantt[1][i-2].toInt() + t[i][2].toInt();
            tabGantt[1][i-1] = QString::number(n);
           }
   stockDonneesTableauDansFichier(tabGantt,2,nbreLignes-1,nomFichier);
}

void Chronogramme::diagrammeGanttPgp(QString** t,int nbreLignes,int nbreColonnes,const QString nomFichier){
   QString** tabGantt = creerTableau(2,nbreLignes-1);
   QString** tPosOrigine = creerTabPosOrigine(t,nbreLignes);
   croissantSuivantColonne4(t,nbreLignes,nbreColonnes);
   reparerPositionProcessus(t,tPosOrigine,nbreLignes,nbreColonnes);
   for(int i=1;i<nbreLignes;i++)
       if(i==1){
                tabGantt[0][0] = t[1][0];
                tabGantt[1][0] = QString::number( t[1][1].toInt()+t[1][2].toInt() );
               }
       else{
            tabGantt[0][i-1] = t[i][0];
            int n = tabGantt[1][i-2].toInt() + t[i][2].toInt();
            tabGantt[1][i-1] = QString::number(n);
           }
   stockDonneesTableauDansFichier(tabGantt,2,nbreLignes-1,nomFichier);
}

QString** Chronogramme::creerTabTempsDexecution(QString** t,int nbreLignes){
    QString** tTemps = creerTableau(3,nbreLignes-1);
    for(int i=1;i<nbreLignes;i++)
        {
         tTemps[0][i-1] = t[i][0];
         tTemps[1][i-1] = t[i][2];
         tTemps[2][i-1] =QString::number(0);
        }
 return tTemps;
}

int Chronogramme::tempsDexecutionProcessus(QString chaine,QString** tTemps,int nbreColonnes){
    int j=0;
    while( j<nbreColonnes && tTemps[0][j].compare(chaine,Qt::CaseInsensitive) )
          j++;
return tTemps[1][j].toInt();
}

void Chronogramme::estSonTour(QString chaine,int q,QString** tTemps,int nbreColonnes){
    int j=0;
    while( j<nbreColonnes && tTemps[0][j].compare(chaine,Qt::CaseInsensitive) )
          j++;
    tTemps[1][j] = QString::number( tTemps[1][j].toInt() - q );
    tTemps[2][j] = QString::number(1);
}

QString Chronogramme::existeSuivant(QString** tTemps,int nbreColonnes){
    int j=0;
    while( j<nbreColonnes && tTemps[2][j].toInt() == 1 )
          j++;
    if( j < nbreColonnes)
        return tTemps[0][j];
    else{
         j=0;
         while( j<nbreColonnes && tTemps[1][j].toInt() == 0 )
               j++;
         if( j < nbreColonnes)
            {
             for(int i=0;i<nbreColonnes;i++)
                 if(tTemps[1][i].toInt() != 0)
                     tTemps[2][i] = QString::number(0);
             return existeSuivant(tTemps,nbreColonnes);
            }
         else
             return "";
        }
}

void Chronogramme::diagrammeGanttTourniquet(QString** t,int nbreLignes,int nbreColonnes,int q,const QString nomFichier){
    croissantSuivantColonne2(t,nbreLignes,nbreColonnes);
    QString** tTemps= creerTabTempsDexecution(t,nbreLignes);
    QFile fichier("fichierTemporaire");
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
       QMessageBox::critical(NULL,"ERREUR","Erreur d'ouverture du fichier <<temporaire>>");
    else{
         QTextStream flux(&fichier);
         QString chaine;
         while(!( (chaine = existeSuivant(tTemps,nbreLignes - 1)).isEmpty()) )
          {
           int n;
           if((n=tempsDexecutionProcessus(chaine,tTemps,nbreColonnes)) >= q)
              {
               estSonTour(chaine,q,tTemps,nbreColonnes);
               flux << chaine + " " + QString::number(q) << endl;
              }
           else{
                int resteq = q;
                while( resteq>0 && !(chaine = existeSuivant(tTemps,nbreLignes - 1)).isEmpty())
                    {
                     int n;
                     if((n=tempsDexecutionProcessus(chaine,tTemps,nbreColonnes)) >= resteq)
                        {
                         estSonTour(chaine,resteq,tTemps,nbreColonnes);
                         flux << chaine + " " + QString::number(resteq) << endl;
                         resteq = 0;
                         break;
                        }
                     else{
                          resteq -=n;
                          estSonTour(chaine,n,tTemps,nbreColonnes);
                          flux << chaine + " " + QString::number(n) << endl;
                         }
                    }
               }
        }
      fichier.close();
      int n,p;
      QString** tTempo = NULL;
      stockDonneesFichierDansTableau("fichierTemporaire",&tTempo,&n,&p);
      QFile fichier(nomFichier);
      if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
         QMessageBox::critical(NULL,"ERREUR","Erreur d'ouverture du fichier <<" + nomFichier + ">>");
      else{
           QTextStream flux(&fichier);

           for(int i=0;i<n;i++)
               if(i != n - 1)
                  flux << tTempo[i][0] + " ";
               else
                   flux << tTempo[i][0] <<endl;

               QString** tDonnees = NULL;
               int nbreLignesDonnees,nbreColonnesDonnees;
               stockDonneesFichierDansTableau("données.txt",&tDonnees ,&nbreLignesDonnees,&nbreColonnesDonnees);
               int indice = 1;
               while(indice<nbreLignesDonnees && tTempo[0][0].compare(tDonnees[indice][0]))
                     indice++;

           for(int i=0;i<n;i++)
               if(i != n - 1)
                  if( i == 0)
                      flux <<QString::number(tDonnees[indice][1].toInt()+tTempo[i][1].toInt()) + " ";//
                  else{
                       int k = 0,somprecedent = 0;
                       while( k < i)
                           if(k==0)
                            somprecedent += tTempo[k++][1].toInt();//
                           else
                            somprecedent += tTempo[k++][1].toInt();
                       flux << QString::number(tTempo[i][1].toInt() + somprecedent ) + " ";
                      }
               else
                   if( i == 0)
                      flux << QString::number(tDonnees[indice][1].toInt()+tTempo[i][1].toInt()) <<endl;
                   else{
                        int k = 0,somprecedent = 0;
                        while( k < i)
                            if(k==0)
                             somprecedent += tTempo[k++][1].toInt() - tDonnees[indice][1].toInt();//
                            else
                             somprecedent += tTempo[k++][1].toInt();
                        somprecedent +=tDonnees[indice][1].toInt();
                        flux << QString::number(tTempo[i][1].toInt() + somprecedent ) + " ";
                       }

           fichier.close();
          }
     }
}

QString Chronogramme::calculTempsDattenteSysteme(QString nomProcessus,const QString nomFichier){
    QString** t = NULL;
    int nbreLignes,nbreColonnes;
    stockDonneesFichierDansTableau("données.txt",&t ,&nbreLignes,&nbreColonnes);
    int k = 1;
    while(k < nbreLignes && t[k][0].compare(nomProcessus,Qt::CaseInsensitive) )
          k++;

    QString** tabGantt = NULL;
    int nbreLignesGantt,nbreColonnesGantt;
    stockDonneesFichierDansTableau(nomFichier,&tabGantt ,&nbreLignesGantt,&nbreColonnesGantt);//ici nbreLignes = 2;
    int j = nbreColonnesGantt - 1;
    while(j >= 0 && tabGantt[0][j].compare(nomProcessus,Qt::CaseInsensitive) )
          j--;

    return  QString::number( tabGantt[1][j].toInt() - t[k][1].toInt() );
}

QString Chronogramme::calculTempsDattenteQueue(QString nomProcessus,const QString nomFichier){
    QString** t = NULL;
    int nbreLignes,nbreColonnes;
    stockDonneesFichierDansTableau("données.txt",&t ,&nbreLignes,&nbreColonnes);
    int k = 1;
    while(k < nbreLignes && t[k][0].compare(nomProcessus,Qt::CaseInsensitive) )
          k++;

    QString** tabGantt = NULL;
    int nbreLignesGantt,nbreColonnesGantt;
    stockDonneesFichierDansTableau(nomFichier,&tabGantt ,&nbreLignesGantt,&nbreColonnesGantt);//ici nbreLignes = 2;
    int j = nbreColonnesGantt - 1;
    while(j >= 0 && tabGantt[0][j].compare(nomProcessus,Qt::CaseInsensitive) )
          j--;

    return  QString::number( tabGantt[1][j].toInt() - t[k][2].toInt() - t[k][1].toInt() );

}

void Chronogramme::stockageTempsDattenteSystemeEtQueueSansRequisitionDansFichier(QString const nomFichier,const QString nomFichierGantt){
    QString** t = NULL;
    int nbreLignes,nbreColonnes;
    stockDonneesFichierDansTableau(nomFichierGantt,&t ,&nbreLignes,&nbreColonnes);
    QFile fichier("fichierTemporaire");
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
       QMessageBox::critical(NULL,"ERREUR","Erreur d'ouverture du fichier <<" + nomFichier + ">>");
    else{
         QTextStream flux(&fichier);
         for(int i=0;i<nbreColonnes;i++)
             if( i != nbreColonnes - 1 )
                flux << t[0][i] + " " + calculTempsDattenteSysteme(t[0][i],nomFichierGantt) + " " + calculTempsDattenteQueue(t[0][i],nomFichierGantt) << endl;
             else
                 flux << t[0][i] + " " + calculTempsDattenteSysteme(t[0][i],nomFichierGantt) + " " + calculTempsDattenteQueue(t[0][i],nomFichierGantt);
         fichier.close();
         int n,p;
         QString** tTempo = NULL;
         stockDonneesFichierDansTableau("fichierTemporaire",&tTempo,&n,&p);
         QFile fichier(nomFichier);
         if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
            QMessageBox::critical(NULL,"ERREUR","Erreur d'ouverture du fichier <<" + nomFichier + ">>");
         else{
              QTextStream flux(&fichier);
              for(int i=0;i<n;i++)
                  if(i != n - 1)
                     flux << tTempo[i][0] + " ";
                  else
                      flux << tTempo[i][0] <<endl;

              for(int i=0;i<n;i++)
                  if(i != n - 1)
                     flux << tTempo[i][1] + " ";
                  else
                      flux << tTempo[i][1] <<endl;

              for(int i=0;i<n;i++)
                  if(i != n - 1)
                     flux << tTempo[i][2] + " ";
                  else
                     flux << tTempo[i][2] <<endl;
              fichier.close();
             }
        }
}

void Chronogramme::stockageTempsDattenteSystemeEtQueueAvecRequisitionDansFichier(QString const nomFichier,const QString nomFichierGantt){
    QString** t = NULL;
    int nbreLignes,nbreColonnes;
    stockDonneesFichierDansTableau("données.txt",&t ,&nbreLignes,&nbreColonnes);
    QFile fichier("fichierTemporaire");
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
       QMessageBox::critical(NULL,"ERREUR","Erreur d'ouverture du fichier <<" + nomFichier + ">>");
    else{
         QTextStream flux(&fichier);
         for(int i=1;i<nbreLignes;i++)
             if( i != nbreLignes - 1 )
                flux << t[i][0] + " " + calculTempsDattenteSysteme(t[i][0],nomFichierGantt) + " " + calculTempsDattenteQueue(t[i][0],nomFichierGantt) << endl;
             else
                 flux << t[i][0] + " " + calculTempsDattenteSysteme(t[i][0],nomFichierGantt) + " " + calculTempsDattenteQueue(t[i][0],nomFichierGantt);
         fichier.close();
         int n,p;
         QString** tTempo = NULL;
         stockDonneesFichierDansTableau("fichierTemporaire",&tTempo,&n,&p);
         QFile fichier(nomFichier);
         if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
            QMessageBox::critical(NULL,"ERREUR","Erreur d'ouverture du fichier <<" + nomFichier + ">>");
         else{
              QTextStream flux(&fichier);
              for(int i=0;i<n;i++)
                  if(i != n - 1)
                     flux << tTempo[i][0] + " ";
                  else
                      flux << tTempo[i][0] <<endl;

              for(int i=0;i<n;i++)
                  if(i != n - 1)
                     flux << tTempo[i][1] + " ";
                  else
                      flux << tTempo[i][1] <<endl;

              for(int i=0;i<n;i++)
                  if(i != n - 1)
                     flux << tTempo[i][2] + " ";
                  else
                     flux << tTempo[i][2] <<endl;
              fichier.close();
             }
        }
}

QString Chronogramme::calculTempsDattenteMoyen(QString nomFichier){
    int nbreColonnes = 0, nbreLignes = 0;
    QString **t=NULL;
    stockDonneesFichierDansTableau(nomFichier,&t ,&nbreLignes,&nbreColonnes);
    int somme = 0;
    for(int j = 0;j<nbreColonnes;j++)
        somme += t[2][j].toInt();
return QString::number((double)somme/nbreColonnes);
}

void Chronogramme::ordreCroissantSuivantTempsDattenteMoyen(QString** t,int nbreLignes,int nbreColonnes){
    for(int j = 0;j<nbreColonnes-1;j++)
        for(int k=j+1;k<nbreColonnes;k++)
           if(t[1][j]>t[1][k])
              {
               int compteur = 0;
               QString temp ;
               while( compteur < nbreLignes )
                     {
                      temp = t[compteur][j];
                      t[compteur][j] = t[compteur][k];
                      t[compteur][k] = temp;
                      compteur++;
                     }
              }
}

void Chronogramme::rangerSuivantNomDesMethodes(QString** t,int nbreLignes,int nbreColonnes){
    QString tabNomFichier[4]={"Fifo","Tourniquet","Pcte","Pgp"};
    for(int j=0;j<3;j++)
        {
         int k = j+1;
         while( k<nbreColonnes && tabNomFichier[j].compare(t[0][k]) )
                k++;
         if(k<nbreColonnes)
            {
             int compteur = 0;
             QString temp ;
             while( compteur < nbreLignes )
                   {
                    temp = t[compteur][j];
                    t[compteur][j] = t[compteur][k];
                    t[compteur][k] = temp;
                    compteur++;
                   }
            }
         }
}

void Chronogramme::votesDesMethodes(){
    int nbreColonnes = 0, nbreLignes = 0;
    QString **t=NULL;
    stockDonneesFichierDansTableau("données.txt",&t ,&nbreLignes,&nbreColonnes);

    diagrammeGanttFifo(t,nbreLignes,nbreColonnes,"diagrammeGanttFifo");
    stockageTempsDattenteSystemeEtQueueSansRequisitionDansFichier("tempsDattenteSystemeEtQueueFifo","diagrammeGanttFifo");

    diagrammeGanttTourniquet(t,nbreLignes,nbreColonnes,2,"diagrammeGanttTourniquet");
    stockageTempsDattenteSystemeEtQueueAvecRequisitionDansFichier("tempsDattenteSystemeEtQueueTourniquet","diagrammeGanttTourniquet");

    diagrammeGanttPcte(t,nbreLignes,nbreColonnes,"diagrammeGanttPcte");
    stockageTempsDattenteSystemeEtQueueSansRequisitionDansFichier("tempsDattenteSystemeEtQueuePcte","diagrammeGanttPcte");

    diagrammeGanttPgp(t,nbreLignes,nbreColonnes,"diagrammeGanttPgp");
    stockageTempsDattenteSystemeEtQueueSansRequisitionDansFichier("tempsDattenteSystemeEtQueuePgp","diagrammeGanttPgp");

    QFile fichier("fichierVotes");
    if(!fichier.open(QIODevice::Append | QIODevice::Text))
       QMessageBox::critical(NULL,"ERREUR","Erreur d'ouverture du fichier <<fichierVotes>>");
    else{
         QTextStream flux(&fichier);

         QString tabNomFichier[4]={"tempsDattenteSystemeEtQueueFifo","tempsDattenteSystemeEtQueueTourniquet","tempsDattenteSystemeEtQueuePcte","tempsDattenteSystemeEtQueuePgp"};
         QString** tabDattenteEtVotes = creerTableau(3,4);
         tabDattenteEtVotes[0][0] = "Fifo";
         tabDattenteEtVotes[0][1] = "Tourniquet";
         tabDattenteEtVotes[0][2] = "Pcte";
         tabDattenteEtVotes[0][3] = "Pgp";

         for(int j=0;j<4;j++)
             tabDattenteEtVotes[1][j] = calculTempsDattenteMoyen(tabNomFichier[j]);

         ordreCroissantSuivantTempsDattenteMoyen(tabDattenteEtVotes,3,4);

         for(int j=0;j<4;j++)
             tabDattenteEtVotes[2][j] = QString::number(4-j);

         rangerSuivantNomDesMethodes(tabDattenteEtVotes,3,4);

         for(int j=0;j<4;j++)
             for(int k=j+1;k<4;k++)
                 if(tabDattenteEtVotes[1][j]==tabDattenteEtVotes[1][k])
                     tabDattenteEtVotes[2][k] = tabDattenteEtVotes[2][j];

         for(int i=1;i<3;i++)
             for(int j=0;j<4;j++)
                 if(j!=3)
                   flux << tabDattenteEtVotes[i][j] + " ";
                 else
                   flux << tabDattenteEtVotes[i][j] << endl;

         fichier.close();
        }
}

void Chronogramme::clicOkHaut(){
    nbreLignesFifchierDonnees = nbreLignes->value();
    nbreColonnesFichierDonnees = nbreColonnes->value();
    TableauDeSaisie    fenetre(nbreLignesFifchierDonnees,nbreColonnesFichierDonnees,&standardItemModel,tableView);
    fenetre.exec();
    if(standardItemModel)
       groupeBoxBasGauche->setEnabled(true);
}

void Chronogramme::clicAnnulerHaut(){
    nbreLignes->setValue(0);
    nbreColonnes->setValue(0);
}

void Chronogramme::clicJoindreFichier(){
QString cheminFichierOuvert = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Text(*.txt)");
if(cheminFichierOuvert.isEmpty())
    QMessageBox::information(NULL,"ATTENTION","Aucun fichier n'a été choisi");
 else{
      QString** t = NULL;
      int nbreLignes,nbreColonnes;
      stockDonneesFichierDansTableau(cheminFichierOuvert,&t ,&nbreLignes,&nbreColonnes);
      stockDonneesTableauDansFichier(t,nbreLignes,nbreColonnes,"données.txt");
      standardItemModel = new QStandardItemModel(nbreLignes,nbreColonnes);
      tableView->setModel(standardItemModel);
      for(int i=0;i<nbreLignes;i++)
         for(int j=0;j<nbreColonnes;j++)
             (standardItemModel)->setItem(i,j, new QStandardItem("     "+t[i][j]));
      groupeBoxBasGauche->setEnabled(true);
      recapitulatif->setEnabled(false);
      if(autoriserATester && nombreDeTestes)
         {
           votesDesMethodes();
           nombreDeTestes--;
           if(!nombreDeTestes)
              {
               autoriserATester = false;
               afficherMethodePlusOptimale->setEnabled(true);
              }
         }
     }
}

void Chronogramme::clicOkBas(){
    if(recapitulatif->isChecked())
       {
        TableauRecapitulatif   fenetre(nbreLignesFifchierDonnees+2,9);
        fenetre.setModal(false);
        fenetre.exec();
       }
    else{
         if(!fifo->isChecked() && !tourniquet->isChecked() && !pcte->isChecked() && !pgp->isChecked())
            QMessageBox::critical(this,"ERREUR","Aucune méthode n'a été choisie\nVeuillez choisir une au moins");
         else{
              int nbreColonnes = 0, nbreLignes = 0;
              QString **t=NULL;
              stockDonneesFichierDansTableau("données.txt",&t ,&nbreLignes,&nbreColonnes);
              if(fifo->isChecked())
                 {
                  cocherFifo = true;
                  diagrammeGanttFifo(t,nbreLignes,nbreColonnes,"diagrammeGanttFifo");
                  stockageTempsDattenteSystemeEtQueueSansRequisitionDansFichier("tempsDattenteSystemeEtQueueFifo","diagrammeGanttFifo");
                  PlanDeDessin fenetre("diagrammeGanttFifo");
                  fenetre.setModal(false);
                  fenetre.exec();
                 }

              if(tourniquet->isChecked())
                 {
                  cocherTourniquet = true;
                  int entier = QInputDialog::getInteger(this, "Quntum", "Donner le quntume");
                  diagrammeGanttTourniquet(t,nbreLignes,nbreColonnes,entier,"diagrammeGanttTourniquet");
                  stockageTempsDattenteSystemeEtQueueAvecRequisitionDansFichier("tempsDattenteSystemeEtQueueTourniquet","diagrammeGanttTourniquet");
                  PlanDeDessin fenetre("diagrammeGanttTourniquet");
                  fenetre.setModal(false);
                  fenetre.exec();
                 }

              if(pcte->isChecked())
                 {
                  cocherPcte = true;
                  diagrammeGanttPcte(t,nbreLignes,nbreColonnes,"diagrammeGanttPcte");
                  stockageTempsDattenteSystemeEtQueueSansRequisitionDansFichier("tempsDattenteSystemeEtQueuePcte","diagrammeGanttPcte");
                  PlanDeDessin fenetre("diagrammeGanttPcte");
                  fenetre.setModal(false);
                  fenetre.exec();
                 }

              if(pgp->isChecked())
                {
                 this->cocherPgp = true;
                 diagrammeGanttPgp(t,nbreLignes,nbreColonnes,"diagrammeGanttPgp");
                 stockageTempsDattenteSystemeEtQueueSansRequisitionDansFichier("tempsDattenteSystemeEtQueuePgp","diagrammeGanttPgp");
                 PlanDeDessin fenetre("diagrammeGanttPgp");
                 fenetre.setModal(false);
                 fenetre.exec();
                }
              if(this->cocherFifo && this->cocherTourniquet && this->cocherPcte && this->cocherPgp)
                 recapitulatif->setEnabled(true);
             }
        }
}

void Chronogramme::clicAnnulerBas(){
    fifo->setChecked(false);
    tourniquet->setChecked(false);
    pcte->setChecked(false);
    pgp->setChecked(false);
    recapitulatif->setChecked(false);
}

void Chronogramme::clicOkBasDroite(){
    if(!classement->isChecked())
         QMessageBox::critical(this,"ERREUR","Veuillez cocher d'abord \"Faire classement des méthodes\"");
    else{
         QMessageBox::information(this,"INFORMATION","Vous avez "+ nbreTestes->text() + " testes\nAlors veuillez saisir successivement les différentes données !!!");
         nombreDeTestes =nombreDeTestesAdjoint =  nbreTestes->text().toInt();
         autoriserATester = true;
         QFile fichier("fichierVotes");
         if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
            QMessageBox::critical(NULL,"ERREUR","Erreur d'ouverture du fichier <<fichierVotes>>");
         else{
              QTextStream flux(&fichier);

              flux << "Fifo ";
              flux << "Tourniquet ";
              flux << "Pcte ";
              flux << "Pgp" << endl;
              fichier.close();
             }
        }
}

void Chronogramme::clicAnnulerBasDroite(){
    classement->setChecked(false);
    nbreTestes->setValue(1);
}

void Chronogramme::clicAfficherMethodePlusOptimale(){
    TableauDeVotes  fenetre(nombreDeTestesAdjoint,9);
    fenetre.exec();
   // QMessageBox::information(this,"METHODE PLUS OPTIMALE","La méthode la plus optimale est celle du : <strong>\""+methodePlusOptimale()+"\"</strong>");
    classement->setChecked(false);
}
