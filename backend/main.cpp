#include "crow_all.h"
#include "huffman.h"
#include <nlohmann/json.hpp>
#include <string>


using json = nlohmann::json;

int main() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/comprimir")
      .methods(crow::HTTPMethod::Post)([](const crow::request &req) {
        json body = json::parse(req.body);
        std::string a_comprimir = body["texto"];
        json j;
        j["comprimido"] = comprimir(a_comprimir);
        return j.dump();
      });
  app.port(8080).multithreaded().run();
}