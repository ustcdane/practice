#include <iostream>
#include "curl_util.h"
// g++ -o curl curl_util.cpp main.cpp -lcurl -std=c++11

CurlCpp::CurlCpp(){};
CurlCpp::~CurlCpp(){};

/* Callbacks */
struct postData
{
    const char *readptr;
    long sizeleft;
};

static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
    struct postData *data_content = (struct postData *)userp;
     
    if(size*nmemb < 1)
        return 0;

    if(data_content->sizeleft)
    {
        *(char *)ptr = data_content->readptr[0]; 
        data_content->readptr++;                
        data_content->sizeleft--;     
        return 1;                        /* we return 1 byte at a time! */ 
    }

    return 0;                          /* no more data left to deliver */ 
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/* GET methods */
std::string CurlCpp::get(const std::string &url)
{   
    httpStatus_ = 0;
    std::string readBuffer;

    curl_ = curl_easy_init();

    if(curl_)
    {
        curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &readBuffer);
        curlCode_ = curl_easy_perform(curl_);

        unsigned int http_code = 0;
        if(curlCode_ != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curlCode_));
            return 0;
        }
        // Get the curl response code 
        curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &http_code);
        httpStatus_ = http_code;

        if(int(httpStatus_) == 400)
            std::cerr << "Response <" << httpStatus_ << "> thrown." << std::endl;

        curl_easy_cleanup(curl_);
    }

  return readBuffer;
}

std::string CurlCpp::get(const std::string &url, const std::map<std::string, std::string> &params)
{
    httpStatus_ = 0;

    std::string readBuffer;
    std::string parameters;

    curl_ = curl_easy_init();

    for(auto itr = params.begin(); itr != params.end(); ++itr) 
        parameters.append(itr->first + "=" + itr->second + "&");

    if(curl_)
    {
        curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, parameters.c_str());

        curlCode_ = curl_easy_perform(curl_);

        unsigned int http_code = 0;
        if(curlCode_ != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curlCode_));
            return 0;
        }
        // Get the curl response code 
		curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &http_code);
        httpStatus_ = http_code;

        if(int(httpStatus_) == 400)
            std::cerr << "Response <" << httpStatus_ << "> thrown." << std::endl;

        curl_easy_cleanup(curl_);
    }

  return readBuffer;
}

/* POST methods */

std::string CurlCpp::post(const std::string &url, const std::map<std::string, std::string> &params)
{   
    curl_ = curl_easy_init();

    std::string parameters;
    std::string readBuffer;

    for(auto itr = params.begin(); itr != params.end(); ++itr) 
        parameters.append(itr->first + "=" + itr->second);

    // std::cerr << parameters << std::endl;

    if(curl_)
    {
        curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &readBuffer);

        curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, parameters.c_str());
        
        // Make the call
        curlCode_ = curl_easy_perform(curl_);

        if(curlCode_ != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curlCode_));
            return 0;
        }
        // Get the curl response code 
        unsigned int http_code;
		curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &http_code);
        httpStatus_ = http_code;
        curl_easy_cleanup(curl_);
    }

    return readBuffer;
}

std::string CurlCpp::post(const std::string &url, const std::map<std::string, std::string> &params, const std::map<std::string, std::string> &headers_map)
{   
    curl_ = curl_easy_init();

    std::string parameters;
    std::string headers_data;

    struct curl_slist *headers = NULL;

    std::string readBuffer;

    for(auto itr = params.begin(); itr != params.end(); ++itr) 
        parameters.append(itr->first + "=" + itr->second + "&");

    for(auto itr = headers_map.begin(); itr != headers_map.end(); ++itr)
        headers_data.append(itr->first + ": "+itr->second);

    if(curl_)
    {
        // Construct our headers
        headers = curl_slist_append(headers, headers_data.c_str());

        curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers); 
        curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
        
        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, parameters.c_str());
        
        // Make the call
        curlCode_ = curl_easy_perform(curl_);

        if(curlCode_ != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curlCode_));
            return 0;
        }
        curl_slist_free_all(headers);
        // Get the curl response code 
        unsigned int http_code;
		curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &http_code);
        httpStatus_ = http_code;
        curl_easy_cleanup(curl_);
    }

    return readBuffer;
}

std::string CurlCpp::post(const std::string &url, const std::string &data)
{   
    const char * data_char_array = data.c_str(); 

    struct postData data_content;

    curl_ = curl_easy_init();
     
    data_content.readptr = data_char_array;
    data_content.sizeleft = (long)strlen(data_char_array);   

    std::string readBuffer;

    if(curl_)
    {
        curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl_, CURLOPT_POST, 1L);
        curl_easy_setopt(curl_, CURLOPT_READFUNCTION, read_callback);
        curl_easy_setopt(curl_, CURLOPT_READDATA, &data_content);

        bool debug = true;

        /* Allows us to view what's going on/debug if necessary */
        if(debug)
            curl_easy_setopt(curl_, CURLOPT_VERBOSE, 1L);
        
        // Make the call
        curlCode_ = curl_easy_perform(curl_);

        if(curlCode_ != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curlCode_));
            return 0;
        }
        // Get the curl response code 
        unsigned int http_code;
		curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &http_code);
        httpStatus_ = http_code;
        curl_easy_cleanup(curl_);
    }

    return readBuffer;
}

