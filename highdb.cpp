#include<vector>
#include <msgpack.hpp>
#include "highdb.h"

highdb::highdb(std::string filepack_):
   filepack(filepack_),
   encoder_(filepack_),
   map_(new ConcurrentHashMap<std::string, site>(1024)) {

}

void highdb::add(std::string &key, std::string &&value) {
    pb::Record record;
    record.set_key(key);
    record.set_value(std::move(value));
    record.set_type(1);
    site s;
    encoder_.write_record(std::move(record), s);
    map_-> put(record.key(), std::move(s));
}

std::string highdb::get(std::string &key) {
    site site_;
    map_ -> for_one(key, site_);
    pb::Record record = encoder_.get_record(std::move(site_));
    return record.value();
}
void highdb::close() {
    close_ = true;
    encoder_.close();
}
// 合并
void highdb::merge() {
    highdb mergedb(filepack + "/tmp");
    int len = map_ -> table_length();
    int current = encoder_.get_current();
    for(int i = 0; i< len; i++) {
        std::vector<std::string> keys = map_ -> getkeys(i);
        for(int j = 0; j < keys.size(); j++) {
           site s;
           map_ -> for_one(keys[j], s);
           if(s.file < current) {
              std::string value = this -> get(keys[i]);
              mergedb.add(keys[i], std::move(value));
           } 
        }
    }
    msgpack::sbuffer  sbuf;
    msgpack::packer<msgpack::sbuffer>   pker(&sbuf); 
    pker.pack(map_);
    
}