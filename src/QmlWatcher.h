#ifndef QMLWATHER_HHHHHH
#define QMLWATHER_HHHHHH
#include <QObject>
#include <QtQml>
#include <QFileSystemWatcher>
#include <QQmlApplicationEngine>
#include <QQuickView>
class QmlWatcher : public QObject
{
    Q_OBJECT
    // QML_ELEMENT
    Q_PROPERTY(QString basicPath MEMBER m_basicPath NOTIFY basicPathChanged)
    Q_PROPERTY(QString qmlFile MEMBER m_qmlFile NOTIFY qmlFileChanged)
    Q_PROPERTY(QString importPath MEMBER m_importPath NOTIFY importPathChanged)
signals:
    void basicPathChanged();
    void qmlFileChanged();
    void importPathChanged();
    void watcherClose();

public:
    QmlWatcher(QObject *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event) override;
    virtual ~QmlWatcher();
    Q_INVOKABLE void openListen();

private:
    void scanPaths(); //扫描目录  将所有文件都加入到监视目录中
    void reloadQml(); //重新加载qml
private slots:
    void directoryChanged();
    void fileChanged();

private:
    QFileSystemWatcher m_watcher;
    QQuickView m_view;
    QString m_basicPath;
    QString m_qmlFile;
    QString m_importPath;
    QSettings m_settings;
};

#endif
