#pragma once
#include <string>
#include <json/json.h>
#include <curl/curl.h>

struct SWorldTimeRow {
	std::string abbreviation;
	std::string datetime;
	std::string dst_from;
	std::string dst_until;
	std::string timezone;
	std::string utc_datetime;
	std::string utc_offset;

	int day_of_week;
	int day_of_year;
	int dst_offset;
	int raw_offset;
	int unixtime;
	int week_number;

	bool dst;
	bool filled = false;
};

class WorldTime {
private:
	CURL* curl_;
	SWorldTimeRow item_;
	std::string buffer_;
public:
	explicit WorldTime(std::string timeZone = "Etc/UTC");

	void setTimeZone(std::string timeZone);

	SWorldTimeRow getWorldTimeRow();
	std::string getBuffer();

	void clear();
	~WorldTime();

private:
	void getCurlResult();
	static SWorldTimeRow readJson(Json::Value jsonValue);
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
	static void throwException(const char *error);
};