/*
** EPITECH PROJECT, 2021
** IDatabase.cpp
** File description:
** IDatabase
*/

#ifndef IDatabase_h
#define IDatabase_h

#include <string>
#include <cstring>
#include <deque>

typedef struct CallBackData {
    int ac;
    std::deque<std::string> av;
    std::deque<std::string> c_name;
} CallBackData_t;

class IDatabase {
    public:
        virtual int open(const std::string &filename) = 0;
        virtual int close() = 0;
        virtual int insert(const std::string &t_name, const std::string &c_name, const std::string &value) = 0;
        virtual int createTable(const std::string &name, const std::string &columns) = 0;
        virtual CallBackData_t getInfo(const std::string &t_name, const std::string &c_name) = 0;
        virtual int update(const std::string &t_name, const std::string &c_name, const std::string &id, const std::string &value) = 0;
        virtual int deleteId(const std::string &t_name, const std::string &id) = 0;
        virtual CallBackData_t custom(const std::string &req) = 0;
    protected:
    private:
};

#endif /* !IDatabase_h */
