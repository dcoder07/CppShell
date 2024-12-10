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
    if (input.substr(0, 5) == "echo ")
      cout << input.substr(5) << endl;
    else
      cout << input << ": command not found" << endl;
  }

  return 0;
}
