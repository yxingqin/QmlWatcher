#ifndef QMLLIVEENIGE_H
#define QMLLIVEENIGE_H
#include <QQmlApplicationEngine>
#include <QtQml>
class QFileSystemWatcher;
class QTimer;

class QmlLiveEngine : public QQmlApplicationEngine
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString absQmlPath MEMBER m_absQmlPath)
public:
    explicit QmlLiveEngine(QObject *parent = nullptr);
    virtual ~QmlLiveEngine();
    Q_INVOKABLE void clearCache() { clearComponentCache(); }
    Q_INVOKABLE void watch(const QString &Qmlpath); //开始实时监听qml
    // Q_INVOKABLE void setWindow(QVariant window);
    void hotload(QUrl url);
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
private slots:
    void onFileSystemChanged();
    void onReloadRequested(); //重新加载qml
private:
    void scanfPaths(const QString &dir); //扫描 所有文件并且监视
    void unwatchAll();

    QFileSystemWatcher *m_watcher;
    QTimer *m_timer;
    QObject *m_window;
    static QObject *Console;
    QObject *m_loaderWin;
    QString m_QmlPath;    //保存用户输入路径 防止用户多次输入
    QString m_absQmlPath; // qml 绝对路径
    QString m_absQmlDir;  // qml文件所在的绝对路径
};

#endif