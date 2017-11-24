//
// Created by kang on 17-11-23.
//

#ifndef LOGGER_ASYNCLOGGER_H
#define LOGGER_ASYNCLOGGER_H

#include "LogBuffer.h"
#include <memory>
#include <thread>
#include <queue>
#include <mutex>
#include <atomic>

class AsyncLogger {
public:
    //AsyncLogger();
    AsyncLogger(std::string log_file_name);
    void append(const char *, int);
    void run(){ running_state = true;}
private:
    void init();
    void appendLogFile();

    std::unique_ptr<LogBuffer> now_input_buffer_;
    std::unique_ptr<LogBuffer> now_output_buffer_;
    std::queue<std::unique_ptr<LogBuffer>> dirty_buffers_;
    std::thread output_thread;

    std::string log_file_name_;
    FILE *log_file_;
    std::mutex mutex_;
    std::atomic_bool running_state;
};


#endif //LOGGER_ASYNCLOGGER_H
