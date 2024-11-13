template <signed B, unsigned N>
class hyperqube{
public:
    static const int volume = B * hyperqube<B, N - 1>::volume;
};

template <signed B>
class hyperqube<B, 0> {
public:
    static const int volume = 1;
};




