#pragma once
#include <vector>
#include "SharedData.h"
#include "Scenario.h"

using namespace std;

long long runSingleThread(SharedData2& data, const vector<Action>& actions);

long long runTwoThreads(SharedData2& data,
    const vector<Action>& actions1,
    const vector<Action>& actions2);

long long runThreeThreads(SharedData2& data,
    const vector<Action>& actions1,
    const vector<Action>& actions2,
    const vector<Action>& actions3);
