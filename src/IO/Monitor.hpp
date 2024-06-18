#ifndef MONITOR_HPP
#define MONITOR_HPP

#include "../Core/Macros.h"
#include "../Core/Units.hpp"

namespace PandoraEngine
{
#pragma once

    namespace MonitorInfo
    {
        struct DLL MonitorParameters
        {
        private:
            char *_deviceName;
            Units::RectPoint _position;
            Units::RectSize _size;
            Units::RectPoint _workPosition;
            Units::RectSize _workSize;

        public:
            MonitorParameters(char *deviceName, Units::RectPoint position, Units::RectSize size, Units::RectPoint workPosition, Units::RectSize workSize);

            char *device_name();

            Units::RectPoint position();
            Units::RectSize size();
            Units::RectPoint work_position();
            Units::RectSize work_size();
        };

        void initialize(bool printMonitorInfos = false);
        int get_monitor_count();
        MonitorParameters get_monitor_parameters(int index);
        MonitorParameters get_primary_monitor_parameters();
    }

} // namespace PandoraEngine

#endif // MONITOR_HPP