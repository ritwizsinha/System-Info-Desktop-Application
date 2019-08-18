#include "CpuWidget.h"
using namespace QtCharts;
#include "SysInfo.h"
CpuWidget::CpuWidget(QWidget* parent):
    SysInfoWidget (parent),
    mSeries(new QPieSeries(this))
{
mSeries->setHoleSize(0.35);
mSeries->append("CPU Load",30.0);

mSeries->append("CPU Free",70.0);
QChart* chart = chartView().chart();
chart->addSeries(mSeries);
chart->setTitle("CPU Average Load");
}
void CpuWidget::updateSeries(){
    double cpuLoadAverage = SysInfo::instance().cpuLoadAverage();
    mSeries->clear();
    mSeries->append("Load", cpuLoadAverage);
    mSeries->append("Free",100.0-cpuLoadAverage);
}
