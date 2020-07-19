#include "highdb.h"

highdb::highdb():
   encoder_(),
   map_(new ConcurrentHashMap<std::string, site>(1024)) {

}

void highdb::add(pb::Record &&record) {
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