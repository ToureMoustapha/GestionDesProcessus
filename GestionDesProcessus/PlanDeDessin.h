#ifndef PLANDEDESSIN_H
#define PLANDEDESSIN_H

#include <QDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFormLayout>

class PlanDeDessin : public QDialog {

    Q_OBJECT
       QString nomFichierGantt;
    private :
      QGroupBox            *groupBox;
      QFormLayout          *formLayoute;

      QHBoxLayout           *hBoxLayout1;
      QGraphicsView         *graphicsView;
      QGraphicsScene        *graphicsScene;

      QHBoxLayout           *hBoxLayout2;
      QPushButton           *afficherDiagramme;
    public :
      PlanDeDessin(QString nomFichierGantt);
      void nbreColonnesLignesFichier(const QString nomFichier,int* nbreLignes,int* nbreColonnes);
      QString** creerTableau(int nbreLignes,int nbreColonnes);
      void stockDonneesFichierDansTableau(const QString nomFichier,QString*** t ,int* nbreLignes,int* nbreColonnes);
      void reparerTableauEnDureeDexecution(QString **t,int nbreColonnes);
      //void paintEvent(QPaintEvent *);
      void attendre(int);
      void tracerVerticalement(int x1,int y1,int x2,int y2,QPen pen);
      void tracerHorizontalement(int x1,int y1,int x2,int y2,QPen pen);
      void dessinerDiagramme();

    private slots :
      void clicAfficherDiagramme();
};


#endif // PLANDEDESSIN_H
