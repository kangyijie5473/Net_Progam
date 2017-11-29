//
// Created by kang on 17-11-29.
//

#include <cassert>
#include "AsyncLogger.h"
AsyncLogger::AsyncLogger(std::string log_file_name)
        :log_file_name_(log_file_name),
         running_state(false),
         thread_start_flag_(false),
         output_thread(std::bind(&AsyncLogger::appendLogFile,this))
{
    init();
}

void AsyncLogger::append(const char *log_message, int len)
{
    std::lock_guard<std::mutex> locker(mutex_);
    assert(now_input_buffer_);
    if(now_input_buffer_->free_size() > len){
        now_input_buffer_->append(log_message, len);
    }else{
        dirty_buffers_.push_back(std::move(now_input_buffer_));
        if(backup_input_buffer_)
            now_input_buffer_ = std::move(backup_input_buffer_);
        else
            now_input_buffer_.reset(new LogBuffer);
        now_input_buffer_->append(log_message, len);
    }

    cond_.notify_one();
}

void AsyncLogger::appendLogFile()
{
    // todo : thread start
    std::vector<std::unique_ptr<LogBuffer>> write_to_file_buffers;
    std::unique_ptr<LogBuffer> now_output_buffer(new LogBuffer);
    std::unique_ptr<LogBuffer> backup_output_buffer(new LogBuffer);
        if(running_state){
            {
                std::unique_lock<std::mutex> locker(mutex_);
                assert(now_input_buffer_);
                if(now_input_buffer_->free_size() == LogBuffer::buffer_max_size)
                    cond_.wait_for(locker, std::chrono::seconds(3));
                dirty_buffers_.push_back(std::move(now_input_buffer_));
                now_input_buffer_ = std::move(now_output_buffer);
                write_to_file_buffers.swap(dirty_buffers_);
                if(!backup_input_buffer_)
                    backup_input_buffer_ = std::move(backup_output_buffer);
            }

            for(int i = 0; i < write_to_file_buffers.size(); i++){
                fwrite(write_to_file_buffers[i]->data(),
                       1,
                       LogBuffer::buffer_max_size - write_to_file_buffers[i]->free_size(),
                       log_file_);

            }

            if(write_to_file_buffers.size() > 2)
                write_to_file_buffers.resize(2);
            if(!now_output_buffer){
                now_output_buffer = std::move(write_to_file_buffers.back());
                now_output_buffer->clear();
            }
            if(!backup_output_buffer){
                backup_output_buffer = std::move(write_to_file_buffers.back());
                backup_output_buffer->clear();
            }
            write_to_file_buffers.clear();
        }


}

void AsyncLogger::init()
{
    log_file_ = fopen(log_file_name_.c_str(), "a");
//    perror("fopen");
//    assert(log_file_);
    now_input_buffer_.reset(new LogBuffer);
    backup_input_buffer_.reset(new LogBuffer);
    output_thread.detach();
}