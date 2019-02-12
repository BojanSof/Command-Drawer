#include <App.h>

int main(int argc, char *argv[])
{
    Application app;
    while(app.isRunning())
    {
        app.handleEvents();
        app.update();
        app.display();
    }
}