// chatgpt_api.hpp
#pragma once
#include <string>

class ChatGPTClient {
public:
    ChatGPTClient(const std::string& apiKey);
    std::string sendMessage(const std::string& userMessage);

private:
    std::string apiKey;
};
