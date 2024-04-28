#pragma once
#include "BaseWindow.hpp"
#include "../Core/Elements/ObjectsHandler.hpp"
#include "../Core/Event.hpp"
#include "InputHandler.hpp"
#include "../Core/Rendering/Color.hpp"


struct GLTtext;
class Window : public BaseWindow, public ObjectsHandler
{
private:
    int FPS_LIMIT = 60;
    //Object update limit per second
    int UPS_LIMIT = 60;

    InputHandler* inputHandler;


    double lastFrameTime = 0;
    double lastUpdateTime = 0;

    int FrameCount = 0;
    int UpdateCount = 0;

    int currentFPS = 0;
    double currentFPSByFrameTime = 0;

    int currentUPS = 0;
    double currentUPSByFrameTime = 0;


    double lastFPSUpdateTime = 0;
    double lastUPSUpdateTime = 0;

    bool isRunning = false;

    Color BackgroundColor = Colors::BLACK;
public:
    bool IsPrintFPSEnabled = false;
    bool IsPrintUPSEnabled = false;


    Window();

    virtual void Initialize();

    /// @brief Starts the Window loop.
    virtual void Start();

    /// @brief Renders all renderable Objects of the Window.
    /// @note  It's called by the Application main thread.
    virtual void Render();

    /// @brief Updates all Objects of the Window.
    /// @note  It's called by the Window's Update thread.
    virtual void Update();

    /// @brief Sets the FPS Limit of the Window.
    /// @param fps The FPS Limit.
    void SetFPSLimit(int fps);

    int GetFPS() { return currentFPS; }
    double GetFPSByFrameTime() { return currentFPSByFrameTime; }

    /// @brief Sets the Object Update Per Second Limit of the Window.
    /// @param ups The UPS Limit.
    void SetUPSLimit(int ups);

    int GetUPS() { return currentUPS; }
    double GetUPSByFrameTime() { return currentUPSByFrameTime; }

    InputHandler* GetInput() 
    {
        if(!InitCheck("GetInput",true)) return nullptr;
        return inputHandler; 
    }

    void SetBackgroundColor(Color color);
    

    /// @brief Invoked every frame berfore the Window is rendered.
    /// @param Window* The Window that is being rendered.
    Event<Window*> OnRender;

    /// @brief Invoked every frame after the Window is rendered.
    /// @param Window* The Window that is being rendered.
    Event<Window*> OnLateRender;

    /// @brief Invoked every frame berfore the Window is updated.
    /// @param Window* The Window that is being updated.
    Event<Window*> OnUpdate;

    /// @brief Invoked every frame after the Window is updated.
    /// @param Window* The Window that is being updated.
    Event<Window*> OnLateUpdate;

    /// @brief Invoked every frame before the Window is cleared.
    /// @param Window* The Window that is being cleared.
    Event<Window*> OnWindowClear;
};

/// @brief Creates and Initializes a new Window.
/// @return The Initialized Window.
Window* createWindow();