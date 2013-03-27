#include <QGuiApplication>
#include <QQuickView>
#include "cpp/painteditem.h"
#include "cpp/brushengine.h"
#include "cpp/openraster/orawriteread.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PaintedItem>("PaintedItem", 1, 0, "PaintedItem");
    qmlRegisterType<BrushEngine>("BrushEngine", 1, 0, "Brush");
    qmlRegisterType<OraWriteRead>("OraWriteRead", 1, 0, "OraWriteRead");

    QQuickView view;
    //view.setSource(QUrl::fromLocalFile("qml/main.qml"));
    view.setSource(QUrl::fromLocalFile("../../aprilbrush/qml/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}
