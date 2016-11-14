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
	bool get(const std::string& url, std::string& readBuf);
    bool get(const std::string& url, const std::map<std::string, std::string>& params, std::string& readBuf);
    // POST
    bool post(const std::string& url, const std::string& data, std::string& readBuf);
    bool post(const std::string& url, const std::map<std::string, std::string>& params, std::string& readBuf);
    bool post(const std::string& url, const std::map<std::string, std::string>& params, const std::map<std::string, std::string>& headers_map, std::string& readBuf);

    unsigned int  HttpStatus() const { 
        return httpStatus_; 
    }

private:
    CURL* curl_ = nullptr;
    CURLcode curlCode_ = CURLE_FAILED_INIT;
    unsigned int httpStatus_ = 0;
};

