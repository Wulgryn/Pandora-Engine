#include "transform.hpp"
#include "PANDORA/mainWindow.hpp"

using namespace pandora;

Transform::Transform()
{
    size = utils::Size(mainWindow::get()->parameters.getSize().Width / 2, mainWindow::get()->parameters.getSize().Height / 2);
}