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

    switch (isValid(input))
    {
    case cd:
      break;
    case echo:
      cout << input.substr(5) << endl;
    case exit0:
      exit = true;
      break;
    case type:
      if (isValid(input.substr(5)))
        cout << input.substr(5) << " is a shell builtin" << endl;
      else
      {
        string path = get_path(input.substr(5));
        if (!path.empty())
          cout << input << " is " << path << endl;
        else
          cout << input << " not found" << endl;
      }
    default:
      cout << input << ": command not found" << endl;
    }
  }
  return 0;
}
