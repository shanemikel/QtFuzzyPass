
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char * argv[])
{
    vector<string> args;
    for (int i = 0; i != argc; ++i)
        args.push_back(string(argv[i]));

    for (auto arg : args)
        cout << arg << ' ';
    cout << '\n';

    return 0;
}
