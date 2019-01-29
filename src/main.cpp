#include <App.h>

int main(int argc, char *argv[])
{
    Application app;
    while(app.isRunning())
    {
        app.HandleEvents();
        app.Update();
        app.Display();
    }
}