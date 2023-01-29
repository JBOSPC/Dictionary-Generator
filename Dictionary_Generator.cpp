#include "Libs/Headers/Generation_worker.h"
#include <fstream>
#include <istream>

#define version "23.01.29"
#define author "JBOSPC"


const std::map<const std::string, const unsigned short int> dict_count_of_seps = {
    {"insert", 2}, {"delete", 1}, {"pattern", 1}, {"file", 1}, {"threads", 1}, {"load", 1},
    {"size", 0}, {"data", 0}, {"clear", 0}, {"run", 0}, {"help", 0}, {"exit", 0}
};


void help_print() {
    
    std::cout << "\nDictionary Generator version " << version << " made by " << author << ".\n";
    std::cout << "\nAvailable commands:\n";
    std::cout << "insert <set name> <{" << '"' << "chars" << '"' << ", ...}> - For adding new set.\n";
    std::cout << "delete <set name> - For removing added set.\n";
    std::cout << "pattern <<set name>> - For adding pattern.\n";
    std::cout << "file <path_to_file or NULL> - For adding alternative output. If empty, keys will be printing in standard output - NULL for clear path.\n";
    std::cout << "threads <threads amount> - For changing amount of using threads in key generating.\n";
    std::cout << "load <file_path> - For loading commands directly from file. Also works if passed to argv (./Dictionary_Generator <file_path1> <file_path2>...).\n";
    std::cout << "size - For checking amount of keys which will created on current pattern.\n";
    std::cout << "data - For informations about added data.\n";
    std::cout << "clear - For clearing all data.\n";
    std::cout << "run - For starting key generating.\n";
    std::cout << "exit - For closing program.\n";
    std::cout << "help - For program instructions.\n\n"; 
}


void exec_command(std::vector<std::string>* command, Generation_worker*& generation_worker, bool& end_stm) {
    
    if (command -> at(0) == "insert") {
        generation_worker -> add_set(command -> at(1), command -> at(2));
    }
    else if (command -> at(0) == "delete") {
        generation_worker -> remove_set(command -> at(1));
    }
    else if (command -> at(0) == "data") {
        generation_worker -> data_print();
    }
    else if (command -> at(0) == "pattern") {
        generation_worker -> pattern_set(command -> at(1));
    }
    else if (command -> at(0) == "file") {
        generation_worker -> add_filepath(command -> at(1));
    }
    else if (command -> at(0) == "clear") {
        generation_worker -> ~Generation_worker();
        generation_worker = new Generation_worker;
    }
    else if (command -> at(0) == "size") {
        generation_worker -> size();
    }
    else if (command -> at(0) == "run") {
        generation_worker -> run_worker();
    }
    else if (command -> at(0) == "threads") {
        generation_worker -> changing_thread_amount(command -> at(1));
    }
    else if (command -> at(0) == "help") {help_print();}
    else if (command -> at(0) == "exit") {end_stm = false;}
}


bool input_command_split(std::vector<std::string>*& splitted_command, std::istream& stream, bool from_file) {
    
    if (!from_file) {std::cout << ">> ";}
    if (splitted_command -> size()) {splitted_command -> clear();}
    splitted_command -> push_back("");
    stream >> (splitted_command -> at(0));    
    if (splitted_command -> at(0) == "" && from_file) {return true;}
    for (char& digit : splitted_command -> at(0)) {
        if (digit >= 65 && digit <= 90) {digit += 32;}
    }

    std::map<const std::string, const unsigned short int>::const_iterator itr = dict_count_of_seps.find(splitted_command -> at(0));
    if (itr == dict_count_of_seps.cend()) {
        std::cout << "Unrecognized command: " << '"' << (splitted_command -> at(0)) << '"' << "\n";
        return true;
    } 

    for (unsigned short int iter = 1; iter <= itr -> second; ++iter) {
        splitted_command -> push_back("");
        if (itr -> first == "pattern" && iter == 1 || itr -> first == "insert" && iter == 2) {
            std::getline(stream, splitted_command -> at(iter));
        }
        else {stream >> (splitted_command -> at(iter));}
    } return false;
}


template <typename Type>
void load_from_file(Type file_path, std::vector<std::string>*& command, Generation_worker*& generation_worker, bool& end_stm) {
    
    if (!std::filesystem::exists(file_path)) {
        std::cout << "File " << file_path << " doesn't exist!\n";
        return;
    }
    std::ifstream file_obj(file_path);
    while (!file_obj.eof()) {
        input_command_split(command, file_obj, true);
        exec_command(command, generation_worker, end_stm);
    }
}


int main(int argc, char** argv) {
    
    std::cout << "Welcome to Dictionary Generator of version " << version << " made by " << author << ".\n";
    std::cout << "Specify parameters and start creating your own dictionary for Brute-Force attacks.\n";
    std::cout << "If you don't know how, type help and read the instructions.\n";

    std::vector<std::string>* command = new std::vector<std::string>;
    Generation_worker* generation_worker = new Generation_worker;
    bool end_stm = true;

    for (unsigned int iter = 1; iter < argc; ++iter) {
        load_from_file<char*>(argv[iter], command, generation_worker, end_stm);
    }

    while (end_stm) {
        if (input_command_split(command, std::cin, false)) {continue;}
        else if (command -> at(0) == "load") {
            load_from_file<std::string>(command -> at(1), command, generation_worker, end_stm);
        }
        else {exec_command(command, generation_worker, end_stm);}
    }
    delete command; delete generation_worker; return 0;
}
