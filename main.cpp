#include "connection.h"
#include "runningAverage.h"
#include "intervalTimer.h"
#include <fstream> 
#include <iostream>

struct __attribute__((__packed__)) reading {
  uint8_t sensorNumber;
  uint8_t valueType;
  uint64_t reading;
} ;

void writeFile(std::fstream &file, struct reading &buffer);
void greet();

int main() 
{
    connection connection;
    connection.connect(12345, "127.0.0.1");

    runningAverage runningAverage;

    intervalTimer intervalTimer(greet, 3000);
    intervalTimer.run();
    
    std::fstream file;
    file.open ("readings.csv", std::fstream::out); 
    file << "unix timestamp, sensor number, reading\n";
    struct reading buffer;
    
    while(1){

        buffer.reading = 0;
        buffer.sensorNumber = 0;
        buffer.valueType = 0;
        int received;
        
        received = connection.receive(&buffer, sizeof(buffer));
        
        writeFile(file, buffer);

        std::cout << "Payload: "     << (int)received
                  << " Value type: "  << (int)buffer.valueType
                  << " Sensor nr: "   << (int)buffer.sensorNumber
                  << " Reading: "     << buffer.reading << "\n";     
    }
}

void writeFile(std::fstream &file, struct reading &buffer){ 

  file << std::chrono::system_clock::now().time_since_epoch().count()<< ", "
       << (int)buffer.sensorNumber << ", "
       << buffer.reading
       << "\n";
  file.flush();
}

void greet()
{
   std::cout << ".........This message was printed from second thread" << "\n";
}