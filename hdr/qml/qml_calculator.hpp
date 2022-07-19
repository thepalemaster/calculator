#pragma once

#include <array>

#include <QAbstractListModel>

#include "calculator.hpp"

namespace CalculatorWrapper {
    
    Calculator& getCalculator ();

    class ShapeListModel: public QAbstractListModel {
    Q_OBJECT
    private:
        std::vector<const std::string*> strList;
        QHash<int, QByteArray> userRoleNames;
    public:
        enum roleNames {
            IDRole = Qt::UserRole + 1,
            ShapeName = Qt::UserRole + 2
        };
        explicit ShapeListModel(QObject* parent = nullptr);
        int rowCount(const QModelIndex & parent) const override;
        int columnCount(const QModelIndex & parent) const override;
        QVariant data(const QModelIndex & index, int role) const override;
    protected:
        QHash<int, QByteArray> roleNames() const override;
    };

    class ShapeInputView: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString shapeName READ name NOTIFY nameChanged)
    Q_PROPERTY(QString field1 READ fieldName1 NOTIFY fieldChanged1)
    Q_PROPERTY(QString field2 READ fieldName2 NOTIFY fieldChanged2)
    Q_PROPERTY(QString field3 READ fieldName3 NOTIFY fieldChanged3)
    Q_PROPERTY(QString field4 READ fieldName4 NOTIFY fieldChanged4)
    Q_PROPERTY(QString option1 READ optionName1 NOTIFY optionChanged1)
    Q_PROPERTY(QString option2 READ optionName2 NOTIFY optionChanged2)
    signals:
        void nameChanged();
        void fieldChanged1();
        void fieldChanged2();
        void fieldChanged3();
        void fieldChanged4();
        void optionChanged1();
        void optionChanged2();
    private:
        std::array<const Shapes::Option*, 7> currentNames;
        int currentShape;
        Calculator calc;
    public slots:
        Q_INVOKABLE void setupShape(int id = 0);
        Q_INVOKABLE void setupNames(bool first, bool second);
        Q_INVOKABLE void calculate(QString num1, QString num2, QString num3,
                                   QString num4, bool first, bool second);
    public:
        ShapeInputView(QObject* parent = nullptr);
        QString name();
        QString fieldName1();
        QString fieldName2();
        QString fieldName3();
        QString fieldName4();
        QString optionName1();
        QString optionName2();
    };

    class ResultListModel: public QAbstractListModel {
        Q_OBJECT
    public:
        explicit ResultListModel(QObject* parent = nullptr);
        Q_INVOKABLE void remove(int index);
        Q_INVOKABLE void edit (int index);
        Q_INVOKABLE void clear(); 
        int rowCount(const QModelIndex & parent) const override;
        QVariant data(const QModelIndex & index, int role) const override;
    };
    
    class StatusBarView {};
}
