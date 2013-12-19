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



#endif // LIBR_H
