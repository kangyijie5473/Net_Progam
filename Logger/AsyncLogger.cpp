//
// Created by kang on 17-11-23.
//

#include "AsyncLogger.h"
AsyncLogger::AsyncLogger(std::string log_file_name = "DefaultLog"):log_file_name_(log_file_name), running_state(false), output_thread(std::bind(&AsyncLogger::appendLogFile,this))
{
    init();
}

//AsyncLogger::AsyncLogger()
//{
//    init();
//}
void AsyncLogger::append(const char *src, int len)
{
    std::lock_guard<std::mutex> locker(mutex_);

    if(now_input_buffer_->free_size() > len)
        now_input_buffer_->append(src, len);
    else{
        dirty_buffers_.push(std::move(now_input_buffer_));
        if(!now_output_buffer_->free_size()){
            now_input_buffer_ = std::move(now_output_buffer_);
            now_output_buffer_ = std::move(dirty_buffers_.front());
        }else{
            now_input_buffer_.reset(new LogBuffer());
            now_input_buffer_->append(src, len);
        }

    }
}
void AsyncLogger::appendLogFile()
{
    while (running_state){
        if(now_output_buffer_->free_size() != LogBuffer::buffer_max_size){
            fwrite(now_output_buffer_->data(), 1, LogBuffer::buffer_max_size - now_output_buffer_->free_size(),log_file_);
            now_output_buffer_->clear();
        }

    }

}
void AsyncLogger::init()
{
    now_input_buffer_.reset(new LogBuffer());
    now_output_buffer_.reset(new LogBuffer());
    log_file_ = fopen(log_file_name_.c_str(), "a");
    //if(log_file_) todo:exception

}