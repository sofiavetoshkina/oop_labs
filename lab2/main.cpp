#include <iostream>
#include <stdexcept>
#include "Three.h"

int main(){

    Three t1 = Three();
    t1.print(std::cout) << std::endl;

    Three t2 = Three(12);
    t2.print(std::cout) << std::endl;

    try{
        Three t3 = Three{'1', '1', '1'};
        t3.print(std::cout) << std::endl;
    } catch (const std::exception &ex){
        std::cerr << "exception: " << ex.what() << std::endl;
    }
        
    try{
        Three t4 = Three("20");
        t4.print(std::cout) << std::endl;
    } catch (const std::exception &ex){
        std::cerr << "exception: " << ex.what() << std::endl;
    }

    Three t5(t2);
    t5.print(std::cout) << std::endl;

    Three t6(std::move(t5));
    t6.print(std::cout) << std::endl;

    Three t_1 = Three{'1', '1', '1'};
    Three t_2 = Three("20");
    Three t7 = t_1.add(t_2);
    t7.print(std::cout) << std::endl;

    try{
        Three t8 = t_1.subtract(t_2);
        t8.print(std::cout) << std::endl;

        Three t9 = t_2.subtract(t_1);
        t9.print(std::cout) << std::endl;

    } catch (const std::exception &ex){
        std::cerr << "exception: " << ex.what() << std::endl;
    }

    return 0;
}