#include "connection.h"
#include "runningAverage.h"
#include "intervalTimer.h"
#include <fstream> 
#include <iostream>
#include <functional>
#include <array>
volatile sig_atomic_t terminate = 0;

struct __attribute__((__packed__)) reading {
  uint8_t sensorNumber;
  uint8_t valueType;
  uint64_t reading;
} ;

void writeFile(std::fstream &file, struct reading &buffer);
void printResetAverage(std::array<runningAverage, 11> &averageArray);
void close(int sig);

int main() {
  signal(SIGINT, close); 

  connection connection;
  connection.connect(12345, "127.0.0.1");

  std::array<runningAverage, 11> averageArray = {}; //averageArray[sensorNr] holds running average obj for sensor
  for (int i = 1; i <= 10; ++i) averageArray[i] = runningAverage();

  intervalTimer intervalTimer(std::bind(&printResetAverage, std::ref(averageArray)), 5000);
  intervalTimer.run();
  
  std::fstream file;
  file.open ("readings.csv", std::fstream::out); 
  file << "unix timestamp, sensor number, reading\n";
  struct reading buffer;
  
  while(terminate == 0){
      buffer.reading = 0;
      buffer.sensorNumber = 0;
      buffer.valueType = 0;
      int received;
      
      received = connection.receive(&buffer, sizeof(buffer));
      
      writeFile(file, buffer);

      averageArray[(int)buffer.sensorNumber].set(buffer.reading);
  }

  intervalTimer.stop();
  file.close();
  connection.closed();
  std::cout << "Terminating..." << "\n";
  
}

void writeFile(std::fstream &file, struct reading &buffer){ 
  file << std::chrono::system_clock::now().time_since_epoch().count()<< ", "
       << (int)buffer.sensorNumber << ", "
       << buffer.reading
       << "\n";
  file.flush();
}

void printResetAverage(std::array<runningAverage, 11> &averageArray){
  std::cout << "Printing averages from second thread" << "\n";

  for (int i = 1; i <= 10; ++i) 
  {
    std::cout << "Sensor number: " << i
              << " Average: " << averageArray[i].getAverage()
              << "\n";
    averageArray[i].reset();
  }
  std::cout << "\n";
}

void close(int sig){ terminate = 1;}