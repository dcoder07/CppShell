#include <bits/stdc++.h>
using namespace std;

int main()
{
  for (;;)
  {
    cout << unitbuf;
    cerr << unitbuf;
    string input;
    cout << "$ ";
    getline(cin, input);

    if (input == "exit 0")
      return 0;

    if (input.substr(0, 5) == "type ")
    {
      if (input.substr(5, 4) == "exit" || input.substr(5, 4) == "echo" || input.substr(5, 4) == "type")
        cout << input.substr(5) << " is a shell builtin" << endl;
      else
        cout << input.substr(5) << ": not found" << endl;
    }

    if (input.substr(0, 5) == "echo ")
      cout << input.substr(5) << endl;

    else
      cout << input << " : command not found" << endl;
  }

  return 0;
}
