#include "cartes.h"

Cartes::Cartes(int b, QString a) : numero(b), symbol(a)
{

}

void Cartes::getImage(const QString& img)
{
    QPixmap image(img);
    QPixmap resizedImage = image.scaled(100, 150, Qt::KeepAspectRatio);
    this->setPixmap(resizedImage);
    this->setFixedSize(100, 150);

    emit imageChanged(img);  // Émettre le signal avec le paramètre img
}
// Implémentation de la fonction setClickable
void Cartes::setClickable(bool clickable)
{
    // pour assurer que  widget Cartes est cliquable
    if (clickable) {
        setAttribute(Qt::WA_TransparentForMouseEvents, false);
        setCursor(Qt::PointingHandCursor);
    }
    //  pour désactivez la capacité de  widget Cartes à être cliqué
    else {
        setAttribute(Qt::WA_TransparentForMouseEvents, true);
        setCursor(Qt::ArrowCursor);
    }
}


void Cartes::passImages()
{
    QString imagePath;

    if (symbol == "or")
    {
        switch (numero)
        {
        case 1:
            imagePath = ":/imag/photo/00.gif";
            break;
        case 2:
            imagePath = ":/imag/photo/01.gif";
            break;
        case 3:
            imagePath=":/imag/photo/02.gif";
        case 4:
            imagePath = ":/imag/photo/03.gif";
            break;
        case 5:
            imagePath = ":/imag/photo/04.gif";
            break;
        case 6:
            imagePath = ":/imag/photo/05.gif";
            break;
        case 7:
            imagePath = ":/imag/photo/06.gif";
            break;
        case 10:
            imagePath = ":/imag/photo/07.gif";
            break;
        case 11:
            imagePath = ":/imag/photo/08.gif";
            break;
        case 12:
            imagePath = ":/imag/photo/09.gif";
            break;
        }
    }
    else if (symbol == "épée")
    {
        switch (numero)
        {
        case 1:
            imagePath = ":/imag/photo/20.gif";
            break;
        case 2:
            imagePath = ":/imag/photo/21.gif";
            break;
        case 3:
            imagePath=":/imag/photo/22.gif";
        case 4:
            imagePath = ":/imag/photo/23.gif";
            break;
        case 5:
            imagePath = ":/imag/photo/24.gif";
            break;
        case 6:
            imagePath = ":/imag/photo/25.gif";
            break;
        case 7:
            imagePath = ":/imag/photo/26.gif";
            break;
        case 10:
            imagePath = ":/imag/photo/27.gif";
            break;
        case 11:
            imagePath = ":/imag/photo/28.gif";
            break;
        case 12:
            imagePath = ":/imag/photo/29.gif";
            break;

        default:
            break;
        }
    }
    else if (symbol == "bâton")
    {
        switch (numero)
        {
        case 1:
            imagePath = ":/imag/photo/10.gif";
            break;
        case 2:
            imagePath = ":/imag/photo/11.gif";
            break;
        case 3:
            imagePath=":/imag/photo/12.gif";
        case 4:
            imagePath = ":/imag/photo/13.gif";
            break;
        case 5:
            imagePath = ":/imag/photo/14.gif";
            break;
        case 6:
            imagePath = ":/imag/photo/15.gif";
            break;
        case 7:
            imagePath = ":/imag/photo/16.gif";
            break;
        case 10:
            imagePath = ":/imag/photo/17.gif";
            break;
        case 11:
            imagePath = ":/imag/photo/18.gif";
            break;
        case 12:
            imagePath = ":/imag/photo/19.gif";
            break;
        }
    }
    else if (symbol == "chaise")
    {
        switch (numero)
        {
        case 1:
            imagePath = ":/imag/photo/30.gif";
            break;
        case 2:
            imagePath = ":/imag/photo/31.gif";
            break;
        case 3:
            imagePath=":/imag/photo/32.gif";
        case 4:
            imagePath = ":/imag/photo/33.gif";
            break;
        case 5:
            imagePath = ":/imag/photo/34.gif";
            break;
        case 6:
            imagePath = ":/imag/photo/35.gif";
            break;
        case 7:
            imagePath = ":/imag/photo/36.gif";
            break;
        case 10:
            imagePath = ":/imag/photo/37.gif";
            break;
        case 11:
            imagePath = ":/imag/photo/38.gif";
            break;
        case 12:
            imagePath = ":/imag/photo/39.gif";
            break;
        }
    }

    getImage(imagePath);
}

int Cartes::getNumero()
{
    return numero;
}

QString Cartes::getSymbol()
{
    return symbol;
}
void Cartes::mousePressEvent(QMouseEvent *event)
{
    // Émettre le signal clicked lorsque la carte est cliquée
    emit clicked();
    QWidget::mousePressEvent(event);
}

