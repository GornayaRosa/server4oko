#ifndef SERVER4OKO_HOMVHANDLER_H
#define SERVER4OKO_HOMVHANDLER_H

#include <iostream>
#include <stdio.h>
#include <getopt.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include "Params.h"
#include <csignal>
class HomvHandler {
private:
    int argc;
    char **args;
    bool run();
    int homvPID;
    Params params;
public:
    HomvHandler(int argc, char **argv);
    bool rerun();
    bool argvParser(std::string &params_filename, std::string &tgbot_params_filename, std::string &web_path,
                    bool &test_flag);
    bool stop();
};


#endif //SERVER4OKO_HOMVHANDLER_H
