#include "HomvHandler.h"
HomvHandler::HomvHandler(int argc, char **argv) {
    homvPID=0;
    params = Params();
    this->argc = argc;
    this->args = new char *[argc + 1];
    for (int i = 1; i < this->argc; i++) {
        this->args[i] = argv[i];
    }
    this->args[this->argc] = nullptr;
    this->run();
}

bool HomvHandler::run() {
    std::cout << "RUN HOMV" << std::endl;
    if((homvPID = fork()) == 0) {
        std::string exe_0=params.getExe0();
        args[0] = &exe_0[0];
        execl(args[0], args[0], "ya.ru", nullptr);
        return true;
    }
    return false;
}

bool HomvHandler::rerun() {
    this->stop();
    this->run();
    return true;
}
bool HomvHandler::stop() {
    kill(homvPID, SIGUSR1);
    return true;
}




