#include "QmlWatcher.h"
#include <QDir>
#include <QDebug>
QmlWatcher::QmlWatcher(QObject *parent)
    : QObject(parent), m_settings("config.ini", QSettings::IniFormat)
{
    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this, &QmlWatcher::directoryChanged);
    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &QmlWatcher::fileChanged);
    m_view.installEventFilter(this);
    // m_view.setFlags(m_view.flags() | Qt::Window | Qt::WindowStaysOnTopHint);
    if (!QFileInfo("./config.ini").isFile())
    {
        m_settings.setValue("loader/basicPath", "./");
        m_settings.setValue("loader/qmlfile", "main.qml");
        m_settings.setValue("loader/importpath", "./");
    }
    else
    {
        m_basicPath = m_settings.value("loader/basicPath").toString();
        m_importPath = m_settings.value("loader/importpath").toString();
        m_qmlFile = m_settings.value("loader/qmlfile").toString();
    }
}
bool QmlWatcher::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == &m_view && event->type() == QEvent::Close)
    {
        emit watcherClose();
    }
    return QObject::eventFilter(watched, event);
}
void QmlWatcher::openListen()
{
    m_settings.setValue("loader/basicPath", m_basicPath);
    m_settings.setValue("loader/qmlfile", m_qmlFile);
    m_settings.setValue("loader/importpath", m_importPath);
    QDir dir(m_basicPath);
    m_view.engine()->setBaseUrl(QUrl::fromLocalFile(m_basicPath));
    m_view.setSource(QUrl(QUrl::fromLocalFile(dir.filePath(m_qmlFile))));
    if (!m_importPath.isEmpty())
        m_view.engine()->addImportPath(m_importPath);
    m_view.show();
    scanPaths();
}

void QmlWatcher::scanPaths()
{
    if (!m_watcher.directories().isEmpty())
        m_watcher.removePaths(m_watcher.directories());
    if (!m_watcher.files().isEmpty())
        m_watcher.removePaths(m_watcher.files());
    QDir baicDir(m_basicPath);
    auto baicList = baicDir.entryList();
    for (auto &i : baicList)
        i.prepend(baicDir.absolutePath() + "/");
    m_watcher.addPaths(baicList);
    if (!m_importPath.isEmpty())
    {
        QDir importDir(m_importPath);
        auto importList = importDir.entryList();
        for (auto &i : importList)
            i.prepend(importDir.absolutePath() + "/");
        m_watcher.addPaths(importList);
    }
    // qDebug() << "正在监视文件 " << m_watcher.files();
    // qDebug() << "正在监视目录 " << m_watcher.directories();
}

void QmlWatcher::reloadQml()
{
    QDir dir(m_basicPath);
    m_view.engine()->clearComponentCache();
    m_view.setSource(QUrl(QUrl::fromLocalFile(dir.filePath(m_qmlFile))));
}

void QmlWatcher::directoryChanged()
{
    scanPaths();
    reloadQml();
}

void QmlWatcher::fileChanged()
{
    reloadQml();
}

QmlWatcher::~QmlWatcher()
{
}
