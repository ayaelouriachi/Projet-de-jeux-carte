
#include "jeuxcarte.h"
#include"cartes.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialise la graine pour std::rand
    std::srand(static_cast<unsigned>(std::time(0)));

    Jeuxcarte w;
    w.show();
    return a.exec();
}
