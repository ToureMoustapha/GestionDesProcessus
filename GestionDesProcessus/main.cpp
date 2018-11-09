#include <QApplication>
#include "FenPrincipale.h"
#include "TableauDeVotes.h"

int main(int argc, char* argv[]){
    QApplication app(argc,argv);

    FenPrincipale fenetre;
    fenetre.show();

    return app.exec();
}
