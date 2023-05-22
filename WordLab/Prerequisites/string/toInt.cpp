template <typename T> int toInt(const T& object) {
	int i = 0;
	std::stringstream ss;
	ss << object;
	ss >> i;
	return i;
}

template <typename T> bool toBool(const T& object) {
    bool flag = false;
    std::stringstream ss;
    ss << object;
    ss >> flag;
    return flag;
}

template <typename T> char toChar(const T& object) {
    char c = 0;
    std::stringstream ss;
    ss << object;
    ss >> c;
    return c;
}

template <typename T> short toShort(const T& object) {
    short sh = 0;
    std::stringstream ss;
    ss << object;
    ss >> sh;
    return sh;
}

template <typename T> long toLong(const T& object) {
    long i = 0;
    std::stringstream ss;
    ss << object;
    ss >> i;
    return i;
}

template <typename T> float toFloat(const T& object) {
    float i = 0;
    std::stringstream ss;
    ss << object;
    ss >> i;
    return i;
}

template <typename T> double toDouble(const T& object) {
    double i = 0;
    std::stringstream ss;
    ss << object;
    ss >> i;
    return i;
}
