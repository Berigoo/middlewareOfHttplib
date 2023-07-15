//
// Created by pach on 7/15/23.
//

#ifndef IOTAPI_TOOLS_H
#define IOTAPI_TOOLS_H

#include <utility>

#include "httplib.h"
#include "mariadb/conncpp.hpp"
using namespace std;
using namespace httplib;

namespace tools {
    namespace middleware{
        class middlewareUnit{
        public:
            middlewareUnit();
            middlewareUnit(function<void(const Request&, Response&)> handler){
                unit = std::move(handler);
            }

            function<void(const Request&, Response&)> unit;                             //Handler function
            middlewareUnit* next = nullptr;
        };
        class middleware{
        public:

            middlewareUnit* head = nullptr;
            middlewareUnit* current = nullptr;

            void addUnit(function<void(const Request& req, Response& res)> handler){    //Add unit to the back of linked list
                if(head == nullptr){
                    head = new middlewareUnit(handler);
                    current = head;
                }else {
                    current = head;
                    middlewareUnit *aux = current;
                    while (current->next) {
                        current = current->next;
                        if (current->next) aux = aux->next;
                    }
                    current->next = new middlewareUnit(std::move(handler));
                    current = head;
                }
            }

            void next(const Request& req, Response& res){
                if(current->next) {                                                     //Iterate middleware units
                    current = current->next;
                    current->unit(req, res);
                }else{
                    res.status = 403;                                                   //Last Default Response
                    res.set_content("Forbidden", "text/plain");
                    current = head;
                }
            }
        };
    }
    namespace db {
        struct dbConn {
        private:
            sql::SQLString url;
            sql::Driver *driver;
        public:
            string host, db;
            sql::SQLString user, passwd;
            unique_ptr<sql::Connection> connection;

            dbConn(string host, string user, string passwd, string db) {
                this->host = host;
                this->user = user;
                this->passwd = passwd;
                this->db = db;

                url = "jdbc:mariadb://" + host + ":3306/" + db;
                driver = sql::mariadb::get_driver_instance();
            }

            void connInit() {
                connection = unique_ptr<sql::Connection>(driver->connect(url, user, passwd));
                if (!connection) {
                    cerr << "Invalid database connection";
                    exit(EXIT_FAILURE);
                }
            }

            sql::ResultSet *execPreparedQuery(string statement, vector<string> values) {
                shared_ptr<sql::PreparedStatement> stmt(connection->prepareStatement(statement));
                try {
                    for (int i = 1; i <= values.size(); i++) stmt->setString(i, values[i - 1]);
                    sql::ResultSet *tmp(stmt->executeQuery());
                    return tmp;
                } catch (sql::SQLException &e) {
                    cerr << "Error reading database: " <<
                         e.what() << endl;
                }
                return nullptr;
            }
        };
    }
}

#endif //IOTAPI_TOOLS_H
