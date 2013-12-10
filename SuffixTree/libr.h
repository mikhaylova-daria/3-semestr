#ifndef LIBR_H
#define LIBR_H

template <typename V>
bool operator < (std::weak_ptr<V> ptr, std::weak_ptr<V> other_ptr){
    return (ptr.lock())->name < (other_ptr.lock())->name;
}

template <typename V>
bool operator == (std::weak_ptr<V> ptr, std::weak_ptr<V> other_ptr){
    return ptr.lock().get() == other_ptr.lock().get();
}

template <typename V>
bool operator == (std::shared_ptr<V> ptr, std::weak_ptr<V> other_ptr){
    return ptr.get() == other_ptr.lock().get();
}

template <typename V>
bool operator == (std::weak_ptr<V> ptr, std::shared_ptr<V> other_ptr){
    return ptr.lock().get() == other_ptr.get();
}

template <typename V>
bool operator == (std::shared_ptr<V> ptr, std::shared_ptr<V> other_ptr){
    return ptr.get() == other_ptr.get();
}


template <typename V>
bool operator != (std::shared_ptr<V> ptr, std::shared_ptr<V> other_ptr){
    return !(ptr.get() == other_ptr.get());
}

template <typename V>
bool operator != (std::weak_ptr<V> ptr, std::weak_ptr<V> other_ptr){
    return !(ptr.lock().get() == other_ptr.lock().get());
}

template <typename V>
bool operator != (std::shared_ptr<V> ptr, std::weak_ptr<V> other_ptr){
    return !(ptr.get() == other_ptr.lock().get());
}

template <typename V>
bool operator != (std::weak_ptr<V> ptr, std::shared_ptr<V> other_ptr){
    return !(ptr.lock().get() == other_ptr.get());
}


namespace my {

class exception: public std::exception {
private:
    std::string _what;
public:
    exception(const char * _what) throw() {
           this->_what = _what;
    }
    const char* what() const throw(){
        return _what.c_str();
    }
    ~exception() throw(){}
};
}
#endif // LIBR_H

