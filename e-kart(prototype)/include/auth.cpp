#pragma once
#include <jwt-cpp/jwt.h>
#include <string>
#include <vector>
#include <bcrypt/BCrypt.hpp>

namespace auth {
    // JWT token generation
    std::string generate_jwt_token(int user_id, const std::string& secret_key) {
        auto token = jwt::create()
            .set_issuer("auth0")
            .set_type("JWS")
            .set_payload_claim("sub", jwt::claim(std::to_string(user_id)))
            .set_issued_at(std::chrono::system_clock::now())
            .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours(24))
            .sign(jwt::algorithm::hs256{secret_key});
        
        return token;
    }

    // JWT token verification
    bool verify_jwt_token(const std::string& token, const std::string& secret_key) {
        try {
            auto decoded = jwt::decode(token);
            auto verifier = jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{secret_key})
                .with_issuer("auth0");
            verifier.verify(decoded);
            return true;
        } catch (const std::exception& e) {
            return false;
        }
    }

    // Extract user ID from JWT token
    int get_user_id_from_token(const std::string& token) {
        auto decoded = jwt::decode(token);
        return std::stoi(decoded.get_payload_claim("sub").as_string());
    }

    // Password hashing
    std::string hash_password(const std::string& password) {
        return BCrypt::generateHash(password, BCrypt::generateSalt(12));
    }

    // Password verification
    bool verify_password(const std::string& password, const std::string& hash) {
        return BCrypt::validatePassword(password, hash);
    }

    // Input validation
    bool is_valid_email(const std::string& email) {
        const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return std::regex_match(email, pattern);
    }

    bool is_valid_password(const std::string& password) {
        return password.length() >= 8;
    }
}
