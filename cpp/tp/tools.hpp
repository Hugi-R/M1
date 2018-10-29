#ifndef TOOLS_HPP
#define TOOLS_HPP 1
#include <vector>
#include <string>


/* split a string by a delimiter, the delimiter is NOT discarded */
static std::vector<std::string> split ( const std::string& s, char delim ){
    std::vector<std::string> res;
    std::string buff{""};
    for(char c : s){
        if(c == delim){
            res.push_back(buff);
            std::string d;
            d.push_back(delim);
            res.push_back(d);
            buff = "";
        } else {
            buff.push_back(c);
        }
    }
    res.push_back(buff);

    //remove "" from vector
    std::vector<std::string> tmp;
    for(auto s : res){
        if(s != "")
            tmp.push_back(s);
    }
    return tmp;
}

#endif
