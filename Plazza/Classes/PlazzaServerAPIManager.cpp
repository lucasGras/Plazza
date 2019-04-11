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
                    (*kitchen->getData())->availableCooks,
                    (*kitchen->getData())->stockDoe,
                    (*kitchen->getData())->stockTomato,
                    (*kitchen->getData())->stockGruyere,
                    (*kitchen->getData())->stockSteak,
                    (*kitchen->getData())->stockMushrooms,
                    (*kitchen->getData())->stockHam,
                    (*kitchen->getData())->stockEggPlant,
                    (*kitchen->getData())->stockGoatCheese,
                    (*kitchen->getData())->stockChiefLove,
            };

            runningKitchensData.push_back(paquet);
        }
        return runningKitchensData;
    }

    /**
     * @brief Make http request (GET) using curl to update the current running kitchens json file
     * @param json
     * @return
     */
    static int makeHttpRequest(const std::string &url)
    {
        CURL *curl;
        CURLcode res;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            return res;
        }
        return -1;
    }

    /**
     * @brief Core && needed function for the nlohmann json serializer.
     * It needs to be in the same namespace as the paquet_t to work.
     * @param j
     * @param value
     */
    void to_json(nlohmann::json &j, const paquet_t &value) {
        j["id"] = value.id;
        j["available_cooks"] = value.available_cooks;
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

    void PlazzaServerAPIManager::refreshReception(const std::vector<plaz::AKitchen *> runningKitchens) {
        auto runningKitchensData = getRunningKitchensData(runningKitchens);
        nlohmann::json json = runningKitchensData;

        //std::cout << json << std::endl;
        makeHttpRequest("http://51.77.211.78:" + std::to_string(PLAZZA_SERVER_PORT) + "/refresh?json=" + json.dump());
    }
}