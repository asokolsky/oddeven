/**
 * Cache is limited in size
 * access is defined as a call to either put or get
 * when item is put, if the chache is full, the LRU element is popped out.
 */
class LruCache<K, V> {
  shared_ptr<V> put(shared_ptr<K> key shared_ptr<V> value);
  
  shared_ptr<V> get(shared_ptr<K> key);
  
  shared_ptr<V> remove(shared_ptr<K> key);
}

//
// failed attempt to implement it....
//

class HashQueue<T, sz> 
{
  /** Queue APIs */
  push(T el);
  T pop();
  bool isFull();
  // T peek();

  /** Hashtable APIs */
  void put(K key, V value);
  V get(K key);


private:
  class Element {
    K _key;
    V _value;
  };
    
  class HashTableElement : public Element 
  {
    
  };

  Vector <HashTableElement> _hash;
  

  class QueElement : public Element
  {
    QueueElement *_next;
    QueueElement *_prev;
  };
  
  QueueElement *_first;
  QueueElement *_last;
  
};


