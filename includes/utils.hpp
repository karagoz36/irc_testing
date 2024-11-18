#pragma once

class Logger {
public:
    static void error(const std::string &msg) {
        std::cerr << "[\033[31mERROR\033[0m] " << msg << std::endl;
    }
    static void info(const std::string &msg) {
        std::cout << "[\033[32mINFO\033[0m] " << msg << std::endl;
    }
    static void warning(const std::string &msg) {
        std::cerr << "[\033[33mWARNING\033[0m] " << msg << std::endl;
    }
	static void success(const std::string &msg) {
        std::cout << "[\033[33mSUCCESS\033[0m] " << msg << std::endl;
};
