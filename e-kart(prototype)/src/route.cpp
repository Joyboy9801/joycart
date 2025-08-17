#include "routes.h"
#include "services.h"
#include "auth.h"

void register_auth_routes(crow::SimpleApp& app, sqlpp::postgresql::connection& db, const std::string& secret_key) {
    // User registration
    CROW_ROUTE(app, "/api/register").methods("POST"_method)
    ([&db, &secret_key](const crow::request& req){
        auto body = crow::json::load(req.body);
        std::string username = body["username"].s();
        std::string email = body["email"].s();
        std::string password = body["password"].s();
        std::string first_name = body.value("first_name", "");
        std::string last_name = body.value("last_name", "");

        // Validation
        if (!auth::is_valid_email(email)) {
            return crow::response(400, "Invalid email format");
        }
        if (!auth::is_valid_password(password)) {
            return crow::response(400, "Password must be at least 8 characters");
        }

        try {
            // Check if user already exists
            auto existing_user = db(select(users.username)
                                     .from(users)
                                     .where(users.username == username));
            
            if (!existing_user.empty()) {
                return crow::response(409, "Username already exists");
            }

            // Hash password
            std::string password_hash = auth::hash_password(password);

            // Insert new user
            db(insert_into(users).set(
                users.username = username,
                users.email = email,
                users.passwordHash = password_hash,
                users.firstName = first_name,
                users.lastName = last_name,
                users.isAdmin = false,
                users.createdAt = std::chrono::system_clock::now(),
                users.updatedAt = std::chrono::system_clock::now()
            ));

            crow::json::wvalue response;
            response["message"] = "User registered successfully";
            return crow::response(response);
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Database error: ") + e.what());
        }
    });

    // User login
    CROW_ROUTE(app, "/api/login").methods("POST"_method)
    ([&db, &secret_key](const crow::request& req){
        auto body = crow::json::load(req.body);
        std::string username = body["username"].s();
        std::string password = body["password"].s();

        try {
            auto result = db(select(all_of(users))
                            .from(users)
                            .where(users.username == username));
            
            for (const auto& row : result) {
                if (auth::verify_password(password, row.passwordHash)) {
                    std::string token = auth::generate_jwt_token(row.id, secret_key);
                    
                    crow::json::wvalue response;
                    response["access_token"] = token;
                    response["user"] = {
                        {"id", row.id},
                        {"username", std::string(row.username)},
                        {"email", std::string(row.email)},
                        {"first_name", std::string(row.firstName)},
                        {"last_name", std::string(row.lastName)},
                        {"is_admin", row.isAdmin}
                    };
                    return crow::response(response);
                }
            }
            
            return crow::response(401, "Invalid credentials");
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Database error: ") + e.what());
        }
    });

    // Refresh token
    CROW_ROUTE(app, "/api/refresh").methods("POST"_method)
    ([&secret_key](const crow::request& req){
        auto auth_header = req.get_header_value("Authorization");
        if (auth_header.empty() || auth_header.substr(0, 7) != "Bearer ") {
            return crow::response(401, "Missing or invalid Authorization header");
        }
        
        std::string token = auth_header.substr(7);
        
        try {
            auto decoded = jwt::decode(token);
            auto verifier = jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{secret_key})
                .with_issuer("auth0");
            verifier.verify(decoded);
            
            int user_id = std::stoi(decoded.get_payload_claim("sub").as_string());
            std::string new_token = auth::generate_jwt_token(user_id, secret_key);
            
            crow::json::wvalue response;
            response["access_token"] = new_token;
            return crow::response(response);
        } catch (const std::exception& e) {
            return crow::response(401, "Invalid token");
        }
    });

    // Logout
    CROW_ROUTE(app, "/api/logout").methods("POST"_method)
    ([](const crow::request& req){
        // In a stateless API, logout is handled client-side by disc
