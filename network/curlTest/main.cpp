#include "curl_util.h"
#include <iostream>
#include <map>
#include <string>
#include <curl/curl.h>

using namespace std;

// g++ -o curl curl_util.cpp main.cpp -lcurl -std=c++11
int main()
{
    string url = "http://fanlingxi.sogou/";

    // Construct a map for our JSON params. Much like a Python Dict
    map<string, string> params;
    params["key"] = "aaaaaa";
    params["type"] = "51";

    //map<string, string> headers;
    //headers["Content-type"] = "application/json";
 

    CurlCpp* curl = new CurlCpp();
    string response = curl->get(url, params);
    cout << response << endl;

    url = "http://api.aerisapi.com/observations/20015/";

    params.clear();
    // Populate the map
    params["client_id"] = "So5KnMdtB8V1R0CvSfS8u";
    params["client_secret"] = "8aGQkpCIjzaVdMWDZJT2iWRmP1KvlSic5kE5lIGq";

    // Construct our [optional] headers map
    map<string, string> headers;
    // Populate the map
    headers["Content-type"] = "application/json";
    // Here we call it with no headers
    response = curl->post(url, params);
    // Optionally (and alternatively), we can add headers.
    response = curl->post(url, params, headers);
	return 0;
}
