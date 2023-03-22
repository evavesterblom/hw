# Sensor Data collect and save via web socket C++
*   General requirements  
    *   Have to compile and run on Linux (and Windows)
    *   Solution in git
*   Task 1  
    *   Sensor data is sent over UDP and broadcasted to port 12345. There are multiple sensors which send data at random intervals.
    *   Data format: uint8 sensor number, uint8 value type, uint64 reading → payload length: 10B
        *   Possible values for **value type** are defined in sensor\_sender.py:14:28
    *   Log the data from sensors and save it in csv format: timestamp, senor id, sensor reading
    *   Print sensor data to standard output with frequency of 1 Hz, averaging over last 10 values
    *   Sensor data can be requested by sending a UDP packet to port 12346  
        *   **request:** uint8 sensor number, uint8 value type/kind (0 - last value, 1 - mean of last 10 values, 2 - mean of all values) → request length 2B
        *   **response**: uint8 sensor number, uint8 value type, uint64 reading → response length 10B



* Solution: connection made to host, listen port 12345, write data to file, calculate running average + printing to cout after 1sec, average is calculated as port 12346 not open.

    * **classes**: connection, intervalTimer, runningAverage.
    
    * **server**: sensor_sender.py -> only transmits sensor data on port 12345, fixed nr of sensors (10)
    
    * **main**:   
        * make connection to server on 12345 
        * init array where average values are to be held
        * set up timer and start it in another thread. Callable function 'printResetAverage' is passed. In 'printResetAverage' the values are held in objects and running average is calculated. When function is called, averages are reset
        * initing filestream for writing data to csv
        * while not terminated - data is read, written to file and running average is calculated
        * on terminate - file closed, interval stopped, main exits, connections closed
    
    * **compile**: 
        * in hw folder ``` g++ main.cpp connection.cpp runningAverage.cpp intervalTimer.cpp -o  main -std=c++11 ```
        * run: ``` ./main ```
        * start server:  ``` python3 sensor_sender.py ```  

