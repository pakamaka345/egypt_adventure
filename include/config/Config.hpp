#pragma once
#include <string>
#include <memory>
#include "nlohmann/json.hpp"

class Character;

class Config
{
public:
    static std::shared_ptr<Config> getInstance(const std::string& path = "");

    template<typename T>
    std::shared_ptr<T> createEntity(const std::string& entityName) {
        auto entityConfig = configJson.at(entityName);
        return std::make_shared<T>(
                entityConfig.at("name").get<std::string>(),
                entityConfig.at("attackRange").get<int>(),
                entityConfig.at("attackDamage").get<float>(),
                entityConfig.at("health").get<float>(),
                entityConfig.at("defense").get<float>(),
                entityConfig.at("priority").get<float>(),
                entityConfig.at("dodgeChance").get<float>(),
                entityConfig.at("x").get<int>(),
                entityConfig.at("y").get<int>(),
                entityConfig.at("symbol").get<std::string>()[0]
        );
    }

    std::shared_ptr<Character> createCharacter();

private:
    explicit Config(const std::string& path);

    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    static nlohmann::json loadJson(const std::string& path);

    static std::shared_ptr<Config> instance;
    nlohmann::json configJson;
};