#include <iostream>
#include <string>
#include <iomanip>

struct Options {
    struct Credentials {
    std::string user;
    std::string password;
  };
  struct SSL {
    std::string ssl_path;
    std::string ssl_client_certificate;
    std::string ssl_client_private_key;
    std::string ssl_client_password;
    std::string ssl_broker_certificate;
  };

  Credentials credentials;
  SSL ssl;
  bool reconnect = true;
  bool auto_connect = true;
};

std::ostream& operator<<(
  std::ostream& out,
  const Options::SSL& opts
){
  out << "SSL options: {";
  if (!opts.ssl_path.empty()) {
    out << "\n";
    out << "ssl_path" << opts.ssl_path;
    out << "ssl_client_certificate" << opts.ssl_client_certificate;
    out << "ssl_client_private_key" << opts.ssl_client_private_key;
    out << "ssl_client_password" << opts.ssl_client_password;
    out << "ssl_broker_certificate" << opts.ssl_broker_certificate;
    out << "\n";
  }
  out << "\n}";
  return out;
}
std::ostream& operator<<(
  std::ostream& out,
  const Options::Credentials& opts
) {
  out << "Credentials: {";
  if (!opts.user.empty()) {
    out << "\n";
    out << "user: " << opts.user;
    out << "password: " << opts.password;
    out << "\n";
  }

  out << "\n}";
  return out;
}
std::ostream& operator<<(std::ostream& out, const Options& opts) {
  out << "Connection Options: {\n";
  out << "reconnect: " << std::boolalpha << opts.reconnect << "\n";
  out << "auto_connect: " << std::boolalpha << opts.auto_connect << "\n";

  out << std::setfill(' ') << std::setw(50) << std::right << opts.ssl;
  out << opts.credentials;

  out << "\n}";
  return out;
}

//-------------------------------------------------------------------------------
int main() {
  auto ms = 5;
  std::cout << std::setw(3) << std::setfill('0') << ms << "\n";

  Options opts {
    {"user", "password"},
    {"ssl_path",
     "ssl_client_certificate",
     "ssl_client_private_key",
     "ssl_client_password",
     "ssl_broker_certificate"}, true, false};

  std::cout << opts;

  return 0;
}
