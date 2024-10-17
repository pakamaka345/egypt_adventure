#include <iostream>
#include "windows.h"

void playSound(int sound)  {
    Beep(sound, 1000);
}

int main() {
    std::cout << "Egypt adventure" << std::endl;
    playSound(523);
    return 0;
}