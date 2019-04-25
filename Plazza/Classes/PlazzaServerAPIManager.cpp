/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Created by lucasg,
*/
#include "PlazzaServerAPIManager.hpp"

namespace plaz::server {

    /**
     * @brief Get a vector of sendable packets based on current running kitchens
     * @param runningKitchens
     * @return
     */
    static std::vector<plaz::server::paquet_t> getRunningKitchensData(const std::vector<plaz::AKitchen *> runningKitchens) {
        std::vector<plaz::server::paquet_t> runningKitchensData;

        runningKitchensData.reserve(runningKitchens.size());
        for (auto &kitchen : runningKitchens) {
            plaz::server::paquet_t paquet = {
                    kitchen->getKitchenId(),
                    (*kitchen->getData())->availableSlots,
                    (*kitchen->getData())->waitingPizza,
                    (*kitchen->getData())->stockDoe,
                    (*kitchen->getData())->stockTomato,
                    (*kitchen->getData())->stockGruyere,
                    (*kitchen->getData())->stockSteak,
                    (*kitchen->getData())->stockMushrooms,
                    (*kitchen->getData())->stockHam,
                    (*kitchen->getData())->stockEggPlant,
                    (*kitchen->getData())->stockGoatCheese,
                    (*kitchen->getData())->stockChiefLove
            };

            runningKitchensData.push_back(paquet);
        }
        return runningKitchensData;
    }

    /**
     * @brief Write data curl function, used to avoid curl to display on term
     * @param buffer
     * @param size
     * @param nmemb
     * @param userp
     * @return size_t
     */
    static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
    {
        ((std::string*)userp)->append((char*)buffer, size * nmemb);
        return size * nmemb;
    }

    /**
     * @brief Make http request (GET) using curl to update the current running kitchens json file
     * @param json
     * @return
     */
    template <typename T>
    static T makeHttpRequest(const std::string &url)
    {
        CURL *curl;
        CURLcode res;
        std::string buffer;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt (curl, CURLOPT_VERBOSE, 0L);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            if constexpr (std::is_same_v<T, std::string>)
                return buffer;
            else if constexpr (std::is_same_v<T, int>)
                return res;
        }
    }

    /**
     * @brief Core && needed function for the nlohmann json serializer.
     * It needs to be in the same namespace as the paquet_t to work.
     * @param j
     * @param value
     */
    void to_json(nlohmann::json &j, const paquet_t &value) {
        j["id"] = value.id;
        j["max_cooks"] = value.max_cooks;
        j["available_cooks"] = value.available_cooks;
        j["waiting_pizza"] = value.waiting_pizza;
        j["doe"] = value.stockDoe;
        j["tomato"] = value.stockTomato;
        j["gruyere"] = value.stockGruyere;
        j["steak"] = value.stockSteak;
        j["mushrooms"] = value.stockMushrooms;
        j["ham"] = value.stockHam;
        j["eggplant"] = value.stockEggPlant;
        j["goatcheese"] = value.stockGoatCheese;
        j["chieflove"] = value.stockChiefLove;
    }

    void PlazzaServerAPIManager::refreshReception(std::vector<plaz::AKitchen *> runningKitchens) {
        auto runningKitchensData = getRunningKitchensData(runningKitchens);
        nlohmann::json json = runningKitchensData;

        if (makeHttpRequest<int>("http://51.77.211.78:" + std::to_string(PLAZZA_SERVER_PORT) + "/refresh/shared?json=" + json.dump()) != 0)
            std::cerr << "Error making http request" << std::endl;
    }

    std::vector<plaz::Order> PlazzaServerAPIManager::getOrders() {
        auto buffer = makeHttpRequest<std::string>("http://51.77.211.78:" + std::to_string(PLAZZA_SERVER_PORT) + "/status/orders");

        return plaz::Order::getOrdersFromJson(buffer);
    }

    void PlazzaServerAPIManager::runApi(plaz::Reception *reception, std::string flag) {
        if (!flag.empty() && flag != "--no-api" && flag != "--server") {
            std::cerr << "Error: invalid argument (" << flag << ")" << std::endl;
            std::exit(84);
        }
        if (flag == "--no-api")
            return;
        if (flag == "--server") {
            reception->setServerMode();
            std::thread serverThread([this, reception]() {
                while (true) {
                    reception->sendOrders(this->getOrders());
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    this->refreshReception(reception->getRunningKitchens());
                }
            });
            serverThread.detach();
        } else {
            std::thread apiThread([this, reception]() {
                while (true) {
                    this->refreshReception(reception->getRunningKitchens());
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            });
            apiThread.detach();
        }
    }
}