#include <core/App.h>

int main(int argc, char* argv[]) {
    AppInstance::Instance()->Init("Hello world", 800, 600);
    AppInstance::Instance()->Run();
   return 0;
}