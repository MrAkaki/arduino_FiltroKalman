#ifndef VEC4_T
#define VEC4_T

template <class T>
class Vec4{

public:
  T v[4];

  Vec4(){}

  Vec4(T x, T y=0,T z=0,T w=0){
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 3;
  }
  Vec4(const Vec4<T>& o){
    for(uint8_t i=0;i<4;++i){
      this->v[i] = o.v[i];
    }
  }

  bool operator==(const Vec4& o){
    bool r = true;
    for(uint8_t i = 0;i<4;++i){
      if(this->v[i] != o.v[i]){
        r = false;
      }
    }
    return r;
  }

  bool operator!=(const Vec4& o){
    return !(*this == o);
  }

  T& operator[](int index){
    return v[index];
  }

  const T& operator[](int index) const{
    return v[index];
  }
};


#endif
