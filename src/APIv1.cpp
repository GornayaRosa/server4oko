#include "APIv1.h"

std::string APIv1::getConfig() {
    std::ifstream cfgFile(params.getParamsFilename());
    config::Config config;
    std::ostringstream cfgStream;
    std::string output;
    cfgStream<<cfgFile.rdbuf();
    cfgFile.close();
    bool ok = google::protobuf::TextFormat::ParseFromString(cfgStream.str(), &config);
    if (!ok){
        std::cerr << "[ERROR] couldn't parse config file!" << std::endl;
    }
    google::protobuf::util::MessageToJsonString(config, &output);
    std::cout<< output << std::endl;
    return output;
}
bool APIv1::putConfig(std::string json){
    config::Config config;
    std::ostringstream cfgStream;
    std::cout << "JSON input size: " <<  json.size() << std::endl;
    std::cout << "JSON input size: " <<  json << std::endl;
    google::protobuf::util::Status ok = google::protobuf::util::JsonStringToMessage(json, &config);
    if(!ok.ok()) {
        std::cerr << "[ERROR] couldn't parse JSON config file!" << std::endl;
        std::cerr << ok.ToString() << std::endl;
        return false;
    }
    std::string str;
    google::protobuf::TextFormat::PrintToString(config, &str);

    std::ofstream out(params.getParamsFilename());
    out << str << std::endl;
    out.close();
    sync();
}


