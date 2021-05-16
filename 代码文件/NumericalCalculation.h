#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <vector>
#include <string>
#include <iostream>
#include "ui_NumericalCalculation.h"
#include "InterpolationCalculation.h"
#include "TypeTrans.h"
#include "Intergration.h"
#include "qcustomplot.h"
#include "CharacteristicValue.h"
#include "odesolver.h"

using namespace  OdeSolver;
class NumericalCalculation : public QMainWindow
{
    Q_OBJECT

public:
    QString  func_str;
    func_t func;
    NumericalCalculation(QWidget *parent = Q_NULLPTR);
    func_t compileFuncOnWindows();
    func_t getCustomFunc();
    QVector<QString> doc2vec(QTextDocument* doc);
    QVector<double> vs2vd(const QVector<QString>& vec);
private:
    Ui::NumericalCalculationClass ui;
    HINSTANCE hdll;
protected:
    public slots:
    void About();
    void Exit();
    void Calculate();
    void PaintxyInter();
    void intergrate_cal();
    void DirectSolve();
    void Iteration_Solve();
    void Charactvalue();
    void LastPartcal();
    void MakeCode();
};

