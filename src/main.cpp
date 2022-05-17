#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QString>
#include "QmlWatcher.h"
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    qmlRegisterType<QmlWatcher>("QmlWatcher", 1, 0, "QmlWatcher");
    engine.load(url);
    return app.exec();
}
