//
// Created by shirgold on 12/01/2020.
//

#ifndef MILE_STONE2_BFS_H
#define MILE_STONE2_BFS_H

#include <set>
#include "Searcher.h"
template<class T, class SOLUTION>
class BFS : public Searcher<T, SOLUTION> {
    queue<State<T>*> myQueue;
    set<State<T>*> used;
public:
    // Searcher's abstract method overriding
    SOLUTION search(ISearchable<T>* searchable) {
      searchable->nullify();
      used.clear();
      this->evaluatedNodes = 0;
      bool flag = false;
        State<T>* initialState = searchable->getInitialState();
        initialState->setTrailCost(0);
        used.insert(initialState);
        addToQueue(initialState);
        while (!myQueue.empty()) {
            State<T>* u = popQueue();
            vector<State<T>*> adj = searchable->getAllPossibleState(u);
            for (State<T>* v : adj) {
                if (used.find(v) == used.end()) {
                    used.insert(v);
                    v->setTrailCost(u->getTrialCost() + 1);
                    v->setCameFrom(u);
                    addToQueue(v);
                }
                if (v == searchable->getGoalState()) {
                    flag = true;
                }
            }
        }
        clearQueue();
        if (!flag) {
            return "no solution";
        }
        return searchable->printAll(searchable->getGoalState());
    }
    State<T>* popQueue() {
        this->evaluatedNodes++;
        if (myQueue.empty()) {
            return nullptr;
        }
        auto top = myQueue.front();
        myQueue.pop();
        return top;
    }
    /*
     * the function inserts the state to the queue
     */
    void addToQueue(State<T>* state) {
        myQueue.push(state);
    }
    void clearQueue() {
        while (!myQueue.empty()) {
            myQueue.pop();
        }
    }
};


#endif //MILE_STONE2_BFS_H
