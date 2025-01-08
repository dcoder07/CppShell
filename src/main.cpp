#include <bits/stdc++.h>
using namespace std;

enum commandType
{
  redirection,
  builtIn,
  executable,
  ext_executable,
  custom_cat_executable,
  nonexistent
};

struct fullCommandType
{
  commandType type;
  string execPath;
  unordered_map<string, string> m;
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

fullCommandType commandToFullCommand(string &command, vector<string> &command_vec)
{
  fullCommandType fct;

  vector<string> builtIn_commands = {"exit", "echo", "type", "pwd", "cd"},
                 extExecutable_commands = {"ls", "cat", "grep", "mkdir", "rm"};

  if (find(command_vec.begin(), command_vec.end(), ">") != command_vec.end())
  {
    fct.type = commandType::redirection;
    return fct;
  }

  if (find(builtIn_commands.begin(), builtIn_commands.end(), command) != builtIn_commands.end())
  {
    fct.type = commandType::builtIn;
    return fct;
  }

  string exec_path = findCommandExecPath(command);
  if (find(extExecutable_commands.begin(), extExecutable_commands.end(), command) != extExecutable_commands.end())
  {
    fct.type = commandType::ext_executable;
    fct.execPath = exec_path;
    return fct;
  }

  if (command.size() > 3 && command.substr(0, 3) == "exe")
  {
    fct.type = commandType::custom_cat_executable;
    fct.execPath = command;
    return fct;
  }

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

string evaluateQuoted(string s, int &i, char ch)
{
  string str = "";
  if (ch == '\"')
  {
    i++;
    while (s[i] != '\"')
    {
      if (s[i] == '\\')
      {
        if (i + 1 < s.size() && s[i + 1] != '\\')
        {
          str += s[i + 1];
          i += 2;
        }
        else if (i + 1 < s.size() && s[i + 1] == '\\')
        {
          while (i + 1 < s.size() && s[i + 1] == '\\')
          {
            str += s[i + 1];
            i++;
          }
          i++;
        }
      }
      else
        str += s[i++];
    }
  }
  else
  {
    i++;
    while (s[i] != '\'')
      str += s[i++];
  }
  return str;
}

vector<string> parseCommand(string s)
{
  vector<string> v;
  int i = 0;
  string temp = "";
  while (i < s.size())
  {
    if (s[i] == '\'' || s[i] == '\"')
    {
      temp += evaluateQuoted(s, i, s[i]);
      i++;
    }

    else if (s[i] == '\\' && i + 1 < s.size())
    {
      temp += s[i + 1];
      i += 2;
    }
    else if (s[i] == ' ')
    {
      if (!temp.empty())
      {
        v.push_back(temp);
        temp = "";
      }
      i++;
    }
    else
    {
      temp += s[i];
      i++;
    }
  }

  if (!temp.empty())
    v.push_back(temp);
  return v;
}

void evaluateCatCommand(vector<string> command_vec, fullCommandType fct)
{
  for (int i = 0; i < command_vec.size(); i++)
  {
    if (i == 0)
      continue;
    string path = command_vec[i];

    if (fct.m.find(path) != fct.m.end())
      path = fct.m[path];

    ifstream f(path);
    if (f.is_open())
      cout << f.rdbuf();
  }
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

    fullCommandType fct = commandToFullCommand(command_vec[0], command_vec);

    if (fct.type == redirection)
    {
      for (int i = 0; i < command_vec.size(); i++)
      {
        if (command_vec[i] == ">" || command_vec[i] == "1>")
        {
          string execPath = findCommandExecPath(command_vec[i + 1]);
          if (execPath.size() == 0)
            continue;
          fct.m[command_vec[i + 1]] = command_vec[i - 1];
        }
      }
    }

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

        fullCommandType cfct = commandToFullCommand(c, command_vec);
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
      evaluateCatCommand(command_vec, fct);

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