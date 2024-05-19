#include <iostream>
#include "WorldTimeApi.h"

using namespace std::string_literals;

WorldTime::WorldTime(std::string timeZone) {
	curl_global_init(CURL_GLOBAL_DEFAULT);

    curl_ = curl_easy_init();
    if (curl_ == nullptr) {
        return;
    }
    setTimeZone(timeZone);
}

void WorldTime::setTimeZone(std::string timeZone) {
    if (curl_ == nullptr) {
        return;
    }
    clear();
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &buffer_);
    std::string url = "http://worldtimeapi.org/api/timezone/" + timeZone;
    curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
}

SWorldTimeRow WorldTime::getWorldTimeRow() {
    getCurlResult();
    return item_;
}

std::string WorldTime::getBuffer(){
    getCurlResult();
    return buffer_;
}

void WorldTime::clear() {
    buffer_.clear();
    item_ = SWorldTimeRow{};
}

WorldTime::~WorldTime() {
    if (curl_ != nullptr) {
        curl_easy_cleanup(curl_);
    }
    curl_global_cleanup();
    curl_ = nullptr;
}

void WorldTime::getCurlResult() {
    if (item_.filled) {
        return;
    }
    if (curl_ == nullptr) {
        throwException("curl was not initialized");
    }
    
    CURLcode res;

    res = curl_easy_perform(curl_);
    if (res != CURLE_OK) {
        throwException(("curl_easy_perform() failed: "s + curl_easy_strerror(res)).c_str());
    }

    Json::CharReaderBuilder builder;
    std::string jsonErrors;
    Json::Value value;
    std::istringstream s(buffer_);

    if (!Json::parseFromStream(builder, s, &value, &jsonErrors)) {
        throwException(("Failed to parse JSON: "s + jsonErrors).c_str());
    }

    item_ = readJson(value);
}

SWorldTimeRow WorldTime::readJson(Json::Value jsonValue) {
    SWorldTimeRow result;
    result.filled = true;

    result.abbreviation = jsonValue["abbreviation"].asString();
    result.datetime = jsonValue["datetime"].asString();
    result.dst_from = jsonValue["dst_from"].asString();
    result.dst_until = jsonValue["dst_until"].asString();
    result.timezone = jsonValue["timezone"].asString();
    result.utc_datetime = jsonValue["utc_datetime"].asString();
    result.utc_offset = jsonValue["utc_offset"].asString();

    result.day_of_week = jsonValue["day_of_week"].asInt();
    result.day_of_year = jsonValue["day_of_year"].asInt();
    result.dst_offset = jsonValue["dst_offset"].asInt();
    result.raw_offset = jsonValue["raw_offset"].asInt();
    result.unixtime = jsonValue["unixtime"].asInt();
    result.week_number = jsonValue["week_number"].asInt();

    result.dst = jsonValue["dst"].asBool();

    return result;
}

size_t WorldTime::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void WorldTime::throwException(const char* error) {
    curl_global_cleanup();
    throw std::logic_error(error);
}

