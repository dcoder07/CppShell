enum commandType
{
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

    vector<string> builtIn_commands = {"exit", "echo", "type", "pwd", "cd"},
                   extExecutable_commands = {"ls", "cat", "grep", "mkdir", "rm"};

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

void evaluateCatCommand(char ch, string &input)
{
    int i = 0;
    vector<string> paths_vec;
    while (i < input.size())
    {
        if (input[i] == ch)
        {
            i++;
            string path = "";
            while (input[i] != ch)
                path += input[i++];
            paths_vec.push_back(path);
        }
        i++;
    }

    for (auto path : paths_vec)
    {
        ifstream f(path);
        if (f.is_open())
            cout << f.rdbuf();
    }
}