#pragma once
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

class Config {
private:
    static nlohmann::json config_data;

    static void load_config() {
        try {
            std::ifstream file("config.json");
            if (file.is_open()) {
                file >> config_data;
            } else {
                // Default configuration
                config_data = {
                    {"server_port", 8080},
                    {"database_host", "localhost"},
                    {"database_port", 5432},
                    {"database_name", "ecommerce"},
                    {"database_user", "postgres"},
                    {"database_password", "password"},
                    {"jwt_secret", "your-secret-key-change-in-production"},
                    {"log_level", "warning"}
                };
                
                // Save default config
                std::ofstream out_file("config.json");
                out_file << config_data.dump(4);
            }
        } catch (const std::exception& e) {
            // Fallback to hardcoded defaults
            config_data = {
                {"server_port", 8080},
                {"database_host", "localhost"},
                {"database_port", 5432},
                {"database_name", "ecommerce"},
                {"database_user", "postgres"},
                {"database_password", "password"},
                {"jwt_secret", "your-secret-key-change-in-production"},
                {"log_level", "warning"}
            };
        }
    }

public:
    static int getServerPort() {
        if (config_data.empty()) load_config();
        return config_data.value("server_port", 8080);
    }

    static std::string getDatabaseHost() {
        if (config_data.empty()) load_config();
        return config_data.value("database_host", "localhost");
    }

    static int getDatabasePort() {
        if (config_data.empty()) load_config();
        return config_data.value("database_port", 5432);
    }

    static std::string getDatabaseName() {
        if (config_data.empty()) load_config();
        return config_data.value("database_name", "ecommerce");
    }

    static std::string getDatabaseUser() {
        if (config_data.empty()) load_config();
        return config_data.value("database_user", "postgres");
    }

    static std::string getDatabasePassword() {
        if (config_data.empty()) load_config();
        return config_data.value("database_password", "password");
    }

    static std::string getJwtSecret() {
        if (config_data.empty()) load_config();
        return config_data.value("jwt_secret", "your-secret-key-change-in-production");
    }

    static std::string getLogLevel() {
        if (config_data.empty()) load_config();
        return config_data.value("log_level", "warning");
    }
};
