// chatgpt_api.cpp
#include "ChatGPT_API.hpp"
#include <third_party/curl/curl.h>
#include "External/json/json.hpp"
#include <iostream>

using json = nlohmann::json;

ChatGPTClient::ChatGPTClient(const std::string& apiKey) : apiKey(apiKey) {}

// Helper to collect API response
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

std::string ChatGPTClient::sendMessage(const std::string& userMessage) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        json j;
        j["model"] = "gpt-3.5-turbo";
        j["messages"] = {
            { {"role", "user"}, {"content", userMessage} }
        };

        std::string requestData = j.dump();

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        std::string authHeader = "Authorization: Bearer " + apiKey;
        headers = curl_slist_append(headers, authHeader.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "cURL failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    try {
        auto jsonResponse = json::parse(response);
        return jsonResponse["choices"][0]["message"]["content"];
    } catch (...) {
        return "[Error] Failed to parse ChatGPT response.";
    }
}
