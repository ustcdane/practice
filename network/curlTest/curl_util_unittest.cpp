#include <iostream>
#include <map>
#include <string>
#include "curl_util.h"
// pls include gtest

class CurlCppTest : public ServiceHandlerTestBase
{
public:
	virtual void SetUp() override
	{
		 curlCpp = new CurlCpp();
	}

	virtual void TearDown() override
	{
		delete curlCpp;
	}

protected:
	CurlCpp* curlCpp = nullptr;
};
// get 1
TEST_F(CurlCppTest, Case1)
{
	using namespace std;
	string url = "http://fanlingxi.sogou/key=aaaaa&type=51";
	map<string, string> params;
	std::string res;
	ASSERT_TRUE(curlCpp->get(url,res));
	ASSERT_EQ(curlCpp->HttpStatus(), 200);
	cout << res << endl;
	cout << curlCpp->HttpStatus() << endl;
}

// get 2
TEST_F(CurlCppTest, Case2)
{
	using namespace std;
	string url = "http://fanlingxi.sogou/";
	map<string, string> params;
	params["key"] = "aaaaa";
	params["type"] = "51";
	string res;
	ASSERT_TRUE(curlCpp->get(url,res));
	ASSERT_EQ(curlCpp->HttpStatus(), 200);
	//cout << res << endl;
	//cout << curlCpp->HttpStatus() << endl;
}

// post 1
TEST_F(CurlCppTest, Case3)
{
	using namespace std;

	string url = "http://fanlingxi.sogou/";
	map<string, string> params;
	params["key"] = "aaaaa";
	params["type"] = "51";
	string res;
	ASSERT_TRUE(curlCpp->post(url, params, res));
	ASSERT_EQ(curlCpp->HttpStatus(), 200);
	//cout << res << endl;
	//cout << curlCpp->HttpStatus() << endl;
}
// post 2
TEST_F(CurlCppTest, Case4)
{
	using namespace std;

	string url = "http://fanlingxi.sogou/";
	map<string, string> params;
	map<string, string> headers;
	params["key"] = "aaaaa";
	params["type"] = "51";
	headers["Content-type"] = "application/json";
	string res;
	ASSERT_TRUE(curlCpp->post(url, params, headers, res));
	ASSERT_EQ(curlCpp->HttpStatus(), 200);
	//cout << response << endl;
	//cout << curlCpp->HttpStatus() << endl;
}
