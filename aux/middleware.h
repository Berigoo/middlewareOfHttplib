//
// Created by pach on 7/15/23.
//

#ifndef IOTAPI_MIDDLEWARE_H
#define IOTAPI_MIDDLEWARE_H

#include "tools.h"

extern tools::middleware::middleware _middleware;

namespace middlewareFunc {
    void checkParams(const Request &req, Response &res);
    void checkParams2(const Request &req, Response &res);
}


#endif //IOTAPI_MIDDLEWARE_H
