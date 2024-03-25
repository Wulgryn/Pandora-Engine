#pragma once
#include "BaseWindow.hpp"
#include "../Core/Rendering/ObjectsHandler.hpp"

class Window : public BaseWindow, public ObjectsHandler
{
private:
    int FPS_LIMIT = 60;
    //Object update limit per second
    int UPS_LIMIT = 60;
protected:
public:
    Window();

    virtual void Initialize();

    virtual void Render();
    /// @brief Updates all Objects of the Window.
    /// @note  It's called by the Window's Update thread.
    virtual void Update();

    /// @brief Sets the FPS Limit of the Window.
    /// @param fps The FPS Limit.
    void SetFPSLimit(int fps);
    /// @brief Sets the Object Update Per Second Limit of the Window.
    /// @param ups The UPS Limit.
    void SetUPSLimit(int ups);
};

/// @brief Creates and Initializes a new Window.
/// @return The Initialized Window.
Window* createWindow();