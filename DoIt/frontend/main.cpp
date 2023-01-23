#include <QApplication>

#include "main_manager.h"

int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);

    QApplication a(argc, argv);
    MainManager manager;
    QApplication::exec();

    return 0;
}
