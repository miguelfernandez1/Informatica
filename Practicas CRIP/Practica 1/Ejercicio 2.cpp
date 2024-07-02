#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <random>
#include <cmath>
#include <chrono>


class BigNumber{
    private:
        std::vector<int> digits; //Lista de dígitos
        bool isNegative;        //Indica si el número es negativo
        uint64_t base;

    public:
        //Constructor por defecto
        BigNumber() : isNegative(false){
            digits.push_back(0);
            base = uint64_t(pow(2, 64));
        }


        // Constructor que toma un vector de dígitos y un booleano que indica el signo
        BigNumber(const std::vector<int>& digits, bool isNegative) : digits(digits), isNegative(isNegative) {}


        //Constructor que recibe un entero inicial
        BigNumber(int num){
            isNegative = (num < 0);
            num = std::abs(num);

            while(num > 0){
                digits.push_back(num % base);
                num /= base;      //Base 2^64
            }

            if(digits.empty()){
                digits.push_back(0);    // Si el número es cero, al menos debe tener un dígito
            }
        }

        //Función para imprimir el número
        void printNumber() const {
            if(isNegative){
                std::cout << "-";
            }

            for(auto it = digits.rbegin(); it != digits.rend(); ++it){
                std::cout << *it;
            }

            std::cout << std::endl;
        }

        void addDigits(int digit){
            digits.push_back(digit);
        }


        //Función para cambiar el signo del número
        BigNumber negate() const {
            BigNumber result = *this;   //Creamos una copia del número actual
            result.isNegative = !result.isNegative; //Invertimos el signo
            return result;
        }


        //Función auxiliar para realizar la suma de dígitos según el algoritmo
        std::pair<int, int> sumDigits(int a, int b, int gamma) const{
            int c = a + b + gamma;
            int gamma_star = 0;

            if(c >= base){
                c -= base;
                gamma_star = 1;
            }

            return std::make_pair(c, gamma_star);
        }

        //Función para sumar dos números
        BigNumber add(const BigNumber& other) const{
            BigNumber result;
            int carry = 0;

            size_t maxSize = std::max(digits.size(), other.digits.size());

            for(size_t i = 0; i < maxSize || carry; ++i){
                int digitA = (i < digits.size()) ? digits[i] : 0;
                int digitB = (i < other.digits.size()) ? other.digits[i] : 0;

                auto sumResult = sumDigits(digitA, digitB, carry);

                result.digits.push_back(sumResult.first);
                carry = sumResult.second;
            }

            result.isNegative = isNegative; //Conservamos el signo del primer número
            return result;
        }


        //Función para restar dos números
        BigNumber operator-(BigNumber& other){
            BigNumber result;
            int borrow = 0;

            size_t maxSize = std::max(digits.size(), other.digits.size());

            for(size_t i = 0; i < maxSize; ++i){
                int digitA = (i < digits.size()) ? digits[i] : 0;
                int digitB = (i < other.digits.size()) ? other.digits[i] : 0;

                if(digitA >= digitB + borrow){
                    result.digits.push_back(digitA - digitB - borrow);
                    borrow = 0;
                }
                else{
                    result.digits.push_back(base + digitA - digitB - borrow);
                    borrow = 1;
                }
            }

            //Eliminamos ceros no significativos
            while(result.digits.size() > 1 && result.digits.back() == 0){
                result.digits.pop_back();
            }

            //Determinarmos el signo del resultado
            if(borrow == 1){
                result.isNegative = true;
            }
            else{
                result.isNegative = isNegative;     //Conservamos el signo del primer número
            }

            return result;
        }



        //Función auxiliar para multiplicar dos dígitos (Algoritmo 5)
        static std::pair<int, int> multiplyDigits(int a, int b, int gamma) {
            int c = a * b + gamma;
            int gamma_star = 0;
            uint64_t base = pow(2, 64);
            while(c >= base){ //Mayor o igual que la base
                c -= base;
                gamma_star++;
            }

            return std::make_pair(c, gamma_star);
        }


        //Algoritmo de multiplicación escolar
        BigNumber operator*(const BigNumber & other) const{
            BigNumber result;
            BigNumber tempResult;

            for(size_t j = 0; j < other.digits.size(); ++j){
                int gamma = 0;
                tempResult.digits.clear();

                for(size_t i = 0; i < digits.size(); ++i){
                    auto product = multiplyDigits(digits[i], other.digits[i], gamma);
                    tempResult.digits.push_back(product.first);
                    gamma = product.second;
                }

                while(gamma > 0){
                    tempResult.digits.push_back(gamma % base);
                    gamma /= base;
                }

                //Agregar ceros al final según el lugar que ocupa en la multiplicación
                for(size_t k = 0; k < j; ++k){
                    tempResult.digits.insert(tempResult.digits.begin(), 0);
                }

                result = result.add(tempResult);
            }

            //Determinamos el signo del resultado
            if(isNegative != other.isNegative){
                result.isNegative = true;
            }
            else{
                result.isNegative = false;
            }

            return result;
        }

        //Función para comparar los valores absolutos de dos números
        int compareAbsoluteValues(const BigNumber& other) const{
            if(digits.size() > other.digits.size()){
                return 1;
            }
            else if(digits.size() < other.digits.size()){
                return -1;
            }

            for(int i = digits.size() - 1; i >= 0; --i){
                if(digits[i] > other.digits[i]){
                    return 1;
                }
                else if(digits[i] < other.digits[i]){
                    return -1;
                }
            }

            return 0;
        }


        //Función algoritmo escolar de la división
        std::pair<BigNumber, BigNumber> divide(const BigNumber & divisor) const{
            if(divisor.digits.size() == 1 && divisor.digits[0] == 0){
                throw std::invalid_argument("División por cero");
            }

            BigNumber quotient;
            BigNumber remainder = *this;    //Copia del dividendo

            //Preparamos el divisor para compararlo con el dividendo 
            BigNumber tempDivisor;
            for(size_t i = 0; i < remainder.digits.size(); ++i){
                tempDivisor.digits.push_back(0);
            }
            tempDivisor.digits.push_back(divisor.digits[0]);

            //Mientras el dividendo sea igual o mayor que el divisor
            while(remainder.compareAbsoluteValues(tempDivisor) != -1){
                quotient.digits.push_back(0);   //Incrementamos el cociente

                //Realizamos la resta para obtener el nuevo dividendo
                remainder = remainder - tempDivisor;

                //Preparamos el nuevo divisor
                tempDivisor.digits.pop_back();
                tempDivisor.digits.insert(tempDivisor.digits.begin(), 0);
            }


            //Determinar el signo del cociente y del resto
            quotient.isNegative = (isNegative != divisor.isNegative);
            remainder.isNegative = isNegative;

            return std::make_pair(quotient, remainder);
        }

 // Función auxiliar para sumar dos números grandes
    static BigNumber auxKaratsuba(const BigNumber& num1, const BigNumber& num2) {
        std::vector<int> result;
        int carry = 0;
        int i = num1.digits.size() - 1;
        int j = num2.digits.size() - 1;
        uint64_t base = uint64_t(pow(2, 64));

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) {
                sum += num1.digits[i];
                i--;
            }
            if (j >= 0) {
                sum += num2.digits[j];
                j--;
            }

            result.push_back(sum % base);
            carry = sum / base;
        }

        std::reverse(result.begin(), result.end());
        return BigNumber(result, false);
    }


    // Función auxiliar para restar dos números grandes
    static BigNumber subtractKaratsuba(const BigNumber& num1, const BigNumber& num2) {
        std::vector<int> result;
        int borrow = 0;
        int i = num1.digits.size() - 1;
        int j = num2.digits.size() - 1;
        uint64_t base = uint64_t(pow(2, 64));

        while (i >= 0) {
            int diff = num1.digits[i] - borrow;
            if (j >= 0) {
                diff -= num2.digits[j];
                j--;
            }
            if (diff < 0) {
                diff += base;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.push_back(diff);
            i--;
        }

        std::reverse(result.begin(), result.end());
        return BigNumber(result, false);
    }


        //Función para multiplicar usando karatsuba
        static BigNumber karatsuba(const BigNumber& num1, const BigNumber& num2){
            size_t m = std::max(num1.digits.size(), num2.digits.size());

            //Caso base
            if(m == 1){
                auto product = multiplyDigits(num1.digits[0], num2.digits[0], 0);
                std::vector<int> digits = {product.first};
                if(product.second > 0){
                    digits.push_back(product.second);
                }

                return BigNumber(digits, false);
            }

            size_t halfSize = m / 2;

            //Dividir los números en partes
            BigNumber a0(std::vector<int>(num1.digits.begin(), num1.digits.begin() + halfSize), false);
            BigNumber a1(std::vector<int>(num1.digits.begin() + halfSize, num1.digits.end()), false);
            BigNumber b0(std::vector<int>(num2.digits.begin(), num2.digits.begin() + halfSize), false);
            BigNumber b1(std::vector<int>(num2.digits.begin() + halfSize, num2.digits.end()), false);

            //Calcular partes recursivamente
            BigNumber c0 = karatsuba(a0, b0);
            BigNumber c2 = karatsuba(a1, b1);
            BigNumber c1 = karatsuba(auxKaratsuba(a0, a1), auxKaratsuba(b0, b1));
            c1 = subtractKaratsuba(c1, c0);
            c2 = subtractKaratsuba(c1, c2);

            //Ajustar el tamaño del resultado
            std::vector<int> zeros(2 * halfSize, 0);
            c0.digits.insert(c0.digits.end(), zeros.begin(), zeros.end());
            c1.digits.insert(c1.digits.end(), zeros.begin(), zeros.begin() + halfSize);

            //Sumar los resultados
            BigNumber result = auxKaratsuba(c0, c1);
            result = auxKaratsuba(result, c2);

            return result;

        }


    //Función de división. Algoritmo 8
    static std::pair<BigNumber, BigNumber> division(const BigNumber &a, const BigNumber &b){
        uint64_t base = uint64_t(pow(2, 64));
        //Verificamos si el divisor tiene solo un dígito
        if(b.digits.size() == 1){
            int divisor = b.digits[0];
            BigNumber quotient;
            std::vector<int> remainder = {0}; //Inicializamos a cero

            for(int j = a.digits.size() - 1; j >= 0; --j){
                int dividend = remainder[0] * base + a.digits[j]; //Parte entera de la división
                int qj = dividend / divisor;    //Cociente
                quotient.digits.push_back(qj);
                int rj = dividend % divisor;    //Residuo
                remainder[0] = rj;
            }

            std::reverse(quotient.digits.begin(), quotient.digits.end());
            return std::make_pair(quotient, BigNumber(remainder, false));
        }

        //Normalización
        int d = base / (b.digits.back() + 1);
        BigNumber normalizedA = multiplySingleDigit(a, d);
        BigNumber normalizedB = multiplySingleDigit(b, d);

        //Dividimos
        int n = normalizedA.digits.size();
        int m = normalizedB.digits.size();
        std::vector<int> quotientDigits(n - m + 1, 0);  //Inicializamos los dígitos del cociente

        for(int j = n; j >= m; --j){
            int qHat;
            if(normalizedA.digits[j] == normalizedB.digits[m - 1]){
                qHat = 0;
            }
            else{
                int dividend = normalizedA.digits[j] * base + normalizedA.digits[j - 1];
                qHat = dividend / normalizedB.digits[j - 1];
                if(qHat * normalizedB.digits[m - 2] > 
                    (dividend - qHat * normalizedB.digits[m - 1]) * base + normalizedA.digits[j - 2]){
                        qHat--;
                    }
            }

            //Restamos qHat * b de a
            BigNumber product = multiplySingleDigit(normalizedB, qHat);
            while(compare(normalizedA, j - m + 1, product)){
                qHat--;
                product = subtractAux(normalizedA, j - m + 1, product);
            }

            //Actualizamos el cociente
            quotientDigits[j - m] = qHat;
            normalizedA = subtractAux(normalizedA, j - m + 1, product);
        }

        std::reverse(quotientDigits.begin(), quotientDigits.end());
        auto divisionResult = BigNumber::division(normalizedA, BigNumber(d));
        BigNumber quotient = divisionResult.first;
        BigNumber remainder = divisionResult.second;

        return std::make_pair(quotient, remainder);
    }


    //Función auxiliar para muliplicar un número grande por un solo dígito
    static BigNumber multiplySingleDigit(const BigNumber& num, int digit){
        int carry = 0;
        std::vector<int> result;
        uint64_t base = uint64_t(pow(2, 64));

        for(int i = num.digits.size() - 1; i >= 0; --i){
            int product = num.digits[i] * digit + carry;
            result.push_back(product % base);
            carry = product / base;
        }

        if(carry > 0){
            result.push_back(carry);
        }

        std::reverse(result.begin(), result.end());
        return BigNumber(result, false);
    }

    //Función auxiliar para comparar dos números grandes desde una posición j
    static bool compare(const BigNumber& a, int j, BigNumber& b){
        if(a.digits.size() - j < b.digits.size()){
            return true;
        }
        if(a.digits.size() - j > b.digits.size()){
            return false;
        }

        for(int i = 0; i < b.digits.size(); ++i){
            if(a.digits[i + j] < b.digits[i]){
                return true;
            }
            if(a.digits[i + j] > b.digits[i]){
                return false;
            }
        }

        return false;
    }


    // Función auxiliar para restar un número grande de otro desde la posición j
    static BigNumber subtractAux(const BigNumber& a, int j, const BigNumber& b) {
        int borrow = 0;
        std::vector<int> result;
        uint64_t base = uint64_t(pow(2, 64));

        for (int i = a.digits.size() - 1; i >= j; --i) {
            int diff = a.digits[i] - borrow;
            if (j + b.digits.size() - 1 - i >= 0) {
                diff -= b.digits[j + b.digits.size() - 1 - i];
            }
            if (diff < 0) {
                diff += base;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.push_back(diff);
        }

        std::reverse(result.begin(), result.end());
        return BigNumber(result, false);
    }


    //Función para obtener el máximo común divisor utilizando el algoritmo de Euclides
    static int euclideanAlgorithm(int a, int b){
        while(b != 0){
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    //Constante estática para representar el número 0
    static BigNumber zero(){
        return BigNumber({0}, false);
    }


    //Sobrecarga del operador de comparación ==
    bool operator==(const BigNumber& other) const{
        return digits == other.digits && isNegative == other.isNegative;
    }


    //Sobrecarga del operador de comparación !=
    bool operator!=(const BigNumber& other) const{
        return !(*this == other);
    }

    //Sobrecarga del operador de asignación
    BigNumber& operator=(const BigNumber& other){
        if(this != &other){ //Verificamos si es la misma instancia
            digits = other.digits;
            isNegative = other.isNegative;
        }

        return *this;
    }

    //Función para convertir el número BigNumber a entero
    int toInt() const{
        int result = 0;
        for(int digit : digits){
            result = result * base + digit;
        }

        return isNegative ? -result : result;
    }

    //Algoritmo Extendido de Euclides. Algoritmo 10
    static std::tuple<int, int, int> extendedEuclideanAlgorithm(BigNumber& a, BigNumber& b) {
        BigNumber m = a;
        BigNumber u0 = BigNumber({1}, false);
        BigNumber v0 = BigNumber({0}, false);
        BigNumber u1 = BigNumber({0}, false);
        BigNumber v1 = BigNumber({1}, false);

        while(b != BigNumber::zero()){
            auto divisionResult = BigNumber::division(a, b);
            BigNumber q = std::get<0>(divisionResult);
            BigNumber r = std::get<1>(divisionResult);

            a = b;
            b = r;

            BigNumber temp1 = q * u1;
            BigNumber temp2 = q * v1;
            BigNumber u = u0 - temp1;
            BigNumber v = v0 - temp2;
            u0 = u1;
            v0 = v1;
            u1 = u;
            v1 = v;
        }

        int gcd = euclideanAlgorithm(m.toInt(), a.toInt());
        int u = u0.toInt();
        int v = v0.toInt();

        return std::make_tuple(gcd, u, v);
    }


    //Sobrecarga del operador de exponenciación (^)
    BigNumber power(int exponent) const{
        BigNumber result({1}, false);
        BigNumber base = *this;

        while(exponent > 0){
            if(exponent % 2 == 1){
                result = result * base;
            }
            base = base * base;
            exponent /= 2;
        }

        return result;
    }

    // Función para comparar dos vectores de dígitos
    int compareVectors(const std::vector<int>& a, const std::vector<int>& b) const {
        if (a.size() != b.size()) {
            return a.size() - b.size();
        }
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] != b[i]) {
                return a[i] - b[i];
            }
        }
        return 0;
    }


    // Función para restar dos vectores de dígitos
    std::vector<int> subtractVectors(const std::vector<int>& a, const std::vector<int>& b) const {
        std::vector<int> result;
        int borrow = 0;

        for (int i = a.size() - 1; i >= 0; --i) {
            int diff = a[i] - (i < b.size() ? b[i] : 0) - borrow;
            if (diff < 0) {
                diff += base;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.insert(result.begin(), diff);
        }

        // Eliminar ceros no significativos del resultado
        auto it = result.begin();
        while (it != result.end() && *it == 0) {
            ++it;
        }
        if (it == result.end()) {
            return std::vector<int>({0});  // El resultado es 0
        } else {
            return std::vector<int>(it, result.end());
        }
    }

    //Sobrecarga del operador de módulo (%)
    BigNumber operator%(const BigNumber& other) const{
        std::vector<int> dividend = digits;
        std::vector<int> divisor = other.digits;
        
        std::vector<int> result;
        std::vector<int> temp;

        for(int i = 0; i < dividend.size(); ++i){
            temp.push_back(dividend[i]);
            int quotient = 0;

            while(compareVectors(temp, divisor) >= 0){
                temp = subtractVectors(temp, divisor);
                quotient++;
            }

            result.push_back(quotient);
        }

        //Eliminamos ceros no significativos
        auto it = result.begin();
        while(it != result.end() && *it == 0){
            ++it;
        }
        if(it == result.end()){
            return BigNumber({0}, false);   //El resultado es 0
        }
        else{
            return BigNumber(std::vector<int>(it, result.end()), isNegative);
        }
    }

    //Sobrecarga operador >
    bool operator>(int other) const {
        return *this > BigNumber(other);
    }

    bool operator>(const BigNumber& other) const {
        // Comparamos la longitud de los vectores de dígitos
        if (digits.size() != other.digits.size()) {
            return digits.size() > other.digits.size();
        }
        
        // Si la longitud es igual, comparamos los dígitos desde el más significativo
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i]) {
                return digits[i] > other.digits[i];
            }
        }
        
        // Si todos los dígitos son iguales, consideramos los números iguales
        return false;
    }


    static BigNumber power_mod(BigNumber& N, BigNumber&a, BigNumber& b){
        BigNumber result(1); // Inicializamos el resultado como 1
        
        // Convertimos b a un número positivo
        BigNumber exp = b;
        if (exp.isNegative) {
            exp.isNegative = false;
            exp = N - exp;
        }
        
        // Convertimos a a BigNumber módulo N para evitar desbordamientos
        BigNumber base = a % N;

        // Realizamos la exponenciación modular rápida
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % N;
            }
            base = (base * base) % N;
            exp = exp / 2;
        }
        
        return result;

       
    }

    static BigNumber gcd(const BigNumber& a, const BigNumber& b){
        BigNumber num1 = a;
        BigNumber num2 = b;
        while(num2 != BigNumber({0}, false)){
            BigNumber temp = num2;
            num2 = num1 % num2;
            num1 = temp;
        }

        return num1;
    }



    // Sobrecarga del operador de mayor o igual que (>=)
    bool operator>=(const BigNumber& other) const {
        // Verificar si ambos números tienen el mismo signo
        if (isNegative != other.isNegative) {
            return isNegative ? false : true; // Si uno es negativo y otro positivo, el positivo es mayor
        }

        // Verificar si ambos números tienen la misma longitud
        if (digits.size() != other.digits.size()) {
            return (digits.size() > other.digits.size()) ? true : false;
        }

        // Comparar los dígitos uno a uno, empezando por los más significativos
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i]) {
                return (digits[i] > other.digits[i]) ? true : false;
            }
        }

        // Los números son iguales
        return true;
    }

    // Sobrecarga del operador de división (/)
    BigNumber operator/(const BigNumber& other) const {
        BigNumber dividend = *this;
        BigNumber divisor = other;
        BigNumber quotient;

        if (divisor == BigNumber({0}, false)) {
            // Manejo de división por cero
            throw std::runtime_error("División por cero");
        }

        // Implementación del algoritmo de división
        BigNumber remainder;
        while (dividend >= divisor) {
            remainder = dividend;
            int digit = 0;
            while (remainder >= divisor * BigNumber({digit + 1}, false)) {
                digit++;
            }
            quotient.digits.push_back(digit);
            BigNumber temp = divisor * BigNumber({digit}, false);
            dividend = dividend - temp;
        }

        // Eliminar ceros no significativos del cociente
        while (!quotient.digits.empty() && quotient.digits.back() == 0) {
            quotient.digits.pop_back();
        }

        if (quotient.digits.empty()) {
            // Si el cociente es 0, asegúrate de establecer su signo correctamente
            quotient.isNegative = false;
            return BigNumber({0}, false);
        } else {
            quotient.isNegative = isNegative != other.isNegative;
            return quotient;
        }
    }


    
    BigNumber getRandomNumber(const BigNumber& min, const BigNumber& max){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distrib(min.toInt(), max.toInt());
        return BigNumber({distrib(gen)}, false);
    }

    //Test de Miller-Rabin Algoritmo 17
    bool strongPseudoprime(BigNumber& n, BigNumber& a){
        if(BigNumber::gcd(a, n) != BigNumber({1}, false)){
            return false;
        }
        BigNumber temp = BigNumber({1}, false);
        BigNumber nMinusOne = n - temp;
        BigNumber t = nMinusOne;
        int s;
        while(t % BigNumber({2}, false) == BigNumber({0}, false)){
            t = t / BigNumber({2}, false);
            s++;
        }

        BigNumber b = a.power(t.toInt()) % n;
        if(b == BigNumber({1}, false) || b == nMinusOne){
            return true;
        }

        for(int r = 1; r < s; ++r){
            b = (b * b) % n;
            if(b == nMinusOne){
                return true;
            }
        }
        return false;
    }

    bool millerRabinTest(BigNumber& n, int k){
        BigNumber temp = BigNumber({1}, false);
        for(int i = 0; i < k; ++i){
            BigNumber a = getRandomNumber(BigNumber({2}, false), n - temp);
            if(!strongPseudoprime(n, a)){
                return false;
            }
        }
        return true;
    }



    //Función para las comprobaciones en el main
    BigNumber generateRandomNumber(int m){
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> distribution(0, 9);  //Números aleatorios entre 0 y 9

        std::vector<int> digits;
        digits.reserve(m);

        //Generar m dígitos aleatorios
        for(int i = 0; i < m; ++i){
            int digit = distribution(gen);
            digits.push_back(digit);
        }

        digits[0] = distribution(gen) + 1;  //Sumamos 1 para evitar el 0

        return BigNumber(digits, false);
        
    }

    //Función auxiliar para medir el tiempo de ejecución de un algoritmo
    //Cambiar los parámetros de la función según los parámetros de los algoritmos a medir
    static double measureExecutionTime(BigNumber& num1, BigNumber& num2 /*, BigNumber& num3*/){
        auto startTime = std::chrono::steady_clock::now();

        //BigNumber sum = num1.add(num2);
        //BigNumber result = num1 * num2;
        //auto result = BigNumber::division(num1, num2);
        //BigNumber product = BigNumber::karatsuba(num1, num2);
        //auto result = BigNumber::extendedEuclideanAlgorithm(num1, num2);        //Descomentar para probar algoritmos y medir tiempos
        //BigNumber result = BigNumber::power_mod(num1, num2, num3);



        auto endTime = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> duration = endTime - startTime;

        return duration.count();
    }

};



int main(){

    for(int n = 100; n <= 1000000; n *= 2){
        int repeticiones = 10;

        std::vector<double> executionTimes;

        BigNumber input1, input2, input3;

        for(int i = 0; i < repeticiones; ++i){
            //Generamos entradas aleatorias
            input1.generateRandomNumber(n);
            input2.generateRandomNumber(n);
            //input3.generateRandomNumber(m);

            //Medimos el tiempo de ejecución y guardamos el resultado
            double executionTime = BigNumber::measureExecutionTime(input1, input2);
            executionTimes.push_back(executionTime);
        }

        //Calculamos la media
        double mean = std::accumulate(executionTimes.begin(), executionTimes.end(), 0.0);

        //Calculamos la desviación estándar
        double sumSquareDiffs = 0.0;
        for(double time : executionTimes){
            sumSquareDiffs += (time - mean) * (time - mean);
        }

        double variance = sumSquareDiffs / executionTimes.size();
        double standardDeviation = std::sqrt(variance);

        //Filtramos las mediciones atípicas
        std::vector<double> filteredExecutionTimes;
        for(double time : executionTimes){
            if(time >= mean - 2 * standardDeviation && time <= mean + 2 * standardDeviation){
                filteredExecutionTimes.push_back(time);
            }
        }

        //Calculamos la media final
        double finalMean = std::accumulate(filteredExecutionTimes.begin(), filteredExecutionTimes.end(), 0.0) / filteredExecutionTimes.size();

        //Imprimimos resultados
        std::cout << n << "," << finalMean << "," << standardDeviation << std::endl;
        
    }


    //Comprobación de resultados
    //Descomentar para probar


    //Suma de dos números
    //BigNumber num1({123456789}, false);
    //BigNumber num2({987654321}, false);

    //BigNumber sum = num1.add(num2);

    //sum.printNumber();

    //Multiplicación de dos enteros
    //BigNumber result = num1 * num2;
    //result.printNumber();

    //División
    //BigNumber num1({1, 2, 3}, false);
    //BigNumber num2({4, 5}, false);

    /*BigNumber num1, num2;
    num1.generateRandomNumber(m);
    num2.generateRandomNumber(m);

    auto result = BigNumber::division(num1, num2);

    std::cout << "Quotient: ";
    result.first.printNumber();
    std::cout << "Remainder: ";
    result.second.printNumber();*/

    //Karatsuba
    /*BigNumber num1({123}, false);
    BigNumber num2({456}, false);

    BigNumber product = BigNumber::karatsuba(num1, num2);

    product.printNumber();*/

    //Algoritmo Extendido de Euclides
    /*BigNumber num1({10}, false);
    BigNumber num2({4}, false);

    auto result = BigNumber::extendedEuclideanAlgorithm(num1, num2);

    std::cout << "GCD: " << std::get<0>(result) << std::endl;
    std::cout << "u : " << std::get<1>(result) << std::endl;
    std::cout << "v : " << std::get<2>(result) << std::endl;*/


    //Exponenciación modular rápida

    /*BigNumber N({10}, false);  // Modulus
    BigNumber a({2}, false);   // Base
    BigNumber b({3}, false);   // Exponent

    BigNumber result = BigNumber::power_mod(N, a, b);
    std::cout << "Resultado: ";
    result.printNumber(); // Imprimir el resultado*/


    return 0;
}