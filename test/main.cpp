
#include <iostream>
#include <string>

using namespace std;

template<typename T> class Fifo
{
private:
    T* array_;
    int size_;
    int capacity_;

public:
    Fifo(int capacity = 10):
        array_(new T[static_cast<unsigned int>(capacity)]),
        size_(0),
        capacity_(capacity)
    {
    }

    //TODO destructor

    void resize(int newcapacity)
    {
        T* new_array = new T[newcapacity];
        int copysize;
        newcapacity > size_ ? copysize = size_ : copysize = newcapacity;
        for(int i=0; i<copysize; i++) new_array[i] = array_[i];
        delete[] array_;
        array_ = new_array;
        capacity_ = newcapacity;
    }

    void push(T val)
    {
        //resize if necessary
        if( (size_+1) > capacity_) resize(capacity_+10);

        //copy forward
        for(int i = size_; i>0; i--)
        {
            array_[i] = array_[i-1];
        }

        //push
        array_[0] = val;

        size_++;
    }

    T pop()
    {
        if(!size_) throw exception("empty");
        T val = array_[size_-1];
        size_--;
        return val;
    }

    int size(){ return size_; }

};

int main(/*int argc, char *argv[]*/)
{
    try {
        Fifo<int> fifo;

        for(int i=0; i<20; i++) fifo.push(i);

        while(fifo.size()) cout << fifo.pop() << endl;


        Fifo<string> strfifo;
        string str;
        for(int i=0; i<20; i++)
        {
            str += static_cast<char>('a'+i);
            strfifo.push(str);
        }

        while(strfifo.size())
        {
            string tmp = strfifo.pop();
            cout << tmp << endl;
        }

    } catch (exception e) {
        cout << e.what();
    }
}
