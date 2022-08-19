#pragma once
#include "trade.h"
#include <iostream>


bool parseFile(std::istream& in,
    std::vector<Trade >& trades);
