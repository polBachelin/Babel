/*
** EPITECH PROJECT, 2021
** Database.cpp
** File description:
** Database
*/

#ifndef Database_h
#define Database_h

#include "IDatabase.hpp"
#include <sqlite3.h>
#include <iostream>

class Database : public IDatabase {
    public:
        Database();
        Database(const std::string &filename);
        ~Database();
        int open(const std::string &filename) override;
        int close() override;
        int insert(const std::string &t_name, const std::string &c_name, const std::string &value) override;
        int createTable(const std::string &name, const std::string &columns) override;
        CallBackData_t getInfo(const std::string &t_name, const std::string &c_name) override;
        int update(const std::string &t_name, const std::string &c_name, const std::string &id, const std::string &value) override;
        int deleteId(const std::string &t_name, const std::string &id) ;
        CallBackData_t custom(const std::string &req) override;
    protected:
    private:
        sqlite3 *_db;
        char *_errMsg;
        CallBackData_t _data;
};

#endif /* !Database_h */
