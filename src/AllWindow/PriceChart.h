#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QCandlestickSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QDebug>
#include <QObject>
#include <QtCharts/QCandlestickSet>
#include <QtCharts/QCandlestickSeries>
#include "../candlestickdatareader.h"
#include <vector>
#include "../database/database.h"
QT_CHARTS_USE_NAMESPACE
class PriceChart : public QChartView
{
public:
    PriceChart(QChart* chart = nullptr);
    virtual ~PriceChart();
protected:
    virtual void mouseMoveEvent(QMouseEvent *pEvent) override;
    virtual void mousePressEvent(QMouseEvent *pEvent) override;
    virtual void mouseReleaseEvent(QMouseEvent *pEvent) override;
    virtual void wheelEvent(QWheelEvent *pEvent) override;
    virtual void enterEvent(QEvent *pEvent)override;
    virtual void leaveEvent(QEvent *pEvent)override;

private:
    bool leftButtonPressed;
    QPoint prePos;

    QGraphicsLineItem* x_line;
    QGraphicsLineItem* y_line;
    QGraphicsSimpleTextItem* y_text;
    QGraphicsSimpleTextItem* cursor_text;
};
QChartView *BuildPriceChart();
std::vector<QCandlestickSet > BuildPriceChartSeries(QString stockId,int Starttime=0);


