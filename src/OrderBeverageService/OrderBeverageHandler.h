#ifndef VENDING_MACHINE_MICROSERVICES_ORDERBEVERAGEHANDLER_H
#define VENDING_MACHINE_MICROSERVICES_ORDERBEVERAGEHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/OrderBeverageService.h"
#include "../../gen-cpp/WeatherService.h"
#include "../../gen-cpp/GetBeverageService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace vending_machine{

  class OrderBeverageServiceHandler : public OrderBeverageServiceIf {
  public:
    OrderBeverageServiceHandler(
        ClientPool<ThriftClient<WeatherServiceClient>> *, 
        ClientPool<ThriftClient<GetBeverageServiceClient>> *) ;
    ~OrderBeverageServiceHandler() override=default;

    void PlaceOrder(std::string& _return, const int64_t city) override;
  private:
    ClientPool<ThriftClient<WeatherServiceClient>> *_weather_client_pool;
    ClientPool<ThriftClient<GetBeverageServiceClient>> *_getbeverage_client_pool;
  };

  // Constructor
  OrderBeverageServiceHandler::OrderBeverageServiceHandler( ClientPool<ThriftClient<WeatherServiceClient>> *weather_client_pool, 
                                                           ClientPool<ThriftClient<GetBeverageServiceClient>> *getbeverage_client_pool)
  {

      // Storing the clientpool
      _weather_client_pool = weather_client_pool;
      _getbeverage_client_pool = getbeverage_client_pool;
  }

  // Remote Procedure "PlaceOrder"
  void OrderBeverageServiceHandler::PlaceOrder(std::string& _return, const int64_t city){
      // Your implementation goes here
      printf("PlaceOrder\n");
      _return = "after anything";
      return BeverageType::type::COLD;
   
      // 1. get the weather service client pool
      auto weather_client_wrapper = _weather_client_pool->Pop();
      if (!weather_client_wrapper) {
        ServiceException se;
        se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
        se.message = "Failed to connect to weather-service";
        throw se;
      }
      auto weather_client = weather_client_wrapper->GetClient();

      // by default get cold
      WeatherType::type weatherType = WeatherType::type::COLD;

      // 2. call the remote procedure : GetWeather
      try {
        weatherType = weather_client->GetWeather(city);
      } 
      catch (...) {
        _weather_client_pool->Push(weather_client_wrapper);
        LOG(error) << "Failed to send call GetWeather to weather-client";
        throw;
      }
      int64_t intWeatherType = weatherType == WeatherType::type::COLD ? 1 : 0;
      _weather_client_pool->Push(weather_client_wrapper);
      _return = "after weather";

      auto getbeverage_client_wrapper = _getbeverage_client_pool->Pop();
      if (!getbeverage_client_wrapper) {
        ServiceException se;
        se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
        se.message = "Failed to connect to getbeverage-service";
        throw se;
      }
      auto getbeverage_client = getbeverage_client_wrapper->GetClient();

      //3. get beverage name
      std::string beverageName ="test";
      try {
        //getbeverage_client->ReturnBeverage(*beverageName,intWeatherType);
      } 
      catch (...) {
        _getbeverage_client_pool->Push(getbeverage_client_wrapper);
        LOG(error) << "Failed to send call ReturnBeverage to getbeverage-client";
        throw;
      }
      _getbeverage_client_pool->Push(getbeverage_client_wrapper);    
      

      _return = beverageName;
  }

} // namespace vending_machine


#endif //VENDING_MACHINE_MICROSERVICES_ORDERBEVERAGEHANDLER_H

