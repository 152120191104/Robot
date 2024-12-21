#include "LidarSensor.h"
#include "FestoRobotAPI.h"
#include <iostream>
#include <cassert>
#include <cstdlib> // Rastgele veri oluşturmak için
#include <ctime>   // Zamanı almak için

void testLidarSensor() {
    // Lidar sensör sayısını belirleyin
    const int rangeNumber = 10; // Örnek olarak 10 sensör
    LidarSensor lidar(rangeNumber);

    // Rastgele mesafe verileri oluştur
    srand(static_cast<unsigned int>(time(0))); // Rastgele sayı üreteci için tohum
    for (int i = 0; i < rangeNumber; ++i) {
        double randomDistance = static_cast<double>(rand() % 1000) / 100.0; // 0.0 ile 10.0 arasında rastgele mesafe
        lidar.update(); // Lidar verilerini güncelle
    }

    // Test: getRange(i) fonksiyonu
    for (int i = 0; i < rangeNumber; ++i) {
        double range = lidar.getRange(i);
        std::cout << "Lidar " << i << " mesafesi: " << range << " metre\n";
        assert(range >= 0.0); // Mesafe negatif olmamalı
    }

    // Test: getMin(index) fonksiyonu
    int minIndex;
    double minDistance = lidar.getMin(minIndex);
    std::cout << "En kısa mesafe: " << minDistance << " metre, indeks: " << minIndex << "\n";
    assert(minIndex >= 0 && minIndex < rangeNumber); // Geçerli indeks kontrolü

    // Test: getMax(index) fonksiyonu
    int maxIndex;
    double maxDistance = lidar.getMax(maxIndex);
    std::cout << "En uzak mesafe: " << maxDistance << " metre, indeks: " << maxIndex << "\n";
    assert(maxIndex >= 0 && maxIndex < rangeNumber); // Geçerli indeks kontrolü

    // Test: operator[] fonksiyonu
    for (int i = 0; i < rangeNumber; ++i) {
        double rangeUsingOperator = lidar[i];
        assert(rangeUsingOperator == lidar.getRange(i)); // İki yöntemle elde edilen mesafeler eşit olmalı
    }

    // Test: getAngle(i) fonksiyonu
    for (int i = 0; i < rangeNumber; ++i) {
        double angle = lidar.getAngle(i);
        std::cout << "Lidar " << i << " açısı: " << angle << " derece\n";
        assert(angle >= 0.0 && angle < 360.0); // Açı 0 ile 360 arasında olmalı
    }

    std::cout << "Tüm LidarSensor testleri başarıyla tamamlandı.\n";
}

int main() {
    testLidarSensor(); // Test fonksiyonunu çağır
    return 0;
}