#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.exchangerate-api.com/v4/latest/INR");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    // Parse JSON response
    json data = json::parse(readBuffer);
    auto rates = data["rates"];

    cout << "Live Conversion Rates (Base: INR)" << endl;
    cout << "1 INR = " << rates["USD"] << " USD" << endl;
    cout << "1 INR = " << rates["AED"] << " AED" << endl;
    cout << "1 INR = " << rates["ZAR"] << " ZAR" << endl;
    cout << "1 INR = " << rates["RUB"] << " RUB" << endl;
    cout << "1 INR = " << rates["AUD"] << " AUD" << endl;

    return 0;
}
