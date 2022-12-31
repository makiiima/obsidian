#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define MAXBUFSIZE 1024    //BUFFER_SIZE
void* clientHandler(void* cfd);

class  webServer
{
private: 
    int sockfd;  
    sockaddr_in sin;   
    const int MAXCLIENT = 16;
   
public:
    webServer();
    ~webServer();
    void start();  
};

int main()
{
    webServer mywebServer; 
    mywebServer.start();
}

webServer::webServer()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(5876); 
    sin.sin_addr.s_addr = htonl(INADDR_ANY); 
    bind(sockfd, (sockaddr*)&sin, sizeof(sin)); 
    listen(sockfd, MAXCLIENT);
}

webServer::~webServer()
{
    close(sockfd);
}


void webServer::start() 
{
    std::cout << "listening\n";
    while(true)
    {
        sockaddr_in client; 
        unsigned int length = sizeof(client);
        int connection_fd = accept(sockfd, (sockaddr*)&client, (socklen_t*)&length);
        std::cout<<inet_ntoa(client.sin_addr)<<":"<<ntohs(client.sin_port)<<" connected.\n";
        pthread_t cilentThread;
        pthread_create(&cilentThread, nullptr, clientHandler,&connection_fd);
    }
}

void* clientHandler(void* cfd)
{   
    int clientSockfd = *(int*)cfd;
    char buffer[MAXBUFSIZE] = {0};
    std::string request;
    while (true)
    {
        int realSize = recv(clientSockfd, buffer, MAXBUFSIZE, 0);
        request.append(buffer, buffer + realSize);
        if (realSize < MAXBUFSIZE) break;
    }
    std::string reply;  
    std::regex whitespace("\\s+");
    std::vector<std::string> tokens(std::sregex_token_iterator(request.begin(), request.end(), whitespace, -1),
                                        std::sregex_token_iterator());
    std::string type = tokens[0]; 
    std::string path = tokens[1];
    std::string http = tokens[2];

    if (type == "GET")
    {
        std::fstream file;
        std::string realPath;
        std::string content_type;
        bool notfound = false;  
        if (path == "/login/noimg.html") 
        {
            realPath = "/Users/hejiajun/desktop/network2022/lab8/rt/html/noimg.html";
            content_type = "text/html";
        }
        else if (path == "/login/test.html") 
        {
            realPath = "/Users/hejiajun/desktop/network2022/lab8/rt/html/test.html";
            content_type = "text/html";
        } 
        else if (path == "/login/test.txt") 
        {
            realPath = "/Users/hejiajun/desktop/network2022/lab8/rt/txt/test.txt";
            content_type = "text/plain";
        }
        else if (path == "/image/logo.jpg") 
        {
            realPath = "/Users/hejiajun/desktop/network2022/lab8/rt/img/logo.jpg";
            content_type = "image/jpeg";
        }
        else notfound = true;

        if(!notfound) 
        {
            file.open(realPath, std::ios::in | std::ios::binary);
            std::istreambuf_iterator<char> begin(file), end;
            std::string fileData(begin, end);
            file.close();
            std::string content_length = std::to_string(fileData.size());
            reply.append("HTTP/1.1 200 OK\n");  
            reply.append("Content-Type: " + content_type + "\n");
            reply.append("Content-Length: " + content_length + "\n\n");
            reply.append(fileData);
            reply.append("\n");
        }
        else 
        {
            std::string response = "<html><body><h1>404 Page not found</h1></body></html>\n";
            reply.append("HTTP/1.1 404 Not Found\n");
            reply.append("Server: Jiajun\n");
            reply.append("Content-Type: text/html\n");
            reply.append("Content-Length: " + std::to_string(response.size()) + "\n\n"); 
            reply.append(response);
            reply.append("\n");
        }
    }
    else if (type == "POST")
    {
        std::string name = "";
        std::string passwd = "";
        std::string data = request.substr(request.find("\r\n\r\n", 0));
        int pos_login = data.find("login");
        int pos_pwd = data.find("pass");
        name = data.substr(pos_login+6, pos_pwd - pos_login - 7);
        passwd = data.substr(pos_pwd + 5);
        reply.append("HTTP/1.1 200 OK\n");
        reply.append("Server: Hejiajun\n");
        reply.append("Content-Type: text/html\n");
        if (name == "Jiajun" && passwd == "5876" ) 
        {
            std::string response = "<html><body>Hello, Jiajun!</body></html>\n";
            reply.append("Content-Length: " + std::to_string(response.size()) + "\n\n");
            reply.append(response);
            reply.append("\n");
        }
        else 
        {
            std::string response = "<html><body>Password wrong, failed</body></html>\n";
            reply.append("Content-Length: " + std::to_string(response.size()) + "\n\n");
            reply.append(response);
            reply.append("\n");
        }
    }
    send(clientSockfd, reply.c_str(), reply.size(), 0);
    close(clientSockfd); 
    return nullptr;
}