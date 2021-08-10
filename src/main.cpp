#include <core/App.h>
#include <utils/Debug.h>
#include "stb_image.h"

int main(int argc, char *argv[]) {
    App::instance()->Init("Hello world", 800, 600);
    App::instance()->Run();

    return 0;
}