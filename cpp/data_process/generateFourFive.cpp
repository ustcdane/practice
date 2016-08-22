#include <fstream>
#include <iostream>
#include <sstream>

#include "cppUtils/StringUtil.hpp"
#include "cppUtils/ThreadPool.hpp"
#include "cppUtils/ListDir.hpp"

using namespace std;
using namespace cppUtils;

// 这两个阈值在这里不起作用,故设置的比较大.数据预处理阶段已进行相应的阈值处理
const int threshold_four_gram = 1734;// 1534
const int threshold_five_gram = 1718;// 1518
int n_gram = -1;

std::unordered_map<string, int> hz_id_map;

// for ThreadPool
class Task: public ITask {
	public:
		Task(const string& str_file, const string& str_in, const string& str_out): str_file(str_file), str_dir_in(str_in),str_dir_out(str_out) {
		}
		virtual void run() {
			string str_file_name(str_dir_in+"/"+str_file);
			ifstream f_in(str_file_name.c_str());
			if (!f_in) {
				fprintf(stderr, "open file %s failed!\n", str_file_name.c_str());
				return ;
			}
			fprintf(stdout, "open file %s success!\n", str_file_name.c_str());
			
			size_t pos = str_file.find('.'); // 1.txt 2.txt -> 1.out 2.out
			if( string::npos == pos)
				return ;
			string output(str_dir_out +"/"+ str_file.substr(0, pos) + ".out");
			ofstream f_out(output.c_str());
			if (!f_out) {
				fprintf(stderr, "Write file %s failed!\n", output.c_str());
			}
			fprintf(stdout, "open file %s success!\n", output.c_str());
			
			int freq = 0;
			size_t i;
			size_t want_total = 0;
			size_t gram_cnt = 0;
			string line;
			vector<int> vec_ids;
			vector<string> buf;
			vector<string> res;
			res.resize(10001);

			for (; getline(f_in, line);) {
				buf.clear();
				vec_ids.clear();
				split(line, buf, "\t");
				if (buf.size() != 2)
					continue;
				freq = atoi(buf[1].c_str());
				string str(buf[0]);
				buf.clear();
				split(str, buf, ":");
				if(buf.size() != n_gram) {
					fprintf(stderr, "file %s line: %d error!\n", str_file.c_str(), want_total+1);
					continue;
				}
				++want_total;
				if(n_gram == 4) { // four gram threshold
					if ( freq >threshold_four_gram ) 
						continue;
				}
				if(n_gram == 5) { // five gram threshold
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
		}// getline
		for (i = 0; i < gram_cnt; ++i)
			f_out << res[i] << endl;
	}// run

	private:
		string str_file;
		string str_dir_in;
		string str_dir_out;
};


int main(int argc, char *argv[])
{
	if (argc != 5) {
		fprintf(stderr, "argv not have 5 parmas\n");
		fprintf(stderr, "Use: unigram.txt\tinputPath\toutputPath\tgram_n([2~5])\n");
		return 1;
	}
	
	n_gram = atoi(argv[4]);
	if(n_gram <2 || n_gram >5) {
		fprintf(stderr, "gram_n %s error!\n", argv[2]);
		return 1;
	}
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
	
	// ThreadPool
	const size_t threadNum = 30;
	const size_t taskLimit = 60;
	
	vector<string> file_vector;
	ThreadPool threadPool(threadNum, taskLimit);
	threadPool.start();
	if(list_dir_name(argv[2], file_vector) == -1) {
		fprintf(stderr, "list input dir error!!!\n");
		return 1;
	}
	for( size_t i=0; i < file_vector.size(); ++i) {
		threadPool.add(CreateTask<Task, const string&, const string&, const string& >(file_vector[i], argv[2], argv[3]));
	}
	return 0;
}
