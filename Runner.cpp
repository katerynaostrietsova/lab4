#include "Runner.h"

#include <thread>
#include <chrono>

using namespace std;

static void executeActions(SharedData2& data, const vector<Action>& actions)
{
    for (const Action& action : actions)
    {
        switch (action.type)
        {
        case ActionType::Read:
            (void)data.get(static_cast<size_t>(action.fieldIndex));
            break;

        case ActionType::Write:
            data.set(static_cast<size_t>(action.fieldIndex), action.value);
            break;

        case ActionType::GetString:
        {
            string s = data.toString();
            (void)s;
            break;
        }

        default:
            break;
        }
    }
}

long long runSingleThread(SharedData2& data, const vector<Action>& actions)
{
    using clock = chrono::steady_clock;

    auto start = clock::now();

    executeActions(data, actions);

    auto finish = clock::now();

    auto elapsed = chrono::duration_cast<chrono::milliseconds>(finish - start);
    return elapsed.count();
}

long long runTwoThreads(SharedData2& data,
    const vector<Action>& actions1,
    const vector<Action>& actions2)
{
    using clock = chrono::steady_clock;

    auto start = clock::now();

    thread t1(executeActions, ref(data), cref(actions1));
    thread t2(executeActions, ref(data), cref(actions2));

    t1.join();
    t2.join();

    auto finish = clock::now();

    auto elapsed = chrono::duration_cast<chrono::milliseconds>(finish - start);
    return elapsed.count();
}

long long runThreeThreads(SharedData2& data,
    const vector<Action>& actions1,
    const vector<Action>& actions2,
    const vector<Action>& actions3)
{
    using clock = chrono::steady_clock;

    auto start = clock::now();

    thread t1(executeActions, ref(data), cref(actions1));
    thread t2(executeActions, ref(data), cref(actions2));
    thread t3(executeActions, ref(data), cref(actions3));

    t1.join();
    t2.join();
    t3.join();

    auto finish = clock::now();

    auto elapsed = chrono::duration_cast<chrono::milliseconds>(finish - start);
    return elapsed.count();
}
