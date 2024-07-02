#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>

class IntegerArbitrario {
    private:
        std::vector<uint64_t> digits;

    public:

        IntegerArbitrario(const std::vector<uint64_t>& digits) : digits(digits) {
        // Eliminar ceros no significativos al principio
            this->digits = digits;
            while (!this->digits.empty() && this->digits.back() == 0) {
                this->digits.pop_back();
            }
    }

        //Destructor para liberar memoria no es necesario si usamos std::vector

        //Función para imprimir el número
        void printNumber() const{
            for(auto it = digits.rbegin(); it != digits.rend(); ++it){
                std::cout << *it;
            }
            std::cout << std::endl;
        }


        // Método para convertir a cadena en formato hexadecimal
        std::string toHexString() const{
            std::stringstream ss;

            if(digits.size() == 1 && digits[0] == 0){
                //El número es cero
                ss << "0x0";
            }
            else{
                //Determinamos el signo
                bool isNegative = (digits.size() > 0 && digits.back() >= 0x8000000000000000);

                //Mostrar el prefijo 0x o -0x
                ss << ((isNegative) ? "-0x" : "0x");

                //Mostrar los digitos en formato hexadecimal
                for(auto it = digits.rbegin(); it != digits.rend(); ++it){
                    ss << std::setfill('0') << std::setw(16) << std::hex << *it;
                }
            }

            return ss.str();

        }

        //Método para convertir desde cadena en formato hexadecimal
        static IntegerArbitrario fromHexString(const std::string& hexString){
            size_t startIndex = (hexString[0] == '-') ? 3 : 2; // Considerar el signo y el prefijo 0x

            std::vector<uint64_t> resultDigits;
            for(size_t i = hexString.size() - 1; i >= startIndex; --i){
                uint64_t digit;
                std::stringstream ss;
                ss << std::hex << hexString[i];
                ss >> digit;
                resultDigits.push_back(digit);
            }

            //Eliminamos ceros no significativos al principio
            while(resultDigits.size() > 1 && resultDigits.back() == 0){
                resultDigits.pop_back();
            }

            return IntegerArbitrario(resultDigits);
        }
        
};