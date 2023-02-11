#include "dirviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DirViewer viewer;
    viewer.show();
    return app.exec();
}
