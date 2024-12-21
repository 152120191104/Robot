#include "Mapper.h"
#include "LidarSensor.h"
#include "RobotControler.h"
#include "FestoRobotAPI.h"
#include <iostream>
#include <cassert>

void testMapper() {
    // FestoRobotAPI nesnesini oluştur
    FestoRobotAPI* api = new FestoRobotAPI();
    RobotControler controller(api);

    // Robotu bağla
    assert(controller.connectRobot() == true);
    std::cout << "Robot başarıyla bağlandı.\n";

    // Lidar sensörünü oluştur
    const int lidarRangeNumber = 10; // Lidar sensöründeki mesafe sayısı
    LidarSensor lidar(lidarRangeNumber);

    // Mapper nesnesini oluştur
    Mapper mapper(10, 10, 1.0, &controller); // 10x10 grid, 1.0 boyut

    // Lidar verilerini güncelle
    lidar.update(); // Rastgele mesafe verileri oluştur
    std::cout << "Lidar verileri güncellendi.\n";

    // Haritayı güncelle
    mapper.updateMap();
    std::cout << "Harita güncellendi.\n";

    // Haritayı göster
    std::cout << "Harita:\n";
    mapper.showMap();

    // Haritayı dosyaya kaydet
    if (mapper.recordMap()) {
        std::cout << "Harita başarıyla dosyaya kaydedildi.\n";
    }
    else {
        std::cout << "Harita kaydedilirken hata oluştu!\n";
    }

    // Robotu bağlantısını kes
    assert(controller.disconnectRobot() == true);
    std::cout << "Robot bağlantısı kesildi.\n";

    delete api; // Bellek sızıntısını önlemek için api nesnesini sil
}

int main() {
    FestoRobotAPI* robotino;
    robotino = new FestoRobotAPI();
    robotino->connect();
    testMapper(); // Test fonksiyonunu çağır
    robotino->disconnect();
    delete robotino;
    
    return 0;
}