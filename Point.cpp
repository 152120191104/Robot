#include "FestoRobotAPI.h"
#include "Point.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath> // nan kontrolü için

void testObjectDetectionWithSensors() {
    // Webots API'si üzerinden robot ile bağlantı kur
    FestoRobotAPI* api = new FestoRobotAPI();
    api->connect(); // Robotla bağlantıyı başlat

    // Robotu bir miktar ileri hareket ettir
    api->move(FORWARD);
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 2 saniye bekle
    api->stop(); // Robotu durdur

    bool objectDetected = false; // Nesne tespit durumu

    // Sensör verilerini güncelle
    for (int i = 0; i < 9; ++i) {
        double range = api->getIRRange(i); // Tüm IR sensörlerinden mesafe al
        std::cout << "IR Sensör " << i << " Mesafesi: " << range << " meters" << std::endl;

        // Mesafe geçerli mi ve belirli bir eşik değerinin altındaysa, nesne var demektir
        if (!std::isnan(range) && range >= 0 && range < 0.3) { // Eşik değerini 0.3 metreye düşürdük
            objectDetected = true; // Nesne tespit edildi
            break; // Nesne tespit edildiğinde döngüden çık
        }
    }

    if (objectDetected) {
        std::cout << "Nesne tespit edildi!" << std::endl;

        // Robotun konumunu al
        double x, y, theta;
        api->getXYTh(x, y, theta); // Robotun konum bilgilerini alıyoruz.

        // Point nesnesini oluştur
        Point point(x, y);

        // Nesnenin konumunu ekrana yazdır
        std::cout << "Robotun Mevcut Konumu:\n";
        std::cout << "X: " << point.getX() << " meters\n";
        std::cout << "Y: " << point.getY() << " meters\n";
    }
    else {
        std::cout << "Nesne tespit edilmedi." << std::endl;
    }

    // Bağlantıyı sonlandır
    api->disconnect();
    delete api; // Bellek sızıntısını önlemek için api nesnesini sil
}

int main() {
    testObjectDetectionWithSensors(); // Test fonksiyonunu çağır
    return 0;
}