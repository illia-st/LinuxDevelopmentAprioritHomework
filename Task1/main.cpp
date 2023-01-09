#include <iostream>
#include "CopyFile.h"
int main(int argc, char ** argv) {
    if(argc < 3){
        std::cerr << "Usage: <full path to the file to copy> <new file name>";
        return -1;
    }
    int ans = CopyFile(argv[1], argv[2]);
    if(ans != 1) return ans;
    return 0;
}
