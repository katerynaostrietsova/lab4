#pragma once

#include <vector>
#include <string>
#include <cstddef>

using namespace std;
enum class ActionType
{
    Read,
    Write,
    GetString
};

struct Action
{
    ActionType type;
    int fieldIndex;
    int value;
};

vector<Action> generateVariant16Actions(size_t count);

vector<Action> generateEqualActions(size_t count);

vector<Action> generateBadActions(size_t count);

void saveActionsToFile(const vector<Action>& actions, const string& filename);

vector<Action> loadActionsFromFile(const string& filename);
