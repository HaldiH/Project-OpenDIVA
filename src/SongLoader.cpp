//
// Created by hugo on 22.02.20.
//

#include "OpenDIVA/SongLoader.hpp"
#include <QDebug>
#include <rapidjson/istreamwrapper.h>

SongLoader::SongLoader(const std::string &songFileLocation) {
    std::ifstream ifs(songFileLocation);
    rapidjson::IStreamWrapper isw(ifs);

    json_document.ParseStream(isw);
}
