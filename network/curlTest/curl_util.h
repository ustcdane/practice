#pragma once
#include <string>
#include <string.h>
#include <curl/curl.h>
#include <map>

//  a C++ wrapper of libcurl

class CurlCpp
{
public:
	CurlCpp();
    ~CurlCpp();
    // GET 
	std::string get(const std::string& url);
    std::string get(const std::string& url, const std::map<std::string, std::string>& params);
    // POST
    std::string post(const std::string& url, const std::string& data);
    std::string post(const std::string& url, const std::map<std::string, std::string>& params);
    std::string post(const std::string& url, const std::map<std::string, std::string>& params, const std::map<std::string, std::string>& headers_map);

    unsigned int  HttpStatus() const { 
        return httpStatus_; 
    }

private:
    CURL* curl_ = nullptr;
    CURLcode curlCode_ = CURLE_FAILED_INIT;
    unsigned int httpStatus_ = 0;
};

