#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // 激情在燃烧
    QPixmap pixmap(":/image/kuchen.png");
    pixmap = pixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QSplashScreen splash(pixmap);
    splash.show();


    QTimer::singleShot(3000, [&](){
        w.show();
        splash.finish(&w);
    });

    return a.exec();
}
