#include "curl_util.h"
#include <iostream>
#include <map>
#include <string>
#include <curl/curl.h>

using namespace std;

// g++ -o curl curl_util.cpp main.cpp -lcurl -std=c++11
int main()
{
    string url = "http://fanlingxi.sogou/key=aaaaaa&type=51";

    //map<string, string> headers;
    //headers["Content-type"] = "application/json";
 	string res;
    cout<<"\n----------Case1---------\n";
	CurlCpp* curl = new CurlCpp();
    
	if(curl->get(url, res))
		cout << res << endl;
    
	url = "http://fanlingxi.sogou/";
    res.clear();
	// Construct a map for our JSON params. Much like a Python Dict
    map<string, string> params;
    params["key"] = "aaaaaa";
    params["type"] = "51";
    cout<<"\n----------Case2---------\n";
	if(curl->get(url, res))
		cout << res << endl;
    
    params.clear();
	url = "http://api.aerisapi.com/observations/20015/";
    // Populate the map
    params["client_id"] = "So5KnMdtB8V1R0CvSfS8u";
    params["client_secret"] = "8aGQkpCIjzaVdMWDZJT2iWRmP1KvlSic5kE5lIGq";

    // Construct our [optional] headers map
    map<string, string> headers;
    // Populate the map
    headers["Content-type"] = "application/json";
	res.clear();
    cout<<"\n----------Case3---------\n";
    // Here we call it with no headers
    if(curl->post(url, params, res))
		cout<<res<<endl;
	res.clear();
    cout<<"\n----------Case4---------\n";
    // Optionally (and alternatively), we can add headers.
    if(curl->post(url, params, headers, res))
		cout<<res<<endl;

	delete curl;
	return 0;
}
