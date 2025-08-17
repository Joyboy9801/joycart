#include <crow.h>
#include <jwt-cpp/jwt.h>
#include <iostream>
#include "config.h"
#include "middleware.h"
#include "routes.h"

int main() {
    crow::SimpleApp app;

    // Database connection
    sqlpp::postgresql::connection db(
        "dbname=" + Config::getDatabaseName() + 
        " user=" + Config::getDatabaseUser() + 
        " password=" + Config::getDatabasePassword() + 
        " host=" + Config::getDatabaseHost() + 
        " port=" + std::to_string(Config::getDatabasePort())
    );

    // JWT configuration
    const std::string secret_key = Config::getJwtSecret();

    // Middleware
    app.loglevel(crow::LogLevel::Warning);
    app.use_middleware<JwtMiddleware>(secret_key);

    // Register routes
    register_auth_routes(app, db, secret_key);
    register_product_routes(app, db);
    register_cart_routes(app, db);
    register_order_routes(app, db);
    register_admin_routes(app, db);

    // Static files
    crow::mustache::set_base(".");
    app.set_static_file_dir("static");
    app.set_template("base.html");

    // Index route
    CROW_ROUTE(app, "/")([](){
        crow::mustache::context ctx;
        ctx.render("index.html");
    });

    std::cout << "E-Commerce API server running on port " << Config::getServerPort() << std::endl;
    app.port(Config::getServerPort()).multithreaded().run();

    return 0;
}
