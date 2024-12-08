#include <bits/stdc++.h>
using namespace std;

int main()
{
  cout << unitbuf;
  cerr << unitbuf;

  cout << "$ ";

  string input;
  for (int i = 0; i < 3; i++)
  {
    getline(cin, input);
    cout << input << ": command not found" << endl;
  }

  return 0;
}
