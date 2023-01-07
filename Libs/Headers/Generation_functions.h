#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <filesystem>
#include <thread>


const static unsigned short int thread_concurency = std::thread::hardware_concurrency();


class Generation_functions {
    
    protected:

    static const char path_limiter = '/'; // In windows change to '\'!

    std::map<std::string, std::set<std::string>*>* sets = new std::map<std::string, std::set<std::string>*>;

    std::vector<std::string>* pattern = new std::vector<std::string>;

    std::filesystem::path file_path;

    unsigned short int thread_amount = thread_concurency;
    
    public:
    
    ~Generation_functions();

    void add_set(const std::string& name, const std::string& set);

    void changing_thread_amount(const std::string& thread_arg);

    void remove_set(const std::string& name);

    void pattern_set(const std::string& pattern_arg);

    void add_filepath(std::string& path);

    void size();

    void data_print();
};