#include "Monitor.hpp"

#include <vector>
#include <iostream>
#include <Windows.h>

bool _printMonitorInfos = false;

std::vector<MonitorInfo::MonitorParameters>& GetMonitorParametersList()
{
    static std::vector<MonitorInfo::MonitorParameters> monitorParametersList;
    return monitorParametersList;
}

MonitorInfo::MonitorParameters primaryMonitorParameters(new char[32]{"Primary Monitor"}, Position(0, 0), Size(0, 0), Position(0, 0), Size(0, 0));


BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
    MONITORINFOEX monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFOEX);
    // Kiválasztott monitor lekérdezése
    if (GetMonitorInfo(hMonitor, &monitorInfo)) {
        // Kiírjuk a monitor paramétereit
        if(_printMonitorInfos)
        {
        std::cout << "Monitor parameters:" << std::endl;
        std::cout << "  Device Name: " << monitorInfo.szDevice << std::endl;
        std::cout << "  Size: " << monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left
                  << " x " << monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top << std::endl;
        std::cout << "  Position: " << monitorInfo.rcMonitor.left << ", " << monitorInfo.rcMonitor.top << std::endl;
        std::cout << "  Work area size: " << monitorInfo.rcWork.right - monitorInfo.rcWork.left
                  << " x " << monitorInfo.rcWork.bottom - monitorInfo.rcWork.top << std::endl;
        std::cout << "  Work area position: " << monitorInfo.rcWork.left << ", " << monitorInfo.rcWork.top << std::endl;
        std::cout << "----------------------" << std::endl;
        }
        MonitorInfo::MonitorParameters monitorParameters(monitorInfo.szDevice, 
                                                        Position(monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top), 
                                                        Size(monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top), 
                                                        Position(monitorInfo.rcWork.left, monitorInfo.rcWork.top), 
                                                        Size(monitorInfo.rcWork.right - monitorInfo.rcWork.left, monitorInfo.rcWork.bottom - monitorInfo.rcWork.top));
        GetMonitorParametersList().push_back(monitorParameters);
    }
    return TRUE;
}

void MonitorInfo::Initialize(bool printMonitorInfos)
{
    printMonitorInfos = _printMonitorInfos;
    MONITORINFOEX monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY), &monitorInfo);

    primaryMonitorParameters = MonitorParameters(monitorInfo.szDevice,
                                                Position(monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top), 
                                                Size(monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top), 
                                                Position(monitorInfo.rcWork.left, monitorInfo.rcWork.top), 
                                                Size(monitorInfo.rcWork.right - monitorInfo.rcWork.left, monitorInfo.rcWork.bottom - monitorInfo.rcWork.top));
    EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, 0);
}

int MonitorInfo::GetMonitorCount()
{
    return GetSystemMetrics(SM_CMONITORS);
}

MonitorInfo::MonitorParameters MonitorInfo::GetMonitorParameters(int index)
{
    return GetMonitorParametersList().at(index);
}

MonitorInfo::MonitorParameters MonitorInfo::GetPrimaryMonitorParameters()
{
    return primaryMonitorParameters;
}
