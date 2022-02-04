#ifndef SERVER4OKO_APIV1_H
#define SERVER4OKO_APIV1_H
#include "string"

#include "stdlib.h"
#include <sstream>
#include <fstream>
#include "../config/config.pb.h"
#include <google/protobuf/text_format.h>
#include <google/protobuf/util/json_util.h>
#include "Params.h"
#include "unistd.h"
class APIv1 {
private:
    Params params = Params();
public:
    std::string getConfig();
    bool putConfig(std::string json);
};



#endif //SERVER4OKO_APIV1_H
