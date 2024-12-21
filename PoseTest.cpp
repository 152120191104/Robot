#include "FestoRobotAPI.h"
#include "Pose.h"
#include <iostream>
#include <thread>
#include <chrono>

void testPoseWithWebots() {
    // Webots API'si üzerinden robot ile bağlantı kur
    FestoRobotAPI* api = new FestoRobotAPI();
    api->connect(); // Robotla bağlantıyı başlat

    // Robotu bir miktar ileri hareket ettir
    api->move(FORWARD);
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 2 saniye bekle
    api->stop(); // Robotu durdur

    // Robotun konum bilgilerini al
    double x, y, theta;
    api->getXYTh(x, y, theta); // Robotun konum bilgilerini alıyoruz.

    // Pose nesnesini oluştur
    Pose pose(x, y, theta);

    // Konumu ekrana yazdır
    std::cout << "Robotun Mevcut Konumu:\n";
    std::cout << "X: " << pose.getX() << " meters\n";
    std::cout << "Y: " << pose.getY() << " meters\n";
    std::cout << "Theta: " << pose.getTheta() << " degrees\n";

    // Bağlantıyı sonlandır
    api->disconnect();
    delete api; // Bellek sızıntısını önlemek için api nesnesini sil
}

int main() {
    testPoseWithWebots(); // Test fonksiyonunu çağır
    return 0;
}