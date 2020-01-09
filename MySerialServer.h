//
// Created by eliadsellem on 1/6/20.
//

#ifndef MILE_STONE2__MYSERIALSERVER_H_
#define MILE_STONE2__MYSERIALSERVER_H_
#include <netinet/in.h>
#include <cstring>
#include "Server.h"
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
using namespace std;
using namespace server_side;
class MySerialServer: public Server {
 public:
  void open(int p, ClientHandler* c);
  virtual void stop();
//  void writeIntoFile(string fileName, char * buffer ,int size);
  static string readFromFile();
  static void start(int sockfd, sockaddr_in address ,ClientHandler* c);
  static bool shouldStop;
};

#endif //MILE_STONE2__MYSERIALSERVER_H_
