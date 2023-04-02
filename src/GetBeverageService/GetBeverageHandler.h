#ifndef VENDING_MACHINE_MICROSERVICES_GETBEVERAGEHANDLER_H
#define VENDING_MACHINE_MICROSERVICES_GETBEVERAGEHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/GetBeverageService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace vending_machine{

class GetBeverageServiceHandler : public GetBeverageServiceIf {
 public:
  GetBeverageServiceHandler();
  ~GetBeverageServiceHandler() override=default;

  string ReturnBeverage(const int64_t BeverageType) override;
};

// Constructor
GetBeverageServiceHandler::GetBeverageServiceHandler() {



}

// Remote Procedure "PlaceOrder"

GetBeverageType::type GetBeverageServiceHandler::ReturnBeverage(const int64_t BeverageType) {
    int HotBeverage[3] = {"Cappuccino", "Latte", "Espresso"};
    int ColdBeverage[3] = {"Lemonade", "Ice Tea", "Soda"} ;

     // Your implementation goes here
     printf("ReturnBeverage\n");
    return BeverageType == 0 ? HotBeverage[rand()%3] : ColdBeverage[rand()%3];

}

} // namespace vending_machine


#endif //VENDING_MACHINE_MICROSERVICES_GETBEVERAGEHANDLER_H

