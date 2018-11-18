#include <iostream>
#include "TIM_SICK/lidar/include/TIM561.h"

using namespace std;

int main(int argc, char** argv){
    std::cout << argv[1] << "\n";
    std::cout << "Connection..." << std::endl;
    TIM561 tim;

    if (argv[1] == "tim") {

        if( tim.connect("192.168.1.93",2112) ) {
            std::cout << "Connected" << std::endl;

            if( tim.start() )
            {
                std::cout << "Started" << std::endl;
                auto tmp = tim.getDataPoints();

                while(true)
                {
                    usleep(70000);
                    tim.update();

                    for( int i = 0 ; i< TIM561::NBR_DATA ; i+=5 )
                    {
                        if( tmp[i].distance < 500 )
                            printf("|");
                        else
                            printf(".");
                    }
                    printf("\n");
                }
            }
        }
        tim.close();

    }

    return 0;
}