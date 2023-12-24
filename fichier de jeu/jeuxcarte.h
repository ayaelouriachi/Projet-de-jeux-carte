//jeuxcarte.h
#ifndef JEUXCARTE_H
#define JEUXCARTE_H
#include"cartes.h"
#include <QMainWindow>
#include <QMediaPlaylist>
#include <QThread>
#include <QMediaPlayer>
QT_BEGIN_NAMESPACE
namespace Ui { class Jeuxcarte; }
QT_END_NAMESPACE

class Jeuxcarte : public QMainWindow
{
    Q_OBJECT

public:
    Jeuxcarte(QWidget *parent = nullptr);
    ~Jeuxcarte();
    Cartes *creer_carte(int numero,const QString &symbol,const QPixmap& image);
    void ajouterMainJoueur(Cartes *A);
    void ajouterComputer(Cartes *A);
    void effacerCartesLayout(QHBoxLayout *layout);
    void setButtonImage(const QString &imagePath);
    int GetDifficulty ();
     void clearLayout(QLayout *layout);

private slots:
    void on_pushButton_clicked();
    void handlePlayerMove(int score);
    void onCarteClicked();
    void on_pushButton_3_clicked();
    void on_EasyButton_clicked();
    void on_pushButton_2_clicked();
    void on_stackedWidget_2_currentChanged(int arg1);


private:
    Ui::Jeuxcarte *ui;
    QList<Cartes*> cartesList;
    bool gameInProgress;
    int Difficulty;
    int scoreJoueur1;
    int scoreOrdinateur;
     QMediaPlayer *player;



};
#endif // JEUXCARTE_H
