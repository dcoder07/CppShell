#include <bits/stdc++.h>
#include "functions.cpp"
using namespace std;

enum commandType;
struct fullCommandType;

string findCommandExecPath(string command);
fullCommandType commandToFullCommand(string command);
vector<string> parseCommand(string s);
void evaluateCatCommand(char ch, string &input);

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
        if (input.size() > 5 && input[5] == '\'')
        {
          int i = 6;
          while (input[i] != '\'')
            cout << input[i++];
        }

        else if (input.size() > 5 && input[5] == '\"')
        {
          int i = 5;
          while (i < input.size())
          {
            if (input[i] == '\"')
            {
              i++;
              while (input[i] != '\"')
                cout << input[i++];
              cout << " ";
            }

            i++;
          }
        }

        else
        {
          for (int i = 1; i < command_vec.size(); i++)
          {
            if (i != 1)
              cout << " ";
            cout << command_vec[i];
          }
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
      string commmand_full_path = fct.execPath;
      for (int i = 1; i < command_vec.size(); i++)
        commmand_full_path += (" " + command_vec[i]);

      const char *command_ptr = commmand_full_path.c_str();
      system(command_ptr);
    }

    else if (fct.type == ext_executable)
    {
      evaluateCatCommand(input[4], input);
    }

    else
      cout << input << ": command not found" << endl;
  }

  return 0;
}