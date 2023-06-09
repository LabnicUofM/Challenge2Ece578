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

  void ReturnBeverage(std::string& _return, const int64_t BeverageType) override;
};

// Constructor
GetBeverageServiceHandler::GetBeverageServiceHandler() {



}

// Remote Procedure "PlaceOrder"

void GetBeverageServiceHandler::ReturnBeverage(std::string& _return, const int64_t BeverageType) {
    std::string HotBeverage[3] = {"Cappuccino", "Latte", "Espresso"};
    std::string ColdBeverage[3] = {"Lemonade", "Ice Tea", "Soda"} ;

    // Your implementation goes here
    printf("ReturnBeverage\n");

    _return = BeverageType == 0 ? HotBeverage[rand()%3] : ColdBeverage[rand()%3];

}

} // namespace vending_machine


#endif //VENDING_MACHINE_MICROSERVICES_GETBEVERAGEHANDLER_H

