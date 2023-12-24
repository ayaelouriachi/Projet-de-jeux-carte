#include "jeuxcarte.h"
#include "ui_jeuxcarte.h"
#include"cartes.h"
#include <algorithm>  // Pour std::random_shuffle
#include <cstdlib>    // Pour std::rand et std::srand
#include <QTimer>
#include <QMessageBox>
#include <qDebug>
#include <QVBoxLayout>
#include <QWidget>
#include <QMediaPlayer>

Jeuxcarte::Jeuxcarte(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Jeuxcarte),scoreJoueur1(0),scoreOrdinateur(0),gameInProgress(false),player(new QMediaPlayer(this))

{
    ui->setupUi(this);


    // Définir les arrière-plans pour les deux stackedWidgets

   QString styleSheetPage2 = "QWidget#stackedWidget { background-image: url(:/res/project 2.png);}";
   QString styleSheetPage1 = "QWidget#stackedWidget_2 { background-image: url(:/res/project 1 sound on.png);}";
   ui->stackedWidget->setStyleSheet(styleSheetPage2);
   ui->stackedWidget_2->setStyleSheet(styleSheetPage1);
   // Définir le fond de l'interface en utilisant une feuille de style CSS
   QString styleSheet = "QMainWindow { background-image: url(:/res/project 3.png); }";
    this->setStyleSheet(styleSheet);
   // Initialiser les scores
    scoreJoueur1 = 0;
    scoreOrdinateur = 0;
    // Affichez les scores initiaux
    ui->labelScoreJoueur1->setText(QString("Score de Joueur 1: %1").arg(scoreJoueur1));
    ui->labelScoreOrdinateur->setText(QString("Score de l'Ordinateur: %1").arg(scoreOrdinateur));
    // Charger une image spécifique sur le bouton au lancement du programme
    setButtonImage(":/res/back2.jpg");



    connect(ui->EasyButton, &QPushButton::clicked, this, [=]() {
        this->Difficulty = 1;
        this->on_EasyButton_clicked();
    });


    connect(ui->pushButton_3, &QPushButton::clicked, this, [=]() {
        this->Difficulty = 2;
        this->on_pushButton_3_clicked();
    });



}


Cartes *Jeuxcarte::creer_carte(int numero, const QString &symbol, const QPixmap &image)
{
    QPixmap resizedImage = image.scaled(100, 150, Qt::KeepAspectRatio);
    Cartes *nouvelleCarte = new Cartes(numero, symbol);
    nouvelleCarte->setPixmap(resizedImage);
    nouvelleCarte->setFixedSize(100, 150);
    nouvelleCarte->setScaledContents(true);
    QLabel *labelImage = new QLabel(this);
    labelImage->setPixmap(resizedImage);
    labelImage->setFixedSize(100, 150);

    // Connectez le signal clicked uniquement pour le layout horizontalLayout_2( de joueur )
    if (ui->horizontalLayout_2->indexOf(nouvelleCarte) != -1) {
        connect(nouvelleCarte, &Cartes::clicked, this, &Jeuxcarte::onCarteClicked);
    }

    return nouvelleCarte;
}

int Jeuxcarte::GetDifficulty () {
    return this->Difficulty ;
}
// la fonction de gestion du clic
void Jeuxcarte::onCarteClicked ()
{


    if (!gameInProgress) {

        return; //Ne rien faire si le jeux  est terminée
    }

    // Récupérez la carte qui a été cliquée
    Cartes *carteCliquee = qobject_cast<Cartes*>(sender());


    // Récupérez le layout actuel de la carte
    QLayout *layoutCarte = carteCliquee->parentWidget()->layout();

    // Supprimez la carte du layout actuel
    layoutCarte->removeWidget(carteCliquee);
    clearLayout(ui->horizontalLayout_3);

    // Ajoutez la carte au nouveau layout (par exemple, horizontalLayout_3)

    ui->horizontalLayout_3->addWidget(carteCliquee);


    // Appelez la fonction passImages de la carte cliquée
    carteCliquee->passImages();

    // Rendez la carte cliquée non cliquable
    carteCliquee->setClickable(false);


    clearLayout(ui->horizontalLayout_4);



    //  une temporisation de 500 ms avant de retirer une carte de horizontalLayout
    QTimer::singleShot(500, this, [=]() {
        // Choisissez entre deux cas : aléatoirement ou en fonction du nombre
        if ( this->GetDifficulty () == 1) {
            // Cas aléatoire
            int count = ui->horizontalLayout->count();
            if (count > 0) {
                int index = qrand() % count;
                QWidget *widget = ui->horizontalLayout->itemAt(index)->widget();
                // Supprimez la carte du layout horizontalLayout
                ui->horizontalLayout->removeWidget(widget);
                // Ajoutez la carte à horizontalLayout_3
                ui->horizontalLayout_4->addWidget(widget);
                // Appelez la fonction passImages de la carte ajoutée à horizontalLayout_3
                if (Cartes *addedCarte = qobject_cast<Cartes*>(widget)) {
                    addedCarte->passImages();
                    // Rendez la carte cliquée de horizontalLayout_3 non cliquable
                    addedCarte->setClickable(false);
                }
            }
        } else if ( this->GetDifficulty () == 2) {
            // Cas en fonction du nombre de la dernière carte affichée dans horizontalLayout_3
            int lastNumber = -1;
            if (ui->horizontalLayout_4->count() > 0) {
                QWidget *lastWidget = ui->horizontalLayout_4->itemAt(ui->horizontalLayout_4->count() - 1)->widget();
                // Supposons que votre Cartes a une fonction pour obtenir son numéro (getNumero() par exemple)
                if (Cartes *lastCarte = qobject_cast<Cartes*>(lastWidget)) {
                    lastNumber = lastCarte->getNumero();
                }
            }


            for (int i = 0; i < ui->horizontalLayout->count(); ++i) {
                QWidget *widget = ui->horizontalLayout->itemAt(i)->widget();
                if (Cartes *carte = qobject_cast<Cartes*>(widget)) {
                    if (carte->isNumeroSuperieur(lastNumber)) {
                        // Supprimez la carte du layout horizontalLayout
                        ui->horizontalLayout->removeWidget(widget);
                        // Ajoutez la carte à horizontalLayout_3
                        ui->horizontalLayout_4->addWidget(widget);

                        // Appelez la fonction passImages de la carte ajoutée à horizontalLayout_3
                        carte->passImages();

                        // Rendez la carte cliquée de horizontalLayout_3 non cliquable
                        carte->setClickable(false);

                        break;  // Arrêtez la boucle après avoir trouvé la première carte valide

                    }

                }

            }

        }


        int count = ui->horizontalLayout_3->count();

        int count1 = ui->horizontalLayout_4->count();
        if (count >= 1 && count1>=1) {
            // Obtention des deux dernières cartes
            QWidget *lastWidget1 = ui->horizontalLayout_3->itemAt(count - 1)->widget();
            QWidget *lastWidget2 = ui->horizontalLayout_4->itemAt(count1 - 1)->widget();


            if (Cartes *lastCarte1 = qobject_cast<Cartes*>(lastWidget1)) {
                if (Cartes *lastCarte2 = qobject_cast<Cartes*>(lastWidget2)) {
                    // Comparez les numéros des deux dernières cartes
                    int numero1 = lastCarte1->getNumero();
                    int numero2 = lastCarte2->getNumero();
                    // Incrémentez le score du joueur 1 par le numéro de la carte avec le plus grand numéro
                    if (numero1 > numero2) {
                        scoreJoueur1 += numero1;
                        ui->labelScoreJoueur1->setText(QString("Score de Joueur 1: %1").arg(scoreJoueur1));
                        QPixmap originalImage(":/res/back24.png");

                        // Redimensionner l'image
                        QPixmap resizedImage = originalImage.scaled(100, 100, Qt::KeepAspectRatio);

                        // Définir l'image redimensionnée sur le QLabel existant (ui->label)
                        ui->label->setPixmap(resizedImage);

                        // Définir la taille fixe du QLabel
                        ui->label->setFixedSize(150, 150);

                        // Permettre la mise à l'échelle du contenu
                        ui->label->setScaledContents(true);



                    } else if (numero2 > numero1) {
                        // Incrémentez le score de l'ordinateur par le numéro de la carte avec le plus grand numéro
                        scoreOrdinateur += numero2;
                        ui->labelScoreOrdinateur->setText(QString("Score de l'Ordinateur: %1").arg(scoreOrdinateur));
                        QPixmap originalImage(":/res/back23.png" );


                        // Redimensionner l'image
                        QPixmap resizedImage = originalImage.scaled(100, 100, Qt::KeepAspectRatio);

                        // Définir l'image redimensionnée sur le QLabel existant (ui->label)
                        ui->label->setPixmap(resizedImage);

                        // Définir la taille fixe du QLabel
                        ui->label->setFixedSize(150, 150);

                        // Permettre la mise à l'échelle du contenu
                        ui->label->setScaledContents(true);


                    }

                    else if (numero2 == numero1){
                        QPixmap originalImage(":/res/equal.png");
                        // Redimensionner l'image
                        QPixmap resizedImage = originalImage.scaled(100, 150, Qt::KeepAspectRatio);

                        // Définir l'image redimensionnée sur le QLabel existant (ui->label)
                        ui->label->setPixmap(resizedImage);

                        // Définir la taille fixe du QLabel
                        ui->label->setFixedSize(150, 150);

                        // Permettre la mise à l'échelle du contenu
                        ui->label->setScaledContents(true);


                    }

                    // Vérifiez si l'un des scores est >= 70
                    if (scoreJoueur1 >= 70 || scoreOrdinateur >= 70) {
                        QString message;
                        if (scoreJoueur1 >= 70) {
                            message = "Le Joueur 1 a gagné!";
                        } else {
                            message = "L'Ordinateur a gagné!";
                        }



                        // Affichez un message de fin de partie
                        QMessageBox::information(this, "Fin de partie", message);



                        // Réinitialisez les scores
                        scoreJoueur1 = 0;
                        scoreOrdinateur = 0;

                        // Mettez à jour les labels des scores
                        ui->labelScoreJoueur1->setText(QString("Score de Joueur 1: %1").arg(scoreJoueur1));
                        ui->labelScoreOrdinateur->setText(QString("Score de l'Ordinateur: %1").arg(scoreOrdinateur));
                        gameInProgress = false;


                        // Enable the button after the game ends
                        ui->pushButton->setEnabled(true);
                    }



                    lastCarte1->setClickable(false);
                    lastCarte2->setClickable(false);



                }


            }

        }

    });
}









void Jeuxcarte::ajouterMainJoueur(Cartes *A)
{
    ui->horizontalLayout_2->setAlignment(Qt::AlignCenter);
    ui->horizontalLayout_2->addWidget(A,0,Qt::AlignCenter);
 ;}


void Jeuxcarte::ajouterComputer(Cartes *A)
{ ui->horizontalLayout->setAlignment(Qt::AlignCenter);
    ui->horizontalLayout->addWidget(A, 0, Qt::AlignCenter);
    A->getImage(":/res/back4.png");
}
void Jeuxcarte::setButtonImage(const QString &imagePath)
{
    // Charger l'image
    QPixmap buttonPixmap(imagePath);

    // Adapter la taille de l'image à la taille du bouton
    QSize buttonSize = ui->pushButton->size();
    QPixmap scaledPixmap = buttonPixmap.scaled(buttonSize, Qt::KeepAspectRatio);

    // Afficher l'image sur le bouton
    QIcon buttonIcon(scaledPixmap);
    ui->pushButton->setIcon(buttonIcon);
    ui->pushButton->setIconSize(buttonSize);
}



Jeuxcarte::~Jeuxcarte()
{
    qDebug () << " Deleted User ...";
    // Libérez la mémoire des cartes créées
    qDeleteAll(cartesList);
    cartesList.clear();
    delete ui;
}


void Jeuxcarte::on_pushButton_clicked()
{if (!gameInProgress) {   ui->label->show();

       player->setMedia(QUrl::fromLocalFile("C:/Users/user/Desktop/cartesecondaire/ay3.mp3"));

     player->play();

    // Effacer les cartes actuellement affichées dans les layouts
    effacerCartesLayout(ui->horizontalLayout_2);  // Layout du joueur principal
    effacerCartesLayout(ui->horizontalLayout);
     effacerCartesLayout(ui->horizontalLayout_3);
    effacerCartesLayout(ui->horizontalLayout_4);
  // Layout de l'ordinateur

    // Créer et initialiser la liste de cartes
    QList<Cartes*> cartesList;

   Cartes* carte1 = creer_carte(1, "or", QPixmap(":/imag/photo/00.gif"));
   Cartes* carte2 = creer_carte(2, "or", QPixmap(":/imag/photo/01.gif"));
    Cartes* carte3 = creer_carte(3, "or", QPixmap(":/imag/photo/02.gif"));
    Cartes* carte4 = creer_carte(4, "or", QPixmap(":/imag/photo/03.gif"));
    Cartes* carte5 = creer_carte(5, "or", QPixmap(":/imag/photo/04.gif"));
    Cartes* carte6 = creer_carte(6, "or", QPixmap(":/imag/photo/05.gif"));
    Cartes* carte7 = creer_carte(7, "or", QPixmap(":/imag/photo/06.gif"));
    Cartes* carte8 = creer_carte(10, "or", QPixmap(":/imag/photo/07.gif"));
    Cartes* carte9 = creer_carte(11, "or", QPixmap(":/imag/photo/08.gif"));
    Cartes* carte10 = creer_carte(12, "or", QPixmap(":/imag/photo/09.gif"));
    Cartes* carte11 = creer_carte(1, "bâton", QPixmap(":/imag/photo/10.gif"));
    Cartes* carte12 = creer_carte(2, "bâton", QPixmap(":/imag/photo/11.gif"));
    Cartes* carte13 = creer_carte(3, "bâton", QPixmap(":/imag/photo/12.gif"));
    Cartes* carte14 = creer_carte(4, "bâton", QPixmap(":/imag/photo/13.gif"));
    Cartes* carte15 = creer_carte(5, "bâton", QPixmap(":/imag/photo/14.gif"));
    Cartes* carte16 = creer_carte(6, "bâton", QPixmap(":/imag/photo/15.gif"));
    Cartes* carte17 = creer_carte(7, "bâton", QPixmap(":/imag/photo/16.gif"));
    Cartes* carte18 = creer_carte(10, "bâton", QPixmap(":/imag/photo/17.gif"));
    Cartes* carte19 = creer_carte(11, "bâton", QPixmap(":/imag/photo/18.gif"));
    Cartes* carte20 = creer_carte(12, "bâton", QPixmap(":/imag/photo/19.gif"));
    Cartes* carte21 = creer_carte(1, "chaise", QPixmap(":/imag/photo/30.gif"));
    Cartes* carte22 = creer_carte(2, "chaise", QPixmap(":/imag/photo/31.gif"));
    Cartes* carte23 = creer_carte(3, "chaise", QPixmap(":/imag/photo/32.gif"));
    Cartes* carte24 = creer_carte(4, "chaise", QPixmap(":/imag/photo/33.gif"));
    Cartes* carte25 = creer_carte(5, "chaise", QPixmap(":/imag/photo/34.gif"));
    Cartes* carte26 = creer_carte(6, "chaise", QPixmap(":/imag/photo/35.gif"));
    Cartes* carte27 = creer_carte(7, "chaise", QPixmap(":/imag/photo/36.gif"));
    Cartes* carte28 = creer_carte(10, "chaise", QPixmap(":/imag/photo/37.gif"));
    Cartes* carte29 = creer_carte(11, "chaise", QPixmap(":/imag/photo/38.gif"));
    Cartes* carte30 = creer_carte(12, "chaise", QPixmap(":/imag/photo/39.gif"));
    Cartes* carte31 = creer_carte(1, "épée", QPixmap(":/imag/photo/20.gif"));
    Cartes* carte32 = creer_carte(2, "épée", QPixmap(":/imag/photo/21.gif"));
    Cartes* carte33 = creer_carte(3, "épée", QPixmap(":/imag/photo/22.gif"));
    Cartes* carte34 = creer_carte(4, "épée", QPixmap(":/imag/photo/23.gif"));
    Cartes* carte35 = creer_carte(5, "épée", QPixmap(":/imag/photo/24.gif"));
    Cartes* carte36 = creer_carte(6, "épée", QPixmap(":/imag/photo/25.gif"));
    Cartes* carte37 = creer_carte(7, "épée", QPixmap(":/imag/photo/26.gif"));
    Cartes* carte38 = creer_carte(10, "épée", QPixmap(":/imag/photo/27.gif"));
    Cartes* carte39 = creer_carte(11, "épée", QPixmap(":/imag/photo/28.gif"));
    Cartes* carte40 = creer_carte(12, "épée", QPixmap(":/imag/photo/29.gif"));

    cartesList<<carte1<<carte2<<carte3<<carte4<<carte5<<carte6<<carte7<<carte8<<carte9<<carte10<<carte11<<carte12<<carte13<<carte14<<carte15<<carte16<<carte17<<carte18<<carte19<<carte20<<carte21<<carte22<<carte23<<carte24<<carte25<<carte26<<carte27<<carte28<<carte29<<carte30<<carte31<<carte32<<carte33<<carte34<<carte35<<carte36<<carte37<<carte38<<carte39<<carte40;

    // Mélanger la liste de cartes
    std::random_shuffle(cartesList.begin(), cartesList.end());
    // Afficher la première carte mélangée dans le nouveau layout


    // Distribuer les cartes aux layouts
    for (int i = 0; i < 20; ++i)
    { // Les 20 premières cartes vont au layout du joueur principal
        Cartes *carteJoueur = cartesList[i];
        ajouterMainJoueur(carteJoueur);

        // Connectez uniquement les cartes du layout horizontalLayout_2
        if (ui->horizontalLayout_2->indexOf(carteJoueur) != -1) {
            connect(carteJoueur, &Cartes::clicked, this, &Jeuxcarte::onCarteClicked);
        }

        // Les 20 cartes suivantes vont au layout de l'ordinateur
        ajouterComputer(cartesList[i + 20]);}
         gameInProgress = true;
      ui->pushButton->setEnabled(false);
    } else {


        scoreJoueur1 = 0;
        scoreOrdinateur = 0;
        ui->labelScoreJoueur1->setText(QString("Score de Joueur 1: %1").arg(scoreJoueur1));
        ui->labelScoreOrdinateur->setText(QString("Score de l'Ordinateur: %1").arg(scoreOrdinateur));

        // Clear existing cards
        effacerCartesLayout(ui->horizontalLayout_2);
        effacerCartesLayout(ui->horizontalLayout);

        // Set the game not in progress

        gameInProgress = false;
        ui->label->hide();

        ui->pushButton->setEnabled(true);

    }
    }




// Fonction pour effacer les cartes d'un layout
void Jeuxcarte::effacerCartesLayout(QHBoxLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child;
    }
}

void Jeuxcarte::handlePlayerMove(int score)
{

    QMessageBox::information(this, "Player Move", QString("Player scored: %1").arg(score));

}


void Jeuxcarte::clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr){

        if (QWidget *widget = item->widget())
        delete widget;
        delete item;}

}


void Jeuxcarte::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

    ui->stackedWidget->close();

}


void Jeuxcarte::on_EasyButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget->close();

}


void Jeuxcarte::on_pushButton_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
    ui->stackedWidget_2->close();


}


void Jeuxcarte::on_stackedWidget_2_currentChanged(int arg1)
{

}

