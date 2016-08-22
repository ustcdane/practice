#include <vector>
#include <string>
#include "cppUtils/ListDir.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc != 2)
    {
        printf("please type directory name.\n");
        return -1;
    }

    printf("%s\n", argv[1]);
	std::vector<std::string> res;
    list_dir_name(argv[1], res);
	string str_name(argv[1]);
	size_t pos = str_name.find('\\');
	for( size_t i=0; i < res.size(); ++i) {
		printf("%d\t%s\n", i, res[i].c_str());
		int pos = res[i].find('.');
		if(std::string::npos == pos) {
			printf("error!!\n");
			//return 1;
		}else {
			printf("%s\t%s\n", res[i].c_str(), res[i].substr(0,pos).c_str());
		}
	}

    return 0;
}

