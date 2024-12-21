#include <bits/stdc++.h>
using namespace std;

enum commandType
{
  builtIn,
  executable,
  nonexistent
};

struct fullCommandType
{
  commandType type;
  string execPath;
};

string findCommandExecPath(string command)
{
  string pathEnv = getenv("PATH");
  stringstream ss(pathEnv);
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

fullCommandType commandToFullCommand(string command)
{
  fullCommandType fct;

  vector<string> builtIn_commands = {"exit", "echo", "type", "pwd", "cd", "cat"};
  if (find(builtIn_commands.begin(), builtIn_commands.end(), command) != builtIn_commands.end())
  {
    fct.type = commandType::builtIn;
    return fct;
  }

  string exec_path = findCommandExecPath(command);
  if (exec_path.size() != 0)
  {
    fct.type = commandType::executable;
    fct.execPath = exec_path;
    return fct;
  }

  else
    fct.type = commandType::nonexistent;
  return fct;
}

vector<string> parseCommand(string s)
{
  vector<string> v;
  stringstream ss(s);
  string temp = "";
  while (ss >> temp)
    v.push_back(temp);
  return v;
}

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

      else if (cmd == "cat")
      {
        int i = 0;
        vector<string> paths_vec;
        while (i < input.size())
        {
          if (input[i] == '\'')
          {
            i++;
            string path = "";
            while (input[i] != '\'')
              path += input[i++];
            paths_vec.push_back(path);
          }
          i++;
        }

        for (auto path : paths_vec)
        {
          ifstream f(path);
          if (f2.is_open())
            cout << f2.rdbuf() << " ";
        }
        cout << endl;
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

    else
      cout << input << ": command not found" << endl;
  }

  return 0;
}