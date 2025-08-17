#pragma once
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/postgresql/postgresql.h>
#include <string>

namespace models {
    // Users table
    struct Users {
        struct Id {
            int value;
            operator int() const { return value; }
        };
        struct Username {
            std::string value;
            operator std::string() const { return value; }
        };
        struct Email {
            std::string value;
            operator std::string() const { return value; }
        };
        struct PasswordHash {
            std::string value;
            operator std::string() const { return value; }
        };
        struct FirstName {
            std::string value;
            operator std::string() const { return value; }
        };
        struct LastName {
            std::string value;
            operator std::string() const { return value; }
        };
        struct Address {
            std::string value;
            operator std::string() const { return value; }
        };
        struct Phone {
            std::string value;
            operator std::string() const { return value; }
        };
        struct IsAdmin {
            bool value;
            operator bool() const { return value; }
        };
        struct CreatedAt {
            std::chrono::system_clock::time_point value;
            operator std::chrono::system_clock::time_point() const { return value; }
        };
        struct UpdatedAt {
            std::chrono::system_clock::time_point value;
            operator std::chrono::system_clock::time_point() const { return value; }
        };
    };

    // Products table
    struct Products {
        struct Id {
            int value;
            operator int() const { return value; }
        };
        struct Name {
            std::string value;
            operator std::string() const { return value; }
        };
        struct Description {
            std::string value;
            operator std::string() const { return value; }
        };
        struct Price {
            double value;
            operator double() const { return value; }
        };
        struct Stock {
            int value;
            operator int() const { return value; }
        };
        struct CategoryId {
            int value;
            operator int() const { return value; }
        };
        struct ImageUrl {
            std::string value;
            operator std::string() const { return value; }
        };
        struct CreatedAt {
            std::chrono::system_clock::time_point value;
            operator std::chrono::system_clock::time_point() const { return value; }
        };
        struct UpdatedAt {
            std::chrono::system_clock::time_point value;
            operator std::chrono::system_clock::time_point() const { return value; }
        };
    };

    // Cart items table
    struct CartItems {
        struct Id {
            int value;
            operator int() const { return value; }
        };
        struct UserId {
            int value;
            operator int() const { return value; }
        };
        struct ProductId {
            int value;
            operator int() const { return value; }
        };
        struct Quantity {
            int value;
            operator int() const { return value; }
        };
        struct CreatedAt {
            std::chrono::system_clock::time_point value;
            operator std::chrono::system_clock::time_point() const { return value; }
        };
        struct UpdatedAt {
            std::chrono::system_clock::time_point value;
            operator std::chrono::system_clock::time_point() const { return value; }
        };
    };

    // Orders table
    struct Orders {
        struct Id {
            int value;
            operator int() const { return value; }
        };
        struct UserId {
            int value;
            operator int() const { return value; }
        };
        struct TotalAmount {
            double value;
            operator double() const { return value; }
        };
        struct Status {
            std::string value;
            operator std::string() const { return value; }
        };
        struct ShippingAddress {
            std::string value;
            operator std::string() const { return value; }
        };
        struct PaymentMethod {
            std::string value;
            operator std::string() const { return value; }
        };
        struct CreatedAt {
            std::chrono::system_clock::time_point value;
            operator std::chrono::system_clock::time_point() const { return value; }
        };
        struct UpdatedAt {
            std::chrono::system_clock::time_point value;
            operator std::chrono::system_clock::time_point() const { return value; }
        };
    };

    // Order items table
    struct OrderItems {
        struct Id {
            int value;
            operator int() const { return value; }
        };
        struct OrderId {
            int value;
            operator int() const { return value; }
        };
        struct ProductId {
            int value;
            operator int() const { return value; }
        };
        struct Quantity {
            int value;
            operator int() const { return value; }
        };
        struct Price {
            double value;
            operator double() const { return value; }
        };
        struct CreatedAt {
            std::chrono::system_clock::time_point value;
            operator std::chrono::system_clock::time_point() const { return value; }
        };
    };

    // Table definitions
    constexpr auto users = sqlpp::table::Users{};
    constexpr auto products = sqlpp::table::Products{};
    constexpr auto cart_items = sqlpp::table::CartItems{};
    constexpr auto orders = sqlpp::table::Orders{};
    constexpr auto order_items = sqlpp::table::OrderItems{};
}
