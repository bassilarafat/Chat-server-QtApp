#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "serversidetcp.h"
#include <QQmlContext>


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    //create serversidetcp object
    ServerSideTcp serverobj;

    //set this object to context property to connect to ui
    engine.rootContext()->setContextProperty("server" ,&serverobj);  //server is the name for the object in my qml file
    engine.load(url);
    return app.exec();
}
