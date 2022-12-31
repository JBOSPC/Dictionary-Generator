#include "Generation_functions.h"
#include <ostream>
#include <thread>
#include <mutex>

class Generation_worker: public Generation_functions {
    
    protected:

    std::mutex mutex;

    std::ostream* out_stream;

    uint16_t free_threads;
    
    void start_generating(std::string perm, 
    std::vector<std::string>::iterator pattern_ptr, const bool first_call);

    public:

    void run_worker();
};