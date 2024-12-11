#include <bits/stdc++.h>
using namespace std;

int main()
{
  int exit = 0, checkValid = 0;
  while (!exit)
  {
    cout << unitbuf;
    cerr << unitbuf;
    string input;
    checkValid = 0;
    cout << "$ ";
    getline(cin, input);

    if (input == "exit 0")
    {
      exit = 1;
      checkValid = 1;
    }

    if (input.substr(0, 5) == "type ")
    {
      checkValid = 1;
      if (input.substr(5, 4) == "type" || input.substr(5, 4) == "exit" || input.substr(5, 4) == "echo")
        cout << input << " is a shell builtin" << endl;
      else
        cout << input << " not found" << endl;
    }

    if (input.substr(0, 5) == "echo ")
    {
      checkValid = 1;
      cout << input.substr(5) << endl;
    }

    if (checkValid == 0)
      cout << input << ": command not found" << endl;
  }

  return 0;
}
