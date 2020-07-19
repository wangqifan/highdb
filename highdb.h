#ifndef HIGH_DB
#define HIGH_DB


#include "encoder.h"
#include "record.pb.h"
#include "ConcurrentHashMap.h"
#include "site.h"
#include <string>

class highdb
{
private:
    encoder encoder_;
    std::shared_ptr<ConcurrentHashMap<std::string, site>> map_;
public:
    highdb(/* args */);
    void add(pb::Record &&record);
    std::string get(std::string &key);
};

#endif