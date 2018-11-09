#include "PlanDeDessin.h"
#include <QPainter>
#include <QFile>
#include <QEventLoop>
#include <QTimer>
#include <QGraphicsTextItem>

PlanDeDessin::PlanDeDessin(QString nomFichier) : QDialog(){
    this->setWindowTitle("CHRONOGRAMME D'EXECUTION DES PROCESSUS");
    nomFichierGantt = nomFichier;
    this->setMinimumSize(1250,700);
    this->setFont(QFont("Comic Sans MS",10));

    groupBox = new QGroupBox(this);
    formLayoute = new QFormLayout(groupBox);

    hBoxLayout1 = new QHBoxLayout;
    graphicsView   = new QGraphicsView;
    hBoxLayout1->addWidget(graphicsView);
    graphicsScene  = new QGraphicsScene;
    graphicsScene->setBackgroundBrush(Qt::white);
    graphicsScene->setSceneRect(0,0,1400,600);
    graphicsView->setScene(graphicsScene);

    hBoxLayout2 = new QHBoxLayout;
    hBoxLayout2->setAlignment(Qt::AlignRight);
    afficherDiagramme = new QPushButton("AFFICHER DIAGRAMME");
    hBoxLayout2->addWidget(afficherDiagramme);

    formLayoute->addRow(hBoxLayout1);
    formLayoute->addRow(hBoxLayout2);

    QObject::connect(afficherDiagramme,SIGNAL(clicked()),this,SLOT(clicAfficherDiagramme()));
}

void PlanDeDessin::nbreColonnesLignesFichier(const QString nomFichier,int* nbreLignes,int* nbreColonnes){
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

QString** PlanDeDessin::creerTableau(int nbreLignes,int nbreColonnes){
  QString** t = NULL;
  t = new QString*[nbreLignes];
  for(int i=0; i<nbreLignes; i++)
       t[i] = new QString[nbreColonnes];
return t;
}

void PlanDeDessin::stockDonneesFichierDansTableau(const QString nomFichier,QString*** t ,int* nbreLignes,int* nbreColonnes){
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

void PlanDeDessin::reparerTableauEnDureeDexecution(QString **t,int nbreColonnes){
    for(int j=nbreColonnes - 1;j>0;j--)
        t[1][j]  = QString::number( t[1][j].toInt() - t[1][j-1].toInt() );
}



void PlanDeDessin::attendre(int temps){

    QEventLoop eventLoop ;
    QTimer::singleShot(temps,&eventLoop,SLOT(quit()));
    eventLoop.exec() ;
}

void PlanDeDessin::tracerHorizontalement(int x1,int y1,int x2,int y2,QPen pen){
    x2 = x2+1;
    while(x1!=x2)
       {
        graphicsScene->addLine(x1,y1,x1,y2,pen);
        x1++;
        attendre(25);
       }
}

void PlanDeDessin::tracerVerticalement(int x1,int y1,int x2,int y2,QPen pen){
    y2 = y2+1;
    while(y1!=y2)
       {
        graphicsScene->addLine(x1,y1,x2,y1,pen);
        y1++;
        attendre(25);
       }

}

void PlanDeDessin::dessinerDiagramme(){
    QString** tOrigine = NULL;
    int nbreLignes,nbreColonnes;
    stockDonneesFichierDansTableau(nomFichierGantt,&tOrigine ,&nbreLignes,&nbreColonnes);

    QString** t = NULL;
    stockDonneesFichierDansTableau(nomFichierGantt,&t ,&nbreLignes,&nbreColonnes);
    reparerTableauEnDureeDexecution(t,nbreColonnes);


    graphicsScene->addLine(40,30,50,20,QPen(Qt::blue,4));
    graphicsScene->addLine(50,20,60,30,QPen(Qt::blue,4));

    graphicsScene->addLine(50,20,50,250,QPen(Qt::blue,4));
    graphicsScene->addLine(50,250,1100,250,QPen(Qt::blue,4));

    graphicsScene->addLine(1090,260,1100,250,QPen(Qt::blue,4));
    graphicsScene->addLine(1090,240,1100,250,QPen(Qt::blue,4));

    graphicsScene->addText("U.C",QFont("Comic Sans MS",15))->setPos(2,175);
    graphicsScene->addLine(48,200,52,200,QPen(Qt::blue,4));

    if(!nomFichierGantt.compare("diagrammeGanttFifo"))
        graphicsScene->addText("Diagramme de gantt de FIFO",QFont("Comic Sans MS",25))->setPos(300,450);
    else
        if(!nomFichierGantt.compare("diagrammeGanttTourniquet"))
            graphicsScene->addText("Diagramme de gantt de TOURNIQUET",QFont("Comic Sans MS",25))->setPos(300,450);
        else
            if(!nomFichierGantt.compare("diagrammeGanttPcte"))
                graphicsScene->addText("Diagramme de gantt de PCTE",QFont("Comic Sans MS",25))->setPos(300,450);
            else
                graphicsScene->addText("Diagramme de gantt de PGP",QFont("Comic Sans MS",25))->setPos(300,450);

    int arret = 56,depart = 56;
    QString** tDonnees = NULL;
    int nbreLignesDonnees,nbreColonnesDonnees;
    stockDonneesFichierDansTableau("données.txt",&tDonnees ,&nbreLignesDonnees,&nbreColonnesDonnees);
    int i = 1;
    while(i<nbreLignesDonnees && t[0][0].compare(tDonnees[i][0]))
          i++;
    arret += tDonnees[i][1].toInt()*40;
    //tracerVerticalement(arret,195,56,205,QPen(Qt::red,2));
    graphicsScene->addText("0",QFont("Comic Sans MS",15))->setPos(depart - 8,250);
    for(int j=0;j<nbreColonnes;j++)
        {
         tracerVerticalement(arret,195,arret,205,QPen(Qt::red,2));
         depart = arret;
         tracerHorizontalement(arret,200,arret + t[1][j].toInt()*40,200,QPen(Qt::red,2));
         arret += t[1][j].toInt()*40;
         tracerVerticalement(arret,195,arret,205,QPen(Qt::red,2));
         tracerVerticalement(arret + 3,200,arret + 3,250,QPen(Qt::red,2,Qt::DotLine));

         graphicsScene->addText(QString::number(tDonnees[i][1].toInt()+tOrigine[1][j].toInt()),QFont("Comic Sans MS",15))->setPos(arret - 8,250);
         graphicsScene->addText(t[0][j],QFont("Comic Sans MS",15))->setPos(( depart + arret )/2 - 10,155);
         arret +=6;
         }
}

void PlanDeDessin::clicAfficherDiagramme(){
    afficherDiagramme->setEnabled(false);
    dessinerDiagramme();
}
