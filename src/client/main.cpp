/*
** EPITECH PROJECT, 2021
** babel
** File description:
** main
*/

#include "TcpServer.hpp"

using asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
  {
    asio::io_context io_context;

    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
      resolver.resolve("127.0.0.1", "5000");

    tcp::socket socket(io_context);
    asio::connect(socket, endpoints);

    packet_t orig;
    packet_t *tmp = &orig;
    tmp->magic = 562;
    tmp->code = 3;
    tmp->data_size = 256;
    strcpy(tmp->data, "salut");
    asio::error_code error;
    std::size_t size = asio::write(socket, asio::buffer(tmp, sizeof(packet_t)), error);
    std::cout << "message sent " << size << "  " << sizeof(packet_t) << std::endl;
    sleep(60);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}