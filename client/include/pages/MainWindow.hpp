/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** Mainwindow
*/

#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QtWidgets>
#include <memory>

namespace Client {
namespace GUI {

class MainWindow : public QMainWindow
{
    public:
        MainWindow();

    private:
        std::unique_ptr<QWidget> mainContainer;
};

}
}

#endif /* !MAINWINDOW_HPP_ */
