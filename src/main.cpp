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

    string cmd = input.substr(0, 4), str = input.substr(5);
    if (cmd == "cd")
      continue;
    else if (cmd == "echo")
      cout << str << endl;
    else if (input.substr(0, 6) == "exit 0")
      exit = true;
    else if (cmd == "type")
    {
      if (isValid(str))
        cout << str << " is a shell builtin" << endl;
      else
      {
        string path = getPathEnv(str);
        if (!path.empty())
          cout << str << " is " << path << endl;
        else
          cout << str << ": not found" << endl;
      }
    }
    else
      cout << input << ": command not found" << endl;
  }
  return 0;
}
