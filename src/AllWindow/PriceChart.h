#pragma once
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtGui/QMouseEvent>

QT_CHARTS_USE_NAMESPACE

class PriceChart : public QChartView
{
public:
    PriceChart(QWidget *parent = nullptr)
        : QChartView(parent)
    {
        // Create line series
        QLineSeries *series = new QLineSeries();
        series->setName("Price");

        // Add data to the series
        QVector<double> xData = {1, 2, 3, 4, 5};
        QVector<double> yData = {10, 20, 15, 25, 30};
        for (int i = 0; i < xData.size(); ++i) {
            series->append(xData[i], yData[i]);
        }

        // Create chart and add series
        QChart *chart = new QChart();
        chart->addSeries(series);

        // Set up X and Y axes
        QValueAxis *xAxis = new QValueAxis();
        xAxis->setTitleText("X");
        chart->setAxisX(xAxis, series);

        QValueAxis *yAxis = new QValueAxis();
        yAxis->setTitleText("Y");
        chart->setAxisY(yAxis, series);

        // Set up chart view
        setChart(chart);
        setRenderHint(QPainter::Antialiasing);
    }

protected:
    void mouseMoveEvent(QMouseEvent *event) override
    {
        // Get mouse coordinates
        QPointF mousePos = chart()->mapToValue(event->pos());

        // Find the closest point on the line series
       //找到line series中最接近鼠标X坐标的点
        QLineSeries *series = static_cast<QLineSeries *>(chart()->series().at(0));
        QPointF closestPoint;
        qreal distance = std::numeric_limits<qreal>::max();
        for (int i = 0; i < series->count(); ++i) {
            QPointF point = series->at(i);
            qreal dx = point.x() - mousePos.x();
            qreal dy = point.y() - mousePos.y();
            qreal d = abs(dx);
            if (d < distance) {
                distance = d;
                closestPoint = point;
            }
        }
    shouldDraw = true;
    drawRect = QRectF(event->pos(), QSizeF(100, 50));
    drawText = QString("X: %1\nY: %2").arg(closestPoint.x()).arg(closestPoint.y());

    // 请求更新，这将导致 paintEvent 被调用
    update();

    QChartView::mouseMoveEvent(event);
        // Display the data of the closest point

    }
    void paintEvent(QPaintEvent *event) {
    QChartView::paintEvent(event); // 调用基类的 paintEvent

    if (shouldDraw) {
        QPainter painter(viewport());
        painter.setPen(Qt::blue);
        painter.drawRect(drawRect);
        painter.drawText(drawRect, Qt::AlignCenter, drawText);
    }
}
    private:
    bool shouldDraw = false;
    QRectF drawRect;
    QString drawText;
};

