#include "smart_home.h"

int main(void)
{
    smart_home_t home;
    smart_home_init(&home);
    smart_home_run(&home);
    return 0;
}
