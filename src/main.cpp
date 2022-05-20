#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QString>
#include "QmlLiveEngine.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QmlLiveEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.hotload(url);
    return app.exec();
}
