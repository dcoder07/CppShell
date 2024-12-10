#include <bits/stdc++.h>
using namespace std;

int main()
{
  cout << unitbuf;
  cerr << unitbuf;

  string input;
  cout << "$ ";
  getline(cin, input);
  if (input == "exit 0")
    return 0;
  cout << input << ": command not found" << endl;

  return 0;
}
