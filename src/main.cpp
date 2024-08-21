#include "logging.h"

int main(int argc, char const *argv[])
{
    init_logging();
    LOG_INFO << "Hello World";
    return 0;
}
