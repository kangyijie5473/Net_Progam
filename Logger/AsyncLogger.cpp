//
// Created by kang on 17-11-29.
//

#include <cassert>
#include <iostream>
#include "AsyncLogger.h"
AsyncLogger::AsyncLogger(std::string log_file_name)
        :log_file_name_(log_file_name),
         running_state(false)
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
        if(backup_input_buffer_){
            std::cout << "backup " << std::endl;
            now_input_buffer_ = std::move(backup_input_buffer_);

        }
        else{
            std::cout <<"reset" << std::endl;
            now_input_buffer_.reset(new LogBuffer);

        }
        now_input_buffer_->append(log_message, len);
        cond_.notify_one();

    }

}

void AsyncLogger::appendLogFile()
{



    std::vector<std::unique_ptr<LogBuffer>> write_to_file_buffers;
    std::unique_ptr<LogBuffer> now_output_buffer(new LogBuffer);
//    std::unique_ptr<LogBuffer> backup_output_buffer(new LogBuffer);
        while (running_state){
            {
                std::unique_lock<std::mutex> locker(mutex_);
                assert(now_input_buffer_);

                if(now_input_buffer_->free_size() == LogBuffer::buffer_max_size)
                    cond_.wait_for(locker, std::chrono::seconds(3));
                std::cout << "run" << std::endl;

                dirty_buffers_.push_back(std::move(now_input_buffer_));
                now_input_buffer_ = std::move(now_output_buffer);
                write_to_file_buffers.swap(dirty_buffers_);
//                if(!backup_input_buffer_)
//                    backup_input_buffer_ = std::move(backup_output_buffer);
            }

            for(int i = 0; i < write_to_file_buffers.size(); i++){
                int temp = fwrite(write_to_file_buffers[i]->data(),
                       1,
                       LogBuffer::buffer_max_size - write_to_file_buffers[i]->free_size(),
                       log_file_);

                if(temp == 1)
                    perror("fwrite");
            }
            std::cout << "size is " << write_to_file_buffers.size() << std::endl;
            if(write_to_file_buffers.size() > 1)
                write_to_file_buffers.resize(1);
            if(!now_output_buffer){
                now_output_buffer = std::move(write_to_file_buffers.back());
                now_output_buffer->clear();
            }
//            if(!backup_output_buffer){
//                backup_output_buffer = std::move(write_to_file_buffers.back());
//                backup_output_buffer->clear();
//            }
            write_to_file_buffers.clear();
        }


}

void AsyncLogger::init()
{
    log_file_ = fopen(log_file_name_.c_str(), "a");

    now_input_buffer_.reset(new LogBuffer);
    backup_input_buffer_.reset(new LogBuffer);

}

void AsyncLogger::run()
{
    running_state = true;
    output_thread.reset(new std::thread(std::bind(&AsyncLogger::appendLogFile,this)));
    output_thread->detach();
}