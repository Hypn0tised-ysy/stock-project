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

    QGraphicsSimpleTextItem* cursor_text;
};



PriceChart::PriceChart(QChart *chart):
    QChartView(chart),
    leftButtonPressed(false) ,
    prePos(0, 0),
    x_line(nullptr),
    y_line(nullptr),
    cursor_text(nullptr)
{
    // 创建线
    x_line = new QGraphicsLineItem();
    // 设置颜色
    x_line->setPen(QPen(QColor( 100, 100, 100 )));
    x_line->setZValue(2);
    y_line = new QGraphicsLineItem();
    y_line->setPen(QPen(QColor( 100, 100, 100 )));
    y_line->setZValue(2);

    // 添加到scene中。
    this->scene()->addItem(x_line);
    this->scene()->addItem(y_line);

    cursor_text = new QGraphicsSimpleTextItem;
    this->scene()->addItem(cursor_text);

}
PriceChart::~PriceChart()
{

}
//// 鼠标移动
void PriceChart::mouseMoveEvent(QMouseEvent *pEvent)
{
    if (leftButtonPressed)
    {
        QPoint oDeltaPos = pEvent->pos() - prePos;
        this->chart()->scroll(-oDeltaPos.x(), oDeltaPos.y());
        prePos = pEvent->pos();
    }        

    // 绘制线
    x_line->setLine(pEvent->pos().rx(),0,pEvent->pos().rx(),this->height());
    y_line->setLine(0,pEvent->pos().ry(),this->width(),pEvent->pos().ry());

    // 设置显示内容
    auto valpos = chart()->mapToValue(pEvent->pos());
    int x = int(valpos.x());
    QCandlestickSeries *candle = qobject_cast<QCandlestickSeries *>(chart()->series().at(0));
    if (x<0) x = 0;
    if (x>=candle->count()) x = candle->count()-1;
    auto d = candle->sets().at(x)->close();
    cursor_text->setText(QString("sit:%1:%2").arg(x).arg(d));
    // 调整显示内容到鼠标右上
    auto pos = pEvent->pos();
    pos.setY(pos.ry()-20);
    pos.setX(pos.rx()+10);
    cursor_text->setPos(pos);

    QChartView::mouseMoveEvent(pEvent);
}

//// 鼠标按键
void PriceChart::mousePressEvent(QMouseEvent *pEvent)
{
    if (pEvent->button() == Qt::LeftButton)
    {
        leftButtonPressed = true;
        prePos = pEvent->pos();
        this->setCursor(Qt::OpenHandCursor);
    }
    QChartView::mousePressEvent(pEvent);
}
//// 鼠标抬起
void PriceChart::mouseReleaseEvent(QMouseEvent *pEvent)
{
    if (pEvent->button() == Qt::LeftButton)
    {
        leftButtonPressed = false;
        this->setCursor(Qt::ArrowCursor);
    }
    QChartView::mouseReleaseEvent(pEvent);
}

void PriceChart::wheelEvent(QWheelEvent *pEvent)
{
    qreal rVal;
    if (pEvent->angleDelta().y() > 0)
        rVal = 0.99;
    else
        rVal = 1.01;


    // 1. 读取视图基本信息
    QRectF oPlotAreaRect = this->chart()->plotArea();
    QPointF oCenterPoint = oPlotAreaRect.center();
    // 2. 水平调整
    oPlotAreaRect.setWidth(oPlotAreaRect.width() * rVal);
    // 3. 竖直调整
    oPlotAreaRect.setHeight(oPlotAreaRect.height() * rVal);
    // 4.1 计算视点，视点不变，围绕中心缩放
    //QPointF oNewCenterPoint(oCenterPoint);
    // 4.2 计算视点，让鼠标点击的位置移动到窗口中心
    //QPointF oNewCenterPoint(pEvent->pos());
    // 4.3 计算视点，让鼠标点击的位置尽量保持不动(等比换算，存在一点误差)
    QPointF oNewCenterPoint(2 * oCenterPoint - pEvent->position() - (oCenterPoint - pEvent->position()) / rVal);
    // 5. 设置视点
    oPlotAreaRect.moveCenter(oNewCenterPoint);
    // 6. 提交缩放调整
    this->chart()->zoomIn(oPlotAreaRect);

    QChartView::wheelEvent(pEvent);
}

void PriceChart::enterEvent(QEvent *pEvent)
{
    x_line->setVisible(true);
    y_line->setVisible(true);
    cursor_text->setVisible(true);
    QChartView::enterEvent(pEvent);
}

void PriceChart::leaveEvent(QEvent *pEvent)
{
    x_line->setVisible(false);
    y_line->setVisible(false);
    cursor_text->setVisible(false);
    QChartView::leaveEvent(pEvent);
}
QChartView* BuildPriceChart()
{
     QCandlestickSeries *acmeSeries = new QCandlestickSeries();
    acmeSeries->setName("Acme Ltd");
    acmeSeries->setIncreasingColor(QColor(Qt::green));
    acmeSeries->setDecreasingColor(QColor(Qt::red));

    QLineSeries *closeSeries = new QLineSeries();
    closeSeries->setName("close");
    closeSeries->setColor(QColor(Qt::black));

    // 示例数据
    QFile acmeData("E:/StockMarket/src/acme_data.txt");
    if (!acmeData.open(QIODevice::ReadOnly | QIODevice::Text))
        return nullptr;

    QStringList categories;

    CandlestickDataReader dataReader(&acmeData);
    int i = 0;
    while (!dataReader.atEnd()) {
        QCandlestickSet *set = dataReader.readCandlestickSet();
        if (set) {
            acmeSeries->append(set);
            closeSeries->append(QPointF(i++, set->close()));
            categories << QDateTime::fromMSecsSinceEpoch(set->timestamp()).toString("dd");            
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(acmeSeries);
    chart->addSeries(closeSeries);
    chart->setTitle("Acme Ltd Historical Data (July 2015)");
    chart->setAnimationOptions(QChart::SeriesAnimations);


    chart->createDefaultAxes();

    QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
    axisX->setCategories(categories);

    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.01);
    axisY->setMin(axisY->min() * 0.99);    
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new PriceChart(chart);
    // 抗锯齿
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}