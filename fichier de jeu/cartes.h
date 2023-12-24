//cartes.h
#ifndef CARTES_H
#define CARTES_H
#include <QString>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>

class Cartes : public QLabel
{
    Q_OBJECT
public:
    explicit Cartes(int b = 0, QString a = "");

public: void passImages();
    void getImage(const QString& img);  // Ajout du paramètre img
    int getNumero();  // Ajout du paramètre numero
    QString getSymbol();  // Ajout du paramètre symbol

    // fonction pour comparer les numéros des cartes
    bool isNumeroSuperieur(int numero) const
    {
        return this->numero > numero;
    }
    // fonction pour mettre les cartes cliquable
    void setClickable(bool clickable);

signals:
    void imageChanged(const QString& img);
    void clicked();  //  déclarer le signal clicked

private:
    int numero;
    QString symbol;

protected:
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // CARTES_H
