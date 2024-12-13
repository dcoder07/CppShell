#include <bits/stdc++.h>
using namespace std;

bool isValid(string command)
{
  string str = command.substr(0, command.find(" "));
  if (str == "type" || str == "echo" || str == "exit" || str == "cd")
    return true;
  return false;
}

string getPathEnv(string command)
{
  string path_env = getenv("PATH");
  stringstream ss(path_env);
  string temp;
  while (!ss.eof())
  {
    getline(ss, temp, ':');
    string commandPath = temp + '/' + command;
    if (filesystem::exists(commandPath))
      return commandPath;
  }
  return "";
}

int main()
{
  bool exit = false;
  while (!exit)
  {
    cout << unitbuf;
    cerr << unitbuf;
    cout << "$ ";
    string input;
    getline(cin, input);

    string cmd = input.substr(0, 4);
    if (cmd == "cd")
      continue;
    else if (cmd == "echo")
      cout << input.substr(5) << endl;
    else if (cmd == "exit0")
      exit = true;
    else if (cmd == "type")
    {
      string st = input.substr(5);
      if (isValid(st))
        cout << st << " is a shell builtin" << endl;
      else
      {
        string path = getPathEnv(st);
        if (!path.empty())
          cout << input.substr(5) << " is " << path << endl;
        else
          cout << path << " not found" << endl;
      }
    }
    else
      cout << input << ": command not found" << endl;
  }
  return 0;
}
