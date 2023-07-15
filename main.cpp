#include <iostream>
#include <cstdlib>
#include <httplib.h>
#include "aux/tools.h"
#include "aux/middleware.h"
#include "jwt-cpp/jwt.h"
using namespace httplib;
using namespace std;

tools::middleware::middleware _middleware;

int main() {
    Server svr;
    tools::db::dbConn conn(getenv("DB_HOST"), getenv("DB_USER"), getenv("DB_PASS"), getenv("DB"));
    conn.connInit();

    _middleware.addUnit(middlewareFunc::checkParams);       //add first func to middleware
    _middleware.addUnit(middlewareFunc::checkParams2);      //add second func to middleware

    svr.Post("/api/devices/login", [](const Request& req, Response& res){
        res.set_content("Hello World", "text/plain");
        return;
    });

    svr.Get("/", _middleware.head->unit);

    svr.listen("localhost", 8000);
}