//
// Created by pach on 7/15/23.
//

#include "middleware.h"

void middlewareFunc::checkParams(const Request &req, Response &res) {
    if(req.params.find("valid") != req.params.end()){
        res.set_content("Found!", "text/plain");
    }else{
        _middleware.next(req, res);
    }
}

void middlewareFunc::checkParams2(const Request &req, Response &res) {
    if(req.params.find("valid2") != req.params.end()){
        res.set_content("Found2!", "text/plain");
    }else{
        _middleware.next(req, res);
    }
}
