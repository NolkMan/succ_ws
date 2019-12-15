#include "web_socket_server.hpp"

#include <fstream>
#include <vector>
#include <iostream>

std::string wsserv::data_path;

std::string get_file(std::string path){
	std::ifstream ifs(wsserv::data_path + path);
	std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

	return content + "\n";
}

std::string wsserv::responce_for_request(std::string request){
	if (request == "home"){
		return get_file("home.html");
	}
	if (request == "more"){
		return get_file("more.html");
	}
	if (request == "flag"){
		return get_file("flag.txt");
	}

	if (request == "info"){
		return get_file("info.html");
	}

	if (request == "photos"){
		return get_file("photos.html");
	}

	return "";
}
