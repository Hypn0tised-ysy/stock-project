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
#include <QtCharts/QCandlestickSet>
#include <QtCharts/QCandlestickSeries>
#include "../candlestickdatareader.h"
#include <vector>
#include "../database/database.h"
#include "../implementation/StockPrice.h"
QT_CHARTS_USE_NAMESPACE
class RTimePriceChart : public QChartView
{
public:
    RTimePriceChart(double StartPrice,QChart* chart = nullptr);
    virtual ~RTimePriceChart();
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
    QGraphicsLineItem* StartPriceLine;
};
class RTimePriceChartView:public  QChartView
{
    Q_OBJECT
    private:
    
    std::vector<double> SecondStockPrice;
    std::vector<double> MinuteStockPrice;
   
    public:
    RTimePriceChartView(std::vector<StockPrice> _StockPrice,QChart *chart=nullptr);
    void UpdateNewSecond(double price);
    ~RTimePriceChartView(); 
    RTimePriceChart *RTimechart;
    QLineSeries *secondSeries;
    QLineSeries *minuteSeries;
    QChart* ShowChart;
};