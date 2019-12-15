#ifndef __UTILS_H
#define __UTILS_H

#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>
#include <iostream>

inline void fail(boost::system::error_code ec, std::string what){
    if(ec == boost::asio::error::operation_aborted)
        return;
    std::cerr << what << ": " << ec.message() << "\n";
}

#endif
