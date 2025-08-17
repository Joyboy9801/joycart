#pragma once
#include <crow.h>
#include <jwt-cpp/jwt.h>
#include "config.h"

class JwtMiddleware {
private:
    std::string secret_key;

public:
    JwtMiddleware(const std::string& key) : secret_key(key) {}

    void before_handle(crow::request& req, crow::response& res, crow::context& ctx) {
        auto auth_header = req.get_header_value("Authorization");
        
        if (auth_header.empty() || auth_header.substr(0, 7) != "Bearer ") {
            res.code = 401;
            res.write("Missing or invalid Authorization header");
            res.end();
            return;
        }
        
        std::string token = auth_header.substr(7);
        
        try {
            auto decoded = jwt::decode(token);
            auto verifier = jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{secret_key})
                .with_issuer("auth0");
            verifier.verify(decoded);
            
            // Add user ID to context
            ctx.set("user_id", decoded.get_payload_claim("sub").as_string());
        } catch (const std::exception& e) {
            res.code = 401;
            res.write("Invalid token");
            res.end();
            return;
        }
    }
};

class CorsMiddleware {
public:
    void before_handle(crow::request& req, crow::response& res, crow::context& ctx) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
        
        if (req.method == "OPTIONS"_method) {
            res.code = 200;
            res.end();
            return;
        }
    }
};
