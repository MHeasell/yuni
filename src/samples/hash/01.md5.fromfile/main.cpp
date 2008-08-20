
#include <yuni/yuni.h>      // The Yuni Global header
#include <yuni/hash/md5.h>  // 
#include <iostream>         // Only for std::cout


int main(int /*argc*/, char* argv[])
{
    // Our MD5 class
    Yuni::Hash::MD5 md5;
    // Print the value on the std::cout
    std::cout << "MD5 (" << argv[0] << ") = " << md5.fromFile(argv[0]) << std::endl;

    return 0;
}
