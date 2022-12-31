#include "Generation_worker.h"
#include <fstream>

#define generation_sep "\n"


void Generation_worker::run_worker() {

    for (const std::string& iter_string : *(this -> pattern)) {
        if (this -> sets -> find(iter_string) == this -> sets -> end()) {
            std::cout << "Set of name " << '"' << iter_string << '"' << " has been removed!\n"; 
            return;
        }
    } 

    std::ofstream file;

    if (!this -> file_path.empty()) {    
        std::string path = this -> file_path.c_str();

        if (std::filesystem::exists(this -> file_path)) {
            std::cout << "File path: " << '"' << path << '"' << " exist!\n"; 
            return;
        }
        
        while (*path.rbegin() != this -> path_limiter) {path.pop_back();} path.pop_back();
        std::filesystem::path dir_to_file{path};
        
        if (!std::filesystem::exists(dir_to_file)) {
            std::cout << "File path: " << '"' << path << '"' << " doesn't exist!\n";
            return;
        }

        file.open(this -> file_path);
        if (!file.good()) {
            std::cout << "Error while creating file: " << path << "\n"; 
            return;
        }
        this -> out_stream = &file;
    } else {this -> out_stream = &std::cout;}

    this -> free_threads = this -> thread_amount - 1;
    this -> start_generating("", this -> pattern -> begin(), true);
    if (!this -> file_path.empty()) {file.close();}
}


void Generation_worker::start_generating(std::string perm, std::vector<std::string>::iterator pattern_ptr, const bool first_call) {

    bool last_recursion = (pattern_ptr == this -> pattern -> end() - 1);
    std::map<std::string, std::set<std::string>*>::iterator iter_ptr = this -> sets -> find(*pattern_ptr);
    const std::set<std::string>::const_reverse_iterator last_digit = iter_ptr -> second -> crbegin();
    std::vector<std::thread> thread_obj;

    for (const std::string& iter_char : *iter_ptr -> second) {
        if (last_recursion) {
            this -> mutex.lock();
            *(this -> out_stream) << (perm + iter_char) << generation_sep;
            this -> mutex.unlock(); continue;
        }
        this -> mutex.lock();
        if (this -> free_threads && iter_char != *last_digit) {         
            this -> free_threads -= 1;
            this -> mutex.unlock();   
            thread_obj.push_back(
                std::thread([this, &perm, &pattern_ptr, &iter_char]() -> void {
                    this -> start_generating(perm + iter_char, pattern_ptr + 1, true);
                })
            );
        }
        else {
            this -> mutex.unlock();
            this -> start_generating(perm + iter_char, pattern_ptr + 1, false);
        }
    }

    for (std::thread& t_obj : thread_obj) {t_obj.join();}
    
    if (first_call) {
        std::lock_guard<std::mutex> lock(this -> mutex);
        this -> free_threads += 1;
    }
}