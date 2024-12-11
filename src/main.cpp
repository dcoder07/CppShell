#include <bits/stdc++.h>
using namespace std;

int main()
{
  bool exit = 0;
  while (!exit)
  {
    cout << "$ ";
    bool checkValid = 0;
    string input;
    getline(cin, input);

    if (input == "exit 0")
    {
      checkValid = 1;
      exit = 1;
    }

    if (input.substr(0, 5) == "type ")
    {
      checkValid = 1;
      string cmd = input.substr(5);
      if (cmd.substr(0, 4) == "type" || cmd.substr(0, 4) == "exit" || cmd.substr(0, 4) == "echo")
      {
        cout << cmd << " is a shell builtin\n";
      }
      else
      {
        cout << cmd << " not found\n";
      }
    }

    if (input.substr(0, 5) == "echo ")
    {
      checkValid = 1;
      string toPrint = input.substr(5);
      cout << toPrint << '\n';
    }

    if (!checkValid)
    {
      cout << input << ": command not found\n";
    }
  }

  return 0;
}
