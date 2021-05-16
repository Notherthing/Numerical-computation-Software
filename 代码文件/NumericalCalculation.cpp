#include <QMessageBox>
#include <vector>
#include <string>
#include <iostream>
#include <QString>
#include "NumericalCalculation.h"
#include "InterpolationCalculation.h"
#include "TypeTrans.h"
#include "Intergration.h"
#include "qcustomplot.h"
#include "DirectSolveEq.h"
#include "IterationSolve.h"
#include "CharacteristicValue.h"
#include "runtimedll.h"

#define maxn 100

using namespace std;
using namespace RuntimeDll;
NumericalCalculation::NumericalCalculation(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    hdll=NULL;
}

void Excepthanding()
{
    QString warning_info = "Please check the information you input";
    QString title = "Error Warning";
    //ui.label->setText(ans);
    static QMessageBox information(QMessageBox::NoIcon, title, warning_info);
    //information.setGeometry(80,80,100,100);
    information.show();
}
void NumericalCalculation::About() //作者函数
{
    //QMessageBox information(QWidget * parent,QString Author,QString Author_info);
    QString Author_info = "Author: Yuchen Huang \nStudent ID: 10185102253";
    QString title = "Author Information";
    //ui.label->setText(ans);
    static QMessageBox information(QMessageBox::NoIcon,title,Author_info);
    //information.setGeometry(80,80,100,100);
    information.show();
}

void NumericalCalculation::Exit()
{
    QApplication* app;
    app->quit();
}

void NumericalCalculation::Calculate()
{
    InterpolationCalculation interpolationCalculation;
    //调用插值多项式类函数
    TypeTrans typeTrans;  
    //调用类型转换类函数
    //const QString ans = "ok";
    //ui.label_10->setText(ans);
    QString xSpot,ySpot,pValue,deValue;
    string xStr, yStr, pStr,dvStr;
    xSpot = ui.lineEdit->text();
    ySpot = ui.lineEdit_2->text();
    pValue = ui.lineEdit_3->text();
    deValue = ui.lineEdit_4->text();
    xStr = xSpot.toStdString();
    yStr = ySpot.toStdString();
    pStr = pValue.toStdString();
    dvStr = deValue.toStdString();
    int deVa = typeTrans.str2int(dvStr);
    //QString test;
    //test=test.fromStdString(xStr);
    //ui.label_10->setText(test);

    vector<double> xVec, yVec;
    double pNum;
    xVec = typeTrans.str2vec(xStr);
    yVec = typeTrans.str2vec(yStr);
    pNum = typeTrans.str2doub(pStr);
    
    vector<double> lagPoly; //保存拉格朗日多项式系数
    lagPoly = interpolationCalculation.lagrange_poly(xVec, yVec);
    
    string lagStr = interpolationCalculation.lagrange_str(lagPoly);
    QString lagQstr;
    lagQstr = lagQstr.fromStdString(lagStr); //得到拉格朗日多项式Qstring，用于显示输出
    double value_lag, value_newton;
    value_lag = interpolationCalculation.value_ans(pNum, lagPoly);
    value_newton = interpolationCalculation.newton(pNum, xVec, yVec);
   
    string valg_str, vane_str;
    valg_str = to_string(value_lag);
    vane_str = to_string(value_newton);
    QString value_lag_Qstr, value_newton_Qstr,value_pie_Qstr, piePloy_Qstr;
    value_lag_Qstr = value_lag_Qstr.fromStdString(valg_str);
    value_newton_Qstr = value_newton_Qstr.fromStdString(vane_str);

    string piecewiseStr = interpolationCalculation.piecewise(deVa,pNum,xVec,yVec);//得到分段插值估值结果
    string piePloy = interpolationCalculation.piecewise_poly(deVa, pNum, xVec, yVec);//得到分段插值多项式
    piePloy_Qstr = value_pie_Qstr.fromStdString(piePloy);
    value_pie_Qstr = value_pie_Qstr.fromStdString(piecewiseStr);
    ui.label_6->setText(lagQstr);
    ui.label_8->setText(value_lag_Qstr);
    ui.label_10->setText(value_newton_Qstr);
    ui.label_13->setText(value_pie_Qstr);
    ui.label_15->setText(piePloy_Qstr);
}

void NumericalCalculation::PaintxyInter()
{
    InterpolationCalculation interpolationCalculation;
    //调用插值多项式类函数
    TypeTrans typeTrans;
    //调用类型转换类函数
    QString xSpot, ySpot, pValue, deValue;
    string xStr, yStr, pStr, dvStr;
    xSpot = ui.lineEdit->text();
    ySpot = ui.lineEdit_2->text();
    pValue = ui.lineEdit_3->text();
    deValue = ui.lineEdit_4->text();
    xStr = xSpot.toStdString();
    yStr = ySpot.toStdString();
    pStr = pValue.toStdString();
    dvStr = deValue.toStdString();
    int deVa = typeTrans.str2int(dvStr);

    vector<double> xVec, yVec;
    double pNum;
    xVec = typeTrans.str2vec(xStr);
    yVec = typeTrans.str2vec(yStr);
    pNum = typeTrans.str2doub(pStr);

    vector<double> lagPoly; //保存拉格朗日多项式系数
    lagPoly = interpolationCalculation.lagrange_poly(xVec, yVec);

    double xMin = typeTrans.findMin(xVec);
    double xMax = typeTrans.findMax(xVec);
    double xRange = xMax - xMin;

    QCustomPlot* customPlot = ui.customPlot;
    //每条曲线都会独占一个graph()
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // 曲线的颜色
    customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色
    customPlot->addGraph();//添加graph等价于添加新曲线
    customPlot->graph(1)->setPen(QPen(Qt::red)); // 曲线的颜色
    // 生成模拟数据点 (x-y0 第一条曲线, x-y1为第2条曲线):
    QVector<double> x(15000), y0(15000), y1(15000);
    
    for (int i = 0; i < 15000; ++i)
    {
        x[i] = xMin + i*(xRange/15000);
        y0[i] = interpolationCalculation.value_ans(x[i],lagPoly); // 第一条曲线：拉格朗日插值函数曲线
        if ((interpolationCalculation.piecewise(deVa, x[i], xVec, yVec) != "Piecewise interpolate has failed."))
        {
            y1[i] = typeTrans.str2doub(interpolationCalculation.piecewise(deVa, x[i], xVec, yVec));              // 第二条曲线：分段插值函数
        }
        else y1[i] = 0;
    }
    // 边框右侧和上侧均显示刻度线，但不显示刻度值:
    // (参见 QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);
    // 使上下两个X轴的范围总是相等，使左右两个Y轴的范围总是相等
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // 把已存在的数据填充进graph的数据区
    customPlot->graph(0)->setData(x, y0);
    customPlot->graph(1)->setData(x, y1);
    //自动调整XY轴的范围，以便显示出graph(0)中所有的点（下面会单独讲到这个函数）
    customPlot->graph(0)->rescaleAxes();
    //自动调整XY轴的范围，以便显示出graph(1)中所有的点
    customPlot->graph(1)->rescaleAxes(true);
    // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    // 立即刷新图像
    ui.customPlot->replot();
}

void NumericalCalculation::intergrate_cal()
{
    Intergration intergration;
    TypeTrans typeTrans;
    double a, b, e;
    int n;
    QString funcqs,aqs, bqs, nqs, eqs;
    QString CTF_ans,CSF_ans,VSS_ans,Bstep_ans,RB_ans;
    string funcs,as, bs, ns, es;
    string CTF_str,CSF_str,VSS_str,RB_str,Bstep_str;

    funcqs = ui.lineEdit_15->text();
    funcs = funcqs.toStdString();

    char test1[maxn], pos_e[maxn], mid_e(maxn);
    double val[maxn];

    strcpy(test1, funcs.c_str());
    parse(test1, pos_e, val);
    double x = 0;
    double res = evaluate(x, pos_e, val);

    aqs = ui.lineEdit_5->text();
    as = aqs.toStdString();
    a = typeTrans.str2doub(as);

    bqs = ui.lineEdit_6->text();
    bs = bqs.toStdString();
    b = typeTrans.str2doub(bs);

    nqs = ui.lineEdit_7->text();
    ns = nqs.toStdString();
    n = int(typeTrans.str2doub(ns));

    eqs = ui.lineEdit_8->text();
    es = eqs.toStdString();
    e = typeTrans.str2doub(es);

    double CTF, CSF, VSS, Bstep, RB;
   
    CTF = intergration.CTF(a, b, n, evaluate,pos_e,val);
    CSF = intergration.CSF(a, b, n, evaluate, pos_e, val);
    VSS = intergration.VariableStepSize(a, b, e, evaluate, pos_e, val)[0];
     Bstep = intergration.VariableStepSize(a, b, e, evaluate, pos_e, val)[1];
     RB = intergration.Romberg(a, b, e, evaluate, pos_e, val)[0];
    
    CTF_ans = CTF_ans.fromStdString(to_string(CTF));
    ui.label_22->setText(CTF_ans);
    CSF_ans = CSF_ans.fromStdString(to_string(CSF));
    ui.label_25->setText(CSF_ans);
    VSS_ans = VSS_ans.fromStdString(to_string(VSS));
    ui.label_27->setText(VSS_ans);
    Bstep_ans = Bstep_ans.fromStdString(to_string(Bstep));
    ui.label_29->setText(Bstep_ans);
    RB_ans = RB_ans.fromStdString(to_string(RB));
    ui.label_32->setText(RB_ans);
}

void NumericalCalculation::DirectSolve()
{
    TypeTrans typeTrans;
    DirectSolveEq  directSolveEq;
    int solve = 0;
    if (ui.radioButton_5->isChecked())  solve = 0;
    if (ui.radioButton_8->isChecked())  solve = 1;
    if (ui.radioButton_9->isChecked())  solve = 2;
    int n;
    QString N;
    string N_str;
    N = ui.lineEdit_9->text();
    N_str = N.toStdString();
    n = int(typeTrans.str2doub(N_str));
    QString nnAry;
    string nnAry_str;
    nnAry = ui.textEdit->toPlainText();
    nnAry_str = nnAry.toStdString();
    vector<vector<double> > nnary = typeTrans.nnArray(nnAry_str);
    QString nVec;
    string nVec_str;
    nVec = ui.lineEdit_10->text();
    nVec_str = nVec.toStdString();
    vector<double> nvec = typeTrans.vec(nVec_str);
    if (N_str == "" || nnAry_str == "" || nVec_str == "")
    {
        Excepthanding();
        return;
    }
    if (!typeTrans.fineMar(nnary, nvec, n))
    {
        Excepthanding();
        return;
    }
    string result;
    if (solve==0)
    {
        result = directSolveEq.Gauss(nnary, nvec, n);
    }
    if (solve==1)
    {
        result = directSolveEq.Square(nnary, nvec, n);
    }
    if (solve==2)
    {
        result = directSolveEq.Chasing_method(nnary, nvec, n);
    }
    QString re_Qstr = re_Qstr.fromStdString(result);
    ui.textBrowser->setText(re_Qstr);
}

void NumericalCalculation::Iteration_Solve()
{
    TypeTrans typeTrans;
    IterationSolve itertionSolve;
    int solve = 0;
    if (ui.radioButton_6->isChecked())  solve = 0;
    if (ui.radioButton_10->isChecked())  solve = 1;
    if (ui.radioButton_11->isChecked())  solve = 2;
    QString nnAry;
    string nnAry_str;
    nnAry = ui.textEdit_2->toPlainText();
    nnAry_str = nnAry.toStdString();
    vector<vector<double> > nnary = typeTrans.nnArray(nnAry_str);
    QString nVec;
    string nVec_str;
    nVec = ui.lineEdit_12->text();
    nVec_str = nVec.toStdString();
    vector<double> nvec = typeTrans.vec(nVec_str);

    double e;
    QString eQStr;
    string e_Str;
    eQStr = ui.lineEdit_14->text();
    e_Str = eQStr.toStdString();
    e = (typeTrans.str2doub(e_Str));

    double w;
    QString wQStr;
    string w_Str;
    wQStr = ui.lineEdit_13->text();
    w_Str = wQStr.toStdString();
    w = (typeTrans.str2doub(w_Str));

    int n;
    QString N;
    string N_str;
    N = ui.lineEdit_11->text();
    N_str = N.toStdString();
    n = int(typeTrans.str2doub(N_str));
    if (N_str == "" || nnAry_str == "" || nVec_str == "" || e_Str=="" || w_Str=="")
    {
        Excepthanding();
        return;
    }
    if (!typeTrans.fineMar(nnary, nvec, n))
    {
        Excepthanding();
        return;
    }

    string result;
    if (nnary.size() != 0 && nvec.size() != 0)
    {
        if (solve == 0)
        {
            result = itertionSolve.Jacobi(nnary, nvec, e);
        }
        if (solve == 1)
        {
            result = itertionSolve.GS(nnary, nvec, e);
        }
        if (solve == 2)
        {
            result = itertionSolve.SOR(nnary, nvec, e, w);
        }
    }
    QString re_Qstr = re_Qstr.fromStdString(result);
    ui.textBrowser_2->setText(re_Qstr);
}

void NumericalCalculation::Charactvalue()
{
    TypeTrans typeTrans;
    CharacteristicValue  characteristicValue;

    QString nnAry;
    string nnAry_str;
    nnAry = ui.textEdit_3->toPlainText();
    nnAry_str = nnAry.toStdString();
    vector<vector<double> > nnary = typeTrans.nnArray(nnAry_str);

    QString nVec;
    string nVec_str;
    nVec = ui.lineEdit_17->text();
    nVec_str = nVec.toStdString();
    vector<double> nvec = typeTrans.vec(nVec_str);

    vector<vector<double> > nnvec = typeTrans.transpose(nvec);
    double e;
    QString eQStr;
    string e_Str;
    eQStr = ui.lineEdit_18->text();
    e_Str = eQStr.toStdString();
    e = (typeTrans.str2doub(e_Str));

    if (nnAry_str == "" || nVec_str == "" || e_Str == "" )
    {
        Excepthanding();
        return;
    }
    int n = nvec.size();
    if (!typeTrans.fineMar(nnary, nvec, n))
    {
        Excepthanding();
        return;
    }


    string res_max, res_min;
    res_max = characteristicValue.Iter_max(nnary, nnvec, e);
    res_min = characteristicValue.Iter_min(nnary, nnvec, e);
    
    QString resQS_max, resQS_min;
    resQS_max = resQS_max.fromStdString(res_max);
    ui.textBrowser_3->setText(resQS_max);
    resQS_min = resQS_min.fromStdString(res_min);
    ui.textBrowser_4->setText(resQS_min);
}

void NumericalCalculation::LastPartcal()
{
    TypeTrans typeTrans;
    QString hQs, xMax, Initial;
    int N = 10;
    hQs =ui.lineEdit_19->text();
    xMax = ui.lineEdit_20->text();
    Initial = ui.textEdit_5->toPlainText();
    double x_tar = typeTrans.str2doub(xMax.toStdString());
    double h = typeTrans.str2doub(hQs.toStdString());
    int solve = 0;
    if (ui.radioButton_4->isChecked())  solve = 0;
    if (ui.radioButton_3->isChecked())  solve = 1;
    if (ui.radioButton_7->isChecked())  solve = 2;
    if (func_str != ui.textEdit_4->toPlainText()) {
        auto ans = QMessageBox::question(this, "未编译的修改", "您修改了函数，是否重新编译？");
        if (ans == QMessageBox::Yes) {
            MakeCode();
            if (!func)  // compile failed
                return;
        }
        else return;
    }
    auto init_code = vs2vd(doc2vec(ui.textEdit_5->document()));
    point init = { init_code[0], ndarray(init_code.begin() + 1, init_code.end()) };
    if (x_tar <= init.x)
        h *= -1;
    point p;
    // choose different method
    if (solve == 0) {
        p = EulerMethod(func, init, h, x_tar);
    }
    else if (solve == 1) {
        p = EulerAdvanced(func, init, h, x_tar);
    }
    else if (solve == 2) {
        int default_val = 4, min_val = 2, max_val = 4, order;
        bool ok;
        order = QInputDialog::getInt(this, "Runge-Kutta法", "order=",
            default_val, min_val, max_val, 1, &ok);
        if (!ok) return;
        p = RungeKuttaMethod(func, init, h, x_tar, order);
    }
    string output = "";
    for (int i = 0; i < path.size(); i++)
    {
        output += to_string(path[i].x);
        output += "     ";
        for (int j = 0; j < (path[i].y).size(); j++)
        {
            output += to_string((path[i].y)[j]);
            output += " ";
        }
        output += '\n';
    }
    QString outputQs = outputQs.fromStdString(output);
    ui.textBrowser_5->setText(outputQs);
}



void NumericalCalculation::MakeCode()
{
    func_t f = getCustomFunc();
    func = f;
    if (!func)
        return;
    func_str = ui.textEdit_4->toPlainText();
    QMessageBox::information(this, "编译自定义函数", "编译成功！\n\n请选择算法");
}

func_t  NumericalCalculation::compileFuncOnWindows()
{
    static std::string dllname("dllfunc");
    QFile file(QString(dllname.c_str()) + ".cpp");
    if (!file.exists()) {
        QMessageBox::critical(this, "编译自定义函数", "源文件不存在！\n"
            "请检查dllfunc.cpp的位置\n"
            "可能是内部错误，请联系作者");
        return nullptr;
    }
    if (hdll) FreeLibrary(hdll);
    switch (compileDll(dllname)) {
    case COMMAND_NOT_EXEC:
        QMessageBox::critical(this, "编译自定义函数", "编译失败！\n"
            "可能是没有编译器，请确保环境中存在g++");
        return nullptr;
    case COMPILE_FAIL:
        QMessageBox::critical(this, "编译自定义函数", "编译失败！\n"
            "可能是函数不符合C++语法");
        return nullptr;
    }

    auto hinst = getDll(dllname);
    if (!hinst) {
        QMessageBox::critical(this, "编译自定义函数", "无法打开DLL文件！");
        //        mydebug(GetLastError())
        return nullptr;
    }
    hdll = hinst;
    func_t f = (func_t)getFirstFuncInDll(hdll);
    if (!f) {
        QMessageBox::critical(this, "编译自定义函数", "无法找到目标函数！");
        return nullptr;
    }
    return f;
}

QVector<QString> NumericalCalculation::doc2vec(QTextDocument* doc)
{
    QVector<QString> rst;
    int tot = doc->blockCount();        //回车符分隔block
    for (int i = 0; i < tot; i++) {
        QString line = doc->findBlockByNumber(i).text();
        line = line.simplified();
        if (line.isEmpty()) break;
        rst.push_back(line);
    }
    return rst;
}

QVector<double> NumericalCalculation::vs2vd(const QVector<QString>& vec)
{
    QVector<double> rst;
    for (int i = 0; i < vec.size(); i++) {
        bool ok = true;
        QString s = vec[i];
        for (int idx = 0; ; ++idx) {
            double num = s.section(' ', idx, idx).toDouble(&ok);
            if (!ok) break;
            // two numbers on one line, error
            if (idx) return QVector<double>{};
            rst.push_back(num);
        }
    }
    return rst;
}

func_t NumericalCalculation::getCustomFunc()
{
    static const QString header(
        "#include <vector>\n"
        "#include <cmath>\n"
        "using namespace std;\n"
        "typedef vector<double> ndarray;\n"
        "\n"
    );
    static const QString func_head(
        "__declspec (dllexport) ndarray func(double x, const ndarray &y) {\n"
        "    ndarray rst(y.size());\n"
    );
    static const QString func_tail(
        "    return rst;\n"
        "}\n"
    );

    auto func_code = doc2vec(ui.textEdit_4->document());
    if (func_code.empty()) {
        QMessageBox::critical(this, "编译自定义函数", "请输入函数");
        return nullptr;
    }

    // generate dllfunc.cpp
    QFile file("dllfunc.cpp");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "编译自定义函数", "无法打开文件dllfunc.cpp");
        return nullptr;
    }
    QTextStream out(&file);
    out << header << func_head;
    for (int i = 0; i < func_code.size(); ++i)
        out << QString("    rst[%1] = ").arg(i) << func_code[i] << ";\n";
    out << func_tail;
    //    out.flush();
    file.close();
    return compileFuncOnWindows();
}
