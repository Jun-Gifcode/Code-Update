#include <iostream>
#include "EMS.hpp"

int main() {
    EMS ems;
    ems.loadFile();// Load data from file
    ems.mainmenu();// Start the main menu loop
    ems.saveFile();// Save data to file before exiting
    return 0;
}