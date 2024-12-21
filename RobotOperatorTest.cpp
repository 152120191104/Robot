#include "RobotOperator.h"
#include "Encryption.h"
#include <iostream>
#include <cassert>
#include "FestoRobotAPI.h"
void testRobotOperator() {
    // Test verileri
    const std::string name = "Ali";
    const std::string surname = "Veli";
    const int rawAccessCode = 4567; // 4 basamaklı kod

    // RobotOperator nesnesi oluşturuluyor
    RobotOperator operator1(name, surname, rawAccessCode);

    // Operatör bilgilerini kontrol et
    std::cout << "Operatör Bilgileri:\n";
    operator1.print();

    // Kod şifreleme ve çözme işlemlerini test et
    int encryptedCode = Encryption::encrypt(rawAccessCode);
    int decryptedCode = Encryption::decrypt(encryptedCode);

    assert(decryptedCode == rawAccessCode);
    std::cout << "Şifreleme ve çözme başarıyla test edildi.\n";

    // Erişim kodu doğrulama testi
    bool accessCheck = operator1.checkAccessCode(rawAccessCode);
    assert(accessCheck);
    std::cout << "Erişim kodu doğrulama başarıyla test edildi.\n";

    // Erişim durumu kontrolü (Yetkili mi?)
    operator1.print(); // "Erişim Durumu: Yetkili" bekleniyor

    // Hatalı kod testi
    accessCheck = operator1.checkAccessCode(3412); // 4 basamaklı hatalı kod
    assert(!accessCheck);
    std::cout << "Hatalı kod doğrulama başarıyla test edildi.\n";

    // Erişim durumu kontrolü (Yetkisiz mi?)
    operator1.print(); // "Erişim Durumu: Yetkisiz" bekleniyor
}

int main() {

    try {
        testRobotOperator();
        std::cout << "Tüm testler başarıyla geçti!\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Bir hata oluştu: " << e.what() << "\n";
    }
    catch (...) {
        std::cerr << "Bilinmeyen bir hata oluştu!\n";
    }

    return 0;
}
