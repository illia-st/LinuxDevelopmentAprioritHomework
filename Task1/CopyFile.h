#pragma once

#include <string>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <csignal>

const std::size_t Buf_size = 4096*1000;

int CopyFile(const std::string& path, const std::string& new_file_name);