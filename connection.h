#include <string>
#include <netinet/in.h>

class connection
{
    public:
        void connect(int port, std::string host);
        int receive(void * buffer, size_t bufferSize); //return payload

    private:
        int socketId;
        struct sockaddr_in client;
};