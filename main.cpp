#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <chrono>
#include <memory>

namespace tw{
    template <typename T> void print(const T &list);

    template<typename T>
    struct Node{
        std::unique_ptr<T> _data;
        std::unique_ptr<Node> next;
        Node* prev;

        Node(): _data(){
            _data = std::make_unique<T>();
        }

    };


    template<typename T>
    class list{

        std::unique_ptr<Node<T>> _head;
        

        public:
        list(){
            _head = std::make_unique<Node<T>>();
            _head->next = nullptr;
            _head->prev = nullptr;
        }


        void push_front(T value)
        {
            auto tmp = std::make_unique<Node<T>>();
            *(tmp->_data) = value;
            tmp->next = std::move(_head->next);
            _head->next = std::move(tmp);

        }

        T pop_front()
        {
            
            if(_head->next->next.get()){
                auto retValue = *(_head->next->_data);
                _head->next = std::move(_head->next->next);
                return retValue;
            }else{
                throw std::out_of_range("empty list");
            }

            
        }

        void push_back(T value)
        {
            Node<T> *tmp = _head.get();

            while(tmp->next.get()){
                tmp = tmp->next.get();
            }

            auto new_node = std::make_unique<Node<T>>();
            *(new_node->_data) = value;
            new_node->next = nullptr;
            tmp->next = std::move(new_node);

        }


        T pop_back()
        {
            if(_head->next == nullptr)
            {
                throw std::out_of_range("empty list");
            }

            Node<T> *tmp = _head.get();

            while(tmp->next->next.get()){
                tmp = tmp->next.get();
            }            
            auto retValue = *(tmp->_data);
            tmp->next = nullptr;
            return retValue;
        }

        void show_all() const
        {
            Node<T> *tmp = _head->next.get();

            while(tmp ){
                std::cout << *(tmp->_data) << ", ";
                tmp = tmp->next.get();
            }
            std::cout << "\n";
        }
        

    };
}



int main(int argc, char** argv){
    std::vector<std::string> arguments(argv, argv+argc);


    tw::list<int> lista;
    lista.push_front(13);
    lista.push_front(14);
    lista.show_all();
    // auto elem = lista.pop_front();
    // // lista.push_back(99);
    // lista.show_all();
    // std::cout << "elem " << elem << std::endl;

    lista.push_back(99);
    lista.show_all();
    lista.pop_back();
    
    
    lista.show_all();

}


namespace tw{
    template <typename T>
    void print(const T &list)
    {
        auto start = std::begin(list);
        auto end = std::end(list);
        if(start != end) { 
            std::cout << "[";
            std::for_each(start, --end, [](auto element){
                std::cout << element << ", ";
            });

            std::cout << *end << "]" <<std::endl;
        }else{
            std::cout <<"[]" <<std::endl;
        }
    }



}


