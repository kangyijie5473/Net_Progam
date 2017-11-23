//
// Created by kang on 17-11-23.
//

#ifndef LOGGER_ASYNCLOGGER_H
#define LOGGER_ASYNCLOGGER_H

#include "LogBuffer.h"
#include <memory>
#include <thread>

class AsyncLogger {
public:
    AsyncLogger();
    AsyncLogger(std::string log_file_name):log_file_name_(log_file_name){};
    void append(const char *, int);
private:
    void init();

    std::unique_ptr<LogBuffer> now_input_buffer_;
    std::unique_ptr<LogBuffer> now_output_buffer_;
    std::queue<std::unique_ptr<LogBuffer>> dirty_buffers_;
    std::thread output_thread;

    std::string log_file_name_;
    std::mutex mutex_;
};


#endif //LOGGER_ASYNCLOGGER_H
