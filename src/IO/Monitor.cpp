#include "Monitor.hpp"
#include "../Console.hpp"

#include <Windows.h>
#include <vector>
using namespace std;
using namespace PandoraEngine;
using namespace Units;

MonitorInfo::MonitorParameters::MonitorParameters(char *deviceName, RectPoint position, RectSize size, RectPoint workPosition, RectSize workSize)
{
    _deviceName = deviceName;
    _position = position;
    _size = size;
    _workPosition = workPosition;
    _workSize = workSize;
}

char *MonitorInfo::MonitorParameters::device_name()
{
    return _deviceName;
}

RectPoint MonitorInfo::MonitorParameters::position()
{
    return _position;
}

RectSize MonitorInfo::MonitorParameters::size()
{
    return _size;
}

RectPoint MonitorInfo::MonitorParameters::work_position()
{
    return _workPosition;
}

RectSize MonitorInfo::MonitorParameters::work_size()
{
    return _workSize;
}

bool _printMonitorInfos = false;

vector<MonitorInfo::MonitorParameters> &get_monitor_parameters_list()
{
    static vector<MonitorInfo::MonitorParameters> monitorParametersList;
    return monitorParametersList;
}

MonitorInfo::MonitorParameters primaryMonitorParameters(new char[32]{"Primary Monitor"}, {0, 0}, {0, 0}, {0, 0}, {0, 0});

BOOL CALLBACK monitor_enum_proc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
    MONITORINFOEX monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFOEX);
    // Kiválasztott monitor lekérdezése
    if (GetMonitorInfo(hMonitor, &monitorInfo))
    {
// Kiírjuk a monitor paramétereit
#ifdef PE_DEBUG
        if (_printMonitorInfos)
        {
            Console::Write("Monitor parameters:\n");
            Console::Write("  Device Name: %s\n", monitorInfo.szDevice);
            Console::Write("  Size: %d x %d\n", monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top);
            Console::Write("  Position: %d, %d\n", monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top);
            Console::Write("  Work area size: %d x %d\n", monitorInfo.rcWork.right - monitorInfo.rcWork.left, monitorInfo.rcWork.bottom - monitorInfo.rcWork.top);
            Console::Write("  Work area position: %d, %d\n", monitorInfo.rcWork.left, monitorInfo.rcWork.top);
            Console::Write("----------------------\n");
        }
#endif
        MonitorInfo::MonitorParameters monitorParameters(monitorInfo.szDevice,
                                                         {monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top},
                                                         {monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top},
                                                         {monitorInfo.rcWork.left, monitorInfo.rcWork.top},
                                                         {monitorInfo.rcWork.right - monitorInfo.rcWork.left, monitorInfo.rcWork.bottom - monitorInfo.rcWork.top});
        get_monitor_parameters_list().push_back(monitorParameters);
    }
    return TRUE;
}

void MonitorInfo::initialize(bool printMonitorInfos)
{
    _printMonitorInfos = printMonitorInfos;
    MONITORINFOEX monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY), &monitorInfo);

    primaryMonitorParameters = MonitorParameters(monitorInfo.szDevice,
                                                 {monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top},
                                                 {monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top},
                                                 {monitorInfo.rcWork.left, monitorInfo.rcWork.top},
                                                 {monitorInfo.rcWork.right - monitorInfo.rcWork.left, monitorInfo.rcWork.bottom - monitorInfo.rcWork.top});
    EnumDisplayMonitors(NULL, NULL, monitor_enum_proc, 0);
}

int MonitorInfo::get_monitor_count()
{
    return GetSystemMetrics(SM_CMONITORS);
}

MonitorInfo::MonitorParameters MonitorInfo::get_monitor_parameters(int index)
{
    return get_monitor_parameters_list().at(index);
}

MonitorInfo::MonitorParameters MonitorInfo::get_primary_monitor_parameters()
{
    return primaryMonitorParameters;
}