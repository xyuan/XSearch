#include <iostream>
using namespace std;

class Crawler
{
public:
    Crawler();
    ~Crawler()

public:
    void fetch(void * arg);
    void download();

private:
    string seed_file_name;
    string output_file_name;
};
