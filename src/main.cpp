#include "core/App.h"

int main() {
    App myApp;
    myApp.Init();
    myApp.RunLoop();
    myApp.Cleanup();
    return 0;
}
