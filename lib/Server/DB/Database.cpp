/*
** EPITECH PROJECT, 2021
** Database.cpp
** File description:
** Database
*/

#include "Database.hpp"

static int verify(void *unused, int argc, char **argv, char **columnName)
{
    (void)unused;
    for (int i = 0; i < argc; i++) {
        std::cout << columnName[i] << " = " <<  (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    return 0;
}

int callForSelect(void *data, int argc, char **argv, char **columnName)
{
    CallBackData_t *tmp = (CallBackData_t *)data;

    for (int i = 0; i < argc; i++) {
        tmp->ac++;
        tmp->av.push_back(argv[i] ? argv[i] : "NULL");
        tmp->c_name.push_back(columnName[i]);
    }
    return 0;
}


Database::Database() : _db(nullptr), _errMsg(nullptr)
{
    _data.ac = 0;
}

Database::Database(const std::string &f) : _db(nullptr), _errMsg(nullptr)
{
    this->open(f);
}


Database::~Database()
{
}

int Database::open(const std::string &filename)
{
    int tmp = sqlite3_open(filename.c_str(), &_db);

    if (tmp) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(_db) <<  std::endl;
        return tmp;
    }
    std::cout << "Database " << filename << " opened successfully" << std::endl;
    return tmp;
}

int Database::close()
{
    return sqlite3_close(_db);
}

int Database::insert(const std::string &t_name, const std::string &c_name, const std::string &value)
{
    std::string req = "INSERT INTO " + t_name + "(" + c_name + ") VALUES (" + value + ");";
    int tmp = sqlite3_exec(_db, req.c_str(), verify, nullptr, &_errMsg);

    if (tmp != SQLITE_OK) {
        std::cerr << "SQL ERROR: " << _errMsg <<  std::endl;
        sqlite3_free(_errMsg);
        return tmp;
    }
    std::cout << "Database insert successful" << std::endl;
    return tmp;
}

int Database::createTable(const std::string &name, const std::string &columns)
{
    std::string req = "CREATE TABLE " + name + "(" + columns + ");";
    int tmp = sqlite3_exec(_db, req.c_str(), verify, nullptr, &_errMsg);

    if (tmp != SQLITE_OK) {
        std::cerr << "SQL CREATE DB ERROR " << name << std::endl;
        std::cerr << "SQL ERROR: " << _errMsg <<  std::endl;
        sqlite3_free(_errMsg);
        return tmp;
    }
    std::cout << "Database table created" << std::endl;
    return tmp;
}

CallBackData_t Database::getInfo(const std::string &t_name, const std::string &c_name)
{
    CallBackData_t data;
    data.ac = 0;
    std::string req = "SELECT " + c_name + " FROM " + t_name + ";";
    int tmp = sqlite3_exec(_db, req.c_str(), callForSelect, &data, &_errMsg);

    if (tmp != SQLITE_OK) {
        std::cerr << "SQL ERROR: " << _errMsg <<  std::endl;
        sqlite3_free(_errMsg);
        return _data;
    }
    _data = data;
    std::cout << "Select succeed" << std::endl;
    return _data;
}

int Database::update(const std::string &t_name, const std::string &c_name, const std::string &id, const std::string &value)
{
    std::string req = "UPDATE " + t_name + " set " + c_name + " = " + value + " where ID=" + id + ";";
    int tmp = sqlite3_exec(_db, req.c_str(), verify, nullptr, &_errMsg);

    if (tmp != SQLITE_OK) {
        std::cerr << "SQL ERROR: " << _errMsg <<  std::endl;
        sqlite3_free(_errMsg);
        return tmp;
    }
    std::cout << "Update succeed" << std::endl;
    return tmp;
}

int Database::deleteId(const std::string &t_name, const std::string &id)
{
    std::string req = "DELETE from " + t_name + " where ID=" + id + ";";
    int tmp = sqlite3_exec(_db, req.c_str(), verify, nullptr, &_errMsg);

    if (tmp != SQLITE_OK) {
        std::cerr << "SQL ERROR: " << _errMsg <<  std::endl;
        sqlite3_free(_errMsg);
        return tmp;
    }
    std::cout << "Delete succeed" << std::endl;
    return tmp;
}

CallBackData_t Database::custom(const std::string &req)
{
    CallBackData_t data;
    data.ac = 0;
    int tmp = sqlite3_exec(_db, req.c_str(), callForSelect, &data, &_errMsg);

    if (tmp != SQLITE_OK) {
        std::cerr << "SQL ERROR: " << _errMsg <<  std::endl;
        sqlite3_free(_errMsg);
        return _data;
    }
    _data.ac = data.ac;
    _data.av = data.av;
    _data.c_name = data.c_name;
    // std::cout << "Custom request succeed" << std::endl;
    return _data;
}
