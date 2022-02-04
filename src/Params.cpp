
#include "Params.h"
#include <string>


Params::Params(){
    detectIp();
    paramsFilename="/oko/config/params.conf";
    tgbotFilename= "/oko/config/params_tgbot.conf";
    webPath = "/oko/web/";
    httpAddr = "http://"+ipAddr+":8080";
    httpsAddr = "http://127.0.0.1:8443";
    //exe0 = "/usr/bin/homv";
    exe0 = "/bin/ping";
    exe1 = "./homv";

}

const std::string &Params::getParamsFilename() const {
    return paramsFilename;
}

const std::string &Params::getTgbotFilename() const {
    return tgbotFilename;
}

const std::string &Params::getHttpAddr() const {
    return httpAddr;
}

const std::string &Params::getHttpsAddr() const {
    return httpsAddr;
}

const std::string &Params::getWebPath() const {
    return webPath;
}

const std::string Params::getExe0()  {
    return exe0;
}

const std::string Params::getExe1()  {
    return exe1;
}

void Params::detectIp() {
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            std::string ifName= std::string (ifa->ifa_name);
            if (addressBuffer!="127.0.0.1"
            && ((ifName.find("eth") != std::string::npos)||(ifName.find("ens") != std::string::npos))){
                this->ipAddr=addressBuffer;
                break;
            }
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
}
