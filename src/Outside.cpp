#include <Outside.h>
using namespace std;

int main()
{
    windows.createWindow(1280, 780, "Outside");

    while (windows.running())
    {
        windows.run_loop();
    }
    return 0;
}
