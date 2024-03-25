#pragma once
#include "Core/Parameters.hpp"

namespace MonitorInfo
{
    struct MonitorParameters
    {
    private:
        char* _deviceName;
        ParametersApp::Position _position;
        ParametersApp::Size _size;
        ParametersApp::Position _workPosition;
        ParametersApp::Size _workSize;
    public:
        MonitorParameters(char* deviceName, ParametersApp::Position position, ParametersApp::Size size, ParametersApp::Position workPosition, ParametersApp::Size workSize)
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

        ParametersApp::Position position()
        {
            return _position;
        }

        ParametersApp::Size size()
        {
            return _size;
        }

        ParametersApp::Position workPosition()
        {
            return _workPosition;
        }

        ParametersApp::Size workSize()
        {
            return _workSize;
        }
    };

    void Initialize(bool printMonitorInfos = false);
    int GetMonitorCount();
    MonitorParameters GetMonitorParameters(int index);
    MonitorParameters GetPrimaryMonitorParameters();
}