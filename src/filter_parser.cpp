#include "filter_parser.h"
#include <sstream>

using namespace std;

void parse_filter_arg(const std::string& arg, std::string& filter_name, Params& params){
    size_t pos = arg.find(':');
    if(pos == string::npos){
        filter_name = arg;
        return;
    }
    filter_name = arg.substr(0, pos);
    string param_name = arg.substr(pos+1);
    stringstream ss(param_name);
    string it;
    while(getline(ss, it, ',')){
        size_t e_pos = it.find('=');
        if(e_pos != string::npos){
            string key = it.substr(0, e_pos);
            string value = it.substr(e_pos + 1);
            params[key] = value;
        }
    }
}