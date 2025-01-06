#include <bits/stdc++.h>
#include "function.cpp"
using namespace std;

int main()
{
  cout << unitbuf;
  cerr << unitbuf;

  while (true)
  {
    cout << "$ ";
    string input;
    getline(cin, input);

    vector<string> command_vec = parseCommand(input);
    if (command_vec.size() == 0)
      continue;

    fullCommandType fct = commandToFullCommand(command_vec[0]);
    if (fct.type == builtIn)
    {
      string cmd = command_vec[0];
      if (cmd == "exit")
      {
        int exit_code = stoi(command_vec[1]);
        return exit_code;
      }

      else if (cmd == "echo")
      {
        for (int j = 1; j < command_vec.size(); j++)
        {
          if (j != 1)
            cout << " ";
          cout << command_vec[j];
        }
        cout << endl;
      }

      else if (cmd == "type")
      {
        if (command_vec.size() < 2)
          continue;
        string c = command_vec[1];

        fullCommandType cfct = commandToFullCommand(c);
        switch (cfct.type)
        {
        case builtIn:
          cout << c << " is a shell builtin" << endl;
          break;
        case executable:
          cout << c << " is " << cfct.execPath << endl;
          break;
        case ext_executable:
          cout << c << " is " << cfct.execPath << endl;
          break;
        case nonexistent:
          cout << c << ": not found" << endl;
          break;

        default:
          break;
        }
      }

      else if (cmd == "pwd")
        cout << filesystem::current_path().string() << endl;

      else if (cmd == "cd")
      {
        string path = command_vec[1];
        if (path == "~")
        {
          path = getenv("HOME");
          chdir(path.c_str());
        }
        else if (filesystem::exists(path))
          chdir(path.c_str());
        else
          cout << cmd << ": " << path << ": No such file or directory" << endl;
      }
    }

    else if (fct.type == executable)
    {
      string command_full_path = fct.execPath;
      for (int i = 1; i < command_vec.size(); i++)
        command_full_path += (" " + command_vec[i]);

      const char *command_ptr = command_full_path.c_str();
      system(command_ptr);
    }

    else if (fct.type == ext_executable)
      evaluateCatCommand(input[4], input);

    else if (fct.type == custom_cat_executable)
    {
      ifstream f(command_vec[1]);
      if (f.is_open())
        cout << f.rdbuf();
    }
    else
      cout << input << ": command not found" << endl;
  }

  return 0;
}