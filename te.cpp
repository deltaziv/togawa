#include <iostream>
#include <iomanip>

int main() {
    int w[] = {0x43876521, 0x78561234, 0x43783210};
    
    std::cout << std::hex;
    std::cout << "w[1]: " << w[1] << std::endl;
    std::cout << "((char *)w + 1)[4]: " 
              << (int)((char *)w + 1)[4] << std::endl;
    std::cout << "((short *)w + 3)[2]: " 
              << (int)((short *)w + 3)[2] << std::endl;
    
    return 0;
}