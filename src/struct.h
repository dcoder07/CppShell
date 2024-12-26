#include <bits/stdc++.h>
using namespace std;

enum commandType
{
    builtIn,
    executable,
    ext_executable,
    nonexistent
};

struct fullCommandType
{
    commandType type;
    string execPath;
};