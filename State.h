//
// Created by shirgold on 07/01/2020.
//
#include <string>
#include <limits>
using namespace std;
#ifndef MILE_STONE2_STATE_H
#define MILE_STONE2_STATE_H
template <class T>
class State {
private:
    T state;
    double cost;
    double trailCost;
    State<T> cameFrom;
public:
    State(T state1) {
        this->state = state1;
        this->trailCost = numeric_limits<double>::infinity();
    }
    State(T state1, double c) {
        this->trailCost = numeric_limits<double>::infinity();
        this->state = state1;
        this->cost = c;
    }
    bool equal(State<T> s) {
        return this->state == s;
    }
    void setCameFrom(State<T> s) {
        this->cameFrom = s;
    }
    void setCost(double c) {
        this->cost = c;
    }
    double getCost() {
        return this->cost;
    }
    State<T> getCameFrom() {
        return this->cameFrom;
    }
    void setTrailCost(double c) {
        this->trailCost = c;
    }
    State<T> getTrialCost() {
        return this->trailCost;
    }

};
#endif //MILE_STONE2_STATE_H
