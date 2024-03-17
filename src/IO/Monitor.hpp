#pragma once
#include "Core/Parameters.hpp"

namespace MonitorInfo
{
    struct MonitorParameters
    {
    private:
        char* _deviceName;
        Position _position;
        Size _size;
        Position _workPosition;
        Size _workSize;
    public:
        MonitorParameters(char* deviceName, Position position, Size size, Position workPosition, Size workSize)
        {
            _deviceName = deviceName;
            _position = position;
            _size = size;
            _workPosition = workPosition;
            _workSize = workSize;
        }

        char* deviceName()
        {
            return _deviceName;
        }

        Position position()
        {
            return _position;
        }

        Size size()
        {
            return _size;
        }

        Position workPosition()
        {
            return _workPosition;
        }

        Size workSize()
        {
            return _workSize;
        }
    };

    void Initialize(bool printMonitorInfos = false);
    int GetMonitorCount();
    MonitorParameters GetMonitorParameters(int index);
    MonitorParameters GetPrimaryMonitorParameters();
}