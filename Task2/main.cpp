#include <iostream>
#include <unistd.h>
#include <memory>
#include <cstring>
#include <fcntl.h>
#include <wait.h>

const std::size_t Buffer_len {1024};

int main(){
    int pipefd[2] {};
    pid_t cpid {};
    if(pipe(pipefd) == -1){
        std::cerr << "pipe" << std::endl;
        exit(EXIT_FAILURE);
    }
    cpid = fork();
    if(cpid == -1){
        std::cerr << "fork" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(cpid == 0){ // child
        close(pipefd[0]);
        const char* msg = "Hi daddy, I'm your child!";
        if(write(pipefd[1], msg, strlen(msg)) == -1) {
            std::cerr << "Couldn't send a message" << std::endl;
            _exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
        _exit(EXIT_SUCCESS);
    }
    else{ // parent
        std::unique_ptr<char[]> buffer = std::make_unique<char[]>(Buffer_len);
        int output_fd = open("Output.txt", O_CREAT | O_WRONLY, 0777);
        if(output_fd == -1){
            wait(NULL);
            std::cerr << "Couldn't create the file Output.txt" << std::endl;
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
        int64_t bytes_received {read(pipefd[0], buffer.get(), Buffer_len)};
        while(bytes_received > 0){
            write(output_fd, static_cast<void*>(buffer.get()), bytes_received);
            write(output_fd, "\n", 1);

            bytes_received = read(pipefd[0], buffer.get(), Buffer_len);
        }
        close(pipefd[0]);
        if(bytes_received == -1){
            close(output_fd);
            wait(NULL);
            std::cerr << "Couldn't write to the file Output.txt" << std::endl;
            exit(EXIT_FAILURE);
        }
        if(write(output_fd, "Hi!", strlen("Hi!")) == -1){
            close(output_fd);
            wait(NULL);
            std::cerr << "Couldn't write to the file Output.txt" << std::endl;
            exit(EXIT_FAILURE);
        }
        close(output_fd);
    }
    exit(EXIT_SUCCESS);
}