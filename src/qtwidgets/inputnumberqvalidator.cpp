#include "inputnumberqvalidator.hpp"

InputNumberQValidator::InputNumberQValidator(QObject *parent) : QValidator(parent)
{}

QValidator::State InputNumberQValidator::validate(QString& input, int& pos) const
{
    bool hasDecimalSeparator = false;
    QString::const_iterator itr;
    bool inDigit = true;
    bool hasSigh = false;
    for (itr = input.begin(); itr != input.end(); ++itr) {
        QChar letter = *itr;
        if(letter.isDigit()) {
            if (!hasSigh && !inDigit) {
                return QValidator::State::Invalid;
            }
            inDigit = true;
            hasSigh = false;
        } else if (letter == QChar('.') || letter == QChar(',')) {
            if (!inDigit || hasSigh || hasDecimalSeparator) {
                return QValidator::State::Invalid;
            }/*
            if (itr + 1 == input.end() ) {
                return QValidator::State::Intermediate;
            }*/
            hasDecimalSeparator = true;
        } else if (letter == QChar(' ')) {
            inDigit = false;
            hasDecimalSeparator = false;
        } else if (letter == QChar('+') || letter == QChar('-')) {
            if (hasSigh) {
                return QValidator::State::Invalid;
            }
            hasSigh = true;
            inDigit = false;
            hasDecimalSeparator = false;
        } else {
            return QValidator::State::Invalid;
        }
    }
    return QValidator::State::Acceptable;
}

