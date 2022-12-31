#include "Generation_functions.h"
#include "Exponential_notation.h"

#define char_string_limiter '"'
#define char_begin_set '<'
#define char_end_set '>'



Generation_functions::~Generation_functions() {

    for (const auto& pair : *(this -> sets)) {delete pair.second;} 
    delete this -> sets; delete this -> pattern;
}


void Generation_functions::remove_set(const std::string& name) {this -> sets -> erase(name);}


void Generation_functions::add_set(const std::string& name, const std::string& sets_string) {
    
    std::set<std::string>* set = new std::set<std::string>;
    std::string* set_string = new std::string;
    bool is_begin_quote = false;
    
    for (const char& iter_char : sets_string) {
        
        if (iter_char == char_string_limiter) {
            if (is_begin_quote) {set -> insert(*set_string); set_string -> clear();}
            is_begin_quote = !is_begin_quote;
        }

        else if (is_begin_quote) {*set_string += iter_char;}
    } delete set_string;

    if (!set -> size()) {  
        std::cout << "Actual adding set of name: " << '"' << name << '"' << " is empty!\n";
        return;
    }
    std::map<std::string, std::set<std::string>*>::iterator itr = this -> sets -> find(name);

    if (itr != this -> sets -> end()) { 
        delete itr -> second;
        this -> sets -> erase(name);
    }
    this -> sets -> insert({name, set});
}


void Generation_functions::changing_thread_amount(const std::string& thread_arg) {

    unsigned short int new_thread_amount;
    std::stringstream ss;
    ss << thread_arg;
    ss >> new_thread_amount;

    if (new_thread_amount > thread_concurency) {
        std::cout << "This machine doesn't have that much threads! Choose threads between 1 -> ." << thread_concurency << '\n';
        return;
    }

    else if (new_thread_amount < 1) {
        std::cout << "Count of threads must be between 1 -> " << thread_concurency << '\n';
        return;
    }

    this -> thread_amount = new_thread_amount;
}


void Generation_functions::data_print() {
    
    std::cout << "\nSets added:\n";
    for (const auto& [name, set] : *(this -> sets)) {
        std::cout << name << ": " << '{';
        for (const auto& iter_char : *set) {    
            std::cout << char_string_limiter << iter_char << char_string_limiter;
            if (iter_char != *(set -> rbegin())) {std::cout << ", ";}
            else {std::cout << '}' << "\n";}
        }
    }
    std::cout << "\nPattern added: ";

    if (this -> pattern -> size()) {
        for (const std::string& iter_string : *(this -> pattern)) {
            std::cout << char_begin_set << iter_string << char_end_set << ' ';
        }
        std::cout << "\n";
    }
    else {std::cout << "NULL\n";}
    std::cout << "\nFile path added: " << ((this -> file_path.empty()) ? ("NULL") : (this -> file_path.c_str())) << "\n";

    std::cout << "\nAmount of threads: " << (this -> thread_amount) << "\n";
}


void Generation_functions::pattern_set(const std::string& pattern_arg) {
    
    if (this -> pattern -> size()) {this -> pattern -> clear();}
    std::vector<std::string>::iterator itr = this -> pattern -> begin();
    bool is_begin_quote = false;

    for (const char& iter_char : pattern_arg) {
        switch (iter_char) {
            case char_begin_set: {
                if (is_begin_quote) {
                    std::cout << "Set of name: " << '"' << *(this -> pattern -> end() - 1) << '"' << " hasn't been closed in command!\n";
                    this -> pattern -> clear(); return;
                }
                is_begin_quote = true;
                this -> pattern -> push_back(""); 
                itr = this -> pattern -> end() - 1;
                break;
            }
            case char_end_set: {
                if (!is_begin_quote) {
                    std::cout << '"' << char_begin_set << '"' << " has been missed in adding command!\n";
                    this -> pattern -> clear(); return;
                }
                is_begin_quote = false;
                if (this -> sets -> find(*itr) == this -> sets -> end()) {
                    std::cout << "Set of name " << '"' << *itr << '"' << " doesn't exist!\n";
                    this -> pattern -> clear(); return;
                }
                break;
            }
            default: {if (is_begin_quote) {*itr += iter_char;} break;}
        }
    }
    if (is_begin_quote) {
        std::cout << "Set of name: " << '"' << *(this -> pattern -> end() - 1) << '"' << " hasn't been closed in command!\n";
        this -> pattern -> clear();
    }
    else if (!this -> pattern -> size()) {
        std::cout << "Actual adding pattern is empty!\n";
    }
}


void Generation_functions::add_filepath(std::string& path) {
    
    if (path == "NULL" || path == "null") {this -> file_path.clear(); return;}

    this -> file_path = path;
    if (std::filesystem::exists(this -> file_path)) {
        std::cout << "File path: " << '"' << path << '"' << " exist!\n"; 
        this -> file_path.clear(); return;
    }

    while (*path.rbegin() != this -> path_limiter) {
        if (path.empty()) {std::cout << "Path to file doesn't exist!\n"; return;}
        path.pop_back();
    } path.pop_back();

    std::filesystem::path dir_to_file{path};
    if (!std::filesystem::exists(dir_to_file)) {
        std::cout << "File path: " << '"' << path << '"' << " doesn't exist!\n";
        this -> file_path.clear(); return;
    }
}

void Generation_functions::size() {

    Exponential_notation key_amount;
    for (const std::string& iter_string : *(this -> pattern)) {key_amount *= this -> sets -> find(iter_string) -> second -> size();}
    key_amount.print();
}