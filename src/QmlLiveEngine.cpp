#include "QmlLiveEngine.h"
#include <QFileInfo>
#include <QTimer>
#include <QFileSystemWatcher>
#include <QQmlContext>
#include <QDir>
#include <QWindow>
QObject *QmlLiveEngine::Console = nullptr;
QmlLiveEngine::QmlLiveEngine(QObject *parent)
    : QQmlApplicationEngine(parent), m_watcher(new QFileSystemWatcher(this)),
      m_timer(new QTimer(this)), m_loaderWin(nullptr)
{
    connect(m_watcher, &QFileSystemWatcher::directoryChanged, this, &QmlLiveEngine::onFileSystemChanged);
    connect(m_watcher, &QFileSystemWatcher::fileChanged, this, &QmlLiveEngine::onFileSystemChanged);
    connect(m_timer, &QTimer::timeout, this, &QmlLiveEngine::onReloadRequested);
    m_timer->setSingleShot(true);
}
QmlLiveEngine::~QmlLiveEngine()
{
}
void QmlLiveEngine::hotload(QUrl url)
{
    rootContext()->setContextProperty("$Engine", this);
    load(url);
    m_window = rootObjects().first();
    Console = m_window->findChild<QObject *>("_console");
    m_loaderWin = m_window->findChild<QObject *>("_loader_win");
    qInstallMessageHandler(QmlLiveEngine::messageHandler); //输出重定向
}
void QmlLiveEngine::watch(const QString &Qmlpath)
{
    if (Qmlpath != m_QmlPath)
    {
        m_QmlPath = Qmlpath;
        //更新 搜索文件
        m_absQmlPath = QDir(Qmlpath).absolutePath();
        m_absQmlDir = m_QmlPath.left(m_QmlPath.lastIndexOf('/'));
        unwatchAll();
        scanfPaths(m_absQmlDir);
        addImportPath(m_absQmlDir);
        qDebug() << "importPaths" << importPathList();
    }
}
void QmlLiveEngine::onFileSystemChanged()
{
    if (!m_timer)
        return;
    if (!m_timer->isActive())
        m_timer->start();
}

void QmlLiveEngine::onReloadRequested()
{
    unwatchAll();
    scanfPaths(m_absQmlDir);
    QMetaObject::invokeMethod(m_window, "_reload");
}

void QmlLiveEngine::scanfPaths(const QString &dir)
{
    QDir d(dir);
    QStringList files = d.entryList(QStringList() << "*.*", QDir::Files);
    QStringList dirs = d.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    m_watcher->addPath(dir);
    for (QString &file : files)
    {
        m_watcher->addPath(dir + '/' + file);
    }

    for (QString &subdir : dirs)
    {
        scanfPaths(dir + '/' + subdir);
    }
}
// void QmlLiveEngine::setWindow(QVariant window)
// {
//     if (m_loaderWin != nullptr)
//     {
//         QWindow *win = window.value<QWindow *>();
//         win->hide();
//         if (win->children().size() > 2)
//         {
//             win->setFlags(Qt::SubWindow);

//             win->setParent(static_cast<QWindow *>(m_window));
//             win->setGeometry(0, 0, 100, 100);
//             qDebug() << win->children().at(1);
//             // win->children().at(1)->setParent(m_loaderWin);
//         }
//     }
// }
void QmlLiveEngine::unwatchAll()
{
    QStringList dirs = m_watcher->directories();
    QStringList files = m_watcher->files();
    QStringList fails;

    for (QString &dir : dirs)
    {
        if (!m_watcher->removePath(dir))
        {
            fails << dir;
        }
    }
    for (QString &file : files)
    {
        if (!m_watcher->removePath(file))
        {
            fails << file;
        }
    }

    if (!fails.empty())
    {
        qWarning() << tr("The following directories or files "
                         "cannot be removed from file system watcher:");
        for (QString &fail : fails)
        {
            qWarning() << "\t" << fail;
        }
    }
}

void QmlLiveEngine::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);

    if (Console != nullptr)
    {
        QString str = msg;
        if (type == QtWarningMsg || type == QtCriticalMsg || type == QtFatalMsg)
        {
            str = "<font color='red'>" + str + "</font>";
        }
        QMetaObject::invokeMethod(Console, "append", Q_ARG(QString, str));
    }
}
