#include "config/Config.hpp"
#include "entities/Character.hpp"
#include <fstream>
#include <mutex>

Config::Config(const std::string &path) : configJson(loadJson(path))
{
}

std::shared_ptr<Config> Config::getInstance(const std::string &path) {
    static std::once_flag initFlag;
    std::call_once(initFlag, [&](){
        instance = std::shared_ptr<Config>(new Config(path));
    });

    return instance;
}

nlohmann::json Config::loadJson(const std::string &path) {
    if (path.empty()) {
        throw std::runtime_error("Path to config file is empty");
    }

    nlohmann::json  json;
    std::ifstream  file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + path);
    }

    file >> json;
    return json;
}

std::shared_ptr<Character> Config::createCharacter() {
    auto characterConfig = configJson.at("Character");
    return std::make_shared<Character>(
                characterConfig.at("name").get<std::string>(),
                characterConfig.at("x").get<int>(),
                characterConfig.at("y").get<int>(),
                characterConfig.at("symbol").get<std::string>()[0]
            );
}

std::shared_ptr<Config> Config::instance = nullptr;

