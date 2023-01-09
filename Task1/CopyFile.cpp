#include "CopyFile.h"



int CopyFile(const std::string& path, const std::string& new_file_name){
    int input_fd = open(path.data(), O_RDONLY);
    if(input_fd == -1){
        return errno;
    }
    struct stat stat_buf {};
    fstat(input_fd, &stat_buf);
    int output_fd = open(new_file_name.data(), O_WRONLY | O_CREAT, stat_buf.st_mode);
    if(output_fd == -1){
        return errno;
    }
    int64_t bytes_written {};
    do{
        bytes_written = sendfile(output_fd, input_fd, NULL, Buf_size);
    }while(bytes_written > 0);
    if(bytes_written == -1){
        return errno;
    }
    return 1;

}