#ifndef SYSINFOLINUXIMPL_H
#define SYSINFOLINUXIMPL_H
#include "SysInfo.h"
#include <QtGlobal>
#include <QVector>
class SysInfoLinuxImpl : public SysInfo
{
public:
    SysInfoLinuxImpl();

    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;

private:
       QVector<qulonglong> cpuRawdata();
       QVector<qulonglong> mCpuLoadLastValues;
};

#endif // SYSINFOLINUXIMPL_H
