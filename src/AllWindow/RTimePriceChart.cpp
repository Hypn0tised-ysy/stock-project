#include "RTimePriceChart.h"
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QChartView> // Add this line
#include <algorithm>
RTimePriceChart::RTimePriceChart(double Startprice,QChart *chart):
    QChartView(chart),
    leftButtonPressed(false) ,
    prePos(0, 0),
    x_line(nullptr),
    y_line(nullptr),
    cursor_text(nullptr),
    y_text(nullptr)
{
    // 创建线
    x_line = new QGraphicsLineItem();
    // 设置颜色
    x_line->setPen(QPen(QColor( 100, 100, 100 )));
    x_line->setZValue(2);
    y_line = new QGraphicsLineItem();
    y_line->setPen(QPen(QColor( 100, 100, 100 )));
    y_line->setZValue(2);
    y_text = new QGraphicsSimpleTextItem();
    // 添加到scene中。
     this->scene()->addItem(x_line);
    this->scene()->addItem(y_line);
    cursor_text = new QGraphicsSimpleTextItem;
    this->scene()->addItem(cursor_text);
    this->scene()->addItem(y_text);
}
RTimePriceChart::~RTimePriceChart()
{
    delete x_line;
    delete y_line;
    delete cursor_text;
    delete y_text;
}
//// 鼠标移动
void RTimePriceChart::mouseMoveEvent(QMouseEvent *pEvent)
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
    QLineSeries *candle = qobject_cast<QLineSeries *>(chart()->series().at(0));
    if (x<0) x = 0;
    if (x>=candle->count()) x = candle->count()-1;
    auto d = candle->points().at(x).y();
    cursor_text->setText(QString("sit:%1:%2").arg(x).arg(d));
    y_text->setText(QString("y:%1").arg(chart()->mapToValue(pEvent->pos()).y()));
    // 调整显示内容到鼠标右上
    auto pos = pEvent->pos();
    pos.setY(pos.ry()-20);
    pos.setX(pos.rx()+10);
    cursor_text->setPos(pos);
    pos = pEvent->pos();
    pos.setX(this->width()-100);
    y_text->setPos(pos);
    QChartView::mouseMoveEvent(pEvent);
}

//// 鼠标按键
void RTimePriceChart::mousePressEvent(QMouseEvent *pEvent)
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
void RTimePriceChart::mouseReleaseEvent(QMouseEvent *pEvent)
{
    if (pEvent->button() == Qt::LeftButton)
    {
        leftButtonPressed = false;
        this->setCursor(Qt::ArrowCursor);
    }
    QChartView::mouseReleaseEvent(pEvent);
}

void RTimePriceChart::wheelEvent(QWheelEvent *pEvent)
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

void RTimePriceChart::enterEvent(QEvent *pEvent)
{
    x_line->setVisible(true);
    y_line->setVisible(true);
    cursor_text->setVisible(true);
    QChartView::enterEvent(pEvent);
}

void RTimePriceChart::leaveEvent(QEvent *pEvent)
{
    x_line->setVisible(false);
    y_line->setVisible(false);
    cursor_text->setVisible(false);
    QChartView::leaveEvent(pEvent);
}
RTimePriceChartView::RTimePriceChartView(std::vector<StockPrice> _StockPrice,QChart *chart):
    QChartView(chart)
{
    for(auto i:_StockPrice)
    {
        SecondStockPrice.push_back(i.price);
    }
    for(int i=0;i<SecondStockPrice.size();i=i+10)
    {
        auto average = std::accumulate(SecondStockPrice.begin() + i, SecondStockPrice.begin() + i + 10, 0.0) / 10;
        MinuteStockPrice.push_back(average);
    }
    if(SecondStockPrice.size()%10!=0)
    {
        auto average = std::accumulate(SecondStockPrice.end() - SecondStockPrice.size()%10, SecondStockPrice.end(), 0.0) / (SecondStockPrice.size()%10);
        MinuteStockPrice.push_back(average);
    }
    secondSeries = new QLineSeries();
    minuteSeries = new QLineSeries();
    for(int i=0;i<SecondStockPrice.size();i++)
    {
        secondSeries->append(i,SecondStockPrice[i]);
    }
    for(int i=0;i<SecondStockPrice.size();i=i+10)
    {
        minuteSeries->append(i,MinuteStockPrice[i/10]);
    }
    if(SecondStockPrice.size()%10!=0)
    {
        minuteSeries->append(SecondStockPrice.size()-1,MinuteStockPrice[MinuteStockPrice.size()-1]);
    }

    secondSeries->setColor(Qt::blue);
    minuteSeries->setColor(Qt::black);  
    setRenderHint(QPainter::Antialiasing);
    ShowChart=new QChart();
    ShowChart->addSeries(secondSeries);
    ShowChart->addSeries(minuteSeries);
    ShowChart->createDefaultAxes();
    ShowChart->legend()->hide();
    double miny = *std::min_element(SecondStockPrice.begin(), SecondStockPrice.end());
    double maxy = *std::max_element(SecondStockPrice.begin(), SecondStockPrice.end());
    ShowChart->axisY()->setRange(miny*0.95, maxy*1.05);
    RTimechart = new RTimePriceChart(SecondStockPrice[0],ShowChart);
}
RTimePriceChartView::~RTimePriceChartView()
{
    delete secondSeries;
    delete minuteSeries;
}
void RTimePriceChartView::UpdateNewSecond(double price)
{
    secondSeries->append(SecondStockPrice.size(),price);
    SecondStockPrice.push_back(price);
    if(SecondStockPrice.size()%10==0)
    {
        auto average = std::accumulate(SecondStockPrice.end() - 10, SecondStockPrice.end(), 0.0) / 10;
        MinuteStockPrice.pop_back();
        MinuteStockPrice.push_back(average);
        minuteSeries->replace(MinuteStockPrice.size()-1,SecondStockPrice.size()-10,average);
    }
    else
    {
        if(SecondStockPrice.size()%10==1)
        {
            auto average=price;
            MinuteStockPrice.push_back(average);
            minuteSeries->append(SecondStockPrice.size()-1,average);
        }
        else
        {
            auto average = std::accumulate(SecondStockPrice.end() - SecondStockPrice.size()%10, SecondStockPrice.end(), 0.0) / (SecondStockPrice.size()%10);
            MinuteStockPrice.pop_back();
            MinuteStockPrice.push_back(average);
            minuteSeries->replace(MinuteStockPrice.size()-1,SecondStockPrice.size()-SecondStockPrice.size()%10,average);
        }
    }
    ShowChart->axisX()->setRange(0,SecondStockPrice.size()+5);
}