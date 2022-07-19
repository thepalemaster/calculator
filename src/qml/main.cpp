#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtQml/qqml.h>

#include "qml_calculator.hpp"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    qmlRegisterType<CalculatorWrapper::ShapeListModel>("ru.AreaCalc.ShapeModel", 1, 0,"ShapeModel");
    qmlRegisterType<CalculatorWrapper::ShapeInputView>("ru.AreaCalc.InputView", 1, 0, "InputView");
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
