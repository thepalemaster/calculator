#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtQml/qqml.h>

#include "calculator.hpp"
#include "shape_list_model.hpp"

#include <QDebug>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    Calculator calc;
    ShapeListModel shModel(calc);
    qmlRegisterType<ShapeListModel>("ru.AreaCalc.ShapeModel", 1, 0,"ShapeModel");
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
