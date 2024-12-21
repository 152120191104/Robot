#include "FestoRobotAPI.h"
#include "Map.h"
#include "LidarSensor.h"
#include "Point.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

void testMapWithLidar() {
    // Webots API'si üzerinden robot ile bağlantı kur
    FestoRobotAPI* api = new FestoRobotAPI();
    api->connect(); // Robotla bağlantıyı başlat

    // Harita boyutları ve hücre boyutu
    int gridX = 20; // X yönünde hücre sayısı
    int gridY = 20; // Y yönünde hücre sayısı
    double gridSize = 0.5; // Her hücrenin boyutu (metre)

    // Map nesnesini oluştur
    Map map(gridX, gridY, gridSize);

    // Robotu bir miktar ileri hareket ettir
    api->move(FORWARD);
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 2 saniye bekle
    api->stop(); // Robotu durdur

    // Robotun konumunu al
    double x, y, theta;
    api->getXYTh(x, y, theta); // Robotun konum bilgilerini alıyoruz.

    // Lidar sensörünü kullanarak haritayı güncelle
    LidarSensor lidar(api->getLidarRangeNumber()); // Lidar sensör sayısını al
    lidar.update(); // Lidar verilerini güncelle

    // Lidar verilerini kullanarak haritayı güncelle
    for (int i = 0; i < lidar.getRangeNumber(); ++i) {
        double distance = lidar.getRange(i);
        double angle = lidar.getAngle(i);

        // Robotun dünya koordinatları
        double robotX = x;
        double robotY = y;

        // Lidar verilerini dünya koordinatlarına dönüştür
        double xWorld = robotX + distance * cos(theta + angle);
        double yWorld = robotY + distance * sin(theta + angle);

        // Harita hücrelerine dönüştür
        int gridX = static_cast<int>(floor(xWorld / gridSize));
        int gridY = static_cast<int>(floor(yWorld / gridSize));

        // Haritaya engel ekle
        if (gridX >= 0 && gridX < map.getNumberX() && gridY >= 0 && gridY < map.getNumberY()) {
            map.setGrid(gridX, gridY, 1); // Engel var
        }
    }

    // Haritayı yazdır
    std::cout << "Harita:\n";
    map.showMap();

    // Bağlantıyı sonlandır
    api->disconnect();
    delete api; // Bellek sızıntısını önlemek için api nesnesini sil
}

int main() {
    FestoRobotAPI* robotino;
    robotino = new FestoRobotAPI();
    robotino->connect();
    testMapWithLidar();
    robotino->disconnect();
    delete robotino;
    // Test fonksiyonunu çağır
    return 0;
}