#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "TAlgorithm.h"

using namespace std;

TAlgorithm::TAlgorithm(TCandidate* pattern,unsigned int candidates_count, unsigned int max_population_count, unsigned int min_improvment_proc,unsigned int pop_check)
    : stop_max_population_count(max_population_count), stop_min_improvment_proc(min_improvment_proc), pop_check(pop_check)
{
    stop_max_population_count = max_population_count;
    stop_min_improvment_proc = min_improvment_proc;
    this->pattern = pattern;

    wsk_population_pres = new TPopulation(candidates_count, pattern);
    wsk_population_prev = nullptr;

    pop_check = pop_check;;
}

TAlgorithm::~TAlgorithm()
{
    if (wsk_population_pres) delete wsk_population_pres;
    if (wsk_population_prev) delete wsk_population_prev;


    older.clear();
}

void TAlgorithm::run()
{
    bool stop = false;

    while (!wsk_population_prev || !stop)
    {
        wsk_population_pres->calculate();
        // wsk_population_pres->get_best_candidate()->info();
        // wsk_population_pres->info();

        older.push_back(new TPopulation(*wsk_population_pres));

        if (older.size() > pop_check) {
            delete older[0];
            older.erase(older.begin());
        }

        if (older.size() >= 2) {
            double val1 = older[older.size() - 2]->get_best_rate();
            double val2 = older[older.size() - 1]->get_best_rate();

            // cout << "val1: " << val1 << " val2: " << val2 << endl;

            bool roznica = (std::abs(val2 - val1) / val1 * 100.0) < stop_min_improvment_proc;
            older_rate.push_back(roznica);

            if (older_rate.size() > pop_check - 1) {
                older_rate.erase(older_rate.begin());
            }
        }

        cout << "== Population #" << wsk_population_pres->get_id();
        cout << " || best val: " << wsk_population_pres->get_best_rate() << endl;
        // wsk_population_pres->info();

        if(wsk_population_pres->get_best_rate() > result)
        {
            result = wsk_population_pres->get_best_rate();
        }
        
        stop = is_stop();

        if (!stop)
        {
            unsigned int candidates_count = wsk_population_pres->get_candidates_count();

            if (wsk_population_prev) delete wsk_population_prev;
            wsk_population_prev = new TPopulation(*wsk_population_pres);

            delete wsk_population_pres;
            wsk_population_pres = new TPopulation(*wsk_population_prev);
            wsk_population_pres->set_id(wsk_population_prev->get_id() + 1);
        }

    }

    cout << "\nAlgorithm stopped after " << wsk_population_pres->get_id() << " generations." << endl;
    wsk_population_pres->get_best_candidate()->info();
    cout << "Best value found: " << result << endl;
}

bool TAlgorithm::is_max_population()
{
    unsigned int id = wsk_population_pres->get_id();
    return (id >= stop_max_population_count);
}

bool TAlgorithm::is_min_improvment()
{
    if (older_rate.size() < pop_check - 1)
        return false;

    bool all_true = std::all_of(older_rate.begin(), older_rate.end(), [](bool val) { return val; });

    return all_true;
}

bool TAlgorithm::is_stop()
{
    if (!wsk_population_prev)
    {
        return is_max_population();
    }
    else
    {
        return is_max_population() || is_min_improvment();
    }
}