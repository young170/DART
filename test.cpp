#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Number of arguments: " << argc << std::endl;
    
    std::cout << "Arguments:" << std::endl;
    for (int i = 1; i < argc; ++i) {
        std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
    }

    return 0;
}
