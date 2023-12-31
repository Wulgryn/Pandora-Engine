#include "DLL/dll.hpp"
#include "parameters.hpp"

namespace utils
{
    class DLL Random
    {
    private:
        
    public:
        Random();
    };
    
    namespace random
    {
        int getInt(int min, int max);
        float getFloat(float min, float max);
        double getDouble(double min, double max);
        byte getByte(byte min, byte max);
    }

} // namespace utils