#ifndef NO_HPP
#define NO_HPP

template <typename T>
class No {
private:
	T valor;
	No<T>* proximoNo;

public:
	No(const T& valor, No<T>* proximoNo = nullptr)
		: valor(valor), proximoNo(proximoNo) {}

	T& getValor() {
		return valor;
	}

	const T& getValor() const {
		return valor;
	}

	No<T>* getProximo() {
		return proximoNo;
	}

	const No<T>* getProximo() const {
		return proximoNo;
	}

	void setProximo(No<T>* novoProximo) {
		proximoNo = novoProximo;
	}
};

#endif
