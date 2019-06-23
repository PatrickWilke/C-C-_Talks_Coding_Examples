//  Created by Patrick Wilke on 02.06.18.
//

#ifndef n_dimensional_container_h
#define n_dimensional_container_h

#include <array>
#include <iostream>
#include <type_traits>
#include <string>

template<typename data_type,int head,int...tail>
struct ContainerArray {
    typedef std::array<typename ContainerArray<data_type,tail...>::type,head> type;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename data_type,int head>
struct ContainerArray<data_type,head> {
    typedef std::array<data_type,head> type;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<int head, int...tail>
struct TemplateProduct{
    const static int value=head*TemplateProduct<tail...>::value;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<int head>
struct TemplateProduct<head>{
    const static int value=head;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename data_type,int first_size ,int...other_dimensions>
class nD_array {

    
public:

    typedef data_type type;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    nD_array(){
        Fill(data_type());
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    nD_array(data_type value){
        Fill(value);
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    constexpr int size(){
        return TemplateProduct<first_size,other_dimensions...>::value;
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    constexpr int dimensionality(){
        return 1+sizeof...(other_dimensions);
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<int layer>
    constexpr int size_of_layer(){
        if constexpr(layer<sizeof...(other_dimensions)+1) {
            return GetLayerSize<layer>(inner_array_);
        }
        else{
            std::cout<<"Layer does not exist!";
            exit(EXIT_FAILURE);
            return -1;
        }
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    friend std::ostream& operator<<(std::ostream& os,nD_array& input){
        return input.write_to_stream(os, input.inner_array_);
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    data_type* data(){
        return (data_type*)(&inner_array_);
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    typename ContainerArray<data_type,other_dimensions...>::type& operator[](int index){
        return inner_array_[index];
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void Fill(data_type parameter_value){
        RecursiveArraySetAllElements(inner_array_, parameter_value);
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
private:
    
    template <int layer,class T, size_t size>
    constexpr int GetLayerSize(std::array<T, size>& array) {
        if constexpr(0<layer) {
            return GetLayerSize<layer-1>(array[0]);
        }
        else{
            return array.size();
        }
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, size_t size>
    void RecursiveArraySetAllElements(std::array<T, size>& array,data_type parameter_value) {
        if constexpr(std::is_same<T, data_type>::value){
            for (int i=0; i<size; ++i) {
                array[i]=parameter_value;
            }
        }
        else{
            for (int i=0; i<size; ++i) {
                RecursiveArraySetAllElements(array[i],parameter_value);
            }
        }
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <class T, size_t size>
    std::ostream& write_to_stream (std::ostream& os,std::array<T, size>& array){
        if constexpr(std::is_same<data_type, T>::value){
            for (int i=0; i<size; ++i) {
                os<<array[i]<<"\t";
            }
            os<<"\n";
        }
        else{
            for (int i=0; i<size; ++i) {
                write_to_stream(os,array[i]);
            }
            os<<"***************************\n";
        }
        return os;
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    typename ContainerArray<data_type,first_size ,other_dimensions...>::type inner_array_;
    
};

//Example
//nD_array<double, 3, 4> test_array(5.0);
//test_array[1][2]=0.0;
//std::cout<<test_array;

#endif /* n_dimensional_container_h */
