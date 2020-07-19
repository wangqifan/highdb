#ifndef ENCODER
#define ENCODER


#include <string>
#include <fstream>
#include <mutex>

#include "record.pb.h"
#include "site.h"

class encoder
{
private:
    int current_file;
    const std::string filepack = "data/";
    const int long maxsize = 1024;
    std::ofstream outfile;
    std::mutex mutex_;
public:
    encoder(/* args */);
    int getFileCout();
    void write_record(pb::Record &&record, site &site_);
    pb::Record get_record(site &&site_);
};


#endif