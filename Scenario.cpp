#include "Scenario.h"

#include <random>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

static mt19937& getRandomEngine()
{
    static random_device rd;
    static mt19937 engine(rd());
    return engine;
}

static int generateWriteValue()
{
    static uniform_int_distribution<int> dist(-100, 100);
    return dist(getRandomEngine());
}

vector<Action> generateVariant16Actions(size_t count)
{
    vector<Action> actions;
    actions.reserve(count);

    uniform_int_distribution<int> dist(0, 99);

    for (size_t i = 0; i < count; ++i)
    {
        int x = dist(getRandomEngine());

        Action a;

        if (x < 20)
        {
            a.type = ActionType::Read;
            a.fieldIndex = 0;
            a.value = 0;
        }
        else if (x < 40)
        {
            a.type = ActionType::Read;
            a.fieldIndex = 1;
            a.value = 0;
        }
        else if (x < 45)
        {
            a.type = ActionType::Write;
            a.fieldIndex = 0;
            a.value = generateWriteValue();
        }
        else if (x < 50)
        {
            a.type = ActionType::Write;
            a.fieldIndex = 1;
            a.value = generateWriteValue();
        }
        else
        {
            a.type = ActionType::GetString;
            a.fieldIndex = -1;
            a.value = 0;
        }

        actions.push_back(a);
    }

    return actions;
}

vector<Action> generateEqualActions(size_t count)
{
    vector<Action> actions;
    actions.reserve(count);

    uniform_int_distribution<int> dist(0, 4);

    for (size_t i = 0; i < count; ++i)
    {
        int choice = dist(getRandomEngine());

        Action a;

        switch (choice)
        {
        case 0:
            a.type = ActionType::Read;
            a.fieldIndex = 0;
            a.value = 0;
            break;
        case 1:
            a.type = ActionType::Read;
            a.fieldIndex = 1;
            a.value = 0;
            break;
        case 2:
            a.type = ActionType::Write;
            a.fieldIndex = 0;
            a.value = generateWriteValue();
            break;
        case 3:
            a.type = ActionType::Write;
            a.fieldIndex = 1;
            a.value = generateWriteValue();
            break;
        case 4:
        default:
            a.type = ActionType::GetString;
            a.fieldIndex = -1;
            a.value = 0;
            break;
        }

        actions.push_back(a);
    }

    return actions;
}

vector<Action> generateBadActions(size_t count)
{
    vector<Action> actions;
    actions.reserve(count);

    uniform_int_distribution<int> dist(0, 99);

    for (size_t i = 0; i < count; ++i)
    {
        int x = dist(getRandomEngine());

        Action a;

        if (x < 30)
        {
            a.type = ActionType::Write;
            a.fieldIndex = 0;
            a.value = generateWriteValue();
        }
        else if (x < 60)
        {
            a.type = ActionType::Write;
            a.fieldIndex = 1;
            a.value = generateWriteValue();
        }
        else if (x < 75)
        {
            a.type = ActionType::Read;
            a.fieldIndex = 0;
            a.value = 0;
        }
        else if (x < 90)
        {
            a.type = ActionType::Read;
            a.fieldIndex = 1;
            a.value = 0;
        }
        else
        {
            a.type = ActionType::GetString;
            a.fieldIndex = -1;
            a.value = 0;
        }

        actions.push_back(a);
    }

    return actions;
}

void saveActionsToFile(const vector<Action>& actions, const string& filename)
{
    ofstream out(filename);
    if (!out)
    {
        throw runtime_error("saveActionsToFile: cannot open file: " + filename);
    }

    for (const Action& a : actions)
    {
        switch (a.type)
        {
        case ActionType::Read:
            out << "read " << a.fieldIndex << '\n';
            break;

        case ActionType::Write:
            out << "write " << a.fieldIndex << ' ' << a.value << '\n';
            break;

        case ActionType::GetString:
            out << "string" << '\n';
            break;
        }
    }
}

vector<Action> loadActionsFromFile(const string& filename)
{
    ifstream in(filename);
    if (!in)
    {
        throw runtime_error("loadActionsFromFile: cannot open file: " + filename);
    }

    vector<Action> actions;
    string command;

    while (in >> command)
    {
        if (command == "read")
        {
            int index;
            in >> index;

            Action a;
            a.type = ActionType::Read;
            a.fieldIndex = index;
            a.value = 0;
            actions.push_back(a);
        }
        else if (command == "write")
        {
            int index;
            int value;
            in >> index >> value;

            Action a;
            a.type = ActionType::Write;
            a.fieldIndex = index;
            a.value = value;
            actions.push_back(a);
        }
        else if (command == "string")
        {
            Action a;
            a.type = ActionType::GetString;
            a.fieldIndex = -1;
            a.value = 0;
            actions.push_back(a);
        }
        else
        {
            throw runtime_error("loadActionsFromFile: unknown command in file: " + command);
        }
    }

    return actions;
}
