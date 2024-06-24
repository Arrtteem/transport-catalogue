#pragma once
#include <deque>
#include <string>
#include <unordered_map>
#include <vector>

#include "geo.h"

struct Stop {
    std::string name_;
    Coordinates coordinates;
};

enum class RouteType {
    Ring, // кольцевой маршрут
    ThereAndback // маршрут туда-обратно
};

struct Bus {
    std::string name_;
    std::vector<Stop*> stops;
    RouteType type;
};

class TransportCatalogue {
public:
    void AddStop(Stop stop);
    void AddBus(Bus bus);
    Stop* GetStopByName(std::string_view stop_name) const;
    Bus* GetBusByName(std::string_view bus_name) const;
    std::vector<std::string> GetBusesByStop(std::string_view stop_name) const;



private:
    std::deque<Stop> stops_;
    std::deque<Bus> buses_;
    std::unordered_map<std::string_view, Stop*> stopname_to_stop_;
    std::unordered_map<std::string_view, Bus*> busname_to_bus_;
};

class Calculation {
public:
    static size_t GetStopsCount(const Bus* bus);
    static size_t GetUniqueStopsCount(const Bus* bus);
    static double GetRouteLength(const Bus* bus);
};
