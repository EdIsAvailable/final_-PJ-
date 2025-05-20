#pragma once

#include <memory>
#include <string>
#include <iostream>

#include <mysql_driver.h>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
// Function declarations
std::unique_ptr<sql::Connection> connectToDatabase();
void registerUser(const std::string& username, const std::string& passwordHash);
void saveMessage(const std::string& sender, const std::string& receiver, const std::string& message);
void fetchMessages(const std::string& receiver);
