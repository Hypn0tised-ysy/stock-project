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
        QLineSeries *series = static_cast<QLineSeries *>(chart()->series().at(0));
        QPointF closestPoint = series->pointAt(series->closestPoint(mousePos));

        // Display the data of the closest point
        qDebug() << "X: " << closestPoint.x() << ", Y: " << closestPoint.y();

        QChartView::mouseMoveEvent(event);
    }
};

