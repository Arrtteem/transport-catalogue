#include "stat_reader.h"
#include "transport_catalogue.h"
#include <unordered_set>
#include <sstream>
#include <utility>
#include <algorithm>

void PrintBusInfo(const Bus* bus, std::ostream& output) {
    size_t stops_count = Calculation::GetStopsCount(bus);
    size_t unique_stops_count = Calculation::GetUniqueStopsCount(bus);
    double route_length = Calculation::GetRouteLength(bus);

    output << "Bus " << bus->name_ << ": "
        << std::to_string(stops_count) << " stops on route, "
        << std::to_string(unique_stops_count) << " unique stops, "
        << std::to_string(route_length) << " route length" << std::endl;
}

void PrintStopInfo(const Stop* stop, const TransportCatalogue& transport_catalogue, std::ostream& output) //Не совсем понял, что нужно сделать
{
    std::string stop_name = stop->name_;

    std::vector<std::string> buses_for_stop = transport_catalogue.GetBusesByStop(stop_name);
    if (buses_for_stop.empty())
    {
        output << "Stop " << stop_name << ": no buses" << std::endl;
    }
    else
    {
        std::sort(buses_for_stop.begin(), buses_for_stop.end());
        output << "Stop " << stop_name << ": buses ";
        for (const std::string& bus : buses_for_stop)
        {
            output << bus << " ";
        }
        output << std::endl;
    }
}

void ParseAndPrintStat(const TransportCatalogue& transport_catalogue, std::string_view request, std::ostream& output) {
    using namespace std::literals;

    if (request.starts_with("Stop ")) 
    {
        std::string stop_name = std::string(request.substr(5));

        Stop* stop = transport_catalogue.GetStopByName(stop_name);
        if (stop == nullptr) 
        {
            output << "Stop "s << stop_name << ": not found"s << std::endl;
        }
        else {

            PrintStopInfo(stop, output);
        }
    }
    else {
        std::string bus_name = std::string(request.substr(4));
        Bus* find_bus = transport_catalogue.GetBusByName(bus_name);
        if (find_bus == nullptr) {
            output << "Bus "s << bus_name << ": not found"s << std::endl;
        }
        else {
            PrintBusInfo(find_bus, output);
        }
    }
}
