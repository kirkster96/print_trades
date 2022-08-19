#include "parse.h"
#include <string>

bool parseFile(std::istream& in, std::vector<Trade>& trades)
{
    unsigned short plen,numUpdates,updateLen;
    char type;
    char *symbol;
    unsigned short size;
    unsigned long long price;
    double val;
    char buf[100];
    unsigned short temp;
    Trade thisTrade;

    in.get(buf[0]);
    in.get(buf[1]);
    plen = buf[0] | buf[1] << 8;
    //::std::cout << "Packet length " << plen;

    in.get(buf[0]);
    in.get(buf[1]);
    numUpdates = buf[0] | buf[1] << 8;
    //::std::cout << " Numer of market updates:  " << numUpdates << "\n";


    while (in) {
        in.read(buf, 100);

        if (in)
        {
            for (unsigned i = 0; i < 100; i++)
            {
                
                if (buf[i] == 'T')
                {
                    symbol = new char[6];
                    symbol[0] = buf[i + 1];
                    if (int(symbol[0]) >= 65 && int(symbol[0]) <= 90 )
                    {
                        symbol[1] = buf[i + 2];
                        symbol[2] = buf[i + 3];
                        symbol[3] = buf[i + 4];
                        symbol[4] = buf[i + 5];
                        symbol[5] = 0;
                        updateLen = buf[i - 2] | buf[i - 1] << 8;

                        size = (unsigned char)buf[i + 7] | (unsigned char)buf[i + 6] << 8;
                        size = size * 100;
                        temp = buf[i + 14];
                        price = (unsigned char)buf[i + 15] | (unsigned char)buf[i + 14] << 8 | (unsigned char)buf[i + 13] << 16 | (unsigned char)buf[i + 12] << 24 | (unsigned char)buf[i + 11] << 32 | (unsigned char)buf[i + 10] << 40 | (unsigned char)buf[i + 9] << 48 | (unsigned char)buf[i + 8] << 56;
                        val = (double)price / 10000;
                        //std::cout << "type: " << buf[i] << " symbol: " << symbol << " Trade Size : " << size << " Trade price : " << val << std::endl;
                        if (val < 300000.0)
                        {
                            thisTrade.symbol = symbol;
                            thisTrade.size = size;
                            thisTrade.price = val;
                        }
                        

                        trades.push_back(thisTrade);
                        i += 15;
                    }
                }
            }
        }

    }

    return true;
}
