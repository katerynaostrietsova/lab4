#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "SharedData.h"
#include "Scenario.h"
#include "Runner.h"

using namespace std;

const size_t ACTIONS_PER_THREAD = 100000;

struct ScenarioResult
{
    string name;
    long long timeOneThread;
    long long timeTwoThreads;
    long long timeThreeThreads;
};

int main()
{
    try
    {
        cout << "Lab 4: multithreaded structure test (variant 16)" << endl;
        cout << "Generating action sequences and saving to files..." << endl;

        {
            vector<Action> t1 = generateVariant16Actions(ACTIONS_PER_THREAD);
            vector<Action> t2 = generateVariant16Actions(ACTIONS_PER_THREAD);
            vector<Action> t3 = generateVariant16Actions(ACTIONS_PER_THREAD);

            saveActionsToFile(t1, "actions_variant16_t1.txt");
            saveActionsToFile(t2, "actions_variant16_t2.txt");
            saveActionsToFile(t3, "actions_variant16_t3.txt");
        }

        {
            vector<Action> t1 = generateEqualActions(ACTIONS_PER_THREAD);
            vector<Action> t2 = generateEqualActions(ACTIONS_PER_THREAD);
            vector<Action> t3 = generateEqualActions(ACTIONS_PER_THREAD);

            saveActionsToFile(t1, "actions_equal_t1.txt");
            saveActionsToFile(t2, "actions_equal_t2.txt");
            saveActionsToFile(t3, "actions_equal_t3.txt");
        }

        {
            vector<Action> t1 = generateBadActions(ACTIONS_PER_THREAD);
            vector<Action> t2 = generateBadActions(ACTIONS_PER_THREAD);
            vector<Action> t3 = generateBadActions(ACTIONS_PER_THREAD);

            saveActionsToFile(t1, "actions_bad_t1.txt");
            saveActionsToFile(t2, "actions_bad_t2.txt");
            saveActionsToFile(t3, "actions_bad_t3.txt");
        }

        cout << "Loading action sequences from files..." << endl;

        vector<Action> var16_t1 = loadActionsFromFile("actions_variant16_t1.txt");
        vector<Action> var16_t2 = loadActionsFromFile("actions_variant16_t2.txt");
        vector<Action> var16_t3 = loadActionsFromFile("actions_variant16_t3.txt");

        vector<Action> equal_t1 = loadActionsFromFile("actions_equal_t1.txt");
        vector<Action> equal_t2 = loadActionsFromFile("actions_equal_t2.txt");
        vector<Action> equal_t3 = loadActionsFromFile("actions_equal_t3.txt");

        vector<Action> bad_t1 = loadActionsFromFile("actions_bad_t1.txt");
        vector<Action> bad_t2 = loadActionsFromFile("actions_bad_t2.txt");
        vector<Action> bad_t3 = loadActionsFromFile("actions_bad_t3.txt");

        vector<ScenarioResult> results;

        {
            ScenarioResult r;
            r.name = "Variant16";

            {
                SharedData2 data;
                r.timeOneThread = runSingleThread(data, var16_t1);
            }

            {
                SharedData2 data;
                r.timeTwoThreads = runTwoThreads(data, var16_t1, var16_t2);
            }

            {
                SharedData2 data;
                r.timeThreeThreads = runThreeThreads(data, var16_t1, var16_t2, var16_t3);
            }

            results.push_back(r);
        }

        {
            ScenarioResult r;
            r.name = "Equal";

            {
                SharedData2 data;
                r.timeOneThread = runSingleThread(data, equal_t1);
            }
            {
                SharedData2 data;
                r.timeTwoThreads = runTwoThreads(data, equal_t1, equal_t2);
            }
            {
                SharedData2 data;
                r.timeThreeThreads = runThreeThreads(data, equal_t1, equal_t2, equal_t3);
            }

            results.push_back(r);
        }

        {
            ScenarioResult r;
            r.name = "Bad";

            {
                SharedData2 data;
                r.timeOneThread = runSingleThread(data, bad_t1);
            }
            {
                SharedData2 data;
                r.timeTwoThreads = runTwoThreads(data, bad_t1, bad_t2);
            }
            {
                SharedData2 data;
                r.timeThreeThreads = runThreeThreads(data, bad_t1, bad_t2, bad_t3);
            }

            results.push_back(r);
        }

        cout << endl;
        cout << "Execution time (milliseconds):" << endl;

        cout << left << setw(12) << "Scenario"
            << right << setw(14) << "1 thread"
            << setw(14) << "2 threads"
            << setw(14) << "3 threads" << endl;

        cout << string(54, '-') << endl;

        for (const auto& r : results)
        {
            cout << left << setw(12) << r.name
                << right << setw(14) << r.timeOneThread
                << setw(14) << r.timeTwoThreads
                << setw(14) << r.timeThreeThreads
                << endl;
        }

        cout << endl;
        cout << "Done. Press Enter to exit." << endl;
        cin.get();

        return 0;
    }
    catch (const exception& ex)
    {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "Unknown error." << endl;
        return 1;
    }
}
