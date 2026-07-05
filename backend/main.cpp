#include "crow_all.h"
#include "huffman.h"
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

int main() {
  crow::App<crow::CORSHandler> app;

  auto &cors = app.get_middleware<crow::CORSHandler>();
  cors.global()
      .origin("*")
      .methods("POST"_method, "OPTIONS"_method)
      .headers("Content-Type");

  CROW_ROUTE(app, "/comprimir")
      .methods(crow::HTTPMethod::Post)([](const crow::request &req) {
        json body = json::parse(req.body);
        std::string a_comprimir = body["texto"];
        json j;
        j["comprimido"] = comprimir(a_comprimir);
        crow::response res(200, j.dump());
        res.set_header("Content-Type", "application/json");
        return res;
      });

  app.port(8080).multithreaded().run();
}