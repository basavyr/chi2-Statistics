#include <iostream>

using namespace std;

void panicError(const char *errorname)
{
    cout << errorname << endl;
}

int main()
{
    const char *errorname;
    errorname = "this is an error";
    panicError(errorname);
    return 0;
}