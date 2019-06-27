//  Created by Patrick Wilke on 13.12.18.


#ifndef Utilities_h
#define Utilities_h

#include <iostream>

namespace PW {
    
    template <typename T>
    void Swap(T& first, T& second) {
    
        T temporary=std::move(first);
    
        first=std::move(second);
        second=std::move(temporary);
    
    }
    ///////////////////////////////////////////////////////////////////////
    template<typename Iterator>
    void PrintAll(Iterator start, Iterator end){
        std::cout<<"********************\n";
        for (Iterator x=start;x!=end;++x) {
            std::cout<<*x<<"\n";
        }
        std::cout<<"********************\n";
    }
    ///////////////////////////////////////////////////////////////////////
    template<typename Container>
    void PrintContainer(Container container){
        std::cout<<"********************\n";
        for (const auto& x: container) {
            std::cout<<x<<"\n";
        }
        std::cout<<"********************\n";
    }
    ///////////////////////////////////////////////////////////////////////
}
#endif /* Utilities_h */
