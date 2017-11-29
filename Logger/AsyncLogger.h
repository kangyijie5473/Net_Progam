//
// Created by kang on 17-11-29.
//

#ifndef LOGGER_ASYNCLOGGER_H
#define LOGGER_ASYNCLOGGER_H


#include "LogBuffer.h"
#include <memory>
#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>

class AsyncLogger {
public:
    AsyncLogger(std::string log_file_name);
    void append(const char *, int);
    void run(){ running_state = true;}
private:
    void init();
    void appendLogFile();

    std::unique_ptr<LogBuffer> now_input_buffer_;
    std::unique_ptr<LogBuffer> backup_input_buffer_;
    std::vector<std::unique_ptr<LogBuffer>> dirty_buffers_;
    std::vector<std::unique_ptr<LogBuffer>> clean_buffers_;
    std::thread output_thread;

    std::string log_file_name_;
    FILE *log_file_;
    std::mutex mutex_;
    std::condition_variable_any cond_;

    std::atomic_bool running_state;
    bool thread_start_flag_;
};



#endif //LOGGER_ASYNCLOGGER_H
