#include <bits/stdc++.h>
using namespace std;

int main()
{
  cout << unitbuf;
  cerr << unitbuf;

  for (;;)
  {
    string input;
    cout << "$ ";
    getline(cin, input);
    if (input == "exit 0")
      return 0;

    if (input.substr(0, 5) == "type ")
    {
      if (input.substr(5) == "exit" || input.substr(5) == "echo" || input.substr(5) == "type")
        cout << input.substr(5) << " is a shell builtin" << endl;
      else
        cout << input.substr(5) << ": not found" << endl;
    }
    else
      cout << input << ": command not found" << endl;
  }

  return 0;
}
