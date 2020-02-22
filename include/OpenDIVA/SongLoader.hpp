//
// Created by hugo on 22.02.20.
//

#ifndef OPENDIVA_SONGLOADER_HPP
#define OPENDIVA_SONGLOADER_HPP

#include <fstream>
#include <rapidjson/document.h>

class SongLoader {
  public:
    explicit SongLoader(const std::string &songFileLocation);

  private:
    rapidjson::Document json_document;
};

#endif // OPENDIVA_SONGLOADER_HPP
