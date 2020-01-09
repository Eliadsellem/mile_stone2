//
// Created by eliadsellem on 1/9/20.
//

#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include "MyClientHandler.h"
#include "State.h"
#include "Point.h"
#include "ISearchable.h"
#include "Matrix.h"

void MyClientHandler::handleClient(int server_socket) {
    int counter = 0;
    while (true) {
        char buffer[1500] = {0};
        //receive massage
        int valRead = read(server_socket, buffer, 1500);
        if (valRead == 0) {
            break;
        }
        string problem = string(buffer);
        problem = problem.substr(0, valRead);
        string solution;
        if (problem.compare("End") == 0) {
            cout << "endddd" << endl;
            if (file_cache->isSolved(problem)) {
                solution = file_cache->getSolution(problem);
                cout << "from file: " << solution << endl;
            } else {
                //create matrix
                ISearchable<Point *> *matrix = createMatrix();
                solution = solver->solve(matrix);
                file_cache->saveSolution(problem, solution);
            }
            close(server_socket);
        } else {
            allProblem.push_back(problem);
            continue;
        }
        //write the massage into file

        char *bufferOut = &solution[0];
        int is_send = send(server_socket, bufferOut, solution.length(), 0);
        if (is_send == -1) {
            cerr << "error sending massage to client" << endl;
        }
        cout << "bufferOut : " << solution << endl;
    }
}

ISearchable<Point *> *MyClientHandler::createMatrix() {
    vector<vector<State<Point *> *>> vertexes;
    int size = allProblem.size();
    string line;
    string substr = "";
    int pos = 0;
    int i, j = 0;
    for (i = 0; i < size - 2; i++) {
        line = allProblem[i];
        while (true) {
            if (line.find(",") < line.find("\n")) {
                substr = line.substr(pos, line.find(","));
                substr = clearSpaces(substr);
                double val = stod(substr);
                Point *p = new Point(i, j);
                State<Point *> *t = new State<Point *>(p, val);
                vertexes[i].push_back(t);
                line = line.substr(line.find(",") + 1);
            } else {
                substr = line.substr(pos, line.find("\n"));
                substr = clearSpaces(substr);
                double val = stof(substr);
                Point *p = new Point(i, j);
                State<Point *> *t = new State<Point *>(p, val);
                vertexes[i].push_back(t);
                break;
            }
        }
    }
    ISearchable<Point *> *matrix = new Matrix(vertexes);
    //get start point
    double x, y;
    split(allProblem[i], &x, &y);
    matrix->setInitialState(vertexes[x][y]);
    //get goal point
    split(allProblem[i + 1], &x, &y);
    matrix->setGoalState(vertexes[x][y]);
    return matrix;

}


void MyClientHandler::split(string line, double *x, double *y) {
    string substr = "";
    double val = 0;
    int pos = 0;
    substr = line.substr(pos, line.find(","));
    substr = clearSpaces(substr);
    val = stod(substr);
    *x = val;
    line = line.substr(line.find(",") + 1);
    substr = line.substr(pos, line.find("\n"));
    substr = clearSpaces(substr);
    val = stod(substr);
    *y = val;
}

string MyClientHandler::clearSpaces(string s) {
    string dest = "";
    for (unsigned int i = 0; i < s.length(); ++i) {
        // remove spaces
        if (s[i] != ' ') {
            dest += s[i];
        }
    }
    return dest;
}
