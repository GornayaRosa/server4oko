#ifndef SERVER4OKO_PARAMS_H
#define SERVER4OKO_PARAMS_H
#include <string>
#include <ifaddrs.h>
#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
class Params {
private:
    std::string paramsFilename;
    std::string tgbotFilename;
    std::string webPath;
    std::string httpAddr;
    std::string httpsAddr;
    std::string exe0;
    std::string exe1;
    std::string ipAddr;

    void detectIp();
public:
    Params();
    const std::string getExe0();
    const std::string getExe1();
    const std::string &getParamsFilename() const;

    const std::string &getTgbotFilename() const;

    const std::string &getHttpAddr() const;

    const std::string &getHttpsAddr() const;

    const std::string &getWebPath() const;


};
#endif //SERVER4OKO_PARAMS_H


