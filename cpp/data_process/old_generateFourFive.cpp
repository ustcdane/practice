#include <fstream>
#include <iostream>
#include <sstream>
#include "StringUtil.hpp"
using namespace std;
using namespace wd;

const int threshold_four_gram = 1534;
const int threshold_five_gram = 1518;

int main(int argc, char *argv[])
{
	if (argc != 4) {
		fprintf(stderr, "argv not have 4 parmas\n");
		return 1;
	}

	std::unordered_map<string, int> hz_id_map;
	ifstream f_unigram(argv[1]);
	if (!f_unigram) {
		fprintf(stderr, "open file %s failed!\n", argv[1]);
		return 1;
	}
	size_t unigram_line_cnt = 0;
	
	string line;
	vector<string> buf;
	getline(f_unigram, line);
	stringstream str_stream(line);
	int unigram_total;
	str_stream >> unigram_total;
	cout << "unigram count:\t" << unigram_total << endl;
	for (; getline(f_unigram, line); ++unigram_line_cnt) {
		buf.clear();
		split(line, buf, "\t");
		//cout << line <<"\t"<<buf.size()<<endl;
		if (buf.size() != 6)
			continue;
		hz_id_map[buf[1]] = atoi(buf[0].c_str());
	}
	//std::unordered_map<string, int>::iterator it = hz_id_map.begin();
	//for (; it != hz_id_map.end(); it++) {
	//	cout << it->first << '\t' << it->second << endl;
	//}

	ifstream f_want(argv[2]);
	if (!f_want) {
		fprintf(stderr, "open file %s failed!\n", argv[2]);
		return 1;
	}
	
	ofstream f_out(argv[3]);
	if (!f_out) {
		fprintf(stderr, "Write file %s failed!\n", argv[3]);
	}

	size_t want_total = 0;
	size_t gram_cnt = 0;
	vector<int> vec_ids;
	int freq = 0;
	size_t i;
	vector<string> res;
	res.resize(10001);
	for (; getline(f_want, line); ++want_total) {
		buf.clear();
		vec_ids.clear();
		split(line, buf, "\t");
		if (buf.size() != 2)
			continue;
		freq = atoi(buf[1].c_str());
		string str(buf[0]);
		buf.clear();
		split(str, buf, ":");
		if(buf.size() == 4) { // four gram threshold
			if ( freq >threshold_four_gram ) 
				continue;
		}
		if(buf.size() == 5) { // five gram threshold
			if ( freq >threshold_five_gram ) 
				continue;
		}
		//cout << buf.size() << "\t" << buf[0] << endl;
		for (i = 0; i < buf.size(); ++i) {
			if (hz_id_map.find(buf[i]) != hz_id_map.end()) { // has hz->id
				vec_ids.push_back(hz_id_map[buf[i]]);
			}
			else
				break;
		}
		if (0 != i && buf.size() != 0 && i == buf.size()) {
			str.clear();
			join(vec_ids.begin(), vec_ids.end(), str, "\t");
			//cout << str << "\t" << freq << endl;
			//f_out << str << "\t"<< freq << endl;
			str += string("\t");
			stringstream ss;
			ss << freq;
			str += ss.str();// freq
			res[gram_cnt++] = str;
			if (gram_cnt == 10000) {
				for (i=0; i< gram_cnt; ++i)
					f_out << res[i] << endl;
				gram_cnt = 0;
			}
		}
	}// for getline
	cout<< gram_cnt << endl;
	for (i=0; i< gram_cnt; ++i)
		f_out << res[i] << endl;

	return 0;
}
