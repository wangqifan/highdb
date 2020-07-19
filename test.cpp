#include <iostream>
#include <fstream>
#include <string>

#include "highdb.h"
#include "record.pb.h"

/*
bool is_write(std::string &key, std::string &value, std::ofstream &outfile) {
    pb::Record record;
    record.set_key(key);
    record.set_value(value);
    record.set_type(1);
    std::string str = record.SerializeAsString();
    std::cout << str << " " << str.size() << std::endl;
    int len = str.size();
    outfile.write((char*)&len, sizeof(int));
    
    return record.SerializePartialToOstream(&outfile);
}
  std::ofstream outfile;

    outfile.open("file.dat", std::ios::out | std::ios::binary | std::ios::app);
   for(int i = 0; i < 2; i++) {
       std::string key;
       std::string value;
       std::cin >> key >> value;
       is_write(key, value, outfile);
   }
   outfile.close();
 
   std::ifstream inFile("file.dat", std::ios::in | std::ios::binary);
   int len;
   while(inFile.read((char*)&len, sizeof(int))) {
       std::cout << "---"  << len << std::endl;
       char buffer[len];
       inFile.read(buffer, sizeof(char) * len);
       pb::Record record;
       record.ParseFromArray(buffer, len);
       std::cout << record.key() << " " << record.value() << std::endl;
   }
*/
int main() {
  
   highdb highdb_;
   for(int i = 0; i < 10000; i++) {
       pb::Record record;

       record.set_key(std::to_string(i));
       record.set_value("value" + std::to_string(i));
       record.set_type(1);
       std::cout << record.key() << " " << record.value() << std::endl;
       highdb_.add(std::move(record));
       std::string key = std::to_string(i);
       std::string value = highdb_.get(key);
       std::cout << "key: " << key <<" value: " <<value << std::endl;
   }
   return 0;
}