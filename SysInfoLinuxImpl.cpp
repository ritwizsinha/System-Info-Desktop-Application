#include "SysInfoLinuxImpl.h"
#include "SysInfoLinuxImpl.h"
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <QtGlobal>
#include <QFile>
SysInfoLinuxImpl::SysInfoLinuxImpl():SysInfo (),mCpuLoadLastValues()
{

}
void SysInfoLinuxImpl::init(){
    mCpuLoadLastValues = cpuRawdata();
}
double SysInfoLinuxImpl::memoryUsed(){
    struct sysinfo meminfo;
    sysinfo(&meminfo);

    qulonglong totalMemory = meminfo.totalram;
    totalMemory +=meminfo.totalswap;
    totalMemory += meminfo.mem_unit;

    qulonglong totalMemoryUsed = meminfo.totalram -meminfo.freeram;
    totalMemoryUsed += meminfo.totalswap - meminfo.freeswap;
    totalMemoryUsed += meminfo.mem_unit;

    double percent = (double)totalMemoryUsed /(double)totalMemory *100;
    return qBound(0.0,percent,100.0);
}
QVector<qulonglong> SysInfoLinuxImpl::cpuRawdata(){
    QFile file("/proc/stat");
    file.open(QIODevice::ReadOnly);
    QByteArray line = file.readLine();
    file.close();
    qulonglong totalUser =0, totalUserNice = 0,totalSystem=0,totalIdle =0;
    std::sscanf(line.data(),"cpu %llu %llu %llu %llu",&totalUser,&totalUserNice,&totalSystem,&totalIdle);
    QVector<qulonglong> rawData;
    rawData.append(totalUser);
    rawData.append(totalUserNice);
    rawData.append(totalSystem);
    rawData.append(totalIdle);
    return rawData;
}
double SysInfoLinuxImpl::cpuLoadAverage()
{
    QVector<qulonglong> firstSample = mCpuLoadLastValues;
    QVector<qulonglong> secondSample = this->cpuRawdata();
    mCpuLoadLastValues = secondSample;

    double overall = (secondSample[0] - firstSample[0])
        + (secondSample[1] - firstSample[1])
        + (secondSample[2] - firstSample[2]);

    double total = overall + (secondSample[3] - firstSample[3]);
    double percent = (overall / total) * 100.0;
    return qBound(0.0, percent, 100.0);
}
