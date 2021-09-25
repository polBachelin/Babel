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
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    asio::io_context io_context;

    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
      resolver.resolve(argv[1], "daytime");

    tcp::socket socket(io_context);
    asio::connect(socket, endpoints);

    packet_t *tmp;
    tmp->code = 3;
    tmp->magic = 562;
    tmp->data = (void *)"salut";
    tmp->data_size = 6;
    for (;;)
    {
      std::array<char, 128> buf;
      asio::error_code error;

      asio::write(socket, asio::buffer(&tmp, sizeof(tmp)), error);

      if (error == asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw asio::system_error(error); // Some other error.
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}